#include "../include/game.h"

void render_minimap(t_game *game)
{
	t_vec2d pos;
	t_player *p = game->player_data;

	pos.x = p->pos.x / (double)MINIMAP_SCALE;
	pos.y = p->pos.y / (double)MINIMAP_SCALE;
}

void	event_listner(void *params)
{
	t_game	*game;

	game = (t_game *)params;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	update_player(game);
	cast_rays(game);
	rays_to_walls(game);
	render_walls(game);
	render_minimap(game);
}
