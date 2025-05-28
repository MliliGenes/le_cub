#include "../include/game.h"

static void	set_angles(t_ray *rays, double fov_rad, double pov_angle)
{
	double	angle_step;
	double	start_angle;
	int		i;

	i = 0;
	angle_step = fov_rad / (SCREEN_WIDTH_DEFAULT - 1);
	start_angle = pov_angle - (fov_rad / 2);
	while (i < SCREEN_WIDTH_DEFAULT)
	{
		rays[i].angle = normalize_angle(start_angle);
		rays[i].dir = (t_vec2d){cos(rays[i].angle), sin(rays[i].angle)};
		start_angle += angle_step;
		i++;
	}
}

static void	cast_single_ray(t_game *game, t_ray *ray)
{
	int		hit;
	

}

void	cast_rays(t_game *game)
{
	t_ray	*rays;
	int		i;

	i = 0;
	rays = game->rays;
	set_angles(rays, game->fov_rad, game->player_data->angle);
	while (i < SCREEN_WIDTH_DEFAULT)
	{
		
		i++;
	}
}
