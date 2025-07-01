#include "../include/game.h"

static int is_wall_hit(t_game *game, int x, int y)
{
    if (y < 0 || x < 0)
        return (1);
    if (y >= game->map_data->height || x >= game->map_data->width)
        return (1);
    return (game->map_data->map[y][x] == '1' || game->map_data->map[y][x] == 'D');
}

// New function to handle distance calculations when a wall is hit
static void calculate_wall_hit_distance(t_ray *ray)
{
    if (ray->side_hit == 0)
        ray->distance = (ray->map_grid_pos.x - ray->map_pixel_pos.x + (double)(1 - ray->steps.x) / 2) / ray->dir.x;
    else
        ray->distance = (ray->map_grid_pos.y - ray->map_pixel_pos.y + (double)(1 - ray->steps.y) / 2) / ray->dir.y;
    ray->distance = fabs(ray->distance);
}

static void advance_ray(t_ray *ray)
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
}

void dda_loop(t_game *game, t_ray *ray)
{
    while (true && ray)
    {
        advance_ray(ray);

        if (is_wall_hit(game, ray->map_grid_pos.x, ray->map_grid_pos.y))
        {
            calculate_wall_hit_distance(ray);
            break;
        }
    }
}

