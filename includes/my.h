#ifndef MY_H
# define MY_H

# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <dirent.h>

# define RSIZE	4096

typedef struct	s_read	t_read;

char	**ft_strsplit(char *str, char c);

#endif /*guardian*/
