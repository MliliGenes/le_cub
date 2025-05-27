#include "../include/game.h"

void	game_loop(t_game *game)
{
	int			start_x;
	int			start_y;
	mlx_image_t	*player;

    // DEBUG
	start_x = 5 * TILE_SIZE - PLAYER_SIZE / 2;
	start_y = 3 * TILE_SIZE - PLAYER_SIZE / 2;
	player = mlx_new_image(game->mlx, PLAYER_SIZE, PLAYER_SIZE);
	for (int y = 0; y < PLAYER_SIZE; y++)
	{
		for (int x = 0; x < PLAYER_SIZE; x++)
		{
			mlx_put_pixel(player, x, y, 0x00FF00FF);
		}
	}
	mlx_image_to_window(game->mlx, player, start_x + TILE_SIZE / 2, start_y
		+ TILE_SIZE / 2);
    game->player_data->img = player;

	mlx_loop_hook(game->mlx, event_listner, game);
	mlx_loop(game->mlx);
}
