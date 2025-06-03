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
	player->forward_backward = 0;
	player->left_right = 0;
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
	total = (t_vec2d){player->forward.x + player->strafe.x,
		player->forward.y + player->strafe.y};
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
	
	// Multiply by 10 for fixed-point precision
	move = (t_vec2i){round(total.x * 10), round(total.y * 10)};
	target = (t_vec2i){player->pos.x * 10 + move.x, player->pos.y * 10 + move.y};
	
	// Check X movement (divide by 10 for actual position)
	if (!check_collision(game->map_data, (t_vec2i){target.x / 10, player->pos.y}))
		player->pos.x = target.x / 10;
	
	// Check Y movement (divide by 10 for actual position)
	if (!check_collision(game->map_data, (t_vec2i){player->pos.x, target.y / 10}))
		player->pos.y = target.y / 10;
}