#include "../include/init.h"

t_wall_hit	*init_walls(void)
{
	t_wall_hit *walls;

	walls = malloc(sizeof(t_ray) * SCREEN_WIDTH_DEFAULT);
	if (!walls)
		return (NULL);
	return (walls);
}
