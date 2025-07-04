#include "../include/parsing.h"

size_t	ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == (char)c)
			return ((char *)&s[len]);
		len--;
	}
	return (NULL);
}

int	ft_check_dot(char *path)
{
	char	*ber;
	char	*dot;
	int		i;

	ber = "cub";
	dot = ft_strrchr(path, '.');
	if (!dot)
		return (0);
	dot = dot + 1;
	if (ft_strlen(dot) != 3)
		return (0);
	i = 0;
	while (i < 3)
	{
		if (dot[i] != ber[i])
			return (0);
		i++;
	}
	return (1);
}
