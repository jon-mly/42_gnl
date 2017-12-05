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

#include "get_next_line.h"
#include <stdio.h>

int		main()
{
	int		fd;
	int		res;

	res = 1;
	fd = open("test2.txt", O_RDONLY);
	if (fd < 0)
		return (-1);
	char **line = malloc(sizeof(char*));
	while ((res = get_next_line(fd, line)) == 1)
	{
		ft_putnbr(res);
		ft_putstr(" - ");
		ft_putendl(*line);
	}
		ft_putnbr(res);
		ft_putstr(" - ");
		ft_putendl(*line);
	close(fd);
	return (0);
}
