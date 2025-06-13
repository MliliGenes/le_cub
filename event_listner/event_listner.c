#include "../include/game.h"

void draw_minimap_walls(t_game *game)
{
    for (int y = 0; y < MINIMAP_HEIGHT; y++)
    {
        for (int x = 0; x < MINIMAP_WIDTH; x++)
        {
            mlx_put_pixel(game->img_minimap, x, y, 0xFFFFFFFF);
        }
    }
}

void	render_minimap(t_game *game)
{
	t_vec2d		pos;
	t_player	*p;

	draw_minimap_walls(game);
	p = game->player_data;
	// pos.x = p->pos.x / (double)MINIMAP_SCALE;
	// pos.y = p->pos.y / (double)MINIMAP_SCALE;
	
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
