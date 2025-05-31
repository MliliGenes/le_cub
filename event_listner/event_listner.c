#include "../include/game.h"

void render_floor_cell(t_game *game)
{

}

void render_walls(t_game *game)
{
	int i = 0;
	t_wall_hit *walls = game->walls;

	
	while (i < SCREEN_WIDTH_DEFAULT)
	{
		if (walls[i].distance <= 0.1)
			walls[i].distance = 0.1;
			
		float line_h = (TILE_SIZE * SCREEN_HEIGHT_DEFAULT) / walls[i].distance;
		int start_y = (SCREEN_HEIGHT_DEFAULT - (int)line_h) / 2;
		int end_y = start_y + (int)line_h;
		
		// Clamp start_y and end_y to screen bounds
		if (start_y < 0)
			start_y = 0;
		if (end_y >= SCREEN_HEIGHT_DEFAULT)
			end_y = SCREEN_HEIGHT_DEFAULT - 1;
		
		// Draw vertical line from start_y to end_y
		for (int y = start_y; y <= end_y; y++)
		{
			uint32_t wall_color = 0xFFFFFFFF; // White walls
			mlx_put_pixel(game->img_scene, i, y, wall_color);
		}
		
		i++;
	}
}

void	event_listner(void *params)
{
	t_game	*game;

	game = (t_game *)params;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	update_player(game);
	game->player_data->img->instances->x = game->player_data->pos.x;
	game->player_data->img->instances->y = game->player_data->pos.y;
	cast_rays(game);
	rays_to_walls(game);
	render_walls(game);
}
