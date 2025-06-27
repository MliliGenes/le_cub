/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 02:39:42 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/06/26 15:25:44 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

void render_floor_cell(t_game *game)
{
    int y;
    int x;
	uint32_t colors[2];

    colors[0] = ft_pixel(game->map_data->ceiling_color[0],game->map_data->ceiling_color[1],game->map_data->ceiling_color[2],255);
    colors[1] = ft_pixel(game->map_data->floor_color[0],game->map_data->floor_color[1],game->map_data->floor_color[2],255);
    for (y = 0; y < SCREEN_HEIGHT_DEFAULT / 2; y++)
    {
        for (x = 0; x < SCREEN_WIDTH_DEFAULT; x++)
        	mlx_put_pixel(game->img_scene, x, y, colors[0]);
    }
    
    for (y = SCREEN_HEIGHT_DEFAULT / 2; y < SCREEN_HEIGHT_DEFAULT; y++)
    {
        for (x = 0; x < SCREEN_WIDTH_DEFAULT; x++)
            mlx_put_pixel(game->img_scene, x, y, colors[1]);
    }
}

void render_walls(t_game *game)
{
    int i = 0;
    t_wall_hit *walls = game->walls;
    render_floor_cell(game);

    while (i < game->screen_width)
    {
        t_wall_hit hit = walls[i];
        if (hit.texture_id < 0 || hit.texture_id >= 4) {
            i++;
            continue;
        }

        double dist = hit.distance;
        double line_h = 1100 / dist;

        int start_y = (game->screen_height - (int)line_h) / 2;
        int end_y = start_y + (int)line_h;
        start_y = start_y < 0 ? 0 : start_y;
        end_y = end_y >= game->screen_height ? game->screen_height - 1 : end_y;

        t_texture *tex = &game->walls_textures[hit.texture_id];
        if (!tex || !tex->arr) {
            i++;
            continue;
        }

        int tex_width = tex->width;
        int tex_height = tex->height;

        // Calculate texture x coordinate with bounds checking
        int tex_x = (int)(hit.texture_x_coord * (double)tex_width);
        tex_x = tex_x < 0 ? 0 : tex_x;
        tex_x = tex_x >= tex_width ? tex_width - 1 : tex_x;

        // Calculate texture stepping
        double step = (double)tex_height / line_h;
        double tex_pos = (start_y - game->screen_height / 2.0 + line_h / 2.0) * step;
        
        for (int y = start_y; y <= end_y; y++)
        {
            int tex_y = (int)tex_pos;
            tex_y = tex_y < 0 ? 0 : tex_y;
            tex_y = tex_y >= tex_height ? tex_height - 1 : tex_y;

            uint32_t color = tex->arr[tex_y][tex_x];
            mlx_put_pixel(game->img_scene, i, y, color);
            tex_pos += step;
        }

        i++;
    }
}