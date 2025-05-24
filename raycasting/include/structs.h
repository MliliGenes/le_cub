/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:29:07 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/24 13:29:56 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "MLX42.h"
# include <stdbool.h>

# define SCREEN_WIDTH_DEFAULT 1024
# define SCREEN_HEIGHT_DEFAULT 768
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

typedef struct s_vec2d
{
	double			x;
	double			y;
}					t_vec2d;

typedef struct s_vec2i
{
	int				x;
	int				y;
}					t_vec2i;

typedef struct s_map
{
	char			**grid;
	int				width;
	int				height;
	int				tile_size;
	char			*north_texture_path;
	char			*south_texture_path;
	char			*east_texture_path;
	char			*west_texture_path;
	uint32_t		floor_color;
	uint32_t		ceiling_color;
}					t_map;

typedef struct s_player
{
	t_vec2d			pos;
	t_vec2d			dir;
	t_vec2d			plane;
	double			angle;
	double			move_speed;
	double			rot_speed;
	int				size_minimap;
	t_vec2d			reminder;
}					t_player;

typedef struct s_ray
{
	t_vec2d			dir;
	double			camera_x;
	t_vec2i			map_pos;
	t_vec2d			side_dist;
	t_vec2d			delta_dist;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	bool			hit;
	int				side_hit;
	double			wall_x_tex;
	int				tex_num;
}					t_ray;

typedef struct s_wall_hit
{
	double			distance;
	t_vec2d			hit_point;
	int				side;
	char			type;
	double			texture_x_coord;
	int				texture_id;
}					t_wall_hit;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img_scene;
	mlx_image_t		*img_minimap;
	t_map			map_data;
	t_player		player_data;
	int				screen_width;
	int				screen_height;
	double			fov_rad;
	mlx_texture_t	*textures[4];
}					t_game;

#endif