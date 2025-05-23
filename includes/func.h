#ifndef FUNC_H
#define FUNC_H


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <fcntl.h>

typedef struct  parse_elements
{
    char **map;
    char *NO;
    char *SO;
    char *WE;
    char *EA;
} parse;

size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strchr(const char *s, int c);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
int ft_check_dot(char *path);
void	allocation_manager(int fd, char **save);
int	ft_newline_check(char *string);
void	*ft_cpy(char *string, char *string1, int n);
char	*ft_strcat(char *string1, char *string2);
int	ft_sstrlen(char *string);
char	*get_next_line(int fd);
void parse_map_file(char *path);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);

#endif