#include "../includes/ft_malloc.h"

static char *ft_strcpy(char *dst, const char *src)
{
    if (dst == NULL || src == NULL)
        return NULL;

    int i;

    i = 0;
    while (src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return (dst);
}

int main(void)
{
    ft_printf("======== Test: Basic ft_malloc ========\n");
    char *a = NULL;
    char *b = NULL;
    char *c = NULL;
    
    if (!ft_malloc(64, (void **)&a) || !a)
    {
        ft_printf("Failed to allocate a\n");
        return 1;
    }
    if (!ft_malloc(128, (void **)&b) || !b)
    {
        ft_printf("Failed to allocate b\n");
        return 1;
    }
    if (!ft_malloc(3000, (void **)&c) || !c) // LARGE zone
    {
        ft_printf("Failed to allocate c\n");
        return 1;
    }
    
    ft_strcpy(a, "hello world");
    ft_strcpy(b, "this is a small block");
    ft_printf("a: %s\n", a);
    ft_printf("b: %s\n", b);

    ft_printf("\n======== ft_show_alloc_mem() ========\n");
    ft_show_alloc_mem();

    ft_printf("\n======== Test: ft_free() + defrag ========\n");
    ft_free((void **)&a);
    ft_free((void **)&b);
    ft_free((void **)&c);

    ft_printf("\n======== ft_show_alloc_mem_ex() ========\n");
    ft_show_alloc_mem_ex();

    ft_printf("\n======== Test: ft_realloc() ========\n");
    char *x = NULL;
    if (!ft_malloc(50, (void **)&x) || !x)
    {
        ft_printf("Failed to allocate x\n");
        return 1;
    }
    ft_strcpy(x, "realloc me");
    if (!ft_realloc((void **)&x, 100))
    {
        ft_printf("Failed to realloc x\n");
        return 1;
    }
    ft_printf("x after ft_realloc: %s\n", x);

    ft_printf("\n======== Final ft_show_alloc_mem_ex() ========\n");
    ft_show_alloc_mem_ex();

    return 0;
}
