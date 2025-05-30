#include "../include/init.h"

t_ray	*init_rays(void)
{
	t_ray	*rays;

	rays = malloc(sizeof(t_ray) * SCREEN_WIDTH_DEFAULT);
	if (!rays)
		return (NULL);
	return (rays);
}
