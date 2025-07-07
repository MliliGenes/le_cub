/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahamzao <sahamzao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:54:40 by sahamzao          #+#    #+#             */
/*   Updated: 2025/07/07 17:54:41 by sahamzao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

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
