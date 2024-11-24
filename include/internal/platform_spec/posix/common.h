#pragma once
#define __QO_POSIX_COMMON__

#include "base.h"

// Sometimes we need to store an interger int as a pointer.
// For example, store file descriptor in a pointer.
QO_FORCE_INLINE
qo_pointer_t
__qo_write_pointer_as_int(
    qo_pointer_t ** ptr , 
    int value
){
    return *(qo_intmax_t *)ptr = value;
}

QO_FORCE_INLINE
int
__qo_read_pointer_as_int(
    qo_pointer_t * ptr
){
    return *(qo_intmax_t *)&ptr;
}