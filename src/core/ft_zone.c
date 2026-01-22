#include "../../includes/ft_malloc.h"
#include "../../includes/ft_malloc_internal.h"
#include <stdint.h>
#include <limits.h>

static size_t get_zone_size(t_zone_type type)
{
    if (type == TINY)
        return PAGE_SIZE * 4;
    else if (type == SMALL)
        return PAGE_SIZE * 32;
    return 0;
}

static t_block *find_block_in_zone(const t_zone *zone, size_t size)
{
    t_block *block = zone->blocks;
    t_block *best_fit = NULL;
    size_t best_size = SIZE_MAX;

    while (block)
    {
        if (block->free && block->size >= size)
        {
            if (block->size == size)
            {
                return block;
            }
            if (block->size < best_size)
            {
                best_fit = block;
                best_size = block->size;
            }
        }
        block = block->next;
    }
    return best_fit;
}

static void split_block(t_block *block, size_t size)
{
    if (!block)
        return;
    
    // Prevent underflow
    if (block->size < size)
        return;
    
    size_t remaining = block->size - size;
    // Split block only if remaining space is sufficient for a new block header
    if (remaining >= sizeof(t_block) + 16)
    {
        t_block *new_block = (t_block *)((char *)(block + 1) + size);
        new_block->size = remaining - sizeof(t_block);
        new_block->free = 1;
        new_block->next = block->next;
        block->next = new_block;
        block->size = size;
    }
}

static t_zone *create_zone(t_zone_type type, size_t size)
{
    if (size == 0)
        return NULL;
    
    size_t zone_size = get_zone_size(type);
    if (zone_size == 0)
        return NULL;
    
    // Validate zone size is sufficient
    if (zone_size < sizeof(t_zone) + sizeof(t_block) + size)
        return NULL;
    
    t_zone *zone = mmap(NULL, zone_size, PROT_READ | PROT_WRITE,
                        MAP_ANON | MAP_PRIVATE, -1, 0);
    if (zone == MAP_FAILED)
        return NULL;

    zone->type = type;
    zone->size = zone_size;
    zone->next = NULL;
    zone->mem = (void *)zone + sizeof(t_zone);

    // Calculate available space in zone
    size_t available = zone_size - sizeof(t_zone);
    size_t block_size_with_header = sizeof(t_block) + size;
    
    // Create first block for requested size
    t_block *block = (t_block *)zone->mem;
    block->size = size;
    block->free = 0;
    
    // If there's remaining space, create a free block
    if (available > block_size_with_header + sizeof(t_block) + 16)
    {
        t_block *free_block = (t_block *)((char *)(block + 1) + size);
        free_block->size = available - block_size_with_header - sizeof(t_block);
        free_block->free = 1;
        free_block->next = NULL;
        block->next = free_block;
    }
    else
    {
        block->next = NULL;
    }

    zone->blocks = block;
    return zone;
}

void *allocate_in_zone(t_zone_type type, size_t size)
{
    t_zone *zone = zone_manager_get_zones();

    // First, try to find a suitable block in existing zones
    while (zone)
    {
        if (zone->type == type)
        {
            t_block *block = find_block_in_zone(zone, size);
            if (block)
            {
                block->free = 0;
                split_block(block, size);
                return (void *)(block + 1);
            }
        }
        zone = zone->next;
    }

    // Create a new zone if no suitable block found
    t_zone *new_zone = create_zone(type, size);
    if (!new_zone)
        return NULL;

    zone_manager_add_zone(new_zone);
    return (void *)(new_zone->blocks + 1);
}

void *allocate_large(size_t size)
{
    // Check for overflow
    size_t total_size = sizeof(t_zone) + sizeof(t_block);
    if (size > SIZE_MAX - total_size)
        return NULL;
    
    total_size += size;
    
    // Align to page size for large allocations
    size_t page_size = getpagesize();
    if (total_size > SIZE_MAX - (page_size - 1))
        return NULL;
    
    total_size = (total_size + page_size - 1) & ~(page_size - 1);
    
    t_zone *zone = mmap(NULL, total_size, PROT_READ | PROT_WRITE,
                        MAP_ANON | MAP_PRIVATE, -1, 0);
    if (zone == MAP_FAILED)
        return NULL;

    zone->type = LARGE;
    zone->size = total_size;
    zone->next = NULL;
    zone_manager_add_zone(zone);

    zone->mem = (void *)zone + sizeof(t_zone);
    t_block *block = (t_block *)zone->mem;
    block->size = size;
    block->free = 0;
    block->next = NULL;

    zone->blocks = block;

    return (void *)(block + 1);
}
