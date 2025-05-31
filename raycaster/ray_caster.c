/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: le-saad <le-saad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 21:28:35 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/31 15:54:43 by le-saad          ###   ########.fr       */
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
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_grid_pos.x += ray->steps.x;
			ray->side_hit = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_grid_pos.y += ray->steps.y;
			ray->side_hit = 1;
		}
		if (game->map_data->map[ray->map_grid_pos.y][ray->map_grid_pos.x] != '0')
		{
			if (ray->side_hit == 0)
				ray->distance = (ray->map_grid_pos.x - ray->map_pixel_pos.x + 
								(1 - ray->steps.x) / 2) / ray->dir.x;
			else
				ray->distance = (ray->map_grid_pos.y - ray->map_pixel_pos.y + 
								(1 - ray->steps.y) / 2) / ray->dir.y;
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

//DEBUG
void draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1)
    {
        x0 < img->width && y0 < img->height ? mlx_put_pixel(img, x0, y0, color) : NULL;
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void	cast_rays(t_game *game)
{
	t_ray	*rays;
	int		i;
	

	memset(game->img_scene->pixels, 0, 
          game->img_scene->width * game->img_scene->height * sizeof(int32_t));
	i = 0;
	rays = game->rays;
	set_angles(rays, game->fov_rad, game->player_data->angle);
	while (i < SCREEN_WIDTH_DEFAULT)
	{
		rays[i].map_pixel_pos = (t_vec2d){(double)game->player_data->pos.x
			/ TILE_SIZE, (double)game->player_data->pos.y / TILE_SIZE};
		rays[i].map_grid_pos = (t_vec2i){(int)rays[i].map_pixel_pos.x,
			(int)rays[i].map_pixel_pos.y};
		cast_single_ray(game, &rays[i]);
		rays[i].hit_point = (t_vec2d){
   			game->player_data->pos.x + rays[i].dir.x * rays[i].distance * TILE_SIZE,
  		 	game->player_data->pos.y + rays[i].dir.y * rays[i].distance * TILE_SIZE
		};
		// int end_x = (int)(game->player_data->pos.x + rays[i].dir.x * rays[i].distance * TILE_SIZE);
		// int end_y = (int)(game->player_data->pos.y + rays[i].dir.y * rays[i].distance * TILE_SIZE);
		// draw_line(game->img_scene, 
        //          (int)game->player_data->pos.x, (int)game->player_data->pos.y, 
        //          end_x, end_y, 0xFF00FFFF);
		// mlx_put_pixel(game->img_scene, end_x, end_y, 0xFF0000FF);
		i++;
	}
}
