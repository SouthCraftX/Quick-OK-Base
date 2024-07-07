#pragma once

#include "../base.h"
#include <mimalloc.h>

#define XOC_CONTAINER_PRIVATE_HEAP  (1)
#define XOC_CONTAINER_NO_PREALLOC   (1 << 1)

union _XOCContainerInfo
{
    xoc_stat_t i32;
    struct 
    {
        xoc_uint16_t trait;
        xoc_uint16_t type;
    };
};
typedef union _XOCContainerInfo XOCContainerInfo;

XOC_GLOBAL_LOCAL xoc_size_t _xoc_container_init_alloc_element_count;

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_set_container_init_alloc_element_count)(
    xoc_size_t count
){
    _xoc_container_init_alloc_element_count = count;
}

XOC_FORCE_INLINE
xoc_size_t
XOC_IMPL(xoc_get_container_init_alloc_element_count)()
{
    return _xoc_container_init_alloc_element_count;
}

XOC_FORCE_INLINE
mi_heap_t *
__xoc_container_acquire_heap(
    xoc_stat_t mode_from_new
){
    return XOC_HAS_FLAG(mode_from_new , XOC_CONTAINER_PRIVATE_HEAP) ?
            mi_heap_new() : mi_heap_get_default();
    
}

#define xoc_set_container_init_alloc_element_count(count) \
    XOC_INTERFACE(xoc_set_container_init_alloc_element_count)(count)

#define xoc_get_container_init_alloc_element_count() \
    XOC_INTERFACE(xoc_get_container_init_alloc_element_count)()