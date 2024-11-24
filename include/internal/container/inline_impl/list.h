#pragma once
#define __QO_LIST_INLINE_IMPL_H__

#include "container_base.h"
#include "../memory/memory_oper.h"

#include "atomic.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _QO_ListNode
{
    QO_ListNode *    next;
    QO_ListNode *    prev;
    qo_byte_t       data[];
};
typedef struct _QO_ListNode QO_ListNode;

struct _QO_List
{
    qo_ref_count_t  ref_count;
    qo_bool_t       has_private_heap;
    qo_size_t       element_size;
    qo_size_t       element_count;
    QO_ListNode *    head;
    QO_ListNode *    tail;
    QO_ListNode *    cur;
    mi_heap_t *         heap;
    __qo_list_destructor_f destructor;
};
typedef struct _QO_List QO_List;
typedef void(*__qo_list_destructor_f)(QO_List *);

QO_FORCE_INLINE
qo_pointer_t
QO_IMPL(qo_list_get_cur)(
    QO_List * list
){
    return list->cur->data;
}

// @brief iterate the list forward from head
// @param list: the list to be iterated
// @param p: the pointer to be filled
#define QO_LIST_ITERATE_FORWARD(list , p) \
    for(QO_ListNode * ___cur_node = (list)->head ; \
        ___cur_node != NULL ; \
        (p) = ___cur_node->data , ___cur_node = ___cur_node->next)

// @brief iterate the list backward from tail
// @param list: the list to be iterated
// @param p: the pointer to be filled
#define QO_LIST_ITERATE_BACKWARD(list , p) \
    for(QO_ListNode * ___cur_node = (list)->tail ; \
        ___cur_node != NULL ; \
        (p) = ___cur_node->data , ___cur_node = ___cur_node->prev)

// @brief iterate the list forward from current node
// @param list: the list to be iterated
// @param p: the pointer to be filled
#define QO_LIST_CUR_ITERATE_FORWARD(list , p) \
    for(QO_ListNode * ___cur_node = (list)->cur ; \
        ___cur_node != NULL ; \
        (p) = ___cur_node->data , ___cur_node = ___cur_node->next)

// @brief iterate the list bacjward from current node 
// @param list: the list to be iterated
// @param p: the pointer to be filled
#define QO_LIST_CUR_ITERATE_BACKWARD(list , p) \
    for(QO_ListNode * ___cur_node = (list)->cur ; \
        ___cur_node != NULL ; \
        (p) = ___cur_node->data , ___cur_node = ___cur_node->prev)

// @brief iterate the list forward from head
// @param list: the list to be iterated
// @param cp: the pointer to be filled
#define QO_LIST_CONST_ITERATE_FORWARD(list , cp) \
    QO_LIST_ITERATE_FORWARD((list) , (const)cp)

// @brief iterate the list backward from tail
// @param list: the list to be iterated
// @param cp: the pointer to be filled
#define QO_LIST_CONST_ITERATE_BACKWARD(list , cp) \
    QO_LIST_ITERATE_BACKWARD((list) , (const)cp)

#define QO_LIST_ITERATE QO_LIST_ITERATE_FORWARD

void
__qo_list_cleanup_for_private_heap(
    QO_List * list
){
    mi_heap_delete(list->heap);
}

void
__qo_list_cleanup_for_shared_heap(
    QO_List * list
){
    qo_byte_t * p;
    QO_LIST_ITERATE_FORWARD(list , p)
    {
        mi_free(p - sizeof(QO_ListNode));
    }
}

void
QO_IMPL(qo_list_unref)(
    QO_List * list
){
    list->ref_count--;
    if (list->ref_count)
        return;
    list->destructor(list);
}

QO_FORCE_INLINE
qo_size_t
__qo_list_init_clac_alloc_size(
    qo_size_t element_size
){
    return sizeof(QO_List) + 
            (element_size + sizeof(QO_ListNode *)) *
            qo_get_container_init_alloc_element_count();
}

QO_FORCE_INLINE
void
__qo_list_prealloc(
    QO_List *    list ,
    qo_byte_t * mem ,
    qo_size_t   node_size
){
    const qo_size_t count = qo_get_container_init_alloc_element_count();
    QO_ListNode * prev_node = ((QO_ListNode *)mem) , * node;
    ((QO_ListNode *)mem)->prev = NULL;
    for (qo_size_t i = 1; i < count; i++)
    {
        node = (QO_ListNode *)(mem + i * node_size);
        node->prev = prev_node;
        prev_node->next = node;
        prev_node = node;
    }
    node->next = NULL;
    list->head = (QO_ListNode *)mem;
    list->tail = node;
    list->cur  = (QO_ListNode *)mem;
}

qo_stat_t
QO_IMPL(qo_list_init)(
    QO_List *    list ,
    qo_size_t   element_size ,
    qo_flag32_t mode
){
    mi_heap_t * heap = __qo_container_acquire_heap(mode);
    if (heap)
    {
        const qo_size_t prealloc_size = (element_size + sizeof(QO_ListNode) *
            _qo_get_container_init_alloc_element_count());
        qo_pointer_t mem = mi_heap_malloc(heap , prealloc_size);
        if (mem)
        {
            __qo_list_prealloc(list , (qo_byte_t *)mem , 
                                   element_size + sizeof(QO_ListNode *));
            list->heap = heap;
            list->element_size = element_size;
            list->has_private_heap = QO_HAS_FLAG(
                mode , 
                QO_CONTAINER_PRIVATE_HEAP
            );
            list->destructor = list->has_private_heap ? 
                __qo_list_cleanup_for_private_heap :
                __qo_list_cleanup_for_shared_heap;
            return QO_OK;   
        }
        return QO_OUT_OF_MEMORY;
    }
    return QO_OUT_OF_MEMORY;
}

QO_FORCE_INLINE
qo_size_t
__qo_list_node_clac_size(
    QO_List * list
){
    return sizeof(QO_ListNode) + list->element_size;
}

QO_FORCE_INLINE
void
QO_IMPL(qo_list_insert_node_ahead)(
    QO_List *        list ,
    QO_ListNode *    node
){
    node->next = list->cur;
    node->prev = list->cur->prev;
    list->cur->prev->next = node;
    list->cur->prev = node;
}


QO_FORCE_INLINE
qo_bool_t
QO_IMPL(qo_list_insert_ahead)(
    QO_List * list,
    qo_pointer_t p_element
){
    QO_ListNode * new_node = (QO_ListNode *)mi_heap_malloc(list->heap , 
                                __qo_list_node_clac_size(list));
    if (new_node)
    {
        if (p_element)
            qo_memory_copy(p_element , new_node->data , list->element_size);
        new_node->next = list->cur->next;
        new_node->prev = list->cur;
        list->cur->next = new_node;
        return qo_true;
    }
    return qo_false;
}


QO_FORCE_INLINE
void
QO_IMPL(qo_list_set)(
    QO_List * list ,
    qo_pointer_t p_element
){
    qo_pointer_t p;
    QO_LIST_ITERATE(list , p)
    {
        qo_memory_copy(p_element , p , list->element_size);
    }
}

QO_FORCE_INLINE
qo_bool_t
QO_IMPL(qo_list_insert_backward)(
    QO_List * list ,
    qo_pointer_t p_element
){
    QO_ListNode * new_node = (QO_ListNode *)mi_heap_malloc(list->heap , 
                                __qo_list_node_clac_size(list));
    if (new_node)
    {
        if (p_element)
            qo_memory_copy(p_element , new_node->data , list->element_size);
        new_node->next = list->cur;
        new_node->prev = list->cur->prev;
        list->cur->prev = new_node;
        return qo_true;
    }
    return qo_false;
}

QO_FORCE_INLINE
qo_size_t
QO_IMPL(qo_list_insert_multiple_ahead)(
    QO_List *    list ,
    qo_byte_t * p_elements ,
    qo_size_t   count
){
    qo_size_t inserted_count = 0;
    for ( ; inserted_count < count ; inserted_count++)
    {
        if (QO_INTERFACE(qo_list_insert_ahead)(list , p_elements))
        {
            p_elements += list->element_size;
        }
        break;
    }
    list->element_count += inserted_count;
    return inserted_count;
}

QO_FORCE_INLINE
qo_size_t
QO_IMPL(qo_list_insert_multiple_backward)(
    QO_List *    list ,
    qo_byte_t * p_elements ,
    qo_size_t   count
){
    qo_size_t inserted_count = 0;
    for ( ; inserted_count < count ; inserted_count++)
    {
        if (QO_INTERFACE(qo_list_insert_backward)(list , p_elements))
        {
            p_elements += list->element_size;
        }
        break;
    }
    list->element_count += inserted_count;
    return inserted_count;
}

QO_FORCE_INLINE
qo_bool_t
QO_IMPL(qo_list_insert_tail)(
    QO_List *            list ,
    const qo_pointer_t  element
){
    QO_ListNode * node = (QO_ListNode*)mi_heap_malloc(
        list->heap , 
        sizeof(QO_ListNode) + list->element_size
    );
    if (node)
    {
        list->tail->next = node;
        node->prev = list->tail;
        node->next = NULL;
        list->tail = node;
        list->element_count ++;
        qo_memory_copy(element , node->data , list->element_size);
        return qo_true;
    }
    return qo_false;
}

QO_FORCE_INLINE
qo_bool_t
QO_IMPL(qo_list_insert_head)(
    QO_List *            list ,
    const qo_pointer_t  element
){
    QO_ListNode * node = (QO_ListNode*)mi_heap_malloc(
        list->heap ,
        sizeof(QO_ListNode) + list->element_size);
    if (QO_LIKELY(node))
    {
        list->head->prev = node;
        node->next = list->head;
        node->prev = NULL;
        list->head = node;
        list->element_count ++;
        qo_memory_copy(element , node->data , list->element_size);
        return qo_true;
    }
    return qo_false;
}

QO_FORCE_INLINE
void
QO_IMPL(qo_list_insert_node_to_head)(
    QO_List *            list ,
    QO_ListNode *        node
){
    list->head->prev = node;
    node->next = list->head;
    node->prev = NULL;
    list->head = node;
}

QO_FORCE_INLINE
void
QO_IMPL(qo_list_insert_node_to_tail)(
    QO_List *            list ,
    QO_ListNode *        node
){
    list->tail->next = node;
    node->prev = list->tail;
    node->next = NULL;
    list->tail = node;
}

void
QO_IMPL(qo_list_insert_node_to_tail_cas)(
    QO_List *            list ,
    QO_ListNode *        new_tail_node
){
    QO_ListNode * old_tail = list->tail;
    while (qo_atomic_cas(&list->tail , old_tail , new_tail_node))
    {
        old_tail = list->tail; 
        // Keep updating old_tail until the tail of list is no longer changed. 
    }
    
}

void
QO_IMPL(qo_list_insert_node_to_head_cas)(
    QO_List *        list ,
    QO_ListNode *    new_head_node
){
    QO_ListNode * old_head = list->head;
    while (qo_atomic_cas_strong_noexplicit(&list->head , old_head , new_head_node))
    {
        old_head = list->head; 
        // Keep updating old_head until the head of list is no longer changed. 
    }
}   

QO_FORCE_INLINE
void
QO_IMPL(qo_list_goto_next)(
    QO_List * list
){
    list->cur = list->cur->next;
}

QO_FORCE_INLINE
void
QO_IMPL(qo_list_goto_prev)(
    QO_List * list
){
    list->cur = list->cur->prev;
}

QO_FORCE_INLINE
void
QO_IMPL(qo_list_remove_cur)(
    QO_List * list 
){
    list->cur->prev->next = list->cur->next;
    list->cur->next->prev = list->cur->prev;
    mi_free(list->cur);
    list->cur = list->cur->prev;
    list->element_count--;
}

qo_size_t
QO_IMPL(qo_list_remove_front)(
    QO_List * list ,
    qo_size_t count
){
    qo_size_t remove_count = 0;
    QO_ListNode * now = list->head->prev , * prev;
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

qo_size_t
QO_IMPL(qo_list_remove_backward)(
    QO_List * list ,
    qo_size_t count
){
    qo_size_t remove_count = 0;
    QO_ListNode * now = list->cur->next , * next;
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

QO_FORCE_INLINE
void
QO_IMPL(qo_list_remove_head)(
    QO_List * list
){
    QO_ListNode * old_head_next = list->head->next;
    old_head_next->prev = NULL;
    mi_free(list->head);
    list->head = old_head_next;
    list->element_count--;
}

QO_FORCE_INLINE
qo_size_t
QO_IMPL(qo_list_get_element_count)(
    QO_List * list
){
    return list->element_count;
}

QO_FORCE_INLINE
qo_size_t
QO_IMPL(qo_list_get_element_size)(
    QO_List * list
){
    return list->element_size;
}

QO_FORCE_INLINE
qo_size_t
QO_IMPL(qo_list_get_data_size)(
    QO_List * list
){
    return list->element_count * (list->element_size + sizeof(QO_ListNode));
}

qo_size_t
QO_IMPL(qo_list_move_ahead)(
    QO_List * list ,
    qo_size_t count
){
    qo_size_t move_count = 0;
    while (list->cur->next && move_count < count)
    {
        list->cur = list->cur->next;
        move_count++;
    }
    return move_count;
}


qo_size_t
QO_IMPL(qo_list_move_backward)(
    QO_List *    list ,
    qo_size_t   count
){
    qo_size_t move_count = 0;
    while (list->cur->prev && move_count < count)
    {
        list->cur = list->cur->prev;
        move_count++;
    }
    return move_count;
}

QO_FORCE_INLINE
void
QO_IMPL(qo_list_goto_head)(
    QO_List * list
){
    list->cur = list->head;
}

QO_FORCE_INLINE
void
QO_IMPL(qo_list_goto_tail)(
    QO_List * list
){
    list->cur = list->tail;
}

QO_FORCE_INLINE
void
QO_IMPL(qo_list_remove_all)(
    QO_List * list
){
    QO_IMPL(qo_list_remove_backward)(list , QO_SIZE_T_MAX);
    QO_IMPL(qo_list_remove_front)(list , QO_SIZE_T_MAX);
}

QO_FORCE_INLINE
void
QO_IMPL(qo_list_destory)(
    QO_List * list
){
    (*(list->destructor))(list);
}



#if defined(__cplusplus)
}
#endif // __cplusplus