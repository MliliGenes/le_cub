#include "../include/game.h"

void	event_listner(void *params)
{
	t_game		*game;
	t_player	*player;
	bool		e_key_down;

	game = (t_game *)params;
	player = game->player_data;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	update_player(game);
	e_key_down = mlx_is_key_down(game->mlx, MLX_KEY_E);
	if (e_key_down && game->e_key_was_up && (game->map_data->map[player->pos.y
			/ TILE_SIZE][player->pos.x / TILE_SIZE] != 'D'
			&& game->map_data->map[player->pos.y / TILE_SIZE][player->pos.x
			/ TILE_SIZE] != 'O'))
		handle_door_interaction(game);
	game->e_key_was_up = !e_key_down;
	cast_rays(game);
	rays_to_walls(game);
	render_walls(game);
	render_minimap(game);
}
