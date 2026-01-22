#include "../../includes/ft_malloc.h"
#include "../../includes/ft_malloc_internal.h"
#include <stdint.h>

/**
 * @brief Validates that a block pointer is within the zone's memory bounds
 * @param zone The zone containing the block (const - no modification)
 * @param block The block to validate (const - no modification)
 * @return 1 if valid, 0 otherwise
 */
int is_valid_block(const t_zone *zone, const t_block *block)
{
    if (!zone || !block)
        return 0;

    void *zone_start = (void *)zone;
    void *zone_end = (char *)zone_start + zone->size;
    void *block_start = (void *)block;
    void *block_end = (char *)block_start + sizeof(t_block) + block->size;

    // Check if block is within zone bounds
    if (block_start < zone_start || block_end > zone_end)
        return 0;

    // Check if block is properly aligned
    if ((uintptr_t)block_start % sizeof(void *) != 0)
        return 0;

    return 1;
}

/**
 * @brief Merges adjacent free blocks in a zone to reduce fragmentation
 * @param zone The zone to merge blocks in
 */
void merge_free_blocks(t_zone *zone)
{
    if (!zone)
        return;

    t_block *cur = zone->blocks;

    while (cur && cur->next)
    {
        // Check if blocks are adjacent in memory
        void *cur_end = (char *)(cur + 1) + cur->size;
        void *next_start = (void *)cur->next;

        if (cur->free && cur->next->free && cur_end == next_start)
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

/**
 * @brief Checks if a zone is completely empty (all blocks are free)
 * @param zone The zone to check (const - no modification)
 * @return 1 if empty, 0 otherwise
 */
int is_zone_empty(const t_zone *zone)
{
    if (!zone)
        return 0;

    t_block *block = zone->blocks;
    while (block)
    {
        if (!block->free)
            return 0;
        block = block->next;
    }
    return 1;
}

// remove_zone moved to zone_manager - use zone_manager_remove_zone() instead
