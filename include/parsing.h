#ifndef PARSING_H
# define PARSING_H

#include "structs.h"



size_t			ft_strlen(const char *s);
char			*ft_strnstr(const char *hay, const char *need, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);
char			*ft_strchr(const char *s, int c);
int				find_map(char *ptr, int i);
int				ft_cheking_nsew(char **arr);
int				ft_checking_nwl(char *ptr);
int				ft_check_emptyline(char *ptr, int *i);
int				ft_valide_lines(char *ptr);
int				ft_count(char const *str, char c);
int				ft_atoi(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strrchr(const char *s, int c);
int				ft_check_dot(char *path);
void			allocation_manager(int fd, char **save);
int				ft_newline_check(char *string);
void			*ft_cpy(char *string, char *string1, int n);
void			ft_freeing(char **arr);
char			*ft_strcat(char *string1, char *string2);
int				ft_sstrlen(char *string);
char			*get_next_line(int fd);
t_map			*parse_map_file(char *path);
char			**ft_split(char const *s, char c);
int				ft_checking_the_four(char **arr);
int				ft_cheking_fc(char **arr);
int				ft_cheking_fc_utils(char **vv, char **bb);
int				ft_cheking_ns(int n_s, char **vv, char **bb);
char			*ft_strdup(const char *s1);

#endif