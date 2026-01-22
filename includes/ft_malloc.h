/**
 * @file ft_malloc.h
 * @brief Public API for ft_malloc - bulletproof memory allocator
 * @author ft_malloc team
 * @version 1.0
 * 
 * This header provides a bulletproof memory allocation API that forces
 * error checking and prevents use-after-free bugs.
 */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include "ft_visibility.h"
# include "ft_printf.h"
# include <stdbool.h>

/** Maximum size for TINY allocations (128 bytes) */
# define TINY_MAX 128

/** Maximum size for SMALL allocations (1024 bytes) */
# define SMALL_MAX 1024

/** Get system page size */
# define PAGE_SIZE getpagesize()

/** Align value to 16-byte boundary */
# define ALIGN16(x) (((x) + 15) & ~15)

/**
 * @brief Allocates memory of the specified size
 * @param size Number of bytes to allocate (must be > 0)
 * @param block Pointer to pointer that will receive the allocated memory
 * @return true on success, false on failure
 * @note On failure, *block is set to NULL
 * @note On success, *block contains the allocated pointer
 */
FT_API bool ft_malloc(size_t size, void **block);

/**
 * @brief Frees allocated memory and sets pointer to NULL
 * @param block Pointer to pointer containing the memory to free
 * @return true on success, false on failure
 * @note After freeing, *block is set to NULL to prevent use-after-free
 * @note Freeing NULL pointer is a valid operation with no effect and returns true
 */
FT_API bool ft_free(void **block);

/**
 * @brief Resizes allocated memory block
 * @param block Pointer to pointer containing the memory to resize
 * @param size New size in bytes
 * @return true on success, false on failure
 * @note If *block is NULL, equivalent to ft_malloc(size, block)
 * @note If size is 0, equivalent to ft_free(block)
 * @note On failure, *block remains unchanged
 * @note On success, *block is updated to the new pointer
 */
FT_API bool ft_realloc(void **block, size_t size);

/**
 * @brief Displays memory allocation information
 * @note Shows only allocated (non-free) blocks
 */
FT_API void ft_show_alloc_mem(void);

/**
 * @brief Displays detailed memory allocation information
 * @note Shows all blocks (both allocated and free) with detailed statistics
 */
FT_API void ft_show_alloc_mem_ex(void);

/**
 * @brief Checks if debug mode is enabled
 * @return 1 if MALLOC_DEBUG environment variable is set to "1", 0 otherwise
 */
int is_debug_mode(void);

#endif
