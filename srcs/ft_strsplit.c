#include <stdlib.h>

static size_t	how_tab(const char *str, char c)
{
	size_t	cn[2] = {-1, 0};

	while (str[++cn[0]])
	{
		if (str[cn[0]] == c && str[cn[0] - 1] != c
				&& str[cn[0] - 1] != '\0')
			++cn[1];
		if (str[cn[0]] != c && str[cn[0] + 1] == '\0')
			++cn[1];
	}
	return (cn[1]);
}

static char	**malloc_all(const char *str, char c)
{
	char	**new;
	size_t	cn[3] = {-1, 0, -1};

	if (!(new = malloc(sizeof(*new) * (how_tab(str, c) + 1))))
		return (0);
	while (str[++cn[0]])
	{
		if (str[cn[0]] != c)
			cn[1]++;
		if (str[cn[0]] == c && str[cn[0] -1] != c
				&& str[cn[0] - 1] != '\0')
		{
			if (!(new[++cn[2]] = malloc(sizeof(*new) * (cn[1] + 1))))
				return (0);
			cn[1] = 0;
		}
		if (str[cn[0]] != c && str[cn[0] + 1] == '\0')
		{
			if (!(new[++cn[2]] = malloc(sizeof(*new) * (cn[1] + 1))))
				return (0);
			cn[1] = 0;
		}
	}
	return (new);
}

char	**ft_strsplit(const char *str, char c)
{
	int	cn[3] = {-1, -1, 0};
	char	**new;

	if (!(new = malloc_all(str, c)))
		return (0);
	while (str[++cn[0]])
	{
		if (str[cn[0]] != c)
			new[cn[2]][++cn[1]] = str[cn[0]];
		if ((str[cn[0]] == c && str[cn[0] + 1] != c && cn[1] > -1))
		{
			new[cn[2]++][++cn[1]] = '\0';
			cn[1] = -1;
		}
	}
	if (cn[1] > -1)
		new[cn[2]++][++cn[1]] = '\0';
	new[cn[2]] = NULL;
	return (new);
}
