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

int main(int argc, char *argv[])
{
	t_game game;
	t_map *parse;

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
		return (EXIT_SUCCESS);
	}
}