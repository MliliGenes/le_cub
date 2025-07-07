/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: le-saad <le-saad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:27:40 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/07/07 10:38:07 by le-saad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/init.h"

// TODO: free old items
void	*free_texture_array(uint32_t **arr, size_t height)
{
	size_t	k;

	if (!arr)
		return (NULL);
	k = 0;
	while (k < height)
		free(arr[k++]);
	free(arr);
	return (NULL);
}

uint32_t	**alloc_textures(mlx_texture_t *texture, t_texture *texture_data)
{
	size_t		h;
	size_t		w;
	uint32_t	**arr;
	size_t		j;

	if (!texture || !texture_data)
		return (NULL);
	texture_data->height = texture->height;
	texture_data->width = texture->width;
	h = texture->height;
	w = texture->width;
	arr = malloc((h + 1) * sizeof(uint32_t *));
	if (!arr)
		return (NULL);
	arr[h] = NULL;
	j = 0;
	while (j < h)
	{
		arr[j] = malloc(w * sizeof(uint32_t));
		if (!arr[j])
			return (free_texture_array(arr, j));
		j++;
	}
	return (arr);
}

uint32_t	get_pixel(const uint8_t *texture_pixels, size_t base_offset)
{
	t_pixel	pixel;

	pixel.r = texture_pixels[base_offset + 0];
	pixel.g = texture_pixels[base_offset + 1];
	pixel.b = texture_pixels[base_offset + 2];
	pixel.a = texture_pixels[base_offset + 3];
	return (ft_pixel(pixel.r, pixel.g, pixel.b, pixel.a));
}

void	fill_single_row_pixels(uint32_t *row_arr, mlx_texture_t *texture,
		size_t row_idx)
{
	size_t	x;
	size_t	base;

	x = 0;
	while (x < texture->width)
	{
		base = (row_idx * texture->width * 4) + (x * 4);
		row_arr[x] = get_pixel(texture->pixels, base);
		x++;
	}
}

void	mlx_text_to_arr(mlx_texture_t *texture, t_texture *texture_data)
{
	uint32_t	**arr;
	size_t		j;

	if (!texture || !texture_data)
		return ;
	arr = alloc_textures(texture, texture_data);
	if (!arr)
		return ;
	j = 0;
	while (j < texture->height)
	{
		fill_single_row_pixels(arr[j], texture, j);
		j++;
	}
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
	door = mlx_load_png("imgs/door.png");
	if (!north || !south || !west || !east || !door)
		return (false);
	mlx_text_to_arr(north, &game->walls_textures[0]);
	mlx_text_to_arr(south, &game->walls_textures[1]);
	mlx_text_to_arr(west, &game->walls_textures[2]);
	mlx_text_to_arr(east, &game->walls_textures[3]);
	mlx_text_to_arr(door, &game->walls_textures[4]);
	return (true);
}
