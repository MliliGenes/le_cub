/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:29:07 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/05/27 21:28:51 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "dependencies.h"

# define SCREEN_WIDTH_DEFAULT 1024
# define SCREEN_HEIGHT_DEFAULT 768
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64
# define TILE_SIZE 64
# define PLAYER_SIZE 4

# define GAME_TITLE "GAMI"

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
}					t_player;

typedef struct s_ray
{
	t_vec2d			dir;
	t_vec2i			map_pos;
	t_vec2i			side_dist;
	t_vec2d			delta_dist;
	double			perp_wall_dist;
	t_vec2i			steps;
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
	t_map			*map_data;
	t_player		*player_data;
	int				screen_width;
	int				screen_height;
	double			fov_rad;
	mlx_texture_t	*textures[4];
}					t_game;

#endif