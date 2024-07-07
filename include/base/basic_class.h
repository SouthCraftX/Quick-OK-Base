#pragma once

#include "types.h"
#include "attribute.h"
#include "platform.h"
#include "stat.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOCClassBase
{
    xoc_stat_t   stat;
    xoc_flag32_t trait;
};

typedef _XOCClassBase XOCClassBase;
typedef XOCClassBase XOCClass;

XOC_FORCE_INLINE
void xoc_class_set_stat(XOCClass * __class, xoc_stat_t stat)
{
    __class->stat = stat;
}

XOC_FORCE_INLINE
xoc_stat_t xoc_class_get_stat(XOCClass * __class)
{
    return __class->stat;
}

XOC_FORCE_INLINE
xoc_flag32_t xoc_class_get_trait(XOCClass * __class)
{
    return __class->trait;
}

XOC_FORCE_INLINE
void xoc_class_set_trait(XOCClass * __class, xoc_flag32_t trait)
{
    __class->trait = trait;
}

enum
{
    XOC_CLASS_TYPE_NONE = 0,
    XOC_CLASS_TYPE_FSTREAM_BASE,
    XOC_CLASS_TYPE_IFSTREAM,
    XOC_CLASS_TYPE_IOFSTREAM,
    XOC_CLASS_TYPE_PIPE,
    XOC_CLASS_TYPE_MEMPOOL,
    XOC_CLASS_TYPE_FORWARD_LIST,
    XOC_CLASS_TYPE_LIST,
    XOC_CLASS_TYPE_MAP,
    XOC_CLASS_TYPE_PAIR,
    XOC_CLASS_TYPE_SET,
    XOC_CLASS_TYPE_RBTREE,
    XOC_CLASS_TYPE_ITERATOR_BASE,
    XOC_CLASS_TYPE_ARRAY_ITERATOR,
    XOC_CLASS_TYPE_LIST_ITERATOR,

} XOC_CLASS_TYPE;

#if defined(__cplusplus)
}
#endif // __cplusplus