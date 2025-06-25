#include "../include/init.h"

// TODO: free old items
void	free_texture_array(uint32_t **arr, size_t height)
{
	size_t	k;

	if (!arr)
		return;
	k = 0;
	while (k < height)
		free(arr[k++]);
	free(arr);
}

void	mlx_text_to_arr(mlx_texture_t *texture, t_texture *texture_data) 
{
	if (!texture || !texture_data)
		return;

	texture_data->height = texture->height;
	texture_data->width = texture->width;
	
	size_t h = texture->height;
	size_t w = texture->width;
	size_t bpp = texture->bytes_per_pixel;

	uint32_t **arr = malloc((h + 1) * sizeof(*arr));
	if (!arr)
		return;

	size_t j = 0;
	while (j < h)
	{
		uint32_t *row = malloc(w * sizeof *row);
		if (!row)
		{
			free_texture_array(arr, j);
			return;
		}
		size_t idx = j * w * bpp;
		size_t x = 0;
		while (x < w)
		{
			size_t base = idx + x * bpp;
			uint8_t r = texture->pixels[base + 0];
			uint8_t g = texture->pixels[base + 1];
			uint8_t b = texture->pixels[base + 2];
			uint8_t a = texture->pixels[base + 3];
			row[x] = ft_pixel(r, g, b, a);
			x++;
		}
		arr[j] = row;
		j++;
	}
	arr[h] = NULL;
	texture_data->arr = arr;
}

bool	init_textures(t_game *game)
{
	t_map *map = game->map_data;
	
	mlx_texture_t *north = mlx_load_png(map->north_texture_path);
	mlx_texture_t *south = mlx_load_png(map->south_texture_path);
	mlx_texture_t *west = mlx_load_png(map->west_texture_path);
	mlx_texture_t *east = mlx_load_png(map->east_texture_path);
	
	if (!north || !south || !west || !east)
		return (false);
	
	mlx_text_to_arr(north, &game->walls_textures[0]);
	mlx_text_to_arr(south, &game->walls_textures[1]);
	mlx_text_to_arr(west, &game->walls_textures[2]);
	mlx_text_to_arr(east, &game->walls_textures[3]);
	
	mlx_delete_texture(north);
	mlx_delete_texture(south);
	mlx_delete_texture(west);
	mlx_delete_texture(east);
	
	return (true);
}