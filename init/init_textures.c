#include "../include/init.h"

// TODO: free old items

uint32_t **mlx_text_to_arr(mlx_texture_t *texture)
{
    if (!texture)
        return NULL;

    size_t h = texture->height;
    size_t w = texture->width;
    size_t bpp = texture->bytes_per_pixel;

    uint32_t **arr = malloc((h + 1) * sizeof(*arr));
    if (!arr)
        return NULL;

    size_t j = 0;
    while (j < h)
    {
        uint32_t *row = malloc(w * sizeof *row);
        if (!row)
        {
            size_t k = 0;
            while (k < j)
                free(arr[k++]);
            free(arr);
            return NULL;
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
    return arr;
}


bool init_textures(t_game *game)
{
    t_map *map = game->map_data;
    if (map->north_texture_path)
        game->walls_textures[0].arr = mlx_text_to_arr(mlx_load_png(map->north_texture_path));
    if (map->east_texture_path)
    game->walls_textures[1].arr = mlx_text_to_arr(mlx_load_png(map->east_texture_path));
    if (map->south_texture_path)
    game->walls_textures[2].arr = mlx_text_to_arr(mlx_load_png(map->south_texture_path));
    if (map->west_texture_path)
    game->walls_textures[3].arr = mlx_text_to_arr(mlx_load_png(map->west_texture_path));
    return true;
}