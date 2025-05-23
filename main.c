#include "includes/func.h"

int main (int ac, char **av)
{
    if(ac != 2)
        return 0;
    char *path = av[1];
    if(!ft_check_dot(path))
        printf("badddd\n");
    else
        printf("good\n");
}