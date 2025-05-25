#include "../include/init.h"

bool	init_game(t_game *game)
{
	game->fov_rad = 70;
	game->screen_width = SCREEN_WIDTH_DEFAULT;
	game->screen_height = SCREEN_HEIGHT_DEFAULT;
	game->mlx = mlx_init(game->screen_width, game->screen_height, GAME_TITLE,
			false);
	if (!game->mlx)
		return (false);
	game->img_scene = mlx_new_image(game->mlx, game->mlx->width,
			game->mlx->height);
	// TODO: game->textures add fucntiont to load the textures
	game->map_data = NULL; // TODO: parse the map
	game->player_data = init_player(game->map_data);
	if (!game->player_data)
		return (false);
	return (true);
}