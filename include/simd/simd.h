#pragma once

#include "../base.h"
#include <immintrin.h>

#pragma intrinsic(_mm_load_si128)
#pragma intrinsic(_mm_loadu_si128)
#pragma intrinsic(_mm_store_si128)
#pragma intrinsic(_mm_storeu_si128)
#pragma intrinsic(_mm_cmpeq_epi8)
#pragma intrinsic(_mm_cmpeq_epi16)
#pragma intrinsic(_mm_cmpeq_epi32)
#pragma intrinsic(_mm_cmpeq_epi64)
#pragma intrinsic(_mm_cmpeq_epi8)
#pragma intrinsic(_mm_cmpeq_epi16)
#pragma intrinsic(_mm_cmpeq_epi32)
#pragma intrinsic(_mm_cmpeq_epi64)
#pragma intrinsic(_mm_add_epi8)
#pragma intrinsic(_mm_add_epi16)
#pragma intrinsic(_mm_add_epi32)
#pragma intrinsic(_mm_add_epi64)
#pragma intrinsic(_mm_sub_epi8)
#pragma intrinsic(_mm_sub_epi16)
#pragma intrinsic(_mm_sub_epi32)
#pragma intrinsic(_mm_sub_epi64)
#pragma intrinsic(_mm_div_epi16)
#pragma intrinsic(_mm_div_epi32)
#pragma intrinsic(_mm_div_epi64)
#pragma intrinsic(_mm_mul_epi16)
#pragma intrinsic(_mm_mul_epi32)
#pragma intrinsic(_mm_mul_epi64)
#pragma intrinsic(_mm_max_epi8)
#pragma intrinsic(_mm_max_epi16)
#pragma intrinsic(_mm_max_epi32)
#pragma intrinsic(_mm_max_epi64)
#pragma intrinsic(_mm_min_epi8)
#pragma intrinsic(_mm_min_epi16)
#pragma intrinsic(_mm_min_epi32)
#pragma intrinsic(_mm_min_epi64)
#pragma intrinsic(_mm_and_si128)
#pragma intrinsic(_mm_or_si128)
#pragma intrinsic(_mm_xor_si128)

#if (defined(QO_WANT_SIMD_256) || defined(QO_WANT_SIMD_512))
#   pragma intrinsic(_mm256_storeu_si256)
#   pragma intrinsic(_mm256_loadu_si256)
#   pragma intrinsic(_mm256_set1_epi8)
#   pragma intrinsic(_mm256_set1_epi16)
#   pragma intrinsic(_mm256_set1_epi32)
#   pragma intrinsic(_mm256_set1_epi64)
#   pragma intrinsic(_mm256_set_epi8)
#   pragma intrinsic(_mm256_set_epi16)
#   pragma intrinsic(_mm256_set_epi32)
#   pragma intrinsic(_mm256_set_epi64)
#   pragma intrinsic(_mm256_add_epi8)
#   pragma intrinsic(_mm256_add_epi16)
#   pragma intrinsic(_mm256_add_epi32)
#   pragma intrinsic(_mm256_add_epi64)
#   pragma intrinsic(_mm256_sub_epi8)
#   pragma intrinsic(_mm256_sub_epi16)
#   pragma intrinsic(_mm256_sub_epi32)
#   pragma intrinsic(_mm256_sub_epi64)
#   pragma intrinsic(_mm256_mul_epi8)
#   pragma intrinsic(_mm256_mul_epi16)
#   pragma intrinsic(_mm256_mul_epi32)
#   pragma intrinsic(_mm256_mul_epi64)
#   pragma intrinsic(_mm256_div_epi8)
#   pragma intrinsic(_mm256_div_epi16)
#   pragma intrinsic(_mm256_div_epi32)
#   pragma intrinsic(_mm256_div_epi64)
#   pragma intrinsic(_mm256_max_epi8)
#   pragma intrinsic(_mm256_max_epi16)
#   pragma intrinsic(_mm256_max_epi32)
#   pragma intrinsic(_mm256_max_epi64)
#   pragma intrinsic(_mm256_min_epi8)
#   pragma intrinsic(_mm256_min_epi16)
#   pragma intrinsic(_mm256_min_epi32)
#   pragma intrinsic(_mm256_min_epi64)
#   pragma intrinsic(_mm256_and_si256)
#   pragma intrinsic(_mm256_andnot_si256)
#   pragma intrinsic(_mm256_or_si256)
#endif // defined(QO_WANT_SIMD_256) || defined(QO_WANT_SIMD_512)

#if defined(QO_WANT_SIMD_512)
#   pragma intrinsic(_mm512_add_epi8)
#   pragma intrinsic(_mm512_add_epi16)
#   pragma intrinsic(_mm512_add_epi32)
#   pragma intrinsic(_mm512_add_epi64)
#   pragma intrinsic(_mm512_sub_epi8)
#   pragma intrinsic(_mm512_sub_epi16)
#   pragma intrinsic(_mm512_sub_epi32)
#   pragma intrinsic(_mm512_sub_epi64)
#   pragma intrinsic(_mm512_mul_epi8)
#   pragma intrinsic(_mm512_mul_epi16)
#   pragma intrinsic(_mm512_mul_epi32)
#   pragma intrinsic(_mm512_mul_epi64)
#   pragma intrinsic(_mm512_div_epi8)
#   pragma intrinsic(_mm512_div_epi16)
#   pragma intrinsic(_mm512_div_epi32)
#   pragma intrinsic(_mm512_div_epi64)
#   pragma intrinsic(_mm512_max_epi8)
#   pragma intrinsic(_mm512_max_epi16)
#   pragma intrinsic(_mm512_max_epi32)
#   pragma intrinsic(_mm512_max_epi64)
#   pragma intrinsic(_mm512_min_epi8)
#   pragma intrinsic(_mm512_min_epi16)
#   pragma intrinsic(_mm512_min_epi32)
#   pragma intrinsic(_mm512_min_epi64)
#   pragma intrinsic(_mm512_and_si512)
#   pragma intrinsic(_mm512_andnot_si512)
#   pragma intrinsic(_mm512_or_si512)
#endif 

#if defined(QO_WANT_SIMD_128) || defined(QO_WANT_SIMD_256) ||\ 
    defined(QO_WANT_SIMD_512)
#   include "v128.h"
#elif defined(QO_WANT_SIMD_256) || defined(QO_WANT_SIMD_512)
#   include "v256.h"
#elif defined(QO_WANT_SIMD_512)
#   include "v512.h"
#else
#   error "QOLib: simd.h is included but no SIMD support is enabled"
#endif

#if defined(__cplusplus)
extern "C" {
#endif


#if defined(QO_SIMD_WANT_256)
;
#else
{
    QO_IMPL(qo_copy128)(source, destination);
    QO_IMPL(qo_copy128)(source + 16, destination + 16);
}
#endif // QO_SIMD_WANT_256

QO_FORCE_INLINE
void
QO_IMPL(qo_copy512)(
    qo_pointer_t source ,
    qo_pointer_t destination
)
#if defined(QO_SIMD_WANT_512)
;
#else
{
    QO_IMPL(qo_copy256)(source, destination);
    QO_IMPL(qo_copy256)(source + 32, destination + 32);
}

#if defined(__cplusplus)
}
#endif // __cplusplus