#include "../include/parsing.h"

int	first_line(char *map)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	while (map[size])
		size++;
	while (map[i] == 32 || (map[i] >= 9 && map[i] <= 13))
		i++;
	size--;
	while (map[size] == 32 || (map[size] >= 9 && map[size] <= 13))
		size--;
	while (i < size)
	{
		if (map[i] != '1' && map[i] != ' ')
			return (-1);
		i++;
	}
	return (1);
}

int	norminette_help_close(char **map, int i, int j, int size)
{
	while (j < size)
	{
		if (map[i][j] == '0')
		{
			if (map[i][j + 1] == ' ' || map[i][j - 1] == ' ' || map[i
				+ 1][j] == ' ' || map[i - 1][j] == ' '
				|| (size_t)j > ft_strlen(map[i + 1]))
				return (-1);
		}
		j++;
	}
	return (1);
}

int	ft_closing(char **map)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] == 32 || (map[i][j] >= 9 && map[i][j] <= 13))
			j++;
		if (map[i][j] != '\0')
		{
			if (map[i][j] != '1')
				return (-1);
			size = ft_strlen(map[i]) - 1;
			while (map[i][size] == 32 || (map[i][size] >= 9
					&& map[i][size] <= 13))
				size--;
			if (map[i][size] != '1')
				return (-1);
			if (norminette_help_close(map, i, j, size) == -1)
				return (-1);
		}
		i++;
	}
	return (1);
}

int	ft_checking_close_map(char **map)
{
	if (first_line(map[0]) == -1)
		return (-1);
	if (ft_closing(map) == -1)
		return (-1);
	return (1);
}

int	ft_check_valid_path(char *ptr, char *str, char *clr, char *codex)
{
	int	fd;

	fd = open(ptr, O_RDONLY, 0444);
	if (fd < 0)
		return (-1);
	fd = open(str, O_RDONLY, 0444);
	if (fd < 0)
		return (-1);
	fd = open(clr, O_RDONLY, 0444);
	if (fd < 0)
		return (-1);
	fd = open(codex, O_RDONLY, 0444);
	if (fd < 0)
		return (-1);
	return (1);
}
