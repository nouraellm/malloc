#include "includes/ft_malloc.h"

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
    char *a = (char *)ft_malloc(64);
    char *b = (char *)ft_malloc(128);
    char *c = (char *)ft_malloc(3000); // LARGE zone
    ft_strcpy(a, "hello world");
    ft_strcpy(b, "this is a small block");
    ft_printf("a: %s\n", a);
    ft_printf("b: %s\n", b);

    ft_printf("\n======== ft_show_alloc_mem() ========\n");
    ft_show_alloc_mem();

    ft_printf("\n======== Test: ft_free() + defrag ========\n");
    ft_free(a);
    ft_free(b);
    ft_free(c);

    ft_printf("\n======== ft_show_alloc_mem_ex() ========\n");
    ft_show_alloc_mem_ex();

    ft_printf("\n======== Test: ft_realloc() ========\n");
    char *x = (char *)ft_malloc(50);
    ft_strcpy(x, "realloc me");
    x = ft_realloc(x, 100);
    ft_printf("x after ft_realloc: %s\n", x);

    ft_printf("\n======== Final ft_show_alloc_mem_ex() ========\n");
    ft_show_alloc_mem_ex();

    return 0;
}
