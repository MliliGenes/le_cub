/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 21:11:00 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/29 21:11:01 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "dependencies.h"
# include "lib.h"
# include "structs.h"

t_map		*init_map(void);
t_player	*init_player(t_map *map_data);
t_ray		*init_rays(void);
t_wall_hit	*init_walls(void);
bool		init_game(t_game *game);

#endif