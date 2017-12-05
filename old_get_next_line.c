/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 11:02:07 by jmlynarc          #+#    #+#             */
/*   Updated: 2017/11/16 12:04:08 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * Append the characters read in the buffer to the chained list until '\n' or
 * EOF is found.
 * Return 1 if successful conversion, -1 if an error occured
 */
int		append_to_list(t_list **lst, char **buffer)
{
	t_list	*new_node;
	char	*p_char;
	t_list	*end;

	end = *lst;
	if (!(p_char = ft_strnew(1)))
		return (-1);
	if (end)
	{
		while (end->next)
			end = end->next;
	}
	while (**buffer != '\n' && **buffer != EOF && **buffer != '\0')
	{
		if (!(new_node = (t_list*)ft_memalloc(sizeof(t_list))))
			return (-1);
		*p_char = **buffer;
		new_node->content = ft_strdup(p_char);
		new_node->content_size = 2;
		new_node->next = NULL;
		**buffer = '\0';
		*buffer = (*buffer + 1);
		if (end)
		{
			end->next = new_node;
			end = end->next;
		}
		else
		{
			*lst = new_node;
			end = *lst;
		}
	}
	if (**buffer == '\n')
	{
		*buffer = (*buffer + 1);
		return (1);
	}
	/*
	 * if '\n' is found, should return 1
	 * else should return 0 as the char found is either '\0' either EOF
	 */
	return (**buffer == '\n');
}

/*
 * Will convert all the chars read and converted to a chained list into the
 * string pointed by dest.
 */
char	**convert_list_to_str(t_list **lst, char **dest)
{
	t_list		*current;
	char		*str;
	size_t		length;

	current = *lst;
	length = 0;
	while (current)
	{
		length++;
		current = current->next;
	}
	if (!(str = ft_strnew(length)))
		return (NULL);
	current = *lst;
	length = 0;
	while (current)
	{
		str[length++] = ((char *)(current->content))[0];
		current = current->next;
	}
	str[length] = '\0';
	*dest = str;
	return (dest);
}

int		get_next_line(const int fd, char **line)
{
	t_list		**lst;
	static char	**buffer = NULL;
	int			res;
	int			buffer_size;

	res = 0;
	if (buffer == NULL)
		buffer = (char **)ft_memalloc(sizeof(char *));
	if (fd < 0 || !(line) || !(buffer) ||
		!(*buffer = (*buffer) ? *buffer : (char *)ft_strnew(BUFF_SIZE)) ||
		!(lst = (t_list**)ft_memalloc(sizeof(t_list*))))
		return (-1);
	*lst = NULL;
	ft_putendl(*buffer);
	if (*buffer)
		res = append_to_list(lst, buffer);
	ft_putnbr(res);
	/*
	 * As a test is done in append_to_list to know if a '\n' has been found,
	 * res will contain the value of that test : 1 if true, 0 else.
	 */
//	while (res != 1 && (buffer_size = read(fd, *buffer, BUFF_SIZE)) > 0)
	buffer_size = read(fd, *buffer, BUFF_SIZE);
	if (buffer_size == 0)
		return (0);
	while (res != 1 && buffer_size > 0)
	{
		(*buffer)[buffer_size] = '\0';
		res = append_to_list(lst, buffer);
		if (res == -1)
			return (-1);
		buffer_size = read(fd, *buffer, BUFF_SIZE);
		(*buffer)[buffer_size] = '\0';
	}
	ft_putendl(*buffer);
	if (*buffer)
		res = append_to_list(lst, buffer);
	if (buffer_size == -1)
		return (-1);
	line = convert_list_to_str(lst, line);
	/*
	 * No content has been read : "line" is not completed
	 * Has reached EOF : should return 0
	 * A '\n' has been found : should return 1
	 * "res" contains the value of this test : it can be returned.
	 */
	return (1);
}
