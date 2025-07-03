#include "include/cub3d.h"

static void set_dimensions(t_map *map)
{
	char **arr;
	int i;
	int tmp;

	i = 0;
	arr = map->map;
	map->width = ft_sstrlen(arr[i]);
	while (arr[i])
	{
		tmp = ft_sstrlen(arr[i]);
		if (tmp > map->width)
			map->width = tmp;
		i++;
	}
	map->height = i;
}

void ll()
{
	system ("leaks cub3d");
}

void	parse_free(t_map *parse)
{
	ft_freeing(parse->map);
	free(parse->north_texture_path);
	free(parse->south_texture_path);
	free(parse->east_texture_path);
	free(parse->west_texture_path);
	free(parse);
}


int main(int argc, char *argv[])
{
	t_game game;
	t_map *parse;

	atexit(ll);
	if (argc == 2)
	{
		if (!ft_check_dot(argv[1]))
		{
			printf("Invalide file format\n");
			return (EXIT_FAILURE);
		}
		parse = parse_map_file(argv[1]);
		if (!parse)
			return (EXIT_FAILURE);
		set_dimensions(parse);
		if (!init_game(&game))
			return (EXIT_FAILURE);
		game.map_data = parse;
		game.player_data = init_player(game.map_data);
		if (!init_textures(&game))
			return false;
		game_loop(&game);
		// TODO clean_up(&game);
		free(game.rays);
		free(game.walls);
		mlx_terminate(game.mlx);
		mlx_delete_image(game.mlx, game.img_scene);
		parse_free(parse);
		for (int i = 0; i <= 4;i++)
		{
			t_texture text = game.walls_textures[i];
			int j = 0;
			while (j < (int)text.height)
				free(text.arr[j++]);
			free(text.arr);
		}
		return (EXIT_SUCCESS);
	}
}
