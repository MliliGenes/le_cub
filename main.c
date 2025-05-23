#include "includes/func.h"

int main (int ac, char **av)
{
    if(ac != 2)
        return 0;
    char *path = av[1];
    if(!ft_check_dot(path))
        return 0;
    else
    {
        parse_map_file(path);
    }
}