#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <stdio.h>
# include <pthread.h>

# define TINY_MAX 128
# define SMALL_MAX 1024
# define PAGE_SIZE getpagesize()
# define ALIGN16(x) (((x) + 15) & ~15)

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

void *ft_malloc(size_t size);
void ft_free(void *ptr);
void *ft_realloc(void *ptr, size_t size);
void ft_show_alloc_mem(void);
void *ft_memcpy(void *dst, const void *src, size_t n);
void ft_show_alloc_mem_ex(void);
char *ft_strcpy(char *dst, const char *src);

t_zone *create_zone(t_zone_type type, size_t size);
void *allocate_in_zone(t_zone_type type, size_t size);
void *allocate_large(size_t size);

extern t_zone *g_zones;
extern pthread_mutex_t g_malloc_mutex;

int is_debug_mode(void);

#endif
