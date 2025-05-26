#include "../includes/parsing.h"

int	find_map(char *ptr, int i)
{
	int	j;

	while (ptr[i] && (ptr[i] != '0' && ptr[i] != '1' && ptr[i] != 'N'
			&& ptr[i] != 'S' && ptr[i] != 'E' && ptr[i] != 'W'))
		i++;
	j = i;
	while (ptr[j] != '\n')
		j--;
	return (j + 1);
}

int	ft_cheking_nsew(char **arr)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (ft_count(arr[i], ' ') != 2)
			return (-1);
		i++;
	}
	return (1);
}

int	ft_checking_nwl(char *ptr)
{
	char	*start;
	int		i;
	int		j;
	int		k;
	int		len;

	i = 0;
	while (ptr[i])
	{
		j = i;
		while (ptr[j] && ptr[j] != '\n')
			j++;
		if (ptr[j] == '\n')
		{
			len = j - i;
			start = malloc(len + 1);
		}
		k = 0;
		while (len)
		{
			start[k] = ptr[j - len];
			len--;
			k++;
		}
		start[k] = '\0';
		if (start[0] == 'C' && start[1] == ' ')
			return (find_map(ptr, j + 1));
		free(start);
		i = j + 1;
	}
	return (0);
}

int	ft_check_emptyline(char *ptr, int *i)
{
	while (ptr[*i] && ptr[*i] != '\n' && (ptr[*i] == 32 || (ptr[*i] >= 9
				&& ptr[*i] <= 13)))
		(*i)++;
	if (ptr[*i] == '\n')
		return (-1);
	return (1);
}

int	ft_valide_lines(char *ptr)
{
	int i = 0;

	while (ptr[i])
	{
		if (ptr[i] == '\n')
		{
			if (ptr[i + 1])
			{
				i++;
				if (ft_check_emptyline(ptr, &i) == -1)
					return (-1);
			}
		}
		i++;
	}
	return (1);
}