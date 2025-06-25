#include "../include/init.h"

t_ray	*init_rays(void)
{
	t_ray	*rays;
	int		i;

	i = 0;
	rays = malloc(sizeof(t_ray) * SCREEN_WIDTH_DEFAULT);
	if (!rays)
		return (NULL);
	ft_memset(rays, 0, sizeof(t_ray) * SCREEN_WIDTH_DEFAULT);
	return (rays);
}
