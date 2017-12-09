/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 11:00:57 by jmlynarc          #+#    #+#             */
/*   Updated: 2017/11/16 11:14:45 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_gnl.h"
#include <stdio.h>
/*
int		main()
{
	int		fd;
	int		res;

	res = 1;
	fd = open("test3.txt", O_RDONLY);
	if (fd < 0)
		return (-1);
	char **line = malloc(sizeof(char*));

	while ((res = get_next_line(fd, line)) == 1)
	{
		ft_putnbr(res);
		ft_putstr(": ");
		ft_putendl(*line);
	}
		ft_putnbr(res);
		ft_putstr(": ");
		ft_putendl(*line);
/ *
	get_next_line(fd, line);
	ft_putnbr(ft_strcmp(*line, "aaa"));
	get_next_line(fd, line);
	ft_putnbr(ft_strcmp(*line, "bbb"));
	get_next_line(fd, line);
	ft_putnbr(ft_strcmp(*line, "ccc"));
	get_next_line(fd, line);
	ft_putnbr(ft_strcmp(*line, "ddd"));
* /
	close(fd);
	return (0);
}
*/

// Multi fd test

int main()
{
	int fd1;
	int fd2;

	fd1 = open("test3.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);

	ft_putnbr(fd1);
	ft_putchar('\n');
	ft_putnbr(fd2);
	ft_putchar('\n');

	char **line = malloc(sizeof(char *));

	get_next_line(fd1, line);
	ft_putendl(*line);
	get_next_line(fd2, line);
	ft_putendl(*line);
	get_next_line(fd1, line);
	ft_putendl(*line);
	get_next_line(fd2, line);
	ft_putendl(*line);

}
