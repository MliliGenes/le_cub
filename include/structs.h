/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: le-saad <le-saad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:29:07 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/31 15:55:40 by le-saad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "dependencies.h"

# define FOV 65
# define SCREEN_WIDTH_DEFAULT 1320
# define SCREEN_HEIGHT_DEFAULT 768
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64
# define TILE_SIZE 128
# define PLAYER_SIZE 2

# define GAME_TITLE "GAMI"

# define NORTH_WALL_COLOR 0xFF0000FF
# define SOUTH_WALL_COLOR 0xFF00FF00
# define EAST_WALL_COLOR 0xFFFF0000
# define WEST_WALL_COLOR 0xFFFFFF00
# define ERROR_WALL_COLOR 0xFF808080

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
	char			**map;
	int				x_player;
	int				y_player;
	int				width;
	int				height;
	char			player_dir;
	char			*north_texture_path;
	char			*south_texture_path;
	char			*east_texture_path;
	char			*west_texture_path;
	uint32_t		floor_color[3];
	uint32_t		ceiling_color[3];
}					t_map;

typedef struct s_utils
{
	char			**no;
	char			**so;
	char			**ea;
	char			**we;
}					t_utils;

typedef struct s_player
{
	t_vec2i			pos;
	int				forward_backward;
	int				left_right;
	t_vec2d			forward;
	t_vec2d			strafe;
	t_vec2d			reminder;
	double			angle;
	double			move_speed;
	double			rot_speed;
	int				size_minimap;
	mlx_image_t		*img;
}					t_player;

typedef struct s_ray
{
	double			angle;
	t_vec2d			dir;
	t_vec2d			hit_point;
	double			distance;
	t_vec2d			map_pixel_pos;
	t_vec2i			map_grid_pos;
	t_vec2d			delta_dist;
	t_vec2d			side_dist;
	t_vec2i			steps;
	int				side_hit;
}					t_ray;

// N = 0; E = 1; S = 2; W = 3
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
	t_map			*map_data;
	t_player		*player_data;
	t_ray			*rays;
	t_wall_hit		*walls;
	int				screen_width;
	int				screen_height;
	double			fov_rad;
	mlx_texture_t	*textures[4];
}					t_game;

#endif