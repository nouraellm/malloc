#ifndef FT_PRINTF_H
#define FT_PRINTF_H

char memory[20000];

struct slice {
 size_t size;
 int free;
 struct slice *next; 
};

void *_malloc(unsigned int size);

#endif
