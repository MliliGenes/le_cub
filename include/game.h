#ifndef GAME_H
#define GAME_H

#include "lib.h"
#include "structs.h"

void game_loop(t_game *game);
void event_listner(void *params);

void update_player(t_game *game);
void mouse_eventlistner(t_game *game);
void cast_rays(t_game *game);
void dda_loop(t_game *game, t_ray *ray);
void rays_to_walls(t_game *game);

void render_floor_cell(t_game *game);
void render_walls(t_game *game);

void render_minimap(t_game *game);
void reset_minimap(t_game *game);
void render_world_on_minimap(t_game *game);
void draw_player(mlx_image_t *minimap);
void draw_dir(mlx_image_t *minimap, t_player *p, t_vec2i pos);

#endif