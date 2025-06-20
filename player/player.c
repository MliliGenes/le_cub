/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 02:38:59 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/06/20 10:06:58 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

static bool	is_wall(t_map *map, int x, int y)
{
	return (map->map[y / TILE_SIZE][x / TILE_SIZE] == '1');
}

static bool	check_collision(t_map *map, t_vec2i pos)
{
	return (is_wall(map, pos.x, pos.y) || is_wall(map, pos.x + PLAYER_SIZE - 1,
			pos.y) || is_wall(map, pos.x, pos.y + PLAYER_SIZE - 1)
		|| is_wall(map, pos.x + PLAYER_SIZE - 1, pos.y + PLAYER_SIZE - 1));
}

static void	update_player_data(mlx_t *mlx, t_player *player)
{
	t_vec2i	mouse;
	t_vec2i	center;
	float	mouse_sensitivity;
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
	mouse_sensitivity = 0.02f;
	player->angle += (mouse.x - center.x) * player->rot_speed
		* mouse_sensitivity;
	mlx_set_mouse_pos(mlx, center.x, center.y);
	if (mlx_is_key_down(mlx, MLX_KEY_W) || mlx_is_key_down(mlx, MLX_KEY_UP))
		player->forward_backward = player->move_speed;
	if (mlx_is_key_down(mlx, MLX_KEY_S) || mlx_is_key_down(mlx, MLX_KEY_DOWN))
		player->forward_backward = -player->move_speed;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		player->left_right = player->move_speed;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		player->left_right = -player->move_speed;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player->angle -= player->rot_speed;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player->angle += player->rot_speed;
	player->angle = normalize_angle(player->angle);
}

static t_vec2d	calc_target_pos(t_player *player)
{
	t_vec2d	total;

	player->forward = (t_vec2d){cos(player->angle) * player->forward_backward,
		sin(player->angle) * player->forward_backward};
	player->strafe = (t_vec2d){cos(player->angle + M_PI / 2)
		* player->left_right, sin(player->angle + M_PI / 2)
		* player->left_right};
	total = (t_vec2d){player->forward.x + player->strafe.x + player->reminder.x,
		player->forward.y + player->strafe.y + player->reminder.y};
	return (total);
}

void	update_player(t_game *game)
{
	t_player	*player;
	t_vec2d		total;
	t_vec2i		move;
	t_vec2i		target;

	player = game->player_data;
	update_player_data(game->mlx, game->player_data);
	total = calc_target_pos(game->player_data);
	move = (t_vec2i){round(total.x), round(total.y)};
	target = (t_vec2i){player->pos.x + move.x, player->pos.y + move.y};
	if (!check_collision(game->map_data, (t_vec2i){target.x, player->pos.y}))
	{
		player->pos.x = target.x;
		player->reminder.x = total.x - move.x;
	}
	else
		player->reminder.x = 0;
	if (!check_collision(game->map_data, (t_vec2i){player->pos.x, target.y}))
	{
		player->pos.y = target.y;
		player->reminder.y = total.y - move.y;
	}
	else
		player->reminder.y = 0;
}
