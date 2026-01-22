# ft_malloc

A production-ready, bulletproof implementation of memory allocation functions in C, featuring zone-based memory management and thread safety.

## Features

- **Bulletproof API**: Returns `bool` for success/failure, forces error checking
- **Use-after-free prevention**: Automatically sets pointers to NULL after freeing
- **Zone-based allocation**: Efficient memory management with TINY, SMALL, and LARGE zones
- **Thread-safe**: Protected by mutex for concurrent access
- **Memory visualization**: Built-in debugging tools for memory inspection
- **Production-ready**: Comprehensive error handling and validation

## Project Structure

```
malloc/
├── includes/              # Public and internal headers
│   ├── ft_malloc.h       # Public API
│   ├── ft_malloc_internal.h  # Internal structures (not for users)
│   ├── ft_printf.h        # Printf implementation
│   └── ft_visibility.h   # Visibility macros
├── src/                   # Source code
│   ├── core/             # Core allocation functions
│   │   ├── ft_malloc.c
│   │   ├── ft_free.c
│   │   ├── ft_realloc.c
│   │   ├── ft_zone.c
│   │   └── ft_block_utils.c  # Block management utilities
│   ├── display/          # Memory visualization
│   │   ├── ft_show_alloc_mem.c
│   │   └── ft_show_alloc_mem_ex.c
│   └── utils/            # Utility functions
│       ├── ft_debug.c
│       ├── ft_thread.c
│       └── ft_memcpy.c
├── tests/                # Test files
│   └── main.c
├── third_party/          # External dependencies
│   └── libftprintf.a
├── build/                # Build artifacts (generated)
├── docs/                 # Documentation
├── subject/              # Project requirements
├── makefile              # Build system
└── README.md             # This file
```

## Quick Start

### Building

```bash
make          # Build the shared library
make test     # Build and run tests
make clean    # Clean build artifacts
make fclean   # Full clean (removes library too)
```

### Usage

```c
#include "includes/ft_malloc.h"

int main(void)
{
    void *ptr = NULL;
    
    // Allocate memory - always check return value
    if (!ft_malloc(1024, &ptr))
    {
        // Handle allocation failure
        return 1;
    }
    
    // Use allocated memory
    // Pointer is valid at this point
    
    // Free memory - pointer is automatically set to NULL
    if (!ft_free(&ptr))
    {
        // Handle free operation failure
        return 1;
    }
    
    // Pointer is now NULL, preventing use-after-free errors
    
    return 0;
}
```

## API Documentation

### `bool ft_malloc(size_t size, void **block)`

Allocates memory of the specified size.

- **Parameters:**
  - `size`: Number of bytes to allocate (must be greater than 0)
  - `block`: Pointer to pointer that will receive the allocated memory
- **Returns:** `true` on success, `false` on failure
- **Notes:**
  - On failure, `*block` is set to `NULL`
  - On success, `*block` contains the allocated pointer
  - Thread-safe

### `bool ft_free(void **block)`

Frees allocated memory and sets pointer to NULL.

- **Parameters:**
  - `block`: Pointer to pointer containing the memory to free
- **Returns:** `true` on success, `false` on failure
- **Notes:**
  - After freeing, `*block` is set to `NULL` to prevent use-after-free
  - Freeing `NULL` pointer is a valid operation with no effect and returns `true`
  - Thread-safe

### `bool ft_realloc(void **block, size_t size)`

Resizes allocated memory block.

- **Parameters:**
  - `block`: Pointer to pointer containing the memory to resize
  - `size`: New size in bytes
- **Returns:** `true` on success, `false` on failure
- **Notes:**
  - If `*block` is `NULL`, equivalent to `ft_malloc(size, block)`
  - If `size` is 0, equivalent to `ft_free(block)`
  - On failure, `*block` remains unchanged
  - On success, `*block` is updated to the new pointer
  - Thread-safe

### `void ft_show_alloc_mem(void)`

Displays memory allocation information (allocated blocks only).

### `void ft_show_alloc_mem_ex(void)`

Displays detailed memory allocation information (all blocks with statistics).

## Architecture

### Zone Types

- **TINY**: Allocations ≤ 128 bytes
- **SMALL**: Allocations ≤ 1024 bytes  
- **LARGE**: Allocations > 1024 bytes

### Memory Layout

```
Zone Structure:
┌─────────────────┐
│ Zone Header     │
├─────────────────┤
│ Block 1 Header  │
│ Block 1 Data    │
├─────────────────┤
│ Block 2 Header  │
│ Block 2 Data    │
└─────────────────┘
```

### Thread Safety

All operations are protected by a global mutex (`g_malloc_mutex`) to ensure thread-safe access to the allocator's internal state.

## Development

### Code Organization

- **Core functions**: `src/core/` - Main allocation logic
- **Display functions**: `src/display/` - Memory visualization
- **Utilities**: `src/utils/` - Helper functions
- **Headers**: `includes/` - Public and internal APIs

### Building from Source

1. Ensure `libftprintf.a` is in `third_party/`
2. Run `make` to build the shared library
3. Run `make test` to build and execute tests

### Debug Mode

Set the `MALLOC_DEBUG` environment variable to enable debug output:

```bash
export MALLOC_DEBUG=1
make test
```

## Design Principles

1. **Bulletproof by Design**: API forces error checking
2. **Safety First**: Automatic NULL assignment prevents use-after-free
3. **Clean Code**: Well-organized, documented, and maintainable
4. **Production Ready**: Comprehensive error handling and validation
5. **Thread Safe**: All operations protected by mutex

## Troubleshooting

### Build Issues

- **Missing libftprintf.a**: Ensure it's in `third_party/` directory
- **Link errors**: Check that all source files are included in makefile

### Runtime Issues

- **Allocation failures**: Check available system memory
- **Thread issues**: Ensure proper mutex initialization

## License

This project was developed for educational purposes.

## Contributing

This is a production-ready implementation following clean code practices and industry standards.
