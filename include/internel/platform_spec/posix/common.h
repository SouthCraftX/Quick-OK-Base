#pragma once
#define __XOCEAN_POSIX_COMMON__

#include "base.h"

// Sometimes we need to store an interger int as a pointer.
// For example, store file descriptor in a pointer.
XOCEAN_FORCE_INLINE
void
__xocean_write_ptr_as_int(
    xocean_pointer_t * ptr , 
    int value
){
    *(xocean_intmax_t *)&ptr = value;
}

XOCEAN_FORCE_INLINE
int
__xocean_read_ptr_as_int(
    xocean_pointer_t * ptr
){
    return *(xocean_intmax_t *)&ptr;
}