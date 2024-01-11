#include "../includes/malloc.h"

void	ft_itoa_fd(size_t nb, char base, int fd, _Bool prefix)
{
	char *str;

	str = "0123456789ABCDEFGHIJKLMNOPQRSTUIVWXYZ";
	if (nb / base)
		ft_itoa_fd(nb / base, base, fd, prefix);
	else if (prefix)
		write(fd, "0x", 2);
	write(fd, &str[nb % base], 1);
}