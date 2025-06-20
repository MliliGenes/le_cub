#include "include/cub3d.h"

int	main()
{
	t_game	game;

	// if (ft_check_dot(argv[1]))
	// 	return (EXIT_FAILURE);
	if (!init_game(&game))
		return (EXIT_FAILURE);
	game_loop(&game);
	//TODO clean_up(&game);
	return (EXIT_SUCCESS);
}