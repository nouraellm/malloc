#include "../includes/ft_malloc.h"

char *ft_strcpy(char *dst, const char *src)
{
    if (dst == NULL || src == NULL)
        return NULL;

    int i;

    i = 0;
    while (src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return (dst);
}
