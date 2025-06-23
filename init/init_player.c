#include "../include/init.h"

static void set_player_pov(t_player *player, char spawn)
{
	if (spawn == 'N')
		player->angle = deg_to_radian(90);
	if (spawn == 'S')
		player->angle = deg_to_radian(270);
	if (spawn == 'E')
		player->angle = deg_to_radian(0);
	if (spawn == 'W')
		player->angle = deg_to_radian(135);
}

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
	set_player_pov(player, map_data->player_dir);
	return (player);
}
