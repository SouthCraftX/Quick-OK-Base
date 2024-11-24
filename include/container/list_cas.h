#pragma once

#include "list.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

QO_FORCE_INLINE
bool
QO_IMPL(qo_list_insert_tail_cas)(
    QO_List *            list ,
    const qo_pointer_t  element
){
    QO_ListNode * node = (QO_ListNode *)mi_heap_malloc(
        list->heap , 
        sizeof(QO_ListNode) + list->element_size
    );
    if (node)
    {
        node->next = NULL;
        qo_memory_copy(node->data , element , list->element_size);
        do
        {
            node = list->tail;
        }
        while(!QO_CAS(list->tail->next , NULL , node));
    }
    return false;
}

#if defined(__cplusplus)
}
#endif // __cplusplus