#include "get_next_line.h"

int		movable_char(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\n' || str[i] == EOF)
			return (i);
	}
	return (i);
}

char	*append_char(char *str, int nb)
{
	char	*dest;

	if (!(dest = ft_strnew(nb)))
		return (NULL);
	dest = ft_strncpy(dest, str, nb);
	dest[nb + 1] = '\0';
	return (dest);
}

void	mv_buffer(char **buffer, int index)
{
	int		i;
	int		length;

	length = ft_strlen((*buffer) + index + 1);
	ft_memmove(*buffer, (*buffer) + index + 1, length);
	i = length - 1;
	while ((*buffer)[++i])
		(*buffer)[i] = '\0';
}

int		extend_line(char **line, char **buffer, int res)
{
	char		*mv_char;
	int			length;

	length = movable_char(*buffer);
	if (!(**buffer))
		return (0);
//	ft_putstr("len : ");
//	ft_putnbr(length);
//	ft_putchar('\n');
	if (length == 0)
	{
		mv_buffer(buffer, 0);
		return (1);
	}
	mv_char = append_char(*buffer, length);
//	ft_putstr("mv_char : ");
//	ft_putendl(mv_char);
	*line = ft_strjoin(*line, mv_char);
	ft_strdel(&mv_char);
	if ((int)ft_strlen(*buffer) > length || res < BUFF_SIZE)
	{
		mv_buffer(buffer, length);
		return (1);
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	int				res;
	int				i;
	static char		**buffer = NULL;

	*line = ft_strnew(0);
	if (!(buffer))
	{
		buffer = (char **)malloc(sizeof(char *));
		*buffer = ft_strnew(BUFF_SIZE);
	}
	if (!(buffer) || !(*buffer) || fd < 0 || !(line) || !(*line))
		return (-1);
//	ft_putstr("BUFFER : ");
//	ft_putendl(*buffer);
	if (**buffer == EOF)
	{
		ft_strdel(buffer);
		return (0);
	}
	if (extend_line(line, buffer, BUFF_SIZE) == 1)
		return (1);
	while ((res = read(fd, *buffer, BUFF_SIZE)) != 0 && res != -1)
	{
		i = res - 1;
		while (++i < BUFF_SIZE)
			(*buffer)[i] = '\0';
//		ft_putstr("INSIDE LOOP : ");
//		ft_putendl(*buffer);
		if (extend_line(line, buffer, res) == 1)
			return (1);
	}
	if (res == 0)
		**buffer = EOF;
//	ft_strdel(buffer);
//	return (res == 0 ? 1 : -1);
	return (res);
}
