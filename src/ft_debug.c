#include "../includes/ft_malloc.h"

int is_debug_mode(void)
{
    char *dbg = getenv("MALLOC_DEBUG");
    return (dbg && dbg[0] == '1');
}
