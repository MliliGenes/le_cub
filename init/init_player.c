#include "../include/init.h"

static void	set_player_pov(t_player *player, char spawn)
{
	if (spawn == 'N')
		player->angle = deg_to_radian(90);
	if (spawn == 'S')
		player->angle = deg_to_radian(270);
	if (spawn == 'E')
		player->angle = deg_to_radian(0);
	if (spawn == 'W')
		player->angle = deg_to_radian(180);
}

t_player	*init_player(t_map *map_data)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	ft_memset(player, 0, sizeof(t_player));
	player->move_speed = 20;
	player->rot_speed = 0.03;
	player->pos = (t_vec2i){
		map_data->x_player * TILE_SIZE + TILE_SIZE / 2,
		map_data->y_player * TILE_SIZE + TILE_SIZE / 2,
	};
	player->forward_backward = 0;
	player->left_right = 0;
	set_player_pov(player, map_data->player_dir);
	return (player);
}
