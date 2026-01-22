/**
 * @file ft_zone_manager.c
 * @brief Encapsulated zone management - provides accessor functions for global state
 */

#include "../../includes/ft_malloc.h"
#include "../../includes/ft_malloc_internal.h"
#include <pthread.h>

/**
 * @brief Get the head of the zones list (thread-safe)
 * @return Pointer to first zone, or NULL if list is empty
 * @note Caller must hold the mutex
 */
t_zone *zone_manager_get_zones(void)
{
    return g_zones;
}

/**
 * @brief Set the head of the zones list (thread-safe)
 * @param zones New head of zones list
 * @note Caller must hold the mutex
 */
void zone_manager_set_zones(t_zone *zones)
{
    g_zones = zones;
}

/**
 * @brief Add a zone to the front of the list (thread-safe)
 * @param zone Zone to add
 * @note Caller must hold the mutex
 */
void zone_manager_add_zone(t_zone *zone)
{
    if (!zone)
        return;
    
    zone->next = g_zones;
    g_zones = zone;
}

/**
 * @brief Remove a zone from the list (thread-safe)
 * @param zone_to_remove Zone to remove
 * @return 1 if removed, 0 if not found
 * @note Caller must hold the mutex
 */
int zone_manager_remove_zone(t_zone *zone_to_remove)
{
    if (!g_zones || !zone_to_remove)
        return 0;

    if (g_zones == zone_to_remove)
    {
        g_zones = g_zones->next;
        return 1;
    }

    t_zone *zone = g_zones;
    while (zone->next)
    {
        if (zone->next == zone_to_remove)
        {
            zone->next = zone->next->next;
            return 1;
        }
        zone = zone->next;
    }
    return 0;
}

/**
 * @brief Lock the malloc mutex
 * @return 0 on success, non-zero on error
 */
int zone_manager_lock(void)
{
    return pthread_mutex_lock(&g_malloc_mutex);
}

/**
 * @brief Unlock the malloc mutex
 * @return 0 on success, non-zero on error
 */
int zone_manager_unlock(void)
{
    return pthread_mutex_unlock(&g_malloc_mutex);
}
