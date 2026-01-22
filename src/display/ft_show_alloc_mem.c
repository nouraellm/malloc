#include "../../includes/ft_malloc.h"
#include "../../includes/ft_malloc_internal.h"

void ft_show_alloc_mem(void)
{
    if (zone_manager_lock() != 0)
        return;

    t_zone *zone = zone_manager_get_zones();
    size_t total = 0;

    while (zone)
    {
        const char *label = (zone->type == TINY) ? "TINY" :
                            (zone->type == SMALL) ? "SMALL" : "LARGE";

        ft_printf("%s : %p\n", label, zone);

        t_block *block = zone->blocks;
        while (block)
        {
            if (!block->free)
            {
                void *start = (void *)(block + 1);
                void *end = (char *)start + block->size;
                ft_printf("%p - %p : %zu bytes\n", start, end, block->size);
                total += block->size;
            }

            block = block->next;
        }

        zone = zone->next;
    }

    ft_printf("Total : %zu bytes\n", total);

    zone_manager_unlock();
}
