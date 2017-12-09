#ifndef TEST_GNL
# define TEST_GNL

# include "libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_list_test
{
    int fd;
    char *ret;
    struct s_list_test *next;
} t_list_test;

int     get_next_line(int const fd, char **line);

#endif
