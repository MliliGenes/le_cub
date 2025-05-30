#include "../include/game.h"

void	game_loop(t_game *game)
{
	int	start_x;
	int	start_y;

	mlx_image_to_window(game->mlx, game->img_scene, 0, 0);
	mlx_loop_hook(game->mlx, event_listner, game);
	mlx_loop(game->mlx);
}
