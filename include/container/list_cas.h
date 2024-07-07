#pragma once

#include "list.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

XOC_FORCE_INLINE
bool
XOC_IMPL(xoc_list_insert_tail_cas)(
    XOC_List *            list ,
    const xoc_pointer_t  element
){
    XOC_ListNode * node = (XOC_ListNode *)mi_heap_malloc(
        list->heap , 
        sizeof(XOC_ListNode) + list->element_size
    );
    if(node)
    {
        node->next = NULL;
        xoc_memory_copy(node->data , element , list->element_size);
        do
        {
            node = list->tail;
        }
        while(!XOC_CAS(list->tail->next , NULL , node));
    }
    return false;
}

#if defined(__cplusplus)
}
#endif // __cplusplus