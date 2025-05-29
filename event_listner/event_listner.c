#include "../include/game.h"

void	event_listner(void *params)
{
	t_game	*game;

	game = (t_game *)params;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	update_player(game);
	cast_rays(game);
}
