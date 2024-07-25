#pragma once

#include "list.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOC_Queue
{
    XOC_List list;
};
typedef struct _XOC_Queue XOC_Queue;

XOC_FORCE_INLINE
xoc_stat_t
XOC_IMPL(xoc_queue_init)(
    XOC_Queue *   queue ,
    xoc_size_t   element_size ,
    xoc_flag32_t mode
){
    return xoc_list_init((XOC_List *)queue , element_size , mode);
}

XOC_FORCE_INLINE
bool
XOC_IMPL(xoc_queue_add)(
    XOC_Queue *           queue ,
    const xoc_pointer_t  element
){
    return xoc_list_insert_head((XOC_List *)queue , element);
}

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_queue_add_node)(
    XOC_Queue *           queue ,
    XOC_ListNode *        node
){
    xoc_list_insert_head((XOC_List *)queue , node->data);
}


XOC_FORCE_INLINE
xoc_size_t
XOC_IMPL(xoc_queue_get_element_count)(
    XOC_Queue * queue
){
    return xoc_list_get_element_count((XOC_List *)queue);
}

XOC_FORCE_INLINE
xoc_size_t
XOC_IMPL(xoc_queue_get_element_size)(
    XOC_Queue * queue
){
    return xoc_list_get_element_size((XOC_List *)queue);
}

XOC_FORCE_INLINE
xoc_size_t
XOC_IMPL(xoc_queue_get_data_size)(
    XOC_Queue * queue
){
    return xoc_list_get_data_size((XOC_List *)queue);
}

XOC_FORCE_INLINE
bool
XOC_IMPL(xoc_queue_pull)(
    XOC_Queue *           queue ,
    xoc_pointer_t        element
){
    if (queue->list.element_count)
    {
        xoc_memory_copy(queue->list.head->data , element , 
                           queue->list.element_size + sizeof(XOC_ListNode));
        xoc_list_remove_head((XOC_List *)queue);
        return true;
    }
    return false;
}

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_queue_destory)(
    XOC_Queue * queue
){
    xoc_list_destory((XOC_List *)queue);
}

#define xoc_queue_init       XOC_INTERFACE(xoc_queue_init)
#define xoc_queue_destory    XOC_INTERFACE(xoc_queue_destory)
#define xoc_queue_pull       XOC_INTERFACE(xoc_queue_pull)
#define xoc_queue_add        XOC_INTERFACE(xoc_queue_add)
#define xoc_queue_get_element_size \
        XOC_INTERFACE(xoc_queue_get_element_size)
#define xoc_queue_get_data_size  \
        XOC_INTERFACE(xoc_queue_get_data_size)

#if defined(__cplusplus)
}
#endif // __cplusplus