/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:34:10 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/07/07 17:34:11 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	is_valid_char(char c)
{
	const char	*valid;

	valid = "01ENWSD ";
	if (!ft_strchr(valid, c))
		return (0);
	return (1);
}

int	ft_why(char **arr)
{
	int		i;
	size_t	j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (!is_valid_char(arr[i][j]))
				return (-1);
			if (arr[i][j] == 'E' || arr[i][j] == 'N' || arr[i][j] == 'W'
				|| arr[i][j] == 'S' || arr[i][j] == 'D')
			{
				if (!arr[i][j + 1] || arr[i][j + 1] == ' ' || arr[i][j
					- 1] == ' ' || j > ft_strlen(arr[i + 1])
					|| j > ft_strlen(arr[i - 1]) || arr[i + 1][j] == ' '
					|| arr[i - 1][j] == ' ')
					return (-1);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_invalid_map(char *map, char **arr)
{
	int	i;

	if (ft_why(arr) == -1)
		return (-1);
	i = index_map_p(map);
	if (ft_nsea(&map[i]) == -1)
		return (-1);
	return (1);
}

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
