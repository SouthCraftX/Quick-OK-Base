#pragma once

#include "simd.h"

XOCEAN_FORCE_INLINE
void
XOCEAN_IMPL(xocean_clear256)(
    xocean_pointer_t    source
){
    _mm256_store_si256((__m256i *)source , _mm256_setzero_si256());
}

XOCEAN_FORCE_INLINE
void
XOCEAN_IMPL(xocean_copy256)(
    xocean_pointer_t    source ,
    xocean_pointer_t    destination 
){
    _mm256_store_si256((__m256i *)destination , _mm_load_si256((__m256i *)source));
}

void
XOCEAN_IMPL(xocean_256_array_copy)(
    xocean_pointer_t    source ,
    xocean_pointer_t    destination ,
    xocean_size_t       size
){
    for(xocean_pointer_t src = source; src < source + size; src += 32, destination += 32)
    {
        XOCEAN_IMPL(xocean_copy256)(src , destination);
    }
}

void
XOCEAN_IMPL(xocean_256_array_clear)(
    xocean_pointer_t    source  ,
    xocean_size_t       size
){
    for(xocean_pointer_t src = source; src < source + size; src += 32)
    {
        XOCEAN_IMPL(xocean_clear256)(src);
    }
}

#define xocean_256_array_clear  XOCEAN_INTERFACE(xocean_256_array_clear)
#define xocean_256_array_copy   XOCEAN_INTERFACE(xocean_256_array_copy)