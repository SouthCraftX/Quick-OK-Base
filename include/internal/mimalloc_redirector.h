#pragma once
#define __QO_MIMALLOC_REDIRECTOR_H__

// for debug
#include "memalloc.h"

#if !defined(__QO_MEMALLOC_H__)
#   error Never include this header file directly. Use qo/memalloc.h instead.
#endif // !defined(__QO_MEMALLOC_H__)

#include <mimalloc.h>

#if defined(__cplusplus)
extern "C" {
#endif // defined(__cplusplus)

QO_NODISCARD QO_FORCE_INLINE
qo_pointer_t
QO_IMPL(qo_alloc)(
    qo_size_t      size
){
    return mi_malloc(size);
}

QO_NODISCARD QO_FORCE_INLINE
qo_pointer_t 
QO_IMPL(qo_small_alloc)(
    qo_size_t      size
){
    return mi_malloc_small(size);
}

QO_FORCE_INLINE 
qo_size_t
QO_IMPL(qo_get_max_small_alloc_size)()
{
    return MI_SMALL_SIZE_MAX;
}

QO_NODISCARD QO_FORCE_INLINE
qo_pointer_t 
QO_IMPL(qo_calloc)(
    qo_size_t      size
){
    return mi_calloc(1 , size);
}

QO_NODISCARD QO_FORCE_INLINE
qo_pointer_t
QO_IMPL(qo_realloc)(
    qo_pointer_t   memory ,
    qo_size_t      new_size
){
    return mi_realloc(memory , new_size);
}

QO_NODISCARD QO_FORCE_INLINE
qo_pointer_t
QO_IMPL(qo_recalloc)(
    qo_pointer_t   memory ,
    qo_size_t      new_size
){
    return mi_recalloc(memory , 1 ,new_size);
}

QO_FORCE_INLINE
void
QO_IMPL(qo_free)(
    qo_pointer_t memory
){
    mi_free(memory);
}

#if defined(__cplusplus)
}
#endif