#ifndef FUNC_H
#define FUNC_H


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

size_t	ft_strlen(const char *s);
char	*ft_strrchr(const char *s, int c);
int ft_check_dot(char *path);

#endif