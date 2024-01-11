#include "../includes/malloc.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;

	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst == src)
		return ((unsigned char*)dst);
	if ((unsigned char*)dst > (unsigned char*)src)
		while (len-- > 0)
			((unsigned char*)dst)[len] = ((unsigned char*)src)[len];
	else
		while (i < len)
		{
			((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
			i++;
		}
	return ((unsigned char*)dst);
}
