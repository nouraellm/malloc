/**
 * @file ft_malloc_errors.h
 * @brief Error codes and error handling utilities
 */

#ifndef FT_MALLOC_ERRORS_H
# define FT_MALLOC_ERRORS_H

/**
 * @enum e_malloc_error
 * @brief Error codes for malloc operations
 */
typedef enum e_malloc_error {
    MALLOC_SUCCESS = 0,        ///< Operation succeeded
    MALLOC_INVALID_PARAM,      ///< Invalid parameter (NULL pointer, etc.)
    MALLOC_SIZE_ZERO,          ///< Size is zero
    MALLOC_OVERFLOW,           ///< Size overflow detected
    MALLOC_ALLOCATION_FAILED,  ///< Memory allocation failed (mmap failed)
    MALLOC_INVALID_POINTER,    ///< Pointer not from our allocator
    MALLOC_MUTEX_ERROR,        ///< Mutex operation failed
    MALLOC_INTERNAL_ERROR       ///< Internal error
} t_malloc_error;

/**
 * @brief Get error message string
 * @param error Error code
 * @return Error message string
 */
const char *ft_malloc_error_string(t_malloc_error error);

#endif
