#pragma once
#include "../base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

void
QO_INTERFACE(qo_memory_copy)(
    qo_pointer_t    source ,
    qo_pointer_t    destination ,
    qo_size_t       size
);

void
QO_INTERFACE(qo_memory_copy_align16)(
    qo_pointer_t    source ,
    qo_pointer_t    destination ,
    qo_size_t       size
);

void
QO_INTERFACE(qo_memory_copy_align32)(
    qo_pointer_t    source ,
    qo_pointer_t    destination ,
    qo_size_t       size
);

void
QO_INTERFACE(qo_memory_clear)(
    qo_pointer_t    destination ,
    qo_size_t       size
);

void
QO_INTERFACE(qo_memory_clear_align16)(
    qo_pointer_t    destination ,
    qo_size_t       size
);

void
QO_INTERFACE(qo_memory_clear_align32)(
    qo_pointer_t    destination ,
    qo_size_t       size
);

void
QO_INTERFACE(qo_memory_set_nonzero)(
    qo_pointer_t    destination ,
    qo_size_t       size ,
    qo_uint8_t      value
);

void
QO_INTERFACE(qo_memory_set_nonzero_align16)(
    qo_pointer_t    target ,
    qo_uint64_t     value[2] ,
    qo_size_t       size
);

void
QO_INTERFACE(qo_memory_set_nonzero_align32)(
    qo_pointer_t    target ,
    qo_uint64_t     value[4] ,
    qo_size_t       size
);

void
QO_INTERFACE(qo_memory_move)(
    qo_pointer_t    addr ,
    qo_size_t       size ,
    qo_offset_t     offset
);

void
QO_INTERFACE(qo_memory_move_align16)(
    qo_pointer_t    addr ,
    qo_size_t       size ,
    qo_offset_t     offset
);

void
QO_INTERFACE(qo_memory_move_align32)(
    qo_pointer_t    addr ,
    qo_size_t       size ,
    qo_offset_t     offset
);

QO_FORCE_INLINE
void
QO_INTERFACE(qo_memory_set)(
    qo_pointer_t    destination ,
    qo_size_t       size ,
    qo_uint8_t      value
){
    value ? QO_INTERFACE(qo_memory_set_nonzero)(destination , size , value) :
            QO_INTERFACE(qo_memory_clear)(destination , size);
}

#define qo_memory_copy  QO_INTERFACE(qo_memory_copy)
#define qo_memory_copy_align16  QO_INTERFACE(qo_memory_copy_align16)
#define qo_memory_copy_align32  QO_INTERFACE(qo_memory_copy_align32)
#define qo_memory_clear QO_INTERFACE(qo_memory_clear)
#define qo_memory_clear_align16 QO_INTERFACE(qo_memory_clear)
#define qo_memory_clear_align32 QO_INTERFACE(qo_memory_clear)
#define qo_memory_set   QO_INTERFACE(qo_memory_set)
#define qo_memory_set_nonzero   QO_INTERFACE(qo_memory_set_nonzero)

#if defined(__cplusplus)
}
#endif // __cplusplus

