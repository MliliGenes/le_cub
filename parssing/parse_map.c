#include "../includes/parsing.h"

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
	char		**floor;
	char		**ceiling;
	char		**f;
	char		**c;
	int			i;
	long long	codex;
	long long	codexo;

	floor = ft_split(arr[4], ' ');
	ceiling = ft_split(arr[5], ' ');
	f = ft_split(floor[1], ',');
	c = ft_split(ceiling[1], ',');
	ft_freeing(floor);
	ft_freeing(ceiling);
	i = 0;
	while (i < 3)
	{
		codex = ft_atoi(f[i]);
		codexo = ft_atoi(c[i]);
		if (codexo == -1 || codex == -1 || codex > 255 || codexo > 255)
		{
			ft_freeing(f);
			ft_freeing(c);
			return (NULL);
		}
		parse->floor_color[i] = (unsigned int)codex;
		parse->ceiling_color[i] = (unsigned int)codexo;
		i++;
	}
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
	{
		ft_freeing(map);
		return (NULL);
	}
	parse = full_members(arr, map);
	if (!parse)
	{
		ft_freeing(map);
		return (NULL);
	}
	parse = parse_colors(arr, parse);
	if (!parse)
	{
		ft_freeing(map);
		return (NULL);
	}
	parse = find_player(map, parse);
	if (!parse)
	{
		ft_freeing(map);
		return (NULL);
	}
	return (parse);
}

t_map	*parse_map_file(char *path)
{
	char	*tet1;
	char	**arr;
	char	*tet;
	char	*ptr;
	t_map	*parse;
	int		fd;

	fd = open(path, O_RDONLY, 0444);
	if (fd < 0)
	{
		printf("invalid file\n");
		return (NULL);
	}
	ptr = NULL;
	tet1 = get_next_line(fd);
	if (tet1 == NULL)
	{
		close(fd);
		return (NULL);
	}
	while (tet1 != NULL)
	{
		tet = ft_strdup(tet1);
		free(tet1);
		ptr = ft_strcat(ptr, tet);
		free(tet);
		tet1 = get_next_line(fd);
	}
	arr = ft_split(ptr, '\n');
	close(fd);
	parse = go_parse_lines(arr, ptr);
	if (!parse)
	{
		free(ptr);
		ft_freeing(arr);
		printf("ERROR : invalid map =(\n");
		return (NULL);
	}
	ft_freeing(arr);
	free(ptr);
	return (parse);
}
