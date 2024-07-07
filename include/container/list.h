#pragma once
#define __XOC_LIST_H__

#include "base.h"

struct _XOC_List;
struct _XOC_ListNode;
typedef struct _XOC_ListNode XOC_ListNode;
typedef struct _XOC_List XOC_List;

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

XOC_FORCE_INLINE
xoc_pointer_t
XOC_INTERFACE(xoc_list_get_cur)(
    XOC_List * list
);

#if defined(__cplusplus)
}
#endif // __cplusplus

#include "internel/container/inline_impl/list.h"

#define xoc_list_init            XOC_INTERFACE(xoc_list_init)
#define xoc_list_get_element_size \
        XOC_INTERFACE(xoc_list_get_element_size)
#define xoc_list_get_element_count \
        XOC_INTERFACE(xoc_list_get_element_count)
#define xoc_list_get_data_size   XOC_INTERFACE(xoc_list_get_data_size)
#define xoc_list_insert_head     XOC_INTERFACE(xoc_list_insert_head)
#define xoc_list_insert_tail     XOC_INTERFACE(xoc_list_insert_tail)
#define xoc_list_insert_ahead    XOC_INTERFACE(xoc_list_insert_ahead)
#define xoc_list_insert_backward XOC_INTERFACE(xoc_list_insert_backward)
#define xoc_list_insert_multiple_ahead \
        XOC_INTERFACE(xoc_list_insert_multiple_ahead)
#define xoc_list_insert_multiple_backward \
        XOC_INTERFACE(xoc_list_insert_multiple_backward)
#define xoc_list_remove_head     XOC_INTERFACE(xoc_list_remove_head)
#define xoc_list_remove_tail     XOC_INTERFACE(xoc_list_remove_tail)
#define xoc_list_remove_cur      XOC_INTERFACE(xoc_list_remove_cur)
#define xoc_list_remove_front    XOC_INTERFACE(xoc_list_remove_front)
#define xoc_list_remove_back     XOC_INTERFACE(xoc_list_remove_back)
#define xoc_list_remove_all      XOC_INTERFACE(xoc_list_remove_all)
#define xoc_list_move_ahead      XOC_INTERFACE(xoc_list_move_ahead)
#define xoc_list_move_backward   XOC_INTERFACE(xoc_list_move_backward)
#define xoc_list_goto_head       XOC_INTERFACE(xoc_list_goto_head)
#define xoc_list_goto_tail       XOC_INTERFACE(xoc_list_goto_tail)
#define xoc_list_destory         XOC_INTERFACE(xoc_list_destory)