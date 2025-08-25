#ifndef FT_MALLOC_INTERNAL_H
# define FT_MALLOC_INTERNAL_H

# include <pthread.h>

typedef enum e_zone_type {
    TINY,
    SMALL,
    LARGE
} t_zone_type;

typedef struct s_block {
    size_t size;
    int free;
    struct s_block *next;
} t_block;

typedef struct s_zone {
    t_zone_type type;
    size_t size;
    struct s_zone *next;
    t_block *blocks;
    void *mem;
} t_zone;

void   *allocate_in_zone(t_zone_type type, size_t size);
void   *allocate_large(size_t size);

extern t_zone *g_zones;
extern pthread_mutex_t g_malloc_mutex;

#endif
