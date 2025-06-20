/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 21:28:35 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/06/20 02:34:01 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		rays[i].distance = 0.0;
		rays[i].angle = normalize_angle(start_angle + (i * angle_step));
		rays[i].dir = (t_vec2d){cos(rays[i].angle), sin(rays[i].angle)};
		rays[i].delta_dist.x = fabs(1 / rays[i].dir.x);
		rays[i].delta_dist.y = fabs(1 / rays[i].dir.y);
		i++;
	}
}

static void	dda_loop(t_game *game, t_ray *ray)
{
	while (true)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->distance = ray->side_dist.x;
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_grid_pos.x += ray->steps.x;
			ray->side_hit = 0;
		}
		else
		{
			ray->distance = ray->side_dist.y;
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_grid_pos.y += ray->steps.y;
			ray->side_hit = 1;
		}
		if (game->map_data->map[ray->map_grid_pos.y][ray->map_grid_pos.x] != '0')
		{
			if (ray->side_hit == 0)
				ray->distance = (ray->map_grid_pos.x - ray->map_pixel_pos.x + (1 - ray->steps.x) / 2) / ray->dir.x;
			else
				ray->distance = (ray->map_grid_pos.y - ray->map_pixel_pos.y + (1 - ray->steps.y) / 2) / ray->dir.y;
			ray->distance = fabs(ray->distance);
			break;
		}
	}
}

static void	cast_single_ray(t_game *game, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->steps.x = -1;
		ray->side_dist.x = (ray->map_pixel_pos.x - ray->map_grid_pos.x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->steps.x = 1;
		ray->side_dist.x = (ray->map_grid_pos.x + 1 - ray->map_pixel_pos.x)
			* ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->steps.y = -1;
		ray->side_dist.y = (ray->map_pixel_pos.y - ray->map_grid_pos.y)
			* ray->delta_dist.y;
	}
	else
	{
		ray->steps.y = 1;
		ray->side_dist.y = (ray->map_grid_pos.y + 1 - ray->map_pixel_pos.y)
			* ray->delta_dist.y;
	}
	dda_loop(game, ray);
}

// DEBUG // 


void	cast_rays(t_game *game)
{
	t_ray	*rays;
	int		i;

	i = 0;
	rays = game->rays;
	set_angles(rays, game->fov_rad, game->player_data->angle);
	while (i < SCREEN_WIDTH_DEFAULT)
	{
		rays[i].map_pixel_pos = (t_vec2d){(double)game->player_data->pos.x
			/ (double)TILE_SIZE, (double)game->player_data->pos.y / (double)TILE_SIZE};
		rays[i].map_grid_pos = (t_vec2i){(int)rays[i].map_pixel_pos.x,
			(int)rays[i].map_pixel_pos.y};
		cast_single_ray(game, &rays[i]);
		rays[i].hit_point = (t_vec2d){
   			game->player_data->pos.x + rays[i].dir.x * rays[i].distance * TILE_SIZE,
  		 	game->player_data->pos.y + rays[i].dir.y * rays[i].distance * TILE_SIZE
		};
		double wallX;
		if (rays[i].side_hit == 0)
			wallX = rays[i].map_pixel_pos.y + rays[i].distance * rays[i].dir.y;
		else
			wallX = rays[i].map_pixel_pos.x + rays[i].distance * rays[i].dir.x;
		wallX -= floor(wallX);
		rays[i].wallX = wallX;
		i++;
	}
}
