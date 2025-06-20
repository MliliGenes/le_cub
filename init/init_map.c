#include "../include/init.h"

char	**create_dynamic_map(void)
{
	char *static_map[] =
	{
		"1111111111",
		"1000000001",
		"1000000001",
		"10000011111111",
		"10000000000001",
		"10000100011111",
		"10110110001",
		"1000010001",
		"1111111111",
		NULL
	};
	int		rows;
	char	**dynamic_map;

	rows = 0;
	while (static_map[rows] != NULL)
		rows++;
	dynamic_map = malloc((rows + 1) * sizeof(char *));
	if (!dynamic_map)
		return (NULL);
	for (int i = 0; i < rows; i++)
	{
		dynamic_map[i] = strdup(static_map[i]);
		if (!dynamic_map[i])
		{
			for (int j = 0; j < i; j++)
				free(dynamic_map[j]);
			free(dynamic_map);
			return (NULL);
		}
	}
	dynamic_map[rows] = NULL;
	return (dynamic_map);
}

t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->map = create_dynamic_map();
	map->x_player = 4;
	map->y_player = 3;
	map->player_dir = 'E';
	map->width = 14;
	map->height = 8;
	map->ceiling_color[0] = 135; // Red component
	map->ceiling_color[1] = 206; // Green component
	map->ceiling_color[2] = 235; // Blue component
	map->floor_color[0] = 255; // Red component
	map->floor_color[1] = 255; // Green component
	map->floor_color[2] = 255; // Blue component
	return (map);
}
