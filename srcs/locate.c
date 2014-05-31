#include "my.h"

char	*locate(char *user)
{
	const char	*url = "https://dashboard.42.fr/crawler/pull/";
	const char	*cmd = "curl -30kq -silent ";
	char		buff[4096];
	pid_t		child;
	char		**arg;
	char		*tmp;
	int		fd[2];

	pipe(fd);
	if (!(tmp = malloc(sizeof(*tmp) * (strlen(cmd) + strlen(url) + strlen(user) + 2))))
		return (NULL);
	tmp = strcpy(tmp, cmd);
	tmp = strcat(tmp, url);
	tmp = strcat(tmp, user);
	tmp = strcat(tmp , "/");
	char	**ret;
	char	*ip;
	if (!(arg = ft_strsplit(tmp, ' ')))
		return (NULL);
	free(tmp);
	child = fork();
	if (child)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		read(0, buff, 4096);
		char	*k = strdup(buff);
		ret = ft_strsplit(k, '"');
		ip = strdup(ret[5]);
		int	b = -1;
		while (ret[++b])
			free(ret[b]);
		free(ret);
		ip[strlen(ip) - 6] = 0;
		if (ip[0] == 'e' && ip[1] == 'r')
			return (NULL);
		return (ip);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], 1);
		execv("/usr/bin/curl", arg);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("usage %s uid.\n", av[0]);
		return (0);
	}
	char	*loc;
	if (!(loc = locate(av[1])))
	{
		printf("User not connected or wrong username !\n");
		return (0);
	}
	printf("%s\n", locate(av[1]));
	return (1);
}
