#pragma once

#include "list.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

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
xocean_size_t
XOCEAN_IMPL(xocean_queue_get_element_count)(
    XOceanQueue * queue
){
    return xocean_list_get_element_count((XOceanList *)queue);
}

XOCEAN_FORCE_INLINE
xocean_size_t
XOCEAN_IMPL(xocean_queue_get_element_size)(
    XOceanQueue * queue
){
    return xocean_list_get_element_size((XOceanList *)queue);
}

XOCEAN_FORCE_INLINE
xocean_size_t
XOCEAN_IMPL(xocean_queue_get_data_size)(
    XOceanQueue * queue
){
    return xocean_list_get_data_size((XOceanList *)queue);
}

XOCEAN_FORCE_INLINE
bool
XOCEAN_IMPL(xocean_queue_pull)(
    XOceanQueue *           queue ,
    xocean_pointer_t        element
){
    if(queue->list.element_count)
    {
        xocean_memory_copy(queue->list.head->data , element , 
                           queue->list.element_size + sizeof(XOceanListNode));
        xocean_list_remove_head((XOceanList *)queue);
        return true;
    }
    return false;
}

XOCEAN_FORCE_INLINE
void
XOCEAN_IMPL(xocean_queue_destory)(
    XOceanQueue * queue
){
    xocean_list_destory((XOceanList *)queue);
}

#define xocean_queue_init       XOCEAN_INTERFACE(xocean_queue_init)
#define xocean_queue_destory    XOCEAN_INTERFACE(xocean_queue_destory)
#define xocean_queue_pull       XOCEAN_INTERFACE(xocean_queue_pull)
#define xocean_queue_add        XOCEAN_INTERFACE(xocean_queue_add)
#define xocean_queue_get_element_size \
        XOCEAN_INTERFACE(xocean_queue_get_element_size)
#define xocean_queue_get_data_size  \
        XOCEAN_INTERFACE(xocean_queue_get_data_size)

#if defined(__cplusplus)
}
#endif // __cplusplus