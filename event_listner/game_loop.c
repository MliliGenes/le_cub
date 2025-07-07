/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: le-saad <le-saad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:12:31 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/07/07 13:34:05 by le-saad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

void load_frames(t_game *game, t_main_menu *param)
{
	param->frames[0] = mlx_load_png("imgs/main_menu/frame_1.png");
    param->frames[1] = mlx_load_png("imgs/main_menu/frame_2.png");
	param->frames[2] = mlx_load_png("imgs/main_menu/frame_3.png");
    param->frames[3] = mlx_load_png("imgs/main_menu/frame_4.png");
    param->frames[4] = mlx_load_png("imgs/main_menu/frame_5.png");
	param->img = NULL;
}

void	game_loop(t_game *game)
{
	t_main_menu frames;

	load_frames(game, &frames);
	game->frames = &frames;
	mlx_image_to_window(game->mlx, game->img_scene, 0, 0);
	mlx_image_to_window(game->mlx, game->img_minimap, MINIMAP_PADDING,
	MINIMAP_PADDING);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(game->mlx, SCREEN_WIDTH_DEFAULT / 2, SCREEN_HEIGHT_DEFAULT
		/ 2);
	game->start_game = false;
	mlx_loop_hook(game->mlx, event_listner, game);
	mlx_loop(game->mlx);
}
