#include "get_next_line.h"

t_buffer	*get_buffer(int fd, t_buffer **node)
{
	t_buffer	*current;

	if (!(node) && !(node = (t_buffer **)malloc(sizeof(t_buffer))))
		return (NULL);
	current = *node;
	while (current)
	{
		if (current->fd == fd)
			return (current);
	}
	if (!(current = (t_buffer *)malloc(sizeof(t_buffer))))
		return (NULL);
	current->fd = fd;
	current->str = ft_strnew(BUFF_SIZE);
	current->next = *node;
	*node = current;
	return (current);
}

int		extend_line(t_buffer *buffer, char **line)
{
	char 		*tmp;
	int 		index;

	if (ft_strchr(buffer->str, '\n'))
		index = (int)(ft_strchr(buffer->str, '\n') - buffer->str);
	else
		index = BUFF_SIZE;	// Will always be out of read size.
	buffer->str[index] = '\0';
	tmp = *line;
	*line = ft_strjoin(tmp, buffer->str);
	free(tmp);
	if (index < BUFF_SIZE)
	{
		ft_memmove(buffer->str, buffer->str + index + 1, BUFF_SIZE - index);
		//ft_memset(buffer->str + index + 1, '\0', BUFF_SIZE - index);
		return (1);
	}
	ft_memset(buffer->str, '\0', BUFF_SIZE);
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	int				res;
	static t_buffer	*list = NULL;
	t_buffer		*buffer;

	// Obtention d'un t_buffer
	buffer = get_buffer(fd, &list);
	// Vérifications de sécurité
	if (!(buffer) || fd < 0 || !(line) || BUFF_SIZE <= 0)
		return (-1);
	// Création d'un container vide pour line.
	*line = ft_strnew(0);
	// A ce moment, le buffer peut contenir des caractères
	// Il faut voir s'il n'y a pas un \n dans ce qui est lu
	if (ft_strlen(buffer->str) > 0)
	{
		if (ft_strchr(buffer->str, '\n'))
		{
			// Un \n a été trouvé : doit etendre line des chars uniquement avant
			// le \n
			// fermeture du buffer au \n
			extend_line(buffer, line);
			return (1);
		} else {
			// Le buffer contient des chars qui vont être ajouté à line.
			extend_line(buffer, line);
		}
	}
	// Lecture continue du fichier
	while ((res = read(fd, buffer->str, BUFF_SIZE)) > 0 &&
			ft_strchr(buffer->str, '\n') == NULL)
	{
		extend_line(buffer, line);
	}
	if (ft_strchr(buffer->str, '\n'))
	{
		extend_line(buffer, line);
		return (1);
		// Un \n a été trouvé : doit etendre line des chars uniquement avant
		// le \n
		// fermeture du buffer au \n
	}
	if (res == -1)
	{
		// Une erreur a été trouvée : nettoyage et renvoi de -1
		return (-1);
	}
	// Aucun char n'a été lu : fin de fichier ou erreur
	return (ft_strlen(*line) > 0 ? 1 : 0);
}
