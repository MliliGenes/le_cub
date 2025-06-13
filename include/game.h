#ifndef GAME_H
# define GAME_H

# include "lib.h"
# include "structs.h"

void	game_loop(t_game *game);
void	event_listner(void *params);

void	update_player(t_game *game);
void	cast_rays(t_game *game);
void	rays_to_walls(t_game *game);

void	render_floor_cell(t_game *game);
void	render_walls(t_game *game);

#endif