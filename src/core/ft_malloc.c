#include "../../includes/ft_malloc.h"
#include "../../includes/ft_malloc_internal.h"

void *ft_malloc(size_t size)
{
    if (is_debug_mode())
        ft_printf("[MALLOC_DEBUG] Allocating %zu bytes\n", size);

    void *ptr;

    pthread_mutex_lock(&g_malloc_mutex);

    if (size == 0)
    {
        pthread_mutex_unlock(&g_malloc_mutex);
        return NULL;
    }

    size = ALIGN16(size);

    if (size <= TINY_MAX)
        ptr = allocate_in_zone(TINY, size);
    else if (size <= SMALL_MAX)
        ptr = allocate_in_zone(SMALL, size);
    else
        ptr = allocate_large(size);

    pthread_mutex_unlock(&g_malloc_mutex);
    return ptr;
}
