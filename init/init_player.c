#include "../include/init.h"

t_player	*init_player(t_map *map_data)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->move_speed = 2;
	player->rot_speed = 0.04;
	player->size_minimap = 4;
	player->pos = (t_vec2i){map_data->x_player * TILE_SIZE + PLAYER_SIZE / 2,
		map_data->y_player * TILE_SIZE + PLAYER_SIZE / 2};
	player->reminder = (t_vec2d){0, 0};
	player->forward_backward = 0;
	player->left_right = 0;
	player->angle = deg_to_radian(0);
	return (player);
}
