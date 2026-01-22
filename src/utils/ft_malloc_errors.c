/**
 * @file ft_malloc_errors.c
 * @brief Error handling utilities
 */

#include "../../includes/ft_malloc_errors.h"

const char *ft_malloc_error_string(t_malloc_error error)
{
    switch (error)
    {
        case MALLOC_SUCCESS:
            return "Success";
        case MALLOC_INVALID_PARAM:
            return "Invalid parameter";
        case MALLOC_SIZE_ZERO:
            return "Size is zero";
        case MALLOC_OVERFLOW:
            return "Size overflow detected";
        case MALLOC_ALLOCATION_FAILED:
            return "Memory allocation failed";
        case MALLOC_INVALID_POINTER:
            return "Invalid pointer (not from our allocator)";
        case MALLOC_MUTEX_ERROR:
            return "Mutex operation failed";
        case MALLOC_INTERNAL_ERROR:
            return "Internal error";
        default:
            return "Unknown error";
    }
}
