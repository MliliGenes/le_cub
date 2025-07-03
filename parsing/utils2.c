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

void	*ft_void_free(t_utils *utils)
{
	if (utils->no)
		ft_freeing(utils->no);
	if (utils->so)
		ft_freeing(utils->so);
	if (utils->we)
		ft_freeing(utils->we);
	if (utils->ea)
		ft_freeing(utils->ea);
	if (utils->c)
		ft_freeing(utils->c);
	if (utils->f)
		ft_freeing(utils->f);
	free(utils);
	return (NULL);
}

t_utils	*utils_ret(char *coor[4], t_norm *norm, char **arr)
{
	t_utils	*utils;

	coor[0] = "NO";
	coor[1] = "SO";
	coor[2] = "WE";
	coor[3] = "EA";
	utils = malloc(sizeof(t_utils));
	utils->no = NULL;
	utils->so = NULL;
	utils->ea = NULL;
	utils->we = NULL;
	utils->f = NULL;
	utils->c = NULL;
	norm->flag = 0;
	norm->size = 0;
	norm->i = 0;
	while (arr[norm->size])
		norm->size++;
	return (utils);
}

void	ft_line_break(char **arr, int *i, int *k, int *j)
{
	*k = 0;
	*j = 0;
	while (arr[*i][*k] == 32 || (arr[*i][*k] >= 9 && arr[*i][*k] <= 13))
		(*k)++;
}

char	*break_lines(char **arr, t_norm *norm, t_utils *utils)
{
	char	**ret;

	ret = ft_cheking_fc(arr, norm->i, norm->k + 1);
	if (!ret)
		return (NULL);
	if (arr[norm->i][norm->k] == 'F')
		utils->f = ret;
	else if (arr[norm->i][norm->k] == 'C')
		utils->c = ret;
	norm->flag++;
	return (*ret);
}

void	ft_paths_break(char **arr,t_norm *norm,t_utils *utils)
{
	if (norm->j == 0)
		utils->no = ft_split(&arr[norm->i][norm->k], ' ');
	else if (norm->j == 1)
		utils->so = ft_split(&arr[norm->i][norm->k], ' ');
	else if (norm->j == 2)
		utils->we = ft_split(&arr[norm->i][norm->k], ' ');
	else if (norm->j == 3)
		utils->ea = ft_split(&arr[norm->i][norm->k], ' ');
	norm->flag++;
	norm->j = 4;
}

t_utils	*ft_checking_the_four(char **arr)
{
	char	*coor[4];
	t_norm	norm;
	t_utils	*utils;

	utils = utils_ret(coor, &norm, arr);
	while (norm.i < norm.size)
	{
		ft_line_break(arr, &norm.i, &norm.k, &norm.j);
		if ((arr[norm.i][norm.k] == 'F' || arr[norm.i][norm.k] == 'C')
			&& (arr[norm.i][norm.k + 1] == ' '))
		{
			if (!break_lines(arr, &norm, utils))
				return (ft_void_free(utils));
		}
		else
		{
			while (norm.j < 4)
			{
				if (!ft_strncmp(&arr[norm.i][norm.k], coor[norm.j], 2))
				{
					if (ft_cheking_nsew(arr, norm.i) == -1)
						return (ft_void_free(utils));
					else
						ft_paths_break(arr,&norm,utils);
				}
				norm.j++;
			}
		}
		norm.i++;
	}
	if (norm.flag != 6)
		return (ft_void_free(utils));
	return (utils);
}
