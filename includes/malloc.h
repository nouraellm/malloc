#ifndef MALLOC_H
#define MALLOC_H

#include <sys/mman.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>

char memory[20000];

struct slice {
 size_t size;
 int free;
 struct slice *next; 
};

void *_malloc(unsigned int size);
void *realloc(void *ptr, size_t size);
void free(void *ptr);

void ft_bzero(void *s, size_t n);
void ft_putstr(char const *s);
void *ft_memmove(void *dst, const void *src, size_t len);
void *ft_memcpy(void *dst, const void *src, size_t n);
void ft_itoa_base(size_t nb, char base, char length, _Bool prefix);
void t_itoa_fd(size_t nb, char base, int fd, _Bool prefix);
size_t ft_strlen(const char *s);
void *ft_memset(void *b, int c, size_t len);
void ft_putstr_fd(char const *s, int fd);
void ft_putchar_fd(char c, int fd);

#endif
