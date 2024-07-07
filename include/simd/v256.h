#pragma once

#include "simd.h"

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_clear256)(
    xoc_pointer_t    source
){
    _mm256_store_si256((__m256i *)source , _mm256_setzero_si256());
}

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_copy256)(
    xoc_pointer_t    source ,
    xoc_pointer_t    destination 
){
    _mm256_store_si256((__m256i *)destination , _mm_load_si256((__m256i *)source));
}

void
XOC_IMPL(xoc_256_array_copy)(
    xoc_pointer_t    source ,
    xoc_pointer_t    destination ,
    xoc_size_t       size
){
    for(xoc_pointer_t src = source; src < source + size; src += 32, destination += 32)
    {
        XOC_IMPL(xoc_copy256)(src , destination);
    }
}

void
XOC_IMPL(xoc_256_array_clear)(
    xoc_pointer_t    source  ,
    xoc_size_t       size
){
    for(xoc_pointer_t src = source; src < source + size; src += 32)
    {
        XOC_IMPL(xoc_clear256)(src);
    }
}

#define xoc_256_array_clear  XOC_INTERFACE(xoc_256_array_clear)
#define xoc_256_array_copy   XOC_INTERFACE(xoc_256_array_copy)