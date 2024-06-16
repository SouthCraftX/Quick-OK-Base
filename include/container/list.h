#pragma once
#define __XOCEAN_LIST_H__

#include "base.h"

struct _XOceanList;
struct _XOceanListNode;
typedef struct _XOceanListNode XOceanListNode;
typedef struct _XOceanList XOceanList;

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

XOCEAN_FORCE_INLINE
xocean_pointer_t
XOCEAN_INTERFACE(xocean_list_get_cur)(
    XOceanList * list
);

#if defined(__cplusplus)
}
#endif // __cplusplus

#include "internel/container/inline_impl/list.h"

#define xocean_list_init            XOCEAN_INTERFACE(xocean_list_init)
#define xocean_list_get_element_size \
        XOCEAN_INTERFACE(xocean_list_get_element_size)
#define xocean_list_get_element_count \
        XOCEAN_INTERFACE(xocean_list_get_element_count)
#define xocean_list_get_data_size   XOCEAN_INTERFACE(xocean_list_get_data_size)
#define xocean_list_insert_head     XOCEAN_INTERFACE(xocean_list_insert_head)
#define xocean_list_insert_tail     XOCEAN_INTERFACE(xocean_list_insert_tail)
#define xocean_list_insert_ahead    XOCEAN_INTERFACE(xocean_list_insert_ahead)
#define xocean_list_insert_backward XOCEAN_INTERFACE(xocean_list_insert_backward)
#define xocean_list_insert_multiple_ahead \
        XOCEAN_INTERFACE(xocean_list_insert_multiple_ahead)
#define xocean_list_insert_multiple_backward \
        XOCEAN_INTERFACE(xocean_list_insert_multiple_backward)
#define xocean_list_remove_head     XOCEAN_INTERFACE(xocean_list_remove_head)
#define xocean_list_remove_tail     XOCEAN_INTERFACE(xocean_list_remove_tail)
#define xocean_list_remove_cur      XOCEAN_INTERFACE(xocean_list_remove_cur)
#define xocean_list_remove_front    XOCEAN_INTERFACE(xocean_list_remove_front)
#define xocean_list_remove_back     XOCEAN_INTERFACE(xocean_list_remove_back)
#define xocean_list_remove_all      XOCEAN_INTERFACE(xocean_list_remove_all)
#define xocean_list_move_ahead      XOCEAN_INTERFACE(xocean_list_move_ahead)
#define xocean_list_move_backward   XOCEAN_INTERFACE(xocean_list_move_backward)
#define xocean_list_goto_head       XOCEAN_INTERFACE(xocean_list_goto_head)
#define xocean_list_goto_tail       XOCEAN_INTERFACE(xocean_list_goto_tail)
#define xocean_list_destory         XOCEAN_INTERFACE(xocean_list_destory)