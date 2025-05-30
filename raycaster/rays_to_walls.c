/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_to_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:47:30 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/30 17:39:53 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		walls[i].distance = rays[i].distance;
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
		if (rays[i].side_hit == 0)
			walls[i].texture_x_coord = rays[i].hit_point.y
				- floor(rays[i].hit_point.y);
		else
			walls[i].texture_x_coord = rays[i].hit_point.x
				- floor(rays[i].hit_point.x);
		if ((rays[i].side_hit == 0 && rays[i].dir.x > 0)
			|| (rays[i].side_hit == 1 && rays[i].dir.y < 0))
			walls[i].texture_x_coord = 1.0 - walls[i].texture_x_coord;
		i++;
	}
}
