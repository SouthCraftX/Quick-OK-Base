#pragma once

#include "types.h"
#include "attribute.h"
#include "platform.h"
#include "stat.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _QOClassBase
{
    qo_stat_t   stat;
    qo_flag32_t trait;
};

typedef _QOClassBase QOClassBase;
typedef QOClassBase QOClass;

QO_FORCE_INLINE
void qo_class_set_stat(QOClass * __class, qo_stat_t stat)
{
    __class->stat = stat;
}

QO_FORCE_INLINE
qo_stat_t qo_class_get_stat(QOClass * __class)
{
    return __class->stat;
}

QO_FORCE_INLINE
qo_flag32_t qo_class_get_trait(QOClass * __class)
{
    return __class->trait;
}

QO_FORCE_INLINE
void qo_class_set_trait(QOClass * __class, qo_flag32_t trait)
{
    __class->trait = trait;
}

enum
{
    QO_CLASS_TYPE_NONE = 0,
    QO_CLASS_TYPE_FSTREAM_BASE,
    QO_CLASS_TYPE_IFSTREAM,
    QO_CLASS_TYPE_IOFSTREAM,
    QO_CLASS_TYPE_PIPE,
    QO_CLASS_TYPE_MEMPOOL,
    QO_CLASS_TYPE_FORWARD_LIST,
    QO_CLASS_TYPE_LIST,
    QO_CLASS_TYPE_MAP,
    QO_CLASS_TYPE_PAIR,
    QO_CLASS_TYPE_SET,
    QO_CLASS_TYPE_RBTREE,
    QO_CLASS_TYPE_ITERATOR_BASE,
    QO_CLASS_TYPE_ARRAY_ITERATOR,
    QO_CLASS_TYPE_LIST_ITERATOR,

} QO_CLASS_TYPE;

#if defined(__cplusplus)
}
#endif // __cplusplus