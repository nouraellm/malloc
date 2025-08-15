
# Malloc

A custom implementation of the `malloc`, `free`, and `realloc` functions in C, mimicking the behavior of the standard C library allocator, built using low-level system calls and zone-based memory management.

## Project Description 

This project reimplements the core dynamic memory allocation routines (`malloc`, `free`, `realloc`) without using the standard library's allocator. The allocator uses:

-  **`mmap`** for allocating and freeing memory pages.
-  **Zone-based allocation strategy**, where:
	- **TINY** allocations go in preallocated TINY zones
	- **SMALL** allocations go in SMALL zones
	- **LARGE** allocations use separate `mmap`ed regions
-  **Thread safety** via `pthread_mutex` to ensure consistent access to allocation metadata.
-  **Custom memory visualization** with `show_alloc_mem()` and `show_alloc_mem_ex()` for debugging.

This memory allocator is preloadable and can be used to override standard allocation in existing binaries via environment variables like `DYLD_INSERT_LIBRARIES` or `LD_PRELOAD`.

## Features

- Custom `malloc`, `free`, and `realloc` (replaces libc)
- Zone allocator for TINY, SMALL, and LARGE blocks
- Page alignment via `getpagesize()`
- Memory usage visualization:
-  `show_alloc_mem()`: simple block display
-  `show_alloc_mem_ex()`: detailed view with free/used tracking
- Thread-safe with global mutex
- Performance-optimized: minimizes `mmap` calls
- Supports dynamic preloading via `.so` file

## Build Instructions

```bash
make test
```

## Output

```bash
cc -Wall -Wextra -Werror -I includes main.c -L. -lft_malloc -o test_malloc
[+] Running test with DYLD_INSERT_LIBRARIES
DYLD_INSERT_LIBRARIES=./libft_malloc.so DYLD_FORCE_FLAT_NAMESPACE=1 ./test_malloc
======== Test: Basic ft_malloc ========
a: hello world
b: this is a small block

======== ft_show_alloc_mem() ========
LARGE : 0x102a60000
0x102a60040 - 0x102a60c00 : 3008 bytes
TINY : 0x102a50000
0x102a50040 - 0x102a500c0 : 128 bytes
TINY : 0x102a40000
0x102a40040 - 0x102a40080 : 64 bytes
Total : 3200 bytes

======== Test: ft_free() + defrag ========

======== ft_show_alloc_mem_ex() ========
LARGE ZONE @ 0x102a60000 | total zone size: 3072 bytes
  [ft_free] 0x102a60040 - 0x102a60c00 : 3008 bytes
TINY ZONE @ 0x102a50000 | total zone size: 65536 bytes
  [ft_free] 0x102a50040 - 0x102a500c0 : 128 bytes
TINY ZONE @ 0x102a40000 | total zone size: 65536 bytes
  [ft_free] 0x102a40040 - 0x102a40080 : 64 bytes
TOTAL USED : 0 bytes
TOTAL ft_free : 3200 bytes

======== Test: ft_realloc() ========
x after ft_realloc: realloc me

======== Final ft_show_alloc_mem_ex() ========
LARGE ZONE @ 0x102a60000 | total zone size: 3072 bytes
  [ft_free] 0x102a60040 - 0x102a60c00 : 3008 bytes
TINY ZONE @ 0x102a50000 | total zone size: 65536 bytes
  [USED] 0x102a50040 - 0x102a500c0 : 128 bytes
TINY ZONE @ 0x102a40000 | total zone size: 65536 bytes
  [ft_free] 0x102a40040 - 0x102a40080 : 64 bytes
TOTAL USED : 128 bytes
TOTAL ft_free : 3072 bytes
```

# Disclaimer

This project was developed just for fun out of 42 school supervision, please don't rely on it blindly for your school work.