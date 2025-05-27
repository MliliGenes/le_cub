#ifndef INIT_H
# define INIT_H

# include "dependencies.h"
# include "lib.h"
# include "structs.h"

t_map		*init_map(void);
t_player	*init_player(t_map *map_data);
bool		init_game(t_game *game);

#endif