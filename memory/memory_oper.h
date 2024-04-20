#pragma once
#include "../base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

void
XOCEAN_INTERFACE(xocean_memory_copy)(
    xocean_pointer_t    source ,
    xocean_pointer_t    destination ,
    xocean_size_t       size
);

void
XOCEAN_INTERFACE(xocean_memory_copy_align16)(
    xocean_pointer_t    source ,
    xocean_pointer_t    destination ,
    xocean_size_t       size
);

void
XOCEAN_INTERFACE(xocean_memory_copy_align32)(
    xocean_pointer_t    source ,
    xocean_pointer_t    destination ,
    xocean_size_t       size
);

void
XOCEAN_INTERFACE(xocean_memory_clear)(
    xocean_pointer_t    destination ,
    xocean_size_t       size
);

void
XOCEAN_INTERFACE(xocean_memory_clear_align16)(
    xocean_pointer_t    destination ,
    xocean_size_t       size
);

void
XOCEAN_INTERFACE(xocean_memory_clear_align32)(
    xocean_pointer_t    destination ,
    xocean_size_t       size
);

void
XOCEAN_INTERFACE(xocean_memory_set_nonzero)(
    xocean_pointer_t    destination ,
    xocean_size_t       size ,
    xocean_uint8_t      value
);

void
XOCEAN_INTERFACE(xocean_memory_set_nonzero_align16)(
    xocean_pointer_t    target ,
    xocean_uint64_t     value[2] ,
    xocean_size_t       size
);

void
XOCEAN_INTERFACE(xocean_memory_set_nonzero_align32)(
    xocean_pointer_t    target ,
    xocean_uint64_t     value[4] ,
    xocean_size_t       size
);

void
XOCEAN_INTERFACE(xocean_memory_move)(
    xocean_pointer_t    addr ,
    xocean_size_t       size ,
    xocean_offset_t     offset
);

void
XOCEAN_INTERFACE(xocean_memory_move_align16)(
    xocean_pointer_t    addr ,
    xocean_size_t       size ,
    xocean_offset_t     offset
);

void
XOCEAN_INTERFACE(xocean_memory_move_align32)(
    xocean_pointer_t    addr ,
    xocean_size_t       size ,
    xocean_offset_t     offset
);

XOCEAN_FORCE_INLINE
void
XOCEAN_INTERFACE(xocean_memory_set)(
    xocean_pointer_t    destination ,
    xocean_size_t       size ,
    xocean_uint8_t      value
){
    value ? XOCEAN_INTERFACE(xocean_memory_set_nonzero)(destination , size , value) :
            XOCEAN_INTERFACE(xocean_memory_clear)(destination , size);
}

#define xocean_memory_copy  XOCEAN_INTERFACE(xocean_memory_copy)
#define xocean_memory_copy_align16  XOCEAN_INTERFACE(xocean_memory_copy_align16)
#define xocean_memory_copy_align32  XOCEAN_INTERFACE(xocean_memory_copy_align32)
#define xocean_memory_clear XOCEAN_INTERFACE(xocean_memory_clear)
#define xocean_memory_clear_align16 XOCEAN_INTERFACE(xocean_memory_clear)
#define xocean_memory_clear_align32 XOCEAN_INTERFACE(xocean_memory_clear)
#define xocean_memory_set   XOCEAN_INTERFACE(xocean_memory_set)
#define xocean_memory_set_nonzero   XOCEAN_INTERFACE(xocean_memory_set_nonzero)

#if defined(__cplusplus)
}
#endif // __cplusplus

