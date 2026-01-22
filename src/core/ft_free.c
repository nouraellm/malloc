#include "../../includes/ft_malloc.h"
#include "../../includes/ft_malloc_internal.h"

static void merge_free_blocks(t_zone *zone)
{
    t_block *cur = zone->blocks;

    while (cur && cur->next)
    {
        if (cur->free && cur->next->free)
        {
            cur->size += sizeof(t_block) + cur->next->size;
            cur->next = cur->next->next;
        }
        else
        {
            cur = cur->next;
        }
    }
}

void ft_free(void *ptr)
{
    if (!ptr)
        return;

    pthread_mutex_lock(&g_malloc_mutex);

    t_block *block = (t_block *)ptr - 1;
    block->free = 1;

    t_zone *zone = g_zones;
    while (zone)
    {
        t_block *b = zone->blocks;
        while (b)
        {
            if (b == block)
            {
                merge_free_blocks(zone);
                break;
            }
            b = b->next;
        }
        zone = zone->next;
    }

    pthread_mutex_unlock(&g_malloc_mutex);
}
