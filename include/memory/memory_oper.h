#pragma once
#include "../base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

void
XOC_INTERFACE(xoc_memory_copy)(
    xoc_pointer_t    source ,
    xoc_pointer_t    destination ,
    xoc_size_t       size
);

void
XOC_INTERFACE(xoc_memory_copy_align16)(
    xoc_pointer_t    source ,
    xoc_pointer_t    destination ,
    xoc_size_t       size
);

void
XOC_INTERFACE(xoc_memory_copy_align32)(
    xoc_pointer_t    source ,
    xoc_pointer_t    destination ,
    xoc_size_t       size
);

void
XOC_INTERFACE(xoc_memory_clear)(
    xoc_pointer_t    destination ,
    xoc_size_t       size
);

void
XOC_INTERFACE(xoc_memory_clear_align16)(
    xoc_pointer_t    destination ,
    xoc_size_t       size
);

void
XOC_INTERFACE(xoc_memory_clear_align32)(
    xoc_pointer_t    destination ,
    xoc_size_t       size
);

void
XOC_INTERFACE(xoc_memory_set_nonzero)(
    xoc_pointer_t    destination ,
    xoc_size_t       size ,
    xoc_uint8_t      value
);

void
XOC_INTERFACE(xoc_memory_set_nonzero_align16)(
    xoc_pointer_t    target ,
    xoc_uint64_t     value[2] ,
    xoc_size_t       size
);

void
XOC_INTERFACE(xoc_memory_set_nonzero_align32)(
    xoc_pointer_t    target ,
    xoc_uint64_t     value[4] ,
    xoc_size_t       size
);

void
XOC_INTERFACE(xoc_memory_move)(
    xoc_pointer_t    addr ,
    xoc_size_t       size ,
    xoc_offset_t     offset
);

void
XOC_INTERFACE(xoc_memory_move_align16)(
    xoc_pointer_t    addr ,
    xoc_size_t       size ,
    xoc_offset_t     offset
);

void
XOC_INTERFACE(xoc_memory_move_align32)(
    xoc_pointer_t    addr ,
    xoc_size_t       size ,
    xoc_offset_t     offset
);

XOC_FORCE_INLINE
void
XOC_INTERFACE(xoc_memory_set)(
    xoc_pointer_t    destination ,
    xoc_size_t       size ,
    xoc_uint8_t      value
){
    value ? XOC_INTERFACE(xoc_memory_set_nonzero)(destination , size , value) :
            XOC_INTERFACE(xoc_memory_clear)(destination , size);
}

#define xoc_memory_copy  XOC_INTERFACE(xoc_memory_copy)
#define xoc_memory_copy_align16  XOC_INTERFACE(xoc_memory_copy_align16)
#define xoc_memory_copy_align32  XOC_INTERFACE(xoc_memory_copy_align32)
#define xoc_memory_clear XOC_INTERFACE(xoc_memory_clear)
#define xoc_memory_clear_align16 XOC_INTERFACE(xoc_memory_clear)
#define xoc_memory_clear_align32 XOC_INTERFACE(xoc_memory_clear)
#define xoc_memory_set   XOC_INTERFACE(xoc_memory_set)
#define xoc_memory_set_nonzero   XOC_INTERFACE(xoc_memory_set_nonzero)

#if defined(__cplusplus)
}
#endif // __cplusplus

