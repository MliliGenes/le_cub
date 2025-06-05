 #include "../include/game.h"

void render_floor_cell(t_game *game)
{

}

void	render_walls(t_game *game)
{
	
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
}
