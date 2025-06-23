#include "../include/parsing.h"

t_map	*full_members(char **map, t_utils *utils)
{
	t_map	*parse;

	parse = malloc(sizeof(t_map));
	if (!parse)
		return (NULL);
	parse->north_texture_path = ft_strdup(utils->no[1]);
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
	return (parse);
}

t_map	*parse_colors(t_utils *utils, t_map *parse)
{
	parse = parse_colors_utils_norm(parse, utils);
	free_help(utils);
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
				parse->player_dir = arr[i][j];
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
	t_utils	*utils;
	char	**map;

	utils = ft_checking_the_four(arr);
	if (!utils)
		return (NULL);
	map = ft_checking_nwl(ptr, arr);
	if (ft_checking_close_map(map) == -1)
		return (ret_help(map));
	parse = full_members(map, utils);
	if (!parse)
		return (ret_help(map));
	parse = parse_colors(utils, parse);
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
	if (ft_invalid_map(ptr) == -1)
		return (ret_first_help(ptr, arr));
	ft_freeing(arr);
	free(ptr);
	return (parse);
}
