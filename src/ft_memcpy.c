#include "../includes/ft_malloc.h"

void *ft_memcpy(void *dst, const void *src, size_t n)
{
    size_t	i;

    i = 0;
    if (src == NULL || dst == NULL)
        return (0);
    if (src == dst)
        return ((unsigned char*)dst);
    while (i < n)
    {
        ((unsigned char*)dst)[i] = ((const unsigned char*)src)[i];
        i++;
    }
    return (dst);
}
