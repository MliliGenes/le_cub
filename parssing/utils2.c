#include "../includes/parsing.h"

void ft_freeing(char **arr)
{
    int i;

    i = 0;
    while(arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}