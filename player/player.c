#include "../include/game.h"

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

static void	set_target_pos(mlx_t *mlx, t_player *player)
{
	player->forward = (t_vec2d){cos(player->angle) * player->forward_backward,
		sin(player->angle) * player->forward_backward};
	player->strafe = (t_vec2d){cos(player->angle + M_PI / 2)
		* player->left_right, sin(player->angle + M_PI / 2)
		* player->left_right};
    
}

void	update_player(t_game *game)
{
	update_player_data(game->mlx, game->player_data);
}
