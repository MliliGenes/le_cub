/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:27:40 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/07/04 19:05:56 by sel-mlil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/init.h"

// TODO: free old items
void	free_texture_array(uint32_t **arr, size_t height)
{
	size_t	k;

	if (!arr)
		return ;
	k = 0;
	while (k < height)
		free(arr[k++]);
	free(arr);
}

void	mlx_text_to_arr(mlx_texture_t *texture, t_texture *texture_data)
{
	size_t		h;
	size_t		w;
	size_t		bpp;
	uint32_t	**arr;
	size_t		j;
	uint32_t	*row;
	size_t		idx;
	size_t		x;
	size_t		base;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;

	if (!texture || !texture_data)
		return ;
	texture_data->height = texture->height;
	texture_data->width = texture->width;
	h = texture->height;
	w = texture->width;
	bpp = texture->bytes_per_pixel;
	arr = malloc((h + 1) * sizeof(*arr));
	if (!arr)
		return ;
	j = 0;
	while (j < h)
	{
		row = malloc(w * sizeof *row);
		if (!row)
		{
			free_texture_array(arr, j);
			return ;
		}
		idx = j * w * bpp;
		x = 0;
		while (x < w)
		{
			base = idx + x * bpp;
			r = texture->pixels[base + 0];
			g = texture->pixels[base + 1];
			b = texture->pixels[base + 2];
			a = texture->pixels[base + 3];
			row[x] = ft_pixel(r, g, b, a);
			x++;
		}
		arr[j] = row;
		j++;
	}
	arr[h] = NULL;
	texture_data->arr = arr;
	mlx_delete_texture(texture);
}

bool	init_textures(t_game *game)
{
	t_map			*map;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	mlx_texture_t	*door;

	map = game->map_data;
	north = mlx_load_png(map->north_texture_path);
	south = mlx_load_png(map->south_texture_path);
	west = mlx_load_png(map->west_texture_path);
	east = mlx_load_png(map->east_texture_path);
	door = mlx_load_png("imgs/metal_door.png");
	if (!north || !south || !west || !east || !door)
		return (false);
	mlx_text_to_arr(north, &game->walls_textures[0]);
	mlx_text_to_arr(south, &game->walls_textures[1]);
	mlx_text_to_arr(west, &game->walls_textures[2]);
	mlx_text_to_arr(east, &game->walls_textures[3]);
	mlx_text_to_arr(door, &game->walls_textures[4]);
	return (true);
}
