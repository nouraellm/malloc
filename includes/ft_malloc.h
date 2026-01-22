#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include "ft_visibility.h"
# include "ft_printf.h"

# define TINY_MAX 128
# define SMALL_MAX 1024
# define PAGE_SIZE getpagesize()
# define ALIGN16(x) (((x) + 15) & ~15)

FT_API void *ft_malloc(size_t size);
FT_API void ft_free(void *ptr);
FT_API void *ft_realloc(void *ptr, size_t size);
FT_API void ft_show_alloc_mem(void);
FT_API void ft_show_alloc_mem_ex(void);

int is_debug_mode(void);

#endif
