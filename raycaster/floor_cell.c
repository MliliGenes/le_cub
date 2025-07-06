#include "../include/game.h"

void render_floor_cell(t_game *game)
{
    int y;
    int x;
	uint32_t colors[2];

    colors[0] = ft_pixel(game->map_data->ceiling_color[0],game->map_data->ceiling_color[1],game->map_data->ceiling_color[2],255);
    colors[1] = ft_pixel(game->map_data->floor_color[0],game->map_data->floor_color[1],game->map_data->floor_color[2],255);
    y = 0;
    while (y < SCREEN_HEIGHT_DEFAULT / 2)
    {
        x = 0;
        while ( x < SCREEN_WIDTH_DEFAULT)
        	mlx_put_pixel(game->img_scene, x++, y, colors[0]);
        y++;
    }
    
    while (y < SCREEN_HEIGHT_DEFAULT)
    {
        x = 0;
        while ( x < SCREEN_WIDTH_DEFAULT)
            mlx_put_pixel(game->img_scene, x++, y, colors[1]);
        y++;
    }
}
