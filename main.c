#include "include/cub3d.h"

int	main(void)
{
	t_game	game;

	if (init_game(&game))
		return (EXIT_FAILURE);

	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
