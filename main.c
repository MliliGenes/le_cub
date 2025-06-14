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
		game_loop(&game);
		//TODO clean_up(&game);
		return (EXIT_SUCCESS);
	}
}