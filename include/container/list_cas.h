#pragma once

#include "list.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

XOCEAN_FORCE_INLINE
bool
XOCEAN_IMPL(xocean_list_insert_tail_cas)(
    XOceanList *            list ,
    const xocean_pointer_t  element
){
    XOceanListNode * node = (XOceanListNode *)mi_heap_malloc(
        list->heap , 
        sizeof(XOceanListNode) + list->element_size
    );
    if(node)
    {
        node->next = NULL;
        xocean_memory_copy(node->data , element , list->element_size);
        do
        {
            node = list->tail;
        }
        while(!XOCEAN_CAS(list->tail->next , NULL , node));
    }
    return false;
}

#if defined(__cplusplus)
}
#endif // __cplusplus