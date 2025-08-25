#include "../includes/ft_malloc.h"
#include "ft_malloc_internal.h"

static void *ft_memcpy(void *dst, const void *src, size_t n)
{
    size_t	i;

    i = 0;
    if (src == NULL || dst == NULL)
        return (0);
    if (src == dst)
        return ((unsigned char*)dst);
    while (i < n)
    {
        ((unsigned char*)dst)[i] = ((const unsigned char*)src)[i];
        i++;
    }
    return (dst);
}

void *ft_realloc(void *ptr, size_t size)
{
    if (!ptr)
        return ft_malloc(size);
    if (size == 0)
    {
        ft_free(ptr);
        return NULL;
    }

    pthread_mutex_lock(&g_malloc_mutex);

    size = ALIGN16(size);
    t_block *block = (t_block *)ptr - 1;

    if (block->size >= size)
    {
        pthread_mutex_unlock(&g_malloc_mutex);
        return ptr;
    }

    void *new_ptr = ft_malloc(size);
    if (new_ptr)
    {
        ft_memcpy(new_ptr, ptr, block->size);
        ft_free(ptr);
    }

    pthread_mutex_unlock(&g_malloc_mutex);
    return new_ptr;
}
