#pragma once
#define __XOC_LIST_INLINE_IMPL_H__

#include "container_base.h"
#include "../memory/memory_oper.h"

#include "atomic.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOC_ListNode
{
    XOC_ListNode *    next;
    XOC_ListNode *    prev;
    xoc_byte_t       data[];
};
typedef struct _XOC_ListNode XOC_ListNode;

struct _XOC_List
{
    xoc_ref_count_t  ref_count;
    xoc_bool_t       has_private_heap;
    xoc_size_t       element_size;
    xoc_size_t       element_count;
    XOC_ListNode *    head;
    XOC_ListNode *    tail;
    XOC_ListNode *    cur;
    mi_heap_t *         heap;
    __xoc_list_destructor_f destructor;
};
typedef struct _XOC_List XOC_List;
typedef void(*__xoc_list_destructor_f)(XOC_List *);

XOC_FORCE_INLINE
xoc_pointer_t
XOC_IMPL(xoc_list_get_cur)(
    XOC_List * list
){
    return list->cur->data;
}

// @brief iterate the list forward from head
// @param list: the list to be iterated
// @param p: the pointer to be filled
#define XOC_LIST_ITERATE_FORWARD(list , p) \
    for(XOC_ListNode * ___cur_node = (list)->head ; \
        ___cur_node != NULL ; \
        (p) = ___cur_node->data , ___cur_node = ___cur_node->next)

// @brief iterate the list backward from tail
// @param list: the list to be iterated
// @param p: the pointer to be filled
#define XOC_LIST_ITERATE_BACKWARD(list , p) \
    for(XOC_ListNode * ___cur_node = (list)->tail ; \
        ___cur_node != NULL ; \
        (p) = ___cur_node->data , ___cur_node = ___cur_node->prev)

// @brief iterate the list forward from current node
// @param list: the list to be iterated
// @param p: the pointer to be filled
#define XOC_LIST_CUR_ITERATE_FORWARD(list , p) \
    for(XOC_ListNode * ___cur_node = (list)->cur ; \
        ___cur_node != NULL ; \
        (p) = ___cur_node->data , ___cur_node = ___cur_node->next)

// @brief iterate the list bacjward from current node 
// @param list: the list to be iterated
// @param p: the pointer to be filled
#define XOC_LIST_CUR_ITERATE_BACKWARD(list , p) \
    for(XOC_ListNode * ___cur_node = (list)->cur ; \
        ___cur_node != NULL ; \
        (p) = ___cur_node->data , ___cur_node = ___cur_node->prev)

// @brief iterate the list forward from head
// @param list: the list to be iterated
// @param cp: the pointer to be filled
#define XOC_LIST_CONST_ITERATE_FORWARD(list , cp) \
    XOC_LIST_ITERATE_FORWARD((list) , (const)cp)

// @brief iterate the list backward from tail
// @param list: the list to be iterated
// @param cp: the pointer to be filled
#define XOC_LIST_CONST_ITERATE_BACKWARD(list , cp) \
    XOC_LIST_ITERATE_BACKWARD((list) , (const)cp)

#define XOC_LIST_ITERATE XOC_LIST_ITERATE_FORWARD

void
__xoc_list_cleanup_for_private_heap(
    XOC_List * list
){
    mi_heap_delete(list->heap);
}

void
__xoc_list_cleanup_for_shared_heap(
    XOC_List * list
){
    xoc_byte_t * p;
    XOC_LIST_ITERATE_FORWARD(list , p)
    {
        mi_free(p - sizeof(XOC_ListNode));
    }
}

void
XOC_IMPL(xoc_list_unref)(
    XOC_List * list
){
    list->ref_count--;
    if (list->ref_count)
        return;
    list->destructor(list);
}

XOC_FORCE_INLINE
xoc_size_t
__xoc_list_init_clac_alloc_size(
    xoc_size_t element_size
){
    return sizeof(XOC_List) + 
            (element_size + sizeof(XOC_ListNode *)) *
            xoc_get_container_init_alloc_element_count();
}

XOC_FORCE_INLINE
void
__xoc_list_prealloc(
    XOC_List *    list ,
    xoc_byte_t * mem ,
    xoc_size_t   node_size
){
    const xoc_size_t count = xoc_get_container_init_alloc_element_count();
    XOC_ListNode * prev_node = ((XOC_ListNode *)mem) , * node;
    ((XOC_ListNode *)mem)->prev = NULL;
    for (xoc_size_t i = 1; i < count; i++)
    {
        node = (XOC_ListNode *)(mem + i * node_size);
        node->prev = prev_node;
        prev_node->next = node;
        prev_node = node;
    }
    node->next = NULL;
    list->head = (XOC_ListNode *)mem;
    list->tail = node;
    list->cur  = (XOC_ListNode *)mem;
}

xoc_stat_t
XOC_IMPL(xoc_list_init)(
    XOC_List *    list ,
    xoc_size_t   element_size ,
    xoc_flag32_t mode
){
    mi_heap_t * heap = __xoc_container_acquire_heap(mode);
    if (heap)
    {
        const xoc_size_t prealloc_size = (element_size + sizeof(XOC_ListNode) *
            _xoc_get_container_init_alloc_element_count());
        xoc_pointer_t mem = mi_heap_malloc(heap , prealloc_size);
        if (mem)
        {
            __xoc_list_prealloc(list , (xoc_byte_t *)mem , 
                                   element_size + sizeof(XOC_ListNode *));
            list->heap = heap;
            list->element_size = element_size;
            list->has_private_heap = XOC_HAS_FLAG(
                mode , 
                XOC_CONTAINER_PRIVATE_HEAP
            );
            list->destructor = list->has_private_heap ? 
                __xoc_list_cleanup_for_private_heap :
                __xoc_list_cleanup_for_shared_heap;
            return XOC_OK;   
        }
        return XOC_OUT_OF_MEMORY;
    }
    return XOC_OUT_OF_MEMORY;
}

XOC_FORCE_INLINE
xoc_size_t
__xoc_list_node_clac_size(
    XOC_List * list
){
    return sizeof(XOC_ListNode) + list->element_size;
}

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_list_insert_node_ahead)(
    XOC_List *        list ,
    XOC_ListNode *    node
){
    node->next = list->cur;
    node->prev = list->cur->prev;
    list->cur->prev->next = node;
    list->cur->prev = node;
}


XOC_FORCE_INLINE
xoc_bool_t
XOC_IMPL(xoc_list_insert_ahead)(
    XOC_List * list,
    xoc_pointer_t p_element
){
    XOC_ListNode * new_node = (XOC_ListNode *)mi_heap_malloc(list->heap , 
                                __xoc_list_node_clac_size(list));
    if (new_node)
    {
        if (p_element)
            xoc_memory_copy(p_element , new_node->data , list->element_size);
        new_node->next = list->cur->next;
        new_node->prev = list->cur;
        list->cur->next = new_node;
        return xoc_true;
    }
    return xoc_false;
}


XOC_FORCE_INLINE
void
XOC_IMPL(xoc_list_set)(
    XOC_List * list ,
    xoc_pointer_t p_element
){
    xoc_pointer_t p;
    XOC_LIST_ITERATE(list , p)
    {
        xoc_memory_copy(p_element , p , list->element_size);
    }
}

XOC_FORCE_INLINE
xoc_bool_t
XOC_IMPL(xoc_list_insert_backward)(
    XOC_List * list ,
    xoc_pointer_t p_element
){
    XOC_ListNode * new_node = (XOC_ListNode *)mi_heap_malloc(list->heap , 
                                __xoc_list_node_clac_size(list));
    if (new_node)
    {
        if (p_element)
            xoc_memory_copy(p_element , new_node->data , list->element_size);
        new_node->next = list->cur;
        new_node->prev = list->cur->prev;
        list->cur->prev = new_node;
        return xoc_true;
    }
    return xoc_false;
}

XOC_FORCE_INLINE
xoc_size_t
XOC_IMPL(xoc_list_insert_multiple_ahead)(
    XOC_List *    list ,
    xoc_byte_t * p_elements ,
    xoc_size_t   count
){
    xoc_size_t inserted_count = 0;
    for ( ; inserted_count < count ; inserted_count++)
    {
        if (XOC_INTERFACE(xoc_list_insert_ahead)(list , p_elements))
        {
            p_elements += list->element_size;
        }
        break;
    }
    list->element_count += inserted_count;
    return inserted_count;
}

XOC_FORCE_INLINE
xoc_size_t
XOC_IMPL(xoc_list_insert_multiple_backward)(
    XOC_List *    list ,
    xoc_byte_t * p_elements ,
    xoc_size_t   count
){
    xoc_size_t inserted_count = 0;
    for ( ; inserted_count < count ; inserted_count++)
    {
        if (XOC_INTERFACE(xoc_list_insert_backward)(list , p_elements))
        {
            p_elements += list->element_size;
        }
        break;
    }
    list->element_count += inserted_count;
    return inserted_count;
}

XOC_FORCE_INLINE
xoc_bool_t
XOC_IMPL(xoc_list_insert_tail)(
    XOC_List *            list ,
    const xoc_pointer_t  element
){
    XOC_ListNode * node = (XOC_ListNode*)mi_heap_malloc(
        list->heap , 
        sizeof(XOC_ListNode) + list->element_size
    );
    if (node)
    {
        list->tail->next = node;
        node->prev = list->tail;
        node->next = NULL;
        list->tail = node;
        list->element_count ++;
        xoc_memory_copy(element , node->data , list->element_size);
        return xoc_true;
    }
    return xoc_false;
}

XOC_FORCE_INLINE
xoc_bool_t
XOC_IMPL(xoc_list_insert_head)(
    XOC_List *            list ,
    const xoc_pointer_t  element
){
    XOC_ListNode * node = (XOC_ListNode*)mi_heap_malloc(
        list->heap ,
        sizeof(XOC_ListNode) + list->element_size);
    if (XOC_LIKELY(node))
    {
        list->head->prev = node;
        node->next = list->head;
        node->prev = NULL;
        list->head = node;
        list->element_count ++;
        xoc_memory_copy(element , node->data , list->element_size);
        return xoc_true;
    }
    return xoc_false;
}

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_list_insert_node_to_head)(
    XOC_List *            list ,
    XOC_ListNode *        node
){
    list->head->prev = node;
    node->next = list->head;
    node->prev = NULL;
    list->head = node;
}

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_list_insert_node_to_tail)(
    XOC_List *            list ,
    XOC_ListNode *        node
){
    list->tail->next = node;
    node->prev = list->tail;
    node->next = NULL;
    list->tail = node;
}

void
XOC_IMPL(xoc_list_insert_node_to_tail_cas)(
    XOC_List *            list ,
    XOC_ListNode *        new_tail_node
){
    XOC_ListNode * old_tail = list->tail;
    while (xoc_atomic_cas(&list->tail , old_tail , new_tail_node))
    {
        old_tail = list->tail; 
        // Keep updating old_tail until the tail of list is no longer changed. 
    }
    
}

void
XOC_IMPL(xoc_list_insert_node_to_head_cas)(
    XOC_List *        list ,
    XOC_ListNode *    new_head_node
){
    XOC_ListNode * old_head = list->head;
    while (xoc_atomic_cas_strong_noexplicit(&list->head , old_head , new_head_node))
    {
        old_head = list->head; 
        // Keep updating old_head until the head of list is no longer changed. 
    }
}   

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_list_goto_next)(
    XOC_List * list
){
    list->cur = list->cur->next;
}

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_list_goto_prev)(
    XOC_List * list
){
    list->cur = list->cur->prev;
}

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_list_remove_cur)(
    XOC_List * list 
){
    list->cur->prev->next = list->cur->next;
    list->cur->next->prev = list->cur->prev;
    mi_free(list->cur);
    list->cur = list->cur->prev;
    list->element_count--;
}

xoc_size_t
XOC_IMPL(xoc_list_remove_front)(
    XOC_List * list ,
    xoc_size_t count
){
    xoc_size_t remove_count = 0;
    XOC_ListNode * now = list->head->prev , * prev;
    while (now && remove_count < count)
    {
        prev = now->prev;
        mi_free(now);
        now = prev;
    }
    if (now) // Is it not the first node?
    {
        list->head->prev = now;
        now->next = list->head;
    }
    else
    {
        list->head->prev = NULL;
    }
    list->element_count -= remove_count;
    return remove_count;
}

xoc_size_t
XOC_IMPL(xoc_list_remove_backward)(
    XOC_List * list ,
    xoc_size_t count
){
    xoc_size_t remove_count = 0;
    XOC_ListNode * now = list->cur->next , * next;
    while (now && remove_count < count)
    {
        next = now->next;
        mi_free(now);
        now = next;
    }
    if (now) // Is it not the last node?
    {
        list->cur->next = now;
        now->prev = list->cur;
    }
    else
    {
        list->cur->next = NULL;
    }
    list->element_count -= remove_count;
    return remove_count;
}

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_list_remove_head)(
    XOC_List * list
){
    XOC_ListNode * old_head_next = list->head->next;
    old_head_next->prev = NULL;
    mi_free(list->head);
    list->head = old_head_next;
    list->element_count--;
}

XOC_FORCE_INLINE
xoc_size_t
XOC_IMPL(xoc_list_get_element_count)(
    XOC_List * list
){
    return list->element_count;
}

XOC_FORCE_INLINE
xoc_size_t
XOC_IMPL(xoc_list_get_element_size)(
    XOC_List * list
){
    return list->element_size;
}

XOC_FORCE_INLINE
xoc_size_t
XOC_IMPL(xoc_list_get_data_size)(
    XOC_List * list
){
    return list->element_count * (list->element_size + sizeof(XOC_ListNode));
}

xoc_size_t
XOC_IMPL(xoc_list_move_ahead)(
    XOC_List * list ,
    xoc_size_t count
){
    xoc_size_t move_count = 0;
    while (list->cur->next && move_count < count)
    {
        list->cur = list->cur->next;
        move_count++;
    }
    return move_count;
}


xoc_size_t
XOC_IMPL(xoc_list_move_backward)(
    XOC_List *    list ,
    xoc_size_t   count
){
    xoc_size_t move_count = 0;
    while (list->cur->prev && move_count < count)
    {
        list->cur = list->cur->prev;
        move_count++;
    }
    return move_count;
}

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_list_goto_head)(
    XOC_List * list
){
    list->cur = list->head;
}

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_list_goto_tail)(
    XOC_List * list
){
    list->cur = list->tail;
}

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_list_remove_all)(
    XOC_List * list
){
    XOC_IMPL(xoc_list_remove_backward)(list , XOC_SIZE_T_MAX);
    XOC_IMPL(xoc_list_remove_front)(list , XOC_SIZE_T_MAX);
}

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_list_destory)(
    XOC_List * list
){
    (*(list->destructor))(list);
}



#if defined(__cplusplus)
}
#endif // __cplusplus