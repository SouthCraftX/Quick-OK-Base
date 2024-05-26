#pragma once
#define __XOCEAN_LIST_H__

#include "base.h"

struct _XOceanList;
struct _XOceanListNode;
typedef struct _XOceanListNode XOceanListNode;
typedef struct _XOceanList XOceanList;

XOCEAN_FORCE_INLINE
xocean_pointer_t
XOCEAN_IMPL(xocean_list_get_cur)(
    XOceanList * list
);


#include "internel/container/inline_impl/list.h"