#pragma once
#define __XOC_POSIX_COMMON__

#include "base.h"

// Sometimes we need to store an interger int as a pointer.
// For example, store file descriptor in a pointer.
XOC_FORCE_INLINE
xoc_pointer_t
__xoc_write_pointer_as_int(
    xoc_pointer_t ** ptr , 
    int value
){
    return *(xoc_intmax_t *)ptr = value;
}

XOC_FORCE_INLINE
int
__xoc_read_pointer_as_int(
    xoc_pointer_t * ptr
){
    return *(xoc_intmax_t *)&ptr;
}