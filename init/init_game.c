#include "../include/init.h"

bool	init_game(t_game *game)
{
	game->fov_rad = deg_to_radian(FOV);
	game->screen_width = SCREEN_WIDTH_DEFAULT;
	game->screen_height = SCREEN_HEIGHT_DEFAULT;
	game->mlx = mlx_init(game->screen_width, game->screen_height, GAME_TITLE,
			false);
	if (!game->mlx)
		return (false);
	game->img_scene = mlx_new_image(game->mlx, game->mlx->width,
			game->mlx->height);
	game->img_minimap = mlx_new_image(game->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	game->map_data = init_map();
	game->player_data = init_player(game->map_data);
	if (!game->player_data)
		return (false);
	game->rays = init_rays();
	if (!game->rays)
		return (false);
	game->walls = init_walls();
	if (!game->rays)
		return (false);
	return (true);
}
