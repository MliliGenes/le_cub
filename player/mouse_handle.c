/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: le-saad <le-saad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 23:15:33 by le-saad           #+#    #+#             */
/*   Updated: 2025/07/01 23:15:34 by le-saad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

void mouse_eventlistner(t_game *game)
{
    t_vec2i mouse;
    t_vec2i center;
    t_player *player = game->player_data;
    mlx_t *mlx = game->mlx;
    static int start = 2;

    player->forward_backward = 0;
    player->left_right = 0;
    center.x = mlx->width / 2;
    center.y = mlx->height / 2;
    mouse.x = mlx->width / 2;
    mouse.y = mlx->height / 2;
    if (!start)
        mlx_get_mouse_pos(mlx, &(mouse.x), &(mouse.y));
    else
        start--;
    float mouse_sensitivity = 0.02f;
    player->angle += (mouse.x - center.x) * player->rot_speed * mouse_sensitivity;
    mlx_set_mouse_pos(mlx, center.x, center.y);
}
