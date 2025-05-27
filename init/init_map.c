#include "../include/init.h"

char	**create_dynamic_map(void)
{
	char	*static_map[] = {"111111111111111111111", "100000000010000000001",
			"101111010010101111101", "101000010000100000101",
			"101011100111101110101", "101000000000000000101",
			"101111011111101111001", "100000000010000000001",
			"111111111111111111111", NULL};
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
    map->x_player = 5;
    map->y_player = 3;
    map->player_dir = 'E';
	return (map);
}
