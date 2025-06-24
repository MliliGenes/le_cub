#include "../include/parsing.h"

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

int	ft_cheking_nsew(char **arr, int i)
{
	if (ft_count(arr[i], ' ') != 2)
		return (-1);
	return (1);
}

char	**ft_checking_nwl(char *ptr, char **arr)
{
	char	**ret;
	int		size;
	int		i;
	int		k;

	size = 0;
	(void)ptr;
	while (arr[size])
		size++;
	i = 0;
	while (i < size)
	{
		k = 0;
		while (arr[i][k] == 32 || (arr[i][k] >= 9 && arr[i][k] <= 13))
			k++;
		if (arr[i][k] == '1')
			break ;
		i++;
	}
	size = i;
	while (arr[size])
		size++;
	size -= i;
	ret = malloc((size + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	k = 0;
	while (k < size)
	{
		ret[k] = ft_strdup(arr[i + k]);
		k++;
	}
	ret[k] = NULL;
	return (ret);
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
	int	i;

	i = 0;
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
