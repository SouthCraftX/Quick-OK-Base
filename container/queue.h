#pragma once

#include "list.h"

struct _XOceanQueue
{
    XOceanList list;
};
typedef struct _XOceanQueue XOceanQueue;

XOCEAN_FORCE_INLINE
xocean_stat_t
XOCEAN_IMPL(xocean_queue_init)(
    XOceanQueue *   queue ,
    xocean_size_t   element_size ,
    xocean_flag32_t mode
){
    return xocean_list_init((XOceanList *)queue , element_size , mode);
}

XOCEAN_FORCE_INLINE
void
XOCEAN_IMPL(xocean_queue_add)(
    XOceanQueue *           queue ,
    const xocean_pointer_t  element
){
    xocean_list_insert_head((XOceanList *)queue , element);
}

XOCEAN_FORCE_INLINE
void
XOCEAN_IMPL(xocean_queue_pull)(
    XOceanQueue *           queue ,
    xocean_pointer_t        element
){
    xocean_memory_copy(queue->list.head->data , element , 
                       queue->list.element_size + sizeof(XOceanListNode));
    xocean_list_remove_head((XOceanList *)queue);
}