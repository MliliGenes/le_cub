/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 02:39:42 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/06/20 11:40:39 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

void render_floor_cell(t_game *game)
{
    int y;
    int x;
    
    for (y = 0; y < SCREEN_HEIGHT_DEFAULT / 2; y++)
    {
        for (x = 0; x < SCREEN_WIDTH_DEFAULT; x++)
        	mlx_put_pixel(game->img_scene, x, y, 0x5C94FCFF);
    }
    
    for (y = SCREEN_HEIGHT_DEFAULT / 2; y < SCREEN_HEIGHT_DEFAULT; y++)
    {
        for (x = 0; x < SCREEN_WIDTH_DEFAULT; x++)
            mlx_put_pixel(game->img_scene, x, y, 0x00A000FF);
    }
}

void render_walls(t_game *game)
{
	int i = 0;
	t_wall_hit *walls = game->walls;
	render_floor_cell(game);
	while (i < SCREEN_WIDTH_DEFAULT)
	{
		float line_h = (TILE_SIZE * SCREEN_HEIGHT_DEFAULT) / walls[i].distance;
		int start_y = (SCREEN_HEIGHT_DEFAULT - round(line_h)) / 2;
		int end_y = start_y + round(line_h);
		if (start_y < 0)
			start_y = 0;
		if (end_y >= SCREEN_HEIGHT_DEFAULT)
			end_y = SCREEN_HEIGHT_DEFAULT - 1;
		// TODO add the texturing logic
		uint32_t wall_color;
		if (walls[i].texture_id == 0)
			wall_color = 0xFF8C00FF;
		if (walls[i].texture_id == 3)
			wall_color = 0xFF0000FF;
		if (walls[i].texture_id == 1)
			wall_color = 0xFF8C50FF;
		if (walls[i].texture_id == 2)
			wall_color = 0xFFAF00FF;
		for (int y = start_y; y <= end_y; y++)
			mlx_put_pixel(game->img_scene, i, y, wall_color);
		i++;
	}	
}
