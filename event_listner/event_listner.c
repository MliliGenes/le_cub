#include "../include/game.h"

void render_floor_cell(t_game *game)
{
    int y;
    int x;
    
    // Draw ceiling (upper half of the screen)
    for (y = 0; y < SCREEN_HEIGHT_DEFAULT / 2; y++)
    {
        for (x = 0; x < SCREEN_WIDTH_DEFAULT; x++)
        mlx_put_pixel(game->img_scene, x, y, 0x000000FF);
    }
    
    // Draw floor (lower half of the screen)
    for (y = SCREEN_HEIGHT_DEFAULT / 2; y < SCREEN_HEIGHT_DEFAULT; y++)
    {
        for (x = 0; x < SCREEN_WIDTH_DEFAULT; x++)
            mlx_put_pixel(game->img_scene, x, y, 0xFFFFFFFF);
    }
}

void render_walls(t_game *game)
{
	int i = 0;
	t_wall_hit *walls = game->walls;
	memset(game->img_scene->pixels, 0, 
          game->img_scene->width * game->img_scene->height * sizeof(int32_t));
	render_floor_cell(game);
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
		uint32_t wall_color; // White walls
		if (walls[i].texture_id == 0)
			wall_color = 0xFF0000FF;
		if (walls[i].texture_id == 1)
			wall_color = 0xFFFF00FF;
		if (walls[i].texture_id == 2)
			wall_color = 0x00FF00FF;
		if (walls[i].texture_id == 3)
			wall_color = 0x0000FFFF;
		for (int y = start_y; y <= end_y; y++)
		{
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
	// game->player_data->img->instances->x = game->player_data->pos.x;
	// game->player_data->img->instances->y = game->player_data->pos.y;
	cast_rays(game);
	rays_to_walls(game);
	render_walls(game);
}
