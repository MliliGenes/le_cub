#include "../includes/parsing.h"

void	ft_freeing(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	ft_cheking_ns(int n_s, char **vv, char **bb)
{
	if (n_s != 2)
	{
		ft_freeing(vv);
		ft_freeing(bb);
		return (-1);
	}
	return (1);
}

int	ft_cheking_fc_utils(char **vv, char **bb)
{
	int	i;
	int	n_s;

	i = 0;
	n_s = 0;
	while (vv[1][i])
	{
		if (vv[1][i] == ',')
			n_s++;
		i++;
	}
	if (ft_cheking_ns(n_s, vv, bb) == -1)
		return (-1);
	i = 0;
	n_s = 0;
	while (bb[1][i])
	{
		if (bb[1][i] == ',')
			n_s++;
		i++;
	}
	if (ft_cheking_ns(n_s, vv, bb) == -1)
		return (-1);
	return (1);
}

int	ft_cheking_fc(char **arr)
{
	char	**vv;
	char	**bb;

	if (ft_count(arr[4], ' ') != 2 || ft_count(arr[5], ' ') != 2)
		return (-1);
	vv = ft_split(arr[4], ' ');
	bb = ft_split(arr[5], ' ');
	if (ft_cheking_fc_utils(vv, bb) == -1)
		return (-1);
	ft_freeing(vv);
	ft_freeing(bb);
	return (1);
}

int	ft_checking_the_four(char **arr)
{
	if (ft_strncmp(arr[0], "NO", 2) == -1)
		return (-1);
	if (ft_strncmp(arr[1], "SO", 2) == -1)
		return (-1);
	if (ft_strncmp(arr[2], "WE", 2) == -1)
		return (-1);
	if (ft_strncmp(arr[3], "EA", 2) == -1)
		return (-1);
	if (arr[4][0] != 'F')
		return (-1);
	if (arr[5][0] != 'C')
		return (-1);
	if (ft_cheking_nsew(arr) == -1)
		return (-1);
	if (ft_cheking_fc(arr) == -1)
		return (-1);
	return (1);
}