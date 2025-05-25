#include "../includes/func.h"

int ft_cheking_ns(int n_s, char **vv , char **bb)
{
    if(n_s != 2)
    {
        free(vv);
        free(bb);
        return -1;
    }
    return 1;
}

int ft_cheking_fc_utils(char **vv, char **bb)
{
    int i;
    int n_s;
    
    i = 0;
    n_s = 0;
    while (vv[1][i])
    {
        if(vv[1][i] == ',')
            n_s++;
        i++;
    }
    if(ft_cheking_ns(n_s,vv,bb) == -1)
        return -1;
    i = 0;
    n_s = 0;
    while (bb[1][i])
    {
        if(bb[1][i] == ',')
            n_s++;
        i++;
    }
    if(ft_cheking_ns(n_s,vv,bb) == -1)
        return -1;
    return 1;
}

int ft_cheking_fc(char **arr)
{
    char **vv;
    char **bb;

    if(ft_count(arr[4], ' ') != 2 || ft_count(arr[5], ' ') != 2)
        return -1;
    vv = ft_split(arr[4], ' ');
    bb = ft_split(arr[5], ' ');
    if(ft_cheking_fc_utils(vv,bb) == -1)
        return -1;
    free(vv);
    free(bb);
    return 1;
}

int ft_checking_the_four(char **arr)
{
    if(ft_strncmp(arr[0], "NO", 2) == -1)
        return -1;
    if(ft_strncmp(arr[1], "SO", 2) == -1)
        return -1;
    if(ft_strncmp(arr[2], "WE", 2) == -1)
        return -1;
    if(ft_strncmp(arr[3], "EA", 2) == -1)
        return -1;
    if(arr[4][0] != 'F')
        return -1;
    if(arr[5][0] != 'C')
        return -1;
    if(ft_cheking_nsew(arr) == -1)
        return -1;
    if(ft_cheking_fc(arr) == -1)
        return -1;
    return 1;
}

int first_line(char *map)
{
    int i;
    int size;

    size = 0;
    i = 0;
    while (map[size])
        size++;
    while(map[i] == 32 ||(map[i] >= 9 && map[i] <= 13))
        i++;
    size--;
    while(map[size] == 32 ||(map[size] >= 9 && map[size] <= 13))
        size--;
    while(i < size)
    {
        if(map[i] != '1' && map[i] != ' ')
            return -1;
        i++;
    }
    return 1;
}

int ft_checking_close_map(char **map)
{
    int i;
    int j;
    int size;

    if(first_line(map[0]) == -1)
        return -1;
    i = 1;
    while (map[i])
    {
        j = 0;
        while(map[i][j] == 32 ||(map[i][j] >= 9 && map[i][j] <= 13))
            j++;
        if(map[i][j] != '1')
            return -1;
        size = ft_strlen(map[i]) - 1;
        while(map[i][size] == 32 ||(map[i][size] >= 9 && map[i][size] <= 13))
            size--;
        if(map[i][size] != '1')
            return -1;
        while (j < size)
        {
            if(map[i][j] == '0')
            {
                if(map[i][j + 1] == ' ' || map[i][j - 1] == ' ' || map[i + 1][j] == ' ' || map[i - 1][j] == ' ')
                    return -1;
            }
            j++;
        }
        i++;
    }
    return 1;
}

parse   *go_parse_lines(char **arr, char *ptr)
{
    parse *parse;
    char    **map;
    int i;

    if(ft_checking_the_four(arr) == -1)
        return NULL;
    i = ft_checking_nwl(ptr);
    int b = ft_valide_lines(ptr + i);
    if(b == -1)
        return NULL;
    parse = malloc(sizeof(*parse));
    map = ft_split(ptr + i, '\n');
    if(ft_checking_close_map(map) == -1)
        return NULL;
    parse->NO = malloc( ft_strlen(ft_strchr(arr[0],'.') + 2) + 1);
    parse->SO = malloc( ft_strlen(ft_strchr(arr[1],'.') + 2) + 1);
    parse->WE = malloc( ft_strlen(ft_strchr(arr[2],'.') + 2) + 1);
    parse->EA = malloc( ft_strlen(ft_strchr(arr[3],'.') + 2) + 1);
    ft_memcpy(parse->NO, ft_strchr(arr[0],'.') + 2, ft_strlen(ft_strchr(arr[0],'.') + 2));
    ft_memcpy(parse->SO, ft_strchr(arr[1],'.') + 2, ft_strlen(ft_strchr(arr[1],'.') + 2));
    ft_memcpy(parse->WE, ft_strchr(arr[2],'.') + 2, ft_strlen(ft_strchr(arr[2],'.') + 2));
    ft_memcpy(parse->EA, ft_strchr(arr[3],'.') + 2, ft_strlen(ft_strchr(arr[3],'.') + 2));
    return parse;
}

void parse_map_file(char *path)
{
    char    *tet1;
    char    **arr;
    char    *tet;
    char    *ptr;
    parse   *parse;
    int     fd;

    fd = open(path, O_RDWR, 0777);
    if(fd < 0)
        return ;
    ptr = NULL;
    tet1 = get_next_line(fd);
	if (tet1 == NULL)
		return ;
    while (tet1 != NULL)
	{
		tet = ft_strdup(tet1);
		free(tet1);
		ptr = ft_strcat(ptr, tet);
		free(tet);
		tet1 = get_next_line(fd);
	}
	arr = ft_split(ptr, '\n');
	close(fd);
    parse = go_parse_lines(arr,ptr);
    if(!parse)
    {
        free(ptr);
        printf("baaaaaaaaaaaaaaaaad =(\n");
        return ;
    }
    free(ptr);
}
