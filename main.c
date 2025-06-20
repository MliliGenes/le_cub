#include "include/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;
	t_map *parse;
	
	if(argc == 2)
	{
		if (!ft_check_dot(argv[1]))
		{
			printf("Invalide file format\n");
			return (EXIT_FAILURE);
		}
		parse = parse_map_file(argv[1]);
		if(!parse)
			return (EXIT_FAILURE);
		if (!init_game(&game))
			return (EXIT_FAILURE);
		game.map_data = parse;
		game.player_data = init_player(game.map_data);
		printf("N:%s E:%s S:%s W:%s\n", game.map_data->north_texture_path, game.map_data->east_texture_path, game.map_data->south_texture_path, game.map_data->west_texture_path);
		printf("R:%d, G:%d ,B:%d\n", parse->ceiling_color[0],parse->ceiling_color[1],parse->ceiling_color[2]);
		printf("R:%d, G:%d ,B:%d\n", parse->floor_color[0],parse->floor_color[1],parse->floor_color[2]);
		game_loop(&game);
		//TODO clean_up(&game);
		return (EXIT_SUCCESS);
	}
}