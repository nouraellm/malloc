/**
 * @file ft_malloc.c
 * @brief Implementation of ft_malloc - bulletproof memory allocation
 */

#include "../../includes/ft_malloc.h"
#include "../../includes/ft_malloc_internal.h"
#include <stdint.h>
#include <limits.h>

/**
 * @brief Allocates memory of the specified size
 * @param size Number of bytes to allocate (must be greater than 0)
 * @param block Pointer to pointer that will receive the allocated memory
 * @return true on success, false on failure
 * @note On failure, *block is set to NULL
 * @note On success, *block contains the allocated pointer
 * @note Thread-safe
 */
bool ft_malloc(size_t size, void **block)
{
    if (!block)
        return false;

    // Initialize output parameter to NULL to ensure clean failure state
    *block = NULL;

    if (is_debug_mode())
        ft_printf("[MALLOC_DEBUG] Allocating %zu bytes\n", size);

    void *ptr;

    // Lock mutex with error checking
    if (zone_manager_lock() != 0)
        return false;

    if (size == 0)
    {
        zone_manager_unlock();
        return false;
    }

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

    if (size <= TINY_MAX)
        ptr = allocate_in_zone(TINY, size);
    else if (size <= SMALL_MAX)
        ptr = allocate_in_zone(SMALL, size);
    else
        ptr = allocate_large(size);

    zone_manager_unlock();

    if (!ptr)
        return false;

    *block = ptr;
    return true;
}
