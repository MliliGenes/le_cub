#include "include/cub3d.h"

int	main(void)
{
	t_game	game;

	if (!init_game(&game))
		return (EXIT_FAILURE);
	game_loop(&game);
	return (EXIT_SUCCESS);
}
