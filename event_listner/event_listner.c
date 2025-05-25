#include "../include/game.h"

void	event_listner(void *params)
{
	t_game *game;

	game = (t_game *)params;
    update_player(game);
    // cast_rays(game);
    // set_walls();
}
