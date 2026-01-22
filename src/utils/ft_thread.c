#include "../../includes/ft_malloc.h"
#include "../../includes/ft_malloc_internal.h"

t_zone *g_zones = NULL;
pthread_mutex_t g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;
