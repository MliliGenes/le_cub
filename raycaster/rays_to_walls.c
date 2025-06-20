#include "../include/game.h"

void	rays_to_walls(t_game *game)
{
	t_ray		*rays;
	t_wall_hit	*walls;
	int			i;

	rays = game->rays;
	walls = game->walls;
	i = 0;
	while (i < SCREEN_WIDTH_DEFAULT)
	{
		double corrected = rays[i].distance * cos(rays[i].angle - game->player_data->angle);
		walls[i].distance = corrected * TILE_SIZE;
		walls[i].side = rays[i].side_hit;
		walls[i].hit_point = rays[i].hit_point;
		if (rays[i].dir.x < 0 && rays[i].side_hit == 0)
			walls[i].texture_id = 1;
		else if (rays[i].dir.x >= 0 && rays[i].side_hit == 0)
			walls[i].texture_id = 3;
		if (rays[i].dir.y < 0 && rays[i].side_hit == 1)
			walls[i].texture_id = 2;
		else if (rays[i].dir.y >= 0 && rays[i].side_hit == 1)
			walls[i].texture_id = 0;
		walls[i].texture_x_coord = rays[i].wallX;
        if ((rays[i].side_hit == 0 && rays[i].dir.x > 0) || 
            (rays[i].side_hit == 1 && rays[i].dir.y < 0))
            walls[i].texture_x_coord = 1.0 - walls[i].texture_x_coord;
		i++;
	}
}
