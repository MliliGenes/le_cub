#include "../include/parsing.h"

t_map	*full_members(char **arr, char **map)
{
	t_map	*parse;
	t_utils	*utils;

	parse = malloc(sizeof(t_map));
	utils = malloc(sizeof(t_utils));
	if (!parse)
		return (NULL);
	utils->no = ft_split(arr[0], ' ');
	utils->so = ft_split(arr[1], ' ');
	utils->we = ft_split(arr[2], ' ');
	utils->ea = ft_split(arr[3], ' ');
	parse->north_texture_path = ft_strdup(utils->so[1]);
	parse->south_texture_path = ft_strdup(utils->so[1]);
	parse->west_texture_path = ft_strdup(utils->we[1]);
	parse->east_texture_path = ft_strdup(utils->ea[1]);
	if (ft_check_valid_path(parse->north_texture_path,
			parse->south_texture_path, parse->west_texture_path,
			parse->east_texture_path) == -1)
	{
		free_help(utils);
		return (NULL);
	}
	parse->map = map;
	free_help(utils);
	return (parse);
}

t_map	*parse_colors(char **arr, t_map *parse)
{
	char	**floor;
	char	**ceiling;
	char	**f;
	char	**c;

	floor = ft_split(arr[4], ' ');
	ceiling = ft_split(arr[5], ' ');
	f = ft_split(floor[1], ',');
	c = ft_split(ceiling[1], ',');
	ft_freeing(floor);
	ft_freeing(ceiling);
	parse = parse_colors_utils_norm(parse, f, c);
	ft_freeing(f);
	ft_freeing(c);
	return (parse);
}

t_map	*find_player(char **arr, t_map *parse)
{
	int	i;
	int	j;

	if (!parse)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (arr[i][j] == 'N' || arr[i][j] == 'S' || arr[i][j] == 'E'
				|| arr[i][j] == 'W')
			{
				parse->x_player = j;
				parse->y_player = i;
				parse->pos_player = arr[i][j];
				return (parse);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

t_map	*go_parse_lines(char **arr, char *ptr)
{
	t_map	*parse;
	char	**map;
	int		i;
	int		b;

	if (ft_checking_the_four(arr) == -1)
		return (NULL);
	i = ft_checking_nwl(ptr);
	b = ft_valide_lines(ptr + i);
	if (b == -1)
		return (NULL);
	map = ft_split(ptr + i, '\n');
	if (ft_checking_close_map(map) == -1)
		return (ret_help(map));
	parse = full_members(arr, map);
	if (!parse)
		return (ret_help(map));
	parse = parse_colors(arr, parse);
	if (!parse)
		return (ret_help(map));
	parse = find_player(map, parse);
	if (!parse)
		return (ret_help(map));
	return (parse);
}

t_map	*parse_map_file(char *path)
{
	char	**arr;
	t_map	*parse;
	char	*ptr;
	int		fd;

	fd = open(path, O_RDONLY, 0444);
	if (fd < 0)
	{
		printf("invalid file\n");
		return (NULL);
	}
	ptr = read_line_hh(fd);
	if (!ptr)
		return (NULL);
	arr = ft_split(ptr, '\n');
	parse = go_parse_lines(arr, ptr);
	if (!parse)
		return (ret_first_help(ptr, arr));
	ft_freeing(arr);
	free(ptr);
	return (parse);
}
