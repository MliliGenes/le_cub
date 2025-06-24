/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahamzao <sahamzao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 02:39:42 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/06/23 22:48:20 by sahamzao         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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

// void render_walls(t_game *game)
// {
// 	int i = 0;
// 	t_wall_hit *walls = game->walls;
// 	render_floor_cell(game);
// 	while (i < SCREEN_WIDTH_DEFAULT)
// 	{
// 		float line_h = (TILE_SIZE * SCREEN_HEIGHT_DEFAULT) / walls[i].distance;
// 		int start_y = (SCREEN_HEIGHT_DEFAULT - round(line_h)) / 2;
// 		int end_y = start_y + round(line_h);
// 		if (start_y < 0)
// 			start_y = 0;
// 		if (end_y >= SCREEN_HEIGHT_DEFAULT)
// 			end_y = SCREEN_HEIGHT_DEFAULT - 1;
// 		// TODO add the texturing logic
// 		uint32_t wall_color;
// 		if (walls[i].texture_id == 0)
// 			wall_color = 0xFF8C00FF;
// 		if (walls[i].texture_id == 3)
// 			wall_color = 0xFF0000FF;
// 		if (walls[i].texture_id == 1)
// 			wall_color = 0xFF8C50FF;
// 		if (walls[i].texture_id == 2)
// 			wall_color = 0xFFAF00FF;
// 		for (int y = start_y; y <= end_y; y++)
// 			mlx_put_pixel(game->img_scene, i, y, wall_color);
// 		i++;
// 	}	
// }

void render_walls(t_game *game)
{
    int i = 0;
    t_wall_hit *walls = game->walls;
    render_floor_cell(game);

    while (i < game->screen_width)
    {
        t_wall_hit hit = walls[i];
        double dist = hit.distance;
        double line_h = TILE_SIZE * game->screen_height / dist;

        int start_y = (game->screen_height - (int)line_h) / 2;
        int end_y = start_y + (int)line_h;
        if (start_y < 0) start_y = 0;
        if (end_y >= game->screen_height) end_y = game->screen_height - 1;

        t_texture *tex = &game->walls_textures[hit.texture_id];
        int tw = TEXTURE_SIZE;
        int th = TEXTURE_SIZE;

        int tex_x = (int)(hit.texture_x_coord * (double)tw);
        if (tex_x < 0) tex_x = 0;
        if (tex_x >= tw) tex_x = tw - 1;

        // Vertical scaling step
        double step = (double)th / line_h;
        double tex_pos = (start_y - game->screen_height / 2.0 + line_h / 2.0) * step;

        // Draw each pixel row in the column
        for (int y = start_y; y <= end_y; y++)
        {
            int tex_y = (int)tex_pos & (th - 1);
            tex_pos += step;

            uint32_t color = tex->arr[tex_y][tex_x];
            mlx_put_pixel(game->img_scene, i, y, color);
        }

        i++;
    }
}
