#include "../include/game.h"

void mouse_eventlistner(t_game *game)
{
    t_vec2i mouse;
    t_vec2i center;
    t_player *player = game->player_data;
    mlx_t *mlx = game->mlx;

    player->forward_backward = 0;
    player->left_right = 0;
    center.x = mlx->width / 2;
    center.y = mlx->height / 2;
    mlx_get_mouse_pos(mlx, &(mouse.x), &(mouse.y));
    float mouse_sensitivity = 0.02f;
    player->angle += (mouse.x - center.x) * player->rot_speed * mouse_sensitivity;
    mlx_set_mouse_pos(mlx, center.x, center.y);
}