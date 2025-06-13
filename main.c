#include "include/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	(void)argc;
	if (ft_check_dot(argv[1]))
		return (EXIT_FAILURE);
	if (!init_game(&game))
		return (EXIT_FAILURE);
	game_loop(&game);
	//TODO clean_up(&game);
	return (EXIT_SUCCESS);
}