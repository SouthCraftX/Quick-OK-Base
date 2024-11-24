#pragma once

#include "../base.h"
#include <mimalloc.h>

#define QO_CONTAINER_PRIVATE_HEAP  (1)
#define QO_CONTAINER_NO_PREALLOC   (1 << 1)

union _QOContainerInfo
{
    qo_stat_t i32;
    struct 
    {
        qo_uint16_t trait;
        qo_uint16_t type;
    };
};
typedef union _QOContainerInfo QOContainerInfo;

QO_GLOBAL_LOCAL qo_size_t _qo_container_init_alloc_element_count;

QO_FORCE_INLINE
void
QO_IMPL(qo_set_container_init_alloc_element_count)(
    qo_size_t count
){
    _qo_container_init_alloc_element_count = count;
}

QO_FORCE_INLINE
qo_size_t
QO_IMPL(qo_get_container_init_alloc_element_count)()
{
    return _qo_container_init_alloc_element_count;
}

QO_FORCE_INLINE
mi_heap_t *
__qo_container_acquire_heap(
    qo_stat_t mode_from_new
){
    return QO_HAS_FLAG(mode_from_new , QO_CONTAINER_PRIVATE_HEAP) ?
            mi_heap_new() : mi_heap_get_default();
    
}

#define qo_set_container_init_alloc_element_count(count) \
    QO_INTERFACE(qo_set_container_init_alloc_element_count)(count)

#define qo_get_container_init_alloc_element_count() \
    QO_INTERFACE(qo_get_container_init_alloc_element_count)()