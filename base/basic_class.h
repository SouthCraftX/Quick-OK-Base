#pragma once

#include "types.h"
#include "attribute.h"
#include "platform.h"
#include "stat.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOceanClassBase
{
    xocean_stat_t   stat;
    xocean_flag32_t trait;
};

typedef _XOceanClassBase XOceanClassBase;
typedef XOceanClassBase XOceanClass;

XOCEAN_FORCE_INLINE
void xocean_class_set_stat(XOceanClass * __class, xocean_stat_t stat)
{
    __class->stat = stat;
}

XOCEAN_FORCE_INLINE
xocean_stat_t xocean_class_get_stat(XOceanClass * __class)
{
    return __class->stat;
}

XOCEAN_FORCE_INLINE
xocean_flag32_t xocean_class_get_trait(XOceanClass * __class)
{
    return __class->trait;
}

XOCEAN_FORCE_INLINE
void xocean_class_set_trait(XOceanClass * __class, xocean_flag32_t trait)
{
    __class->trait = trait;
}

enum
{
    XOCEAN_CLASS_TYPE_NONE = 0,
    XOCEAN_CLASS_TYPE_FSTREAM_BASE,
    XOCEAN_CLASS_TYPE_IFSTREAM,
    XOCEAN_CLASS_TYPE_IOFSTREAM,
    XOCEAN_CLASS_TYPE_PIPE,
    XOCEAN_CLASS_TYPE_MEMPOOL,
    XOCEAN_CLASS_TYPE_FORWARD_LIST,
    XOCEAN_CLASS_TYPE_LIST,
    XOCEAN_CLASS_TYPE_MAP,
    XOCEAN_CLASS_TYPE_PAIR,
    XOCEAN_CLASS_TYPE_SET,
    XOCEAN_CLASS_TYPE_RBTREE,
    XOCEAN_CLASS_TYPE_ITERATOR_BASE,
    XOCEAN_CLASS_TYPE_ARRAY_ITERATOR,
    XOCEAN_CLASS_TYPE_LIST_ITERATOR,

} XOCEAN_CLASS_TYPE;

#if defined(__cplusplus)
}
#endif // __cplusplus