#include "includes/parsing.h"

int	main(int ac, char **av)
{
	t_map *parse;

	if (ac != 2)
		return (0);
	char *path = av[1];
	if (!ft_check_dot(path))
	{
		printf("Invalide file format\n");
		return (0);
	}
	else
	{
		parse = parse_map_file(path);
		printf("%d\n", parse->floor_color[2]);
		// ft_freeing(parse->map);
		// free(parse->north_texture_path);
		// free(parse->south_texture_path);
		// free(parse->east_texture_path);
		// free(parse->west_texture_path);
		// free(parse);
	}
	// while(1);
}