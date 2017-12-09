#include "get_next_line.h"

char	*append_char(char *str, int nb, char **line)
{
	char	*dest;

	if (!(dest = ft_strnew(nb)))
		return (NULL);
	dest = ft_strncpy(dest, str, nb);
	dest[nb + 1] = '\0';
	*line = ft_strjoin(*line, dest);
	ft_strdel(&dest);
	return (*line);
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
	int			length;

	length = 0;
	while ((*buffer)[length] && (*buffer)[length] != '\n')
		length++;
	if (!(**buffer))
		return (0);
	if (length == 0)
	{
		mv_buffer(buffer, 0);
		return (1);
	}
	*line = append_char(*buffer, length, line);
	if ((int)ft_strlen(*buffer) > length || res < BUFF_SIZE)
	{
		mv_buffer(buffer, length);
		return (1);
	}
	return (0);
}

char	**get_buffer(char **buffer)
{
	if (!(buffer))
	{
		buffer = (char **)malloc(sizeof(char *));
		*buffer = ft_strnew(BUFF_SIZE);
	}
	return (buffer);
}

int		get_next_line(const int fd, char **line)
{
	int				res;
	int				i;
	static char		**buffer = NULL;

	*line = ft_strnew(0);
	buffer = get_buffer(buffer);
	if (!(buffer) || !(*buffer) || fd < 0 || !(line) || !(*line))
	{
		ft_strdel(buffer);
		return (-1);
	}
	if (**buffer == EOF)
	{
		ft_strdel(buffer);
		return (0);
	}
	if (extend_line(line, buffer, BUFF_SIZE) == 1)
		return (1);
	while ((res = read(fd, *buffer, BUFF_SIZE)) > 0)
	{
		i = res - 1;
		while (++i < BUFF_SIZE)
			(*buffer)[i] = '\0';
		if (extend_line(line, buffer, res) == 1)
			return (1);
	}
	if (res == 0 && ft_strlen(*line) > 0)
	{
		**buffer = EOF;
		return (1);
	}
	ft_strdel(buffer);
	return (res);
}
