/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mlil <sel-mlil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:27:40 by sel-mlil          #+#    #+#             */
/*   Updated: 2025/07/06 10:13:52 by sel-mlil         ###   ########.fr       */
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

// Function 1: Allocates the 2D array structure (array of row pointers and each row)
uint32_t	**init_texture(mlx_texture_t *texture, t_texture *texture_data)
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
		{
			free_texture_array(arr, j);
			return (NULL);
		}
		j++;
	}
	return (arr);
}

// Function 2: Extracts RGBA components for a single pixel at a given offset
t_pixel	get_pixel(const uint8_t *texture_pixels, size_t base_offset)
{
	t_pixel	pixel;

	pixel.r = texture_pixels[base_offset + 0];
	pixel.g = texture_pixels[base_offset + 1];
	pixel.b = texture_pixels[base_offset + 2];
	pixel.a = texture_pixels[base_offset + 3];
	return (pixel);
}

// Function 3: Fills a single row of the 2D array with pixel data
void	fill_single_row_pixels(uint32_t *row_arr, mlx_texture_t *texture,
		size_t row_idx)
{
	size_t	x;
	size_t	base;
	t_pixel	components;

	x = 0;
	while (x < texture->width)
	{
		base = (row_idx * texture->width * texture->bytes_per_pixel) + (x
				* texture->bytes_per_pixel);
		components = get_pixel(texture->pixels, base);
		row_arr[x] = ft_pixel(components.r, components.g, components.b,
				components.a);
		x++;
	}
}

void	fill_all_rows(uint32_t **arr, mlx_texture_t *texture)
{
	size_t	j;

	j = 0;
	while (j < texture->height)
	{
		fill_single_row_pixels(arr[j], texture, j);
		j++;
	}
}

// Original function, now acting as the main orchestrator
void	mlx_text_to_arr(mlx_texture_t *texture, t_texture *texture_data)
{
	uint32_t	**arr;

	if (!texture || !texture_data)
		return ;
	arr = init_texture(texture, texture_data);
	if (!arr)
		return ;
	fill_all_rows(arr, texture);
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
	door = mlx_load_png("metal_door.png");
	if (!north || !south || !west || !east || !door)
		return (false);
	mlx_text_to_arr(north, &game->walls_textures[0]);
	mlx_text_to_arr(south, &game->walls_textures[1]);
	mlx_text_to_arr(west, &game->walls_textures[2]);
	mlx_text_to_arr(east, &game->walls_textures[3]);
	mlx_text_to_arr(door, &game->walls_textures[4]);
	return (true);
}
