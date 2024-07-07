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

#if (defined(XOC_WANT_SIMD_256) || defined(XOC_WANT_SIMD_512))
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
#endif // defined(XOC_WANT_SIMD_256) || defined(XOC_WANT_SIMD_512)

#if defined(XOC_WANT_SIMD_512)
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

#if defined(XOC_WANT_SIMD_128) || defined(XOC_WANT_SIMD_256) ||\ 
    defined(XOC_WANT_SIMD_512)
#   include "v128.h"
#elif defined(XOC_WANT_SIMD_256) || defined(XOC_WANT_SIMD_512)
#   include "v256.h"
#elif defined(XOC_WANT_SIMD_512)
#   include "v512.h"
#else
#   error "XOCLib: simd.h is included but no SIMD support is enabled"
#endif

#if defined(__cplusplus)
extern "C" {
#endif


#if defined(XOC_SIMD_WANT_256)
;
#else
{
    XOC_IMPL(xoc_copy128)(source, destination);
    XOC_IMPL(xoc_copy128)(source + 16, destination + 16);
}
#endif // XOC_SIMD_WANT_256

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_copy512)(
    xoc_pointer_t source ,
    xoc_pointer_t destination
)
#if defined(XOC_SIMD_WANT_512)
;
#else
{
    XOC_IMPL(xoc_copy256)(source, destination);
    XOC_IMPL(xoc_copy256)(source + 32, destination + 32);
}

#if defined(__cplusplus)
}
#endif // __cplusplus