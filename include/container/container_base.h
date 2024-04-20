#pragma once

#include "../base.h"
#include "mimalloc.h"

#define XOCEAN_CONTAINER_PRIVATE_HEAP  (1)
#define XOCEAN_CONTAINER_NO_PREALLOC   (1 << 1)

union _XOceanContainerInfo
{
    xocean_stat_t i32;
    struct 
    {
        xocean_uint16_t trait;
        xocean_uint16_t type;
    };
};
typedef union _XOceanContainerInfo XOceanContainerInfo;

XOCEAN_GLOBAL_LOCAL xocean_size_t _xocean_container_init_alloc_element_count;

XOCEAN_FORCE_INLINE
void
XOCEAN_IMPL(xocean_set_container_init_alloc_element_count)(
    xocean_size_t count
){
    _xocean_container_init_alloc_element_count = count;
}

XOCEAN_FORCE_INLINE
xocean_size_t
XOCEAN_IMPL(xocean_get_container_init_alloc_element_count)()
{
    return _xocean_container_init_alloc_element_count;
}

XOCEAN_FORCE_INLINE
mi_heap_t *
__xocean_container_acquire_heap(
    xocean_stat_t mode_from_new
){
    return XOCEAN_HAS_FLAG(mode_from_new , XOCEAN_CONTAINER_PRIVATE_HEAP) ?
            mi_heap_new() : mi_heap_get_default();
    
}

#define xocean_set_container_init_alloc_element_count(count) \
    XOCEAN_INTERFACE(xocean_set_container_init_alloc_element_count)(count)

#define xocean_get_container_init_alloc_element_count() \
    XOCEAN_INTERFACE(xocean_get_container_init_alloc_element_count)()