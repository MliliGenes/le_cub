#include "../include/init.h"

t_player	*init_player(t_map *map_data)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->move_speed = 17.5;
	player->rot_speed = 0.04;
	player->size_minimap = 4;
	player->pos = (t_vec2i){map_data->x_player * TILE_SIZE,
		map_data->y_player * TILE_SIZE};
	player->forward_backward = 0;
	player->left_right = 0;
	player->angle = deg_to_radian(90);
	return (player);
}
