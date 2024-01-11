#include "../includes/malloc.h"

void	ft_itoa_base(size_t nb, char base, char length, _Bool prefix)
{
	char	*str;

	str = "0123456789ABCDEFGHIJKLMNOPQRSTUIVWXYZ";
	if (nb / base)
		ft_itoa_base(nb / base, base, length - 1, prefix);
	else
	{
		if (prefix)
			ft_putstr("0x");
		while (--length > 0)
		{
			ft_putstr("0");
		}
	}
	write(1, &str[nb % base], 1);
}