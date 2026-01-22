#include "../../includes/ft_malloc.h"

/**
 * @file ft_memcpy.c
 * @brief Memory copy utility function
 * @note Internal utility, does not use standard library
 */

/**
 * @brief Copies n bytes from src to dst
 * @param dst Destination buffer
 * @param src Source buffer
 * @param n Number of bytes to copy
 * @return Pointer to dst, or NULL on error
 */
void *ft_memcpy(void *dst, const void *src, size_t n)
{
    size_t i;
    unsigned char *d;
    const unsigned char *s;

    if (!src || !dst)
        return NULL;
    
    if (n == 0)
        return dst;
    
    if (src == dst)
        return (unsigned char*)dst;
    
    // Check for potential overflow
    if (n > SIZE_MAX / sizeof(unsigned char))
        return NULL;
    
    d = (unsigned char*)dst;
    s = (const unsigned char*)src;
    
    i = 0;
    while (i < n)
    {
        d[i] = s[i];
        i++;
    }
    return (dst);
}
