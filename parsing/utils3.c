#include "../include/parsing.h"

int	is__space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

long long	ft_atoi(const char *str)
{
	size_t	res;
	int		i;

	res = 0;
	i = 0;
	if (!str)
		return (-1);
	while (is__space(str[i]))
		i++;
	if (str[i] == '-')
		return (-1);
	if (str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (res);
}

void	free_help(t_utils *utils)
{
	ft_freeing(utils->no);
	ft_freeing(utils->so);
	ft_freeing(utils->ea);
	ft_freeing(utils->we);
	free(utils);
}
