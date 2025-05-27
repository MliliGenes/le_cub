#ifndef GAME_H
# define GAME_H

# include "structs.h"
# include "lib.h"

void	game_loop(t_game *game);
void	event_listner(void *params);

void	update_player(t_game *game);

#endif