#include "../include/game.h"

void	reset_minimap(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINIMAP_HEIGHT)
	{
		x = 0;
		while (x < MINIMAP_WIDTH)
		{
			mlx_put_pixel(game->img_minimap, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}

void render_world_on_minimap(t_game *game)
{
    t_player *p = game->player_data;
    const int center_x = MINIMAP_WIDTH / 2;
    const int center_y = MINIMAP_HEIGHT / 2;
	double scale = 0.08;
    
    for (int screen_y = 0; screen_y < MINIMAP_HEIGHT; screen_y++)
    {
        for (int screen_x = 0; screen_x < MINIMAP_WIDTH; screen_x++)
        {
            double world_x = p->pos.x + ((screen_x - center_x) / scale);
            double world_y = p->pos.y + ((screen_y - center_y) / scale);
            int map_x = (int)world_x / TILE_SIZE;
            int map_y = (int)world_y / TILE_SIZE;    
            uint32_t color = 0x000000FF;
            if (map_x >= 0 && map_x < (game->map_data->width) && 
                map_y >= 0 && map_y < (game->map_data->height))
            {
                if (game->map_data->map[map_y][map_x] == '1')
                    color = 0x000000FF;
                else if (game->map_data->map[map_y][map_x] == '0')
                    color = 0xFFFFFFFF;
            }
            mlx_put_pixel(game->img_minimap, screen_x, screen_y, color);
        }
    }
}

void	draw_player(mlx_image_t *minimap)
{
	t_vec2i	px_pos;
	int		y;
	int		x;

	y = -2;
	while (y <= 2)
	{
		x = -2;
		while (x <= 2)
		{
			px_pos = (t_vec2i){MINIMAP_WIDTH / 2 + x, MINIMAP_HEIGHT / 2 + y};
			mlx_put_pixel(minimap, px_pos.x, px_pos.y, 0xFF0000FF);
			x++;
		}
		y++;
	}
}

void	draw_dir(mlx_image_t *minimap, t_player *p, t_vec2i pos)
{
	t_vec2d	end;
	int		i;
	t_vec2i	line;
	double	direction_length;

	i = 0;
	direction_length = 15;
	end.x = pos.x + cos(p->angle) * direction_length;
	end.y = pos.y - sin(p->angle) * direction_length;
	while (i < 10)
	{
		line.x = pos.x + (cos(p->angle) * direction_length * i) / 10;
		line.y = pos.y + (sin(p->angle) * direction_length * i) / 10;
		mlx_put_pixel(minimap, line.x, line.y, 0xFF0000FF);
		i++;
	}
}

void	render_minimap(t_game *game)
{
	t_vec2d		pos;
	t_player	*p;

	p = game->player_data;
	pos.x = p->pos.x / (double)MINIMAP_SCALE;
	pos.y = p->pos.y / (double)MINIMAP_SCALE;
	reset_minimap(game);
	render_world_on_minimap(game);
	draw_player(game->img_minimap);
	draw_dir(game->img_minimap, game->player_data, (t_vec2i){MINIMAP_WIDTH / 2,
		MINIMAP_HEIGHT / 2});
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
