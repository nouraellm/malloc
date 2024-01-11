#include "../includes/malloc.h"

void	*ft_memset(void *b, int c, size_t len)
{
	int	i;

	i = 0;
	while (i < (int)len)
	{
		((char*)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
