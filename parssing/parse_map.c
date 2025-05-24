#include "../includes/func.h"

int find_map(char *ptr, int i)
{
    int j;
    while(ptr[i] && (ptr[i] != '0' && ptr[i] != '1' && ptr[i] != 'N' && ptr[i] != 'S' && ptr[i] != 'E' && ptr[i] != 'W' ))
        i++;
    j = i;
    while (ptr[j] != '\n')
        j--;
    return j + 1;
}

int ft_checking_nwl(char *ptr)
{
    char *start;
    int i;
    int j;
    int k;
    int len;

    i = 0;
    while(ptr[i])
    {
        j = i;
        while (ptr[j] && ptr[j] != '\n')
            j++;
        if(ptr[j] == '\n')
        {
            len = j - i;
            start = malloc(len + 1);
        }
            k = 0;
            while (len)
            {
                start[k] = ptr[j - len];
                len--;
                k++;
        }
        start[k] = '\0';
        if(start[0] == 'C' && start[1] == ' ')
            return find_map(ptr, j + 1);
        free(start);
        i = j + 1;
    }
    return 0;
}

int ft_check_emptyline(char *ptr, int *i)
{
    while (ptr[*i] && ptr[*i] != '\n' && (ptr[*i] == 32 || (ptr[*i] >= 9 && ptr[*i] <= 13)))
        (*i)++;
    if(ptr[*i] == '\n')
        return -1;
    return 1;
}

int ft_valide_lines(char *ptr)
{
    int i = 0;

    while (ptr[i])
    {
        if(ptr[i] == '\n')
        {
            i++;
            if(ft_check_emptyline(ptr, &i ) == -1)
                return -1;
        }
        i++;
    }
    return 1;
}

int    go_parse_lines(char **arr, char *ptr)
{
    parse *parse;
    int i;

    if(ft_strncmp(arr[0], "NO", 2) == -1)
        return 0;
    if(ft_strncmp(arr[1], "SO", 2) == -1)
        return 0;
    if(ft_strncmp(arr[2], "WE", 2) == -1)
        return 0;
    if(ft_strncmp(arr[3], "EA", 2) == -1)
        return 0;
    if(arr[4][0] != 'F')
        return 0;
    if(arr[5][0] != 'C')
        return 0;

    i = ft_checking_nwl(ptr);
    int b = ft_valide_lines(ptr + i);
    if(b == -1)
        return 0;
    parse = malloc(sizeof(*parse));
    parse->NO = malloc( ft_strlen(ft_strchr(arr[0],'.') + 2) + 1);
    parse->SO = malloc( ft_strlen(ft_strchr(arr[1],'.') + 2) + 1);
    parse->WE = malloc( ft_strlen(ft_strchr(arr[2],'.') + 2) + 1);
    parse->EA = malloc( ft_strlen(ft_strchr(arr[3],'.') + 2) + 1);
    ft_memcpy(parse->NO, ft_strchr(arr[0],'.') + 2, ft_strlen(ft_strchr(arr[0],'.') + 2) );
    ft_memcpy(parse->SO, ft_strchr(arr[1],'.') + 2, ft_strlen(ft_strchr(arr[1],'.') + 2));
    ft_memcpy(parse->WE, ft_strchr(arr[2],'.') + 2, ft_strlen(ft_strchr(arr[2],'.') + 2));
    ft_memcpy(parse->EA, ft_strchr(arr[3],'.') + 2, ft_strlen(ft_strchr(arr[3],'.') + 2));
    return 1;
}

void parse_map_file(char *path)
{
    char    *tet1;
    char    **arr;
    char    *tet;
    char    *ptr;
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
    if( go_parse_lines(arr,ptr) == 0)
    {
        printf("baaaaaaaaaaaaaaaaad =(\n");
        return ;
    }
}
