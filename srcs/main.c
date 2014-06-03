#include "my.h"

char	is_curl(const char const *str)
{
	const char const	*curl = "curl";
	size_t				count;

	count = 0;
	while (str[count] == curl[count] && curl[count] && str[count])
		count++;
	if (str[count] == 0 && curl[count] == 0)
		return (1);
	return (0);
}

void	freetab(char **str)
{
	size_t	count;

	count = -1;
	while (str[++count])
		free(str[count]);
	free(str);
}

char	*concat_slash(char *path, char *name)
{
	size_t	len;
	char	*new;
	size_t	count;

	len = strlen(path) + strlen(name);
	if (!(new = malloc(sizeof(*new) * (len + 2))))
		return (0);
	len = -1;
	count = -1;
	while (*(path + ++count))
		*(new + ++len) = *(path + count);
	*(new + ++len) = '/';
	count = -1;
	while (*(name + ++count))
		*(new + ++len) = *(name + count);
	*(new + ++len) = 0;
	return (new);
}

char	*locate_curl(void)
{
	char			*ret;
	char			**path;
	char			*tmp;
	size_t			count;
	DIR				*dir;
	struct dirent	*name;

	printf("Locating curl...\n");
	count = -1;
	if (!(tmp = getenv("PATH")))
		return (0);
	if (!(path = ft_strsplit(tmp, ':')))
		return (0);
	while (path[++count])
	{
		if (!(dir = opendir(path[count])))
		{
			fprintf(stderr, "Fail to load %s continue.\n", path[count]);
			continue;
		}
		while ((name = readdir(dir)))
		{
			if (is_curl(name->d_name))
			{
				if (!(ret = malloc(sizeof(*ret) * (strlen(name->d_name) + strlen(path[count] + 2)))))
					return (0);
				if (!(ret = concat_slash(path[count], name->d_name)))
					return (0);
				printf("Curl found at %s\n", ret);
				freetab(path);
				return (ret);
			}
		}
	}
	freetab(path);
	fprintf(stderr, "Curl not found exit !\n");
	return (0);
}

char	find_student(const char const *name, const char const *src)
{
	const char const	*url = "https://dashboard.42.fr/crawler/pull/";
	const char const	*cmd = "curl -30kq -silent ";
	char				*tmp;
	pid_t				child;
	int					fd[2];
	char				buff[RSIZE];
	char				**arg;
	ssize_t				count;
	size_t				len;
	char				f;

	f = 0;
	printf("traking %s :\n", name);
	if (!(tmp = malloc(sizeof(*tmp) * (strlen(cmd) + strlen(url) + strlen(name) + 1))))
		return (0);
	tmp = strcpy(tmp, cmd);
	tmp = strcat(tmp, url);
	tmp = strcat(tmp, name);
	tmp = strcat(tmp, "/");
	if (!(arg = ft_strsplit(tmp, ' ')))
		return (0);
	free(tmp);
	pipe(fd);
	child = fork();
	if (child == -1)
	{
		fprintf(stderr, "Fork(); failed !\n");
		return (0);
	}
	if (child)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		count = read(fd[0], buff, RSIZE);
		if (count == -1)
		{
			fprintf(stderr, "READ ERROR OLOLOL\n");
			return (0);
		}
		buff[count] = 0;
		count = -1;
		while (buff[++count])
		{
			if (buff[count] == ':' && buff[count + 1] == ' ' && buff[count + 2] == '"' && buff[count + 3] == 'e')
			{
				count += 3;
				len = count;
				while (buff[len++] != '.')
					;
				write(1, buff + count, len - count - 1);
				write(1, "\n", 1);
				f = 1;
				bzero(buff, RSIZE);
			}
		}
		if (!(f))
			printf("User not connected or not exist !\n");
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], 1);
		execv(src, arg);
	}
	freetab(arg);
	return (1);
}

int		main(int ac, char **av)
{
	char	*src;
	size_t	count;

	printf("\x1b[1;31mRed By leone !\nSee https://github.com/42leone !\n");
	if (ac == 1)
	{
		fprintf(stderr, "Usage %s \"uid\" \"uid\" \"uid\" \"uid\"\n", av[0]);
		return (-1);
	}
	count = 0;
	if (!(src = locate_curl()))
		return (0);
	while (av[++count])
		find_student(av[count], src);
	free(src);
	printf("Thx for use !\x1b[0;00m\n");
	return (1);
}
