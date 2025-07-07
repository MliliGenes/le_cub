/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: le-saad <le-saad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 02:39:42 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/07/07 14:25:27 by le-saad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

t_wall_render calculate_wall_height(t_game *game, double distance)
{
    t_wall_render render;
    
    render.line_h = (SCREEN_HEIGHT_DEFAULT * 1.2) / distance;
    render.start_y = (game->screen_height - (int)render.line_h) / 2;
    render.end_y = render.start_y + (int)render.line_h;
    if (render.start_y < 0)
        render.start_y = 0;
    if (render.end_y >= game->screen_height)
        render.end_y =  game->screen_height - 1;
    return render;
}

int calculate_texture_x(double texture_x_coord, int tex_width)
{
    int tex_x = (int)(texture_x_coord * (double)tex_width);
    tex_x = tex_x < 0 ? 0 : tex_x;
    tex_x = tex_x >= tex_width ? tex_width - 1 : tex_x;
    return tex_x;
}

void calculate_texture_stepping(t_wall_render *render, t_game *game, int tex_height)
{
    render->step = (double)tex_height / render->line_h;
    render->tex_pos = (render->start_y - game->screen_height / 2.0 + render->line_h / 2.0) * render->step;
}

void draw_wall_column(t_game *game, t_wall_render *render, t_texture *tex, int column_x)
{
    int y;

    y = render->start_y;
    while (y <= render->end_y)
    {
        int tex_y = (int)render->tex_pos;
        tex_y = tex_y < 0 ? 0 : tex_y;
        tex_y = tex_y >= (int)tex->height ? tex->height - 1 : tex_y;

        uint32_t color = tex->arr[tex_y][render->tex_x];
        mlx_put_pixel(game->img_scene, column_x, y, color);
        render->tex_pos += render->step;
        y++;
    }
}

void render_walls(t_game *game)
{
    int i = 0;
    t_wall_hit *walls = game->walls;
    render_floor_cell(game);

    while (i < game->screen_width)
    {
        t_wall_hit hit = walls[i];
        if (hit.texture_id < 0 || hit.texture_id >= 5) {
            i++;
            continue;
        }

        t_texture *tex = &game->walls_textures[hit.texture_id];
        if (!tex || !tex->arr) {
            i++;
            continue;
        }
        t_wall_render render = calculate_wall_height(game, hit.distance);
        render.tex_x = calculate_texture_x(hit.texture_x_coord, tex->width);
        calculate_texture_stepping(&render, game, tex->height);
        draw_wall_column(game, &render, tex, i);
        i++;
    }
}
