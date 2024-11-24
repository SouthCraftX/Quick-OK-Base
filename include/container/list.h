#pragma once
#define __QO_LIST_H__

#include "base.h"

struct _QO_List;
struct _QO_ListNode;
typedef struct _QO_ListNode QO_ListNode;
typedef struct _QO_List QO_List;

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

QO_FORCE_INLINE
qo_pointer_t
QO_INTERFACE(qo_list_get_cur)(
    QO_List * list
);

#if defined(__cplusplus)
}
#endif // __cplusplus

#include "internal/container/inline_impl/list.h"

#define qo_list_init            QO_INTERFACE(qo_list_init)
#define qo_list_get_element_size \
        QO_INTERFACE(qo_list_get_element_size)
#define qo_list_get_element_count \
        QO_INTERFACE(qo_list_get_element_count)
#define qo_list_get_data_size   QO_INTERFACE(qo_list_get_data_size)
#define qo_list_insert_head     QO_INTERFACE(qo_list_insert_head)
#define qo_list_insert_tail     QO_INTERFACE(qo_list_insert_tail)
#define qo_list_insert_ahead    QO_INTERFACE(qo_list_insert_ahead)
#define qo_list_insert_backward QO_INTERFACE(qo_list_insert_backward)
#define qo_list_insert_multiple_ahead \
        QO_INTERFACE(qo_list_insert_multiple_ahead)
#define qo_list_insert_multiple_backward \
        QO_INTERFACE(qo_list_insert_multiple_backward)
#define qo_list_remove_head     QO_INTERFACE(qo_list_remove_head)
#define qo_list_remove_tail     QO_INTERFACE(qo_list_remove_tail)
#define qo_list_remove_cur      QO_INTERFACE(qo_list_remove_cur)
#define qo_list_remove_front    QO_INTERFACE(qo_list_remove_front)
#define qo_list_remove_back     QO_INTERFACE(qo_list_remove_back)
#define qo_list_remove_all      QO_INTERFACE(qo_list_remove_all)
#define qo_list_move_ahead      QO_INTERFACE(qo_list_move_ahead)
#define qo_list_move_backward   QO_INTERFACE(qo_list_move_backward)
#define qo_list_goto_head       QO_INTERFACE(qo_list_goto_head)
#define qo_list_goto_tail       QO_INTERFACE(qo_list_goto_tail)
#define qo_list_destory         QO_INTERFACE(qo_list_destory)