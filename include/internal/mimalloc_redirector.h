#pragma once
#define __XOC_MIMALLOC_REDIRECTOR_H__

// for debug
#include "memalloc.h"

#if !defined(__XOC_MEMALLOC_H__)
#   error Never include this header file directly. Use xoc/memalloc.h instead.
#endif // !defined(__XOC_MEMALLOC_H__)

#include <mimalloc.h>

#if defined(__cplusplus)
extern "C" {
#endif // defined(__cplusplus)

XOC_NODISCARD XOC_FORCE_INLINE
xoc_pointer_t
XOC_IMPL(xoc_alloc)(
    xoc_size_t      size
){
    return mi_malloc(size);
}

XOC_NODISCARD XOC_FORCE_INLINE
xoc_pointer_t 
XOC_IMPL(xoc_small_alloc)(
    xoc_size_t      size
){
    return mi_malloc_small(size);
}

XOC_FORCE_INLINE 
xoc_size_t
XOC_IMPL(xoc_get_max_small_alloc_size)()
{
    return MI_SMALL_SIZE_MAX;
}

XOC_NODISCARD XOC_FORCE_INLINE
xoc_pointer_t 
XOC_IMPL(xoc_calloc)(
    xoc_size_t      size
){
    return mi_calloc(1 , size);
}

XOC_NODISCARD XOC_FORCE_INLINE
xoc_pointer_t
XOC_IMPL(xoc_realloc)(
    xoc_pointer_t   memory ,
    xoc_size_t      new_size
){
    return mi_realloc(memory , new_size);
}

XOC_NODISCARD XOC_FORCE_INLINE
xoc_pointer_t
XOC_IMPL(xoc_recalloc)(
    xoc_pointer_t   memory ,
    xoc_size_t      new_size
){
    return mi_recalloc(memory , 1 ,new_size);
}

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_free)(
    xoc_pointer_t memory
){
    mi_free(memory);
}

#if defined(__cplusplus)
}
#endif