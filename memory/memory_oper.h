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
XOCEAN_INTERFACE(xocean_memory_clear)(
    xocean_pointer_t    destination ,
    xocean_size_t       size
);

void
XOCEAN_INTERFACE(xocean_memory_set_nonzero)(
    xocean_pointer_t    destination ,
    xocean_size_t       size ,
    xocean_uint8_t      value
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

#define xocean_memory_copy(source , destination, size) \
        XOCEAN_INTERFACE(xocean_memory_copy)(source , destination , size)
    
#define xocean_memory_clear(destination, size) \
        XOCEAN_INTERFACE(xocean_memory_clear)(destination , size)
    
#define xocean_memory_set(destination, size, value) \
        XOCEAN_INTERFACE(xocean_memory_set)(destination , size , value)

#define xocean_memory_set_nonzero(destination, size, value) \
        XOCEAN_INTERFACE(xocean_memory_set_nonzero)(destination , size , value)

#if defined(__cplusplus)
}
#endif // __cplusplus

