#include "../include/game.h"

void game_loop(t_game *game)
{
    mlx_loop_hook(game->mlx, event_listner, game);
    mlx_loop(game->mlx);
}
