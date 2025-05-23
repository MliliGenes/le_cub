#include "../includes/func.h"

void    go_parse_lines(char **arr)
{
    parse *parse;

    
    if(ft_strncmp(arr[0], "NO", 2) == -1)
        return ;
    if(ft_strncmp(arr[1], "SO", 2) == -1)
        return ;
    if(ft_strncmp(arr[2], "WE", 2) == -1)
        return ;
    if(ft_strncmp(arr[3], "EA", 2) == -1)
        return ;
    parse = malloc(sizeof(parse));
    parse->NO = malloc( ft_strlen(ft_strchr(arr[0],'.')) + 2);
    parse->SO = malloc( ft_strlen(ft_strchr(arr[1],'.')) + 2);
    parse->WE = malloc( ft_strlen(ft_strchr(arr[2],'.')) + 2);
    parse->EA = malloc( ft_strlen(ft_strchr(arr[3],'.')) + 2);
    ft_memcpy(parse->NO, ft_strchr(arr[0],'.') + 2, ft_strlen(ft_strchr(arr[0],'.') + 2));
    ft_memcpy(parse->SO, ft_strchr(arr[1],'.') + 2, ft_strlen(ft_strchr(arr[1],'.') + 2));
    ft_memcpy(parse->WE, ft_strchr(arr[2],'.') + 2, ft_strlen(ft_strchr(arr[2],'.') + 2));
    ft_memcpy(parse->EA, ft_strchr(arr[3],'.') + 2, ft_strlen(ft_strchr(arr[3],'.') + 2));
}

void parse_map_file(char *path)
{
    size_t size;
    char    *tet1;
    char    **arr;
    char    *tet;
    char    *ptr;
    int     fd;

    fd = open(path, O_RDWR, 0777);
    if(fd < 0)
        return ;
    ptr = NULL;
    size = 0;
    tet1 = get_next_line(fd);
	if (tet1 == NULL)
		return ;
    while (tet1 != NULL)
	{
        size++;
		tet = ft_strdup(tet1);
		free(tet1);
		ptr = ft_strcat(ptr, tet);
		free(tet);
		tet1 = get_next_line(fd);
	}
    // printf("%s", ptr);
	arr = ft_split(ptr, '\n');
    free(ptr);
	close(fd);
    go_parse_lines(arr);
}
