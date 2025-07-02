#include "../include/game.h"
#include <math.h> // Make sure you have this include for cos, sin, and fabs

// Assuming your t_game struct and other definitions are available.
// Also assuming definitions for TILE_SIZE.

void	handle_door_interaction(t_game *game)
{
	t_ray	door_ray;
	double	player_angle;

	player_angle = game->player_data->angle;
	door_ray.angle = player_angle;
	door_ray.dir.x = cos(player_angle);
	door_ray.dir.y = sin(player_angle);
	door_ray.delta_dist.x = fabs(1 / door_ray.dir.x);
	door_ray.delta_dist.y = fabs(1 / door_ray.dir.y);
	door_ray.map_pixel_pos.x = (double)game->player_data->pos.x / TILE_SIZE;
	door_ray.map_pixel_pos.y = (double)game->player_data->pos.y / TILE_SIZE;
	door_ray.map_grid_pos.x = (int)door_ray.map_pixel_pos.x;
	door_ray.map_grid_pos.y = (int)door_ray.map_pixel_pos.y;
	cast_single_ray(game, &door_ray, true);
	if ((door_ray.collision_type == 'D' || door_ray.collision_type == 'O') && door_ray.distance < 2)
	{
		if (game->map_data->map[door_ray.map_grid_pos.y][door_ray.map_grid_pos.x] == 'D')
			game->map_data->map[door_ray.map_grid_pos.y][door_ray.map_grid_pos.x] = 'O';
		else if (game->map_data->map[door_ray.map_grid_pos.y][door_ray.map_grid_pos.x] == 'O')
			game->map_data->map[door_ray.map_grid_pos.y][door_ray.map_grid_pos.x] = 'D';
	}
}
