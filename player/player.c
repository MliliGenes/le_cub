#include "../include/game.h"

static bool	check_collision(t_map *map, t_vec2i pos)
{
	return (map->map[pos.y / TILE_SIZE][pos.x / TILE_SIZE] == '1'
		|| map->map[(pos.y + PLAYER_SIZE - 1) / TILE_SIZE][pos.x
		/ TILE_SIZE] == '1' || map->map[pos.y / TILE_SIZE][(pos.x + PLAYER_SIZE
			- 1) / TILE_SIZE] == '1' || map->map[(pos.y + PLAYER_SIZE - 1)
		/ TILE_SIZE][(pos.x + PLAYER_SIZE - 1) / TILE_SIZE] == '1');
}

static void	update_player_data(mlx_t *mlx, t_player *player)
{
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

static void	set_target_pos(mlx_t *mlx, t_map *map, t_player *player)
{
	t_vec2d	total;
	t_vec2i	move;
	t_vec2i	target;

	player->forward = (t_vec2d){cos(player->angle) * player->forward_backward,
		sin(player->angle) * player->forward_backward};
	player->strafe = (t_vec2d){cos(player->angle + M_PI / 2)
		* player->left_right, sin(player->angle + M_PI / 2)
		* player->left_right};
	total = (t_vec2d){player->forward.x + player->strafe.x + player->reminder.x,
		player->forward.y + player->strafe.y + player->reminder.y};
	move = (t_vec2i){round(total.x), round(total.y)};
	target = (t_vec2i){player->pos.x + move.x, player->pos.y + move.y};
	if (check_collision(map, (t_vec2i){target.x, player->pos.y}))
		player->pos.x = target.x;
	if (check_collision(map, (t_vec2i){player->pos.y, target.y}))
		player->pos.y = target.y;
}

void	update_player(t_game *game)
{
	update_player_data(game->mlx, game->player_data);
	set_target_pos(game->mlx, game->map_data, game->player_data);
}
