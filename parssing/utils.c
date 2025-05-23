#include "../includes/func.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		size;
	char	*ptr;

	i = 0;
	size = ft_strlen(s1) + 1;
	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int i;

	i = 0;
	while(n < i)
	{
		if(s1[i] != s2[i])
			return -1;
		i++;
	}
	return 0;
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	i;

	i = 0;
	if (!dst && !src)
		return (0);
	while (i < n)
	{
		*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
		i++;
	}
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}