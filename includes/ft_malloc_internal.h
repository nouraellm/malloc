#ifndef FT_MALLOC_INTERNAL_H
# define FT_MALLOC_INTERNAL_H

# include <pthread.h>
# include <stddef.h>

/**
 * @file ft_malloc_internal.h
 * @brief Internal data structures and functions for ft_malloc implementation
 * @note This header is for internal use only and should not be included by user code
 */

/**
 * @enum e_zone_type
 * @brief Zone types for different allocation sizes
 */
typedef enum e_zone_type {
    TINY,   ///< For allocations <= TINY_MAX (128 bytes)
    SMALL,  ///< For allocations <= SMALL_MAX (1024 bytes)
    LARGE   ///< For allocations > SMALL_MAX
} t_zone_type;

/**
 * @struct s_block
 * @brief Memory block metadata
 */
typedef struct s_block {
    size_t size;              ///< Size of the block (excluding header)
    int free;                 ///< 1 if free, 0 if allocated
    struct s_block *next;     ///< Pointer to next block in the zone
} t_block;

/**
 * @struct s_zone
 * @brief Memory zone containing multiple blocks
 */
typedef struct s_zone {
    t_zone_type type;         ///< Type of zone (TINY, SMALL, LARGE)
    size_t size;              ///< Total size of the zone
    struct s_zone *next;      ///< Pointer to next zone
    t_block *blocks;          ///< Linked list of blocks in this zone
    void *mem;                ///< Pointer to the start of usable memory
} t_zone;

// Zone allocation functions
void   *allocate_in_zone(t_zone_type type, size_t size);
void   *allocate_large(size_t size);

// Block utility functions
int     is_valid_block(const t_zone *zone, const t_block *block);
void    merge_free_blocks(t_zone *zone);
int     is_zone_empty(const t_zone *zone);

// Zone manager - encapsulated access to global state
t_zone  *zone_manager_get_zones(void);
void    zone_manager_set_zones(t_zone *zones);
void    zone_manager_add_zone(t_zone *zone);
int     zone_manager_remove_zone(t_zone *zone_to_remove);
int     zone_manager_lock(void);
int     zone_manager_unlock(void);

// Global state (internal use only - use zone_manager functions instead)
extern t_zone *g_zones;
extern pthread_mutex_t g_malloc_mutex;

#endif
