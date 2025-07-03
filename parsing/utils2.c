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

int sil_count(char **arr,int k,int i)
{
	int sil;

	sil = 0;
	while (arr[i][k])
	{
		if (arr[i][k] == ',')
			sil++;
		k++;
	}
	if (sil != 2)
		return (-1);
	return 1;
}

void	skiiipox(char **arr, t_help *help,int i)
{
	while (arr[i][help->save] && (arr[i][help->save] == 32 || (arr[i][help->save] >= 9
				&& arr[i][help->save] <= 13)))
		(help->save)++;
}

void	lenght_sk(t_help *help, char **arr,int i)
{
	help->to_malc = 0;
	while (arr[i][help->save])
	{
		if (arr[i][help->save] != ' ' && (arr[i][help->save] < 9 || arr[i][help->save] > 13))
			help->to_malc++;
		help->save++;
	}
}

char	*cpy_help_norm(char **arr,t_help *help,int i,char *ptr)
{
	int	k;

	k = 0;
	while (k < help->to_malc)
	{
		if (arr[i][k + help->len] != ' ' && (arr[i][help->len + k] < 9 || arr[i][help->len
				+ k] > 13))
		{
			ptr[k] = arr[i][help->len + k];
			k++;
		}
		else
			help->len++;
	}
	ptr[k] = '\0';
	return ptr;
}

char	**ft_cheking_fc(char **arr, int i, int k)
{
	char	**vv;
	t_help	help;
	char	*ptr;

	help.save = k;
	help.len = k;
	if(sil_count(arr,k,i) == -1)
		return NULL;
	skiiipox(arr,&help,i);
	help.gg = help.save;
	lenght_sk(&help,arr,i);
	ptr = malloc((help.to_malc) + 1);
	help.len = help.gg;
	ptr = cpy_help_norm(arr,&help,i,ptr);
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

void	ft_paths_break(char **arr, t_norm *norm, t_utils *utils)
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

void	*final_breack(t_norm *norm, char **arr, t_utils *utils, char **coor)
{
	while (norm->j < 4)
	{
		if (!ft_strncmp(&arr[norm->i][norm->k], coor[norm->j], 2))
		{
			if (ft_cheking_nsew(arr, norm->i) == -1)
				return (NULL);
			else
				ft_paths_break(arr, norm, utils);
		}
		norm->j++;
	}
	return ("ff");
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
			if (!final_breack(&norm, arr, utils, coor))
				return (ft_void_free(utils));
		}
		norm.i++;
	}
	if (norm.flag != 6)
		return (ft_void_free(utils));
	return (utils);
}
