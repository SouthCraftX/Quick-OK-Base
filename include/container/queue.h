#pragma once

#include "list.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _QO_Queue
{
    QO_List list;
};
typedef struct _QO_Queue QO_Queue;

QO_FORCE_INLINE
qo_stat_t
QO_IMPL(qo_queue_init)(
    QO_Queue *   queue ,
    qo_size_t   element_size ,
    qo_flag32_t mode
){
    return qo_list_init((QO_List *)queue , element_size , mode);
}

QO_FORCE_INLINE
bool
QO_IMPL(qo_queue_add)(
    QO_Queue *           queue ,
    const qo_pointer_t  element
){
    return qo_list_insert_head((QO_List *)queue , element);
}

QO_FORCE_INLINE
void
QO_IMPL(qo_queue_add_node)(
    QO_Queue *           queue ,
    QO_ListNode *        node
){
    qo_list_insert_head((QO_List *)queue , node->data);
}


QO_FORCE_INLINE
qo_size_t
QO_IMPL(qo_queue_get_element_count)(
    QO_Queue * queue
){
    return qo_list_get_element_count((QO_List *)queue);
}

QO_FORCE_INLINE
qo_size_t
QO_IMPL(qo_queue_get_element_size)(
    QO_Queue * queue
){
    return qo_list_get_element_size((QO_List *)queue);
}

QO_FORCE_INLINE
qo_size_t
QO_IMPL(qo_queue_get_data_size)(
    QO_Queue * queue
){
    return qo_list_get_data_size((QO_List *)queue);
}

QO_FORCE_INLINE
bool
QO_IMPL(qo_queue_pull)(
    QO_Queue *           queue ,
    qo_pointer_t        element
){
    if (queue->list.element_count)
    {
        qo_memory_copy(queue->list.head->data , element , 
                           queue->list.element_size + sizeof(QO_ListNode));
        qo_list_remove_head((QO_List *)queue);
        return true;
    }
    return false;
}

QO_FORCE_INLINE
void
QO_IMPL(qo_queue_destory)(
    QO_Queue * queue
){
    qo_list_destory((QO_List *)queue);
}

#define qo_queue_init       QO_INTERFACE(qo_queue_init)
#define qo_queue_destory    QO_INTERFACE(qo_queue_destory)
#define qo_queue_pull       QO_INTERFACE(qo_queue_pull)
#define qo_queue_add        QO_INTERFACE(qo_queue_add)
#define qo_queue_get_element_size \
        QO_INTERFACE(qo_queue_get_element_size)
#define qo_queue_get_data_size  \
        QO_INTERFACE(qo_queue_get_data_size)

#if defined(__cplusplus)
}
#endif // __cplusplus