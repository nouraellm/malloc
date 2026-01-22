/**
 * @file ft_free.c
 * @brief Implementation of ft_free - safely frees allocated memory
 */

#include "../../includes/ft_malloc.h"
#include "../../includes/ft_malloc_internal.h"
#include <stdint.h>

/**
 * @brief Frees allocated memory and sets pointer to NULL
 * @param block Pointer to pointer containing the memory to free
 * @return true on success, false on failure
 * @note After freeing, *block is set to NULL to prevent use-after-free
 * @note Freeing NULL pointer is a valid operation with no effect and returns true
 * @note Thread-safe
 */

bool ft_free(void **block)
{
    if (!block)
        return false;

    if (!*block)
    {
        // Freeing NULL pointer is a valid operation with no effect
        return true;
    }

    void *ptr = *block;
    *block = NULL; // Set to NULL immediately to prevent use-after-free

    // Lock mutex with error checking
    if (zone_manager_lock() != 0)
        return false;

    t_block *block_ptr = (t_block *)ptr - 1;
    t_zone *found_zone = NULL;
    int found = 0;

    // Find the zone and validate the pointer
    t_zone *zone = zone_manager_get_zones();
    while (zone && !found)
    {
        t_block *b = zone->blocks;
        while (b && !found)
        {
            if (b == block_ptr)
            {
                // Validate the block
                if (is_valid_block(zone, block_ptr))
                {
                    found = 1;
                    found_zone = zone;
                }
                else
                {
                    zone_manager_unlock();
                    return false; // Invalid pointer
                }
            }
            b = b->next;
        }
        zone = zone->next;
    }

    if (!found)
    {
        zone_manager_unlock();
        return false; // Pointer not found in our allocator
    }

    block_ptr->free = 1;
    merge_free_blocks(found_zone);

    // If it's a large zone and now empty, unmap it
    if (found_zone->type == LARGE && is_zone_empty(found_zone))
    {
        zone_manager_remove_zone(found_zone);
        zone_manager_unlock();
        
        // Unmap the zone and verify operation success
        if (munmap(found_zone, found_zone->size) != 0)
        {
            // munmap operation failed - zone already removed from list
            // Log error condition in debug mode for diagnostics
            if (is_debug_mode())
                ft_printf("[MALLOC_ERROR] munmap failed for zone %p\n", found_zone);
        }
        return true;
    }

    // TINY/SMALL zones are retained for reuse even when empty
    // This optimization reduces mmap/munmap overhead for frequent allocations
    
    zone_manager_unlock();
    return true;
}
