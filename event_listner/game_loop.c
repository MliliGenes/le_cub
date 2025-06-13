#include "../include/game.h"

void	game_loop(t_game *game)
{
	mlx_image_to_window(game->mlx, game->img_scene, 0, 0);
	mlx_image_to_window(game->mlx, game->img_minimap, MINIMAP_PADDING, MINIMAP_PADDING);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(game->mlx, SCREEN_WIDTH_DEFAULT / 2, SCREEN_HEIGHT_DEFAULT / 2);
	mlx_loop_hook(game->mlx, event_listner, game);
	mlx_loop(game->mlx);
}
