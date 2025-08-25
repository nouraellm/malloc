#include "../includes/ft_malloc.h"
#include "ft_malloc_internal.h"

void ft_show_alloc_mem(void)
{
    pthread_mutex_lock(&g_malloc_mutex);

    t_zone *zone = g_zones;
    size_t total = 0;

    while (zone)
    {
        const char *label = (zone->type == TINY) ? "TINY" :
                            (zone->type == SMALL) ? "SMALL" : "LARGE";

        printf("%s : %p\n", label, zone);

        t_block *block = zone->blocks;
        while (block)
        {
            if (!block->free)
            {
                void *start = (void *)(block + 1);
                void *end = (char *)start + block->size;
                printf("%p - %p : %zu bytes\n", start, end, block->size);
                total += block->size;
            }

            block = block->next;
        }

        zone = zone->next;
    }

    printf("Total : %zu bytes\n", total);

    pthread_mutex_unlock(&g_malloc_mutex);
}
