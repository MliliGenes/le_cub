#ifndef LIB_H
# define LIB_H

# include "dependencies.h"
# include "structs.h"

double	deg_to_radian(double deg);
double	normalize_angle(double angle);
uint32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

#endif