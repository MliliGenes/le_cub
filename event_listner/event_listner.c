/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: le-saad <le-saad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:23:23 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/07/07 13:33:38 by le-saad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

bool	player_in_door_tile(t_game *game, t_player *player)
{
	return (game->map_data->map[player->pos.y / TILE_SIZE][player->pos.x
		/ TILE_SIZE] != 'D' && game->map_data->map[player->pos.y
		/ TILE_SIZE][player->pos.x / TILE_SIZE] != 'O');
}

void next_frame(t_game *game)
{
	static int index = 0;
	static int count = 0;
	static int step = 1;

	if (count >= 8)
	{
		if (index == 4)
			step = -1;
		if (index == 0)
			step = 1;
		index += step;
		count = 0;	
	}
	count ++;
	mlx_delete_image(game->mlx, game->frames->img);
	if (game->frames->frames[index])
	{		
		game->frames->img = mlx_texture_to_image(game->mlx, game->frames->frames[index]);
		mlx_image_to_window(game->mlx, game->frames->img, 0, 0);
	}
}

void free_frames(t_main_menu *frames)
{
	int i = 0;
	while (i < 5)
	{
		if (frames->frames[i])
		{
			mlx_delete_texture(frames->frames[i]);
			frames->frames[i] = NULL;
		}
		i++;
	}
}

void	event_listner(void *params)
{
	t_game		*game;
	t_player	*player;
	bool		e_key_down;

	game = (t_game *)params;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ENTER))
		game->start_game = true;
	if (!game->start_game)
	{
		next_frame(game);
		return;
	}
	mlx_delete_image(game->mlx, game->frames->img);
	free_frames(game->frames);
	player = game->player_data;
	update_player(game);
	e_key_down = mlx_is_key_down(game->mlx, MLX_KEY_E);
	if (e_key_down && game->e_key_was_up && player_in_door_tile(game, player))
		handle_door_interaction(game);
	game->e_key_was_up = !e_key_down;
	cast_rays(game);
	rays_to_walls(game);
	render_walls(game);
	render_minimap(game);
}
