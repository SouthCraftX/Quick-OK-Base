#pragma once

#include "simd.h"

QO_FORCE_INLINE
void
QO_IMPL(qo_clear256)(
    qo_pointer_t    source
){
    _mm256_store_si256((__m256i *)source , _mm256_setzero_si256());
}

QO_FORCE_INLINE
void
QO_IMPL(qo_copy256)(
    qo_pointer_t    source ,
    qo_pointer_t    destination 
){
    _mm256_store_si256((__m256i *)destination , _mm_load_si256((__m256i *)source));
}

void
QO_IMPL(qo_256_array_copy)(
    qo_pointer_t    source ,
    qo_pointer_t    destination ,
    qo_size_t       size
){
    for(qo_pointer_t src = source; src < source + size; src += 32, destination += 32)
    {
        QO_IMPL(qo_copy256)(src , destination);
    }
}

void
QO_IMPL(qo_256_array_clear)(
    qo_pointer_t    source  ,
    qo_size_t       size
){
    for(qo_pointer_t src = source; src < source + size; src += 32)
    {
        QO_IMPL(qo_clear256)(src);
    }
}

#define qo_256_array_clear  QO_INTERFACE(qo_256_array_clear)
#define qo_256_array_copy   QO_INTERFACE(qo_256_array_copy)