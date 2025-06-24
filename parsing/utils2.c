#include "../include/parsing.h"

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

char	**ft_cheking_fc(char **arr, int i, int k)
{
	char	**vv;
	int		sil;
	int		save;
	int		len;
	char	*ptr;
	int		gg;
	int		to_malc;

	sil = 0;
	save = k;
	len = k;
	while (arr[i][k])
	{
		if (arr[i][k] == ',')
			sil++;
		k++;
	}
	if (sil != 2)
		return (NULL);
	while (arr[i][save] && (arr[i][save] == 32 || (arr[i][save] >= 9
				&& arr[i][save] <= 13)))
		save++;
	to_malc = 0;
	gg = save;
	while (arr[i][save])
	{
		if (arr[i][save] != ' ' && (arr[i][save] < 9 || arr[i][save] > 13))
			to_malc++;
		save++;
	}
	ptr = malloc((to_malc) + 1);
	k = 0;
	len = gg;
	while (k < to_malc)
	{
		if (arr[i][k + len] != ' ' && (arr[i][len + k] < 9 || arr[i][len
				+ k] > 13))
		{
			ptr[k] = arr[i][len + k];
			k++;
		}
		else
			len++;
	}
	ptr[k] = '\0';
	vv = ft_split(ptr, ',');
	free(ptr);
	return (vv);
}

t_utils	*ft_checking_the_four(char **arr)
{
	char	*coor[4];
	char	**ret;
	int		i;
	int		flag;
	int		j;
	int		k;
	t_utils	*utils;
	int		size;

	coor[0] = "NO";
	coor[1] = "SO";
	coor[2] = "WE";
	coor[3] = "EA";
	i = 0;
	utils = malloc(sizeof(t_utils));
	flag = 0;
	size = 0;
	while (arr[size])
		size++;
	while (i < size)
	{
		k = 0;
		j = 0;
		while (arr[i][k] == 32 || (arr[i][k] >= 9 && arr[i][k] <= 13))
			k++;
		if ((arr[i][k] == 'F' || arr[i][k] == 'C') && (arr[i][k + 1] == ' '))
		{
			ret = ft_cheking_fc(arr, i, k + 1);
			if (!ret)
				return (NULL);
			if (arr[i][k] == 'F')
				utils->f = ret;
			else if (arr[i][k] == 'C')
				utils->c = ret;
			flag++;
		}
		else
		{
			while (j < 4)
			{
				if (!ft_strncmp(&arr[i][k], coor[j], 2))
				{
					if (ft_cheking_nsew(arr, i) == -1)
						return (NULL);
					else
					{
						if (j == 0)
							utils->no = ft_split(&arr[i][k], ' ');
						else if (j == 1)
							utils->so = ft_split(&arr[i][k], ' ');
						else if (j == 2)
							utils->we = ft_split(&arr[i][k], ' ');
						else if (j == 3)
							utils->ea = ft_split(&arr[i][k], ' ');
						flag++;
						j = 4;
					}
				}
				j++;
			}
		}
		i++;
	}
	if (flag != 6)
		return (NULL);
	return (utils);
}
