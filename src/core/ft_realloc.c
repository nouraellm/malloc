#include "../../includes/ft_malloc.h"
#include "../../includes/ft_malloc_internal.h"
#include <stdint.h>
#include <limits.h>

/**
 * @file ft_realloc.c
 * @brief Implementation of ft_realloc - resizes allocated memory
 */

#include "../../includes/ft_malloc.h"
#include "../../includes/ft_malloc_internal.h"
#include <stdint.h>
#include <limits.h>

// Forward declaration for internal memcpy utility
void *ft_memcpy(void *dst, const void *src, size_t n);

/**
 * @brief Resizes allocated memory block
 * @param block Pointer to pointer containing the memory to resize
 * @param size New size in bytes
 * @return true on success, false on failure
 * @note If *block is NULL, equivalent to ft_malloc(size, block)
 * @note If size is 0, equivalent to ft_free(block)
 * @note On failure, *block remains unchanged
 * @note On success, *block is updated to the new pointer
 * @note Thread-safe
 */

bool ft_realloc(void **block, size_t size)
{
    if (!block)
        return false;

    // If block is NULL, equivalent to malloc
    if (!*block)
    {
        return ft_malloc(size, block);
    }

    // If size is 0, equivalent to free
    if (size == 0)
    {
        return ft_free(block);
    }

    void *ptr = *block;

    // Lock mutex with error checking
    if (zone_manager_lock() != 0)
        return false;

    // Check for overflow
    if (size > SIZE_MAX - 15)
    {
        zone_manager_unlock();
        return false;
    }

    size = ALIGN16(size);

    // Check if aligned size overflowed
    if (size == 0 || size > SIZE_MAX - sizeof(t_block) - sizeof(t_zone))
    {
        zone_manager_unlock();
        return false;
    }

    t_block *block_ptr = (t_block *)ptr - 1;

    // Validate pointer belongs to our allocator
    t_zone *zone = zone_manager_get_zones();
    int found = 0;
    while (zone && !found)
    {
        t_block *b = zone->blocks;
        while (b && !found)
        {
            if (b == block_ptr)
            {
                found = 1;
                break;
            }
            b = b->next;
        }
        zone = zone->next;
    }

    if (!found)
    {
        zone_manager_unlock();
        return false;
    }

    // Current block size is sufficient - no reallocation needed
    if (block_ptr->size >= size)
    {
        zone_manager_unlock();
        return true;
    }

    // Release mutex before calling ft_malloc/ft_free to prevent deadlock
    zone_manager_unlock();

    // Allocate new memory block
    void *new_ptr = NULL;
    if (!ft_malloc(size, &new_ptr))
    {
        return false;
    }

    // Copy existing data to new location using minimum of old and new size
    size_t copy_size = (block_ptr->size < size) ? block_ptr->size : size;
    if (ft_memcpy(new_ptr, ptr, copy_size) == NULL)
    {
        // Memory copy operation failed - release new allocation and return error
        void *temp = new_ptr;
        ft_free(&temp);
        return false;
    }

    // Release old memory allocation
    void *old_ptr = ptr;
    bool free_success = ft_free(&old_ptr);
    
    // Update block pointer to reference new memory location
    *block = new_ptr;
    
    // Return success status - reallocation completed even if free operation failed
    return free_success;
}
