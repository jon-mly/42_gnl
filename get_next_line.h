/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 11:01:03 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/05/08 14:40:53 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define BUFF_SIZE 1
# define EOL '\n'
# define EOF (-1)

typedef struct	s_buffer
{
	char				*str;
	int					fd;
	struct s_buffer		*next;
}				t_buffer;

int				get_next_line(const int fd, char **line);

#endif
