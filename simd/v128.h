#pragma once

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

#include "../base.h"

#if !defined(__cplusplus)
extern "C" {
#endif // __cplusplus

XOCEAN_FORCE_INLINE
xocean_bool_t xocean_i128_cmpeq(xocean_pointer_t x , xocean_pointer_t y)
{
    xocean_bool_t res[128];
    __m128i x_vec = _mm_load_si128((__m128i *)x);
    __m128i y_vec = _mm_load_si128((__m128i *)y);
    __m128i res_vec = _mm_cmpeq_epi8(x_vec, y_vec);
    _mm_store_si128((__m128i *)res, res_vec);
    return res[0];
}

// @param : type --- si128/pd/sd
#define xocean_128copy(dst , src , type) (_mm_store_##type##((__m128i *)dst, _mm_load_##type##((__m128i *)src)))

// @param:  x , y --- source
//          res --- result
///         op_type --- i8/i16/i32/i64/u8/u16/u32/u64/pd/sd
//          load_type --- si128/pd/sd
#define xocean_128_add(x , y , res , op_type , load_type) (_mm_store_##load_type##(res , _mm_add_ep##op_type##(_mm_load_##load_type##(x) , _mm_load_##load_type##(y))))     
#define xocean_128_sub(x , y , res , op_type , load_type) (_mm_store_##load_type##(res , _mm_sub_ep##op_type##(_mm_load_##load_type##(x) , _mm_load_##load_type##(y))))
#define xocean_128_mul(x , y , res , op_type , load_type) (_mm_store_##load_type##(res , _mm_mul_ep##op_type##(_mm_load_##load_type##(x) , _mm_load_##load_type##(y))))
#define xocean_128_div(x , y , res , op_type , load_type) (_mm_store_##load_type##(res , _mm_div_ep##op_type##(_mm_load_##load_type##(x) , _mm_load_##load_type##(y))))
#define xocean_128_min(x , y , res , op_type , load_type) (_mm_store_##load_type##(res , _mm_min_ep##op_type##(_mm_load_##load_type##(x) , _mm_load_##load_type##(y))))
#define xocean_128_max(x , y , res , op_type , load_type) (_mm_store_##load_type##(res , _mm_max_ep##op_type##(_mm_load_##load_type##(x) , _mm_load_##load_type##(y))))
#define xocean_128_xor(x , y , res , op_type , load_type) (_mm_store_##load_type##(res , _mm_xor_##op_type##(_mm_load_##load_type##(x) , _mm_load_##load_type##(y))))
#define xocean_128_or(x , y , res , op_type , load_type) (_mm_store_##load_type##(res , _mm_or_##op_type##(_mm_load_##load_type##(x) , _mm_load_##load_type##(y))))
#define xocean_128_and(x , y , res , op_type , load_type) (_mm_store_##load_type##(res , _mm_and_##op_type##(_mm_load_##load_type##(x) , _mm_load_##load_type##(y))))
#define xocean_128_notand(x , y , res , op_type , load_type) (_mm_store_##load_type##(res , _mm_notand_##op_type##(_mm_load_##load_type##(x) , _mm_load_##load_type##(y))))

#define xocean_i128_slli(x , n , op_type) (_mm_store_si128(x , _mm_slli_##op_type##(x , n)))
#define xocean_i128_srli(x , n , op_type) (_mm_store_si128(x , _mm_srli_##op_type##(x , n)))

#define xocean_128_fp64_add(x , y , res) xocean_128_add(x , y , res , pd , pd)
#define xocean_128_fp32_add(x , y , res) xocean_128_add(x , y , res , ps , ps)
#define xocean_128_fp64_sub(x , y , res) xocean_128_sub(x , y , res , pd , pd)
#define xocean_128_fp32_sub(x , y , res) xocean_128_sub(x , y , res , ps , ps)
#define xocean_128_fp64_mul(x , y , res) xocean_128_mul(x , y , res , pd , pd)

// @param size Must be aligned to 16 bytes
void xocean_i128_zeromem(xocean_byte_t * dst , const xocean_size_t size)
{
    __m128i zero_vec = _mm_setzero_si128();
    xocean_size_t i;
    for (xocean_size_t i = 0; i < size; i += 16)
    {
        _mm_store_si128((__m128i *)dst , zero_vec);
        dst += 16;
    }
}

// @param dst The array you want to copy to (must be aligned in 16 bytes)
// @param src The array you want to copy from (must be aligned in 16 bytes)
// @param size The size to copy (must be mutilple of 16)
void xocean_i128_array_copy(xocean_byte_t * dst , const xocean_byte_t * src , 
                            const xocean_size_t size)
{
    for ( ; src < src + size; src += 16 , dst += 16)
    {
        _mm_store_si128((__m128i *)dst , _mm_load_si128((__m128i *)src));
    }
}


// @param sx     The size of the array 'x' (must be aligned in 16 bytes)
// @param sy     The size of the array 'y' (must be aligned in 16 bytes)
// @param res    The array store result    (must be aligned in 16 bytes)
// @param type   The type of data(i8/i16/i32/i64/u8/u16/u32/u64)
#define xocean_i128_array_add(x , y , sx , sy , res , type)                    \
do                                                                             \
{                                                                              \ 
    xocean_byte_t * x_now = x , y_now = y , res_now = res;                     \
    static_assert(                                                             \   
        sx >= sy ,                                                             \ 
        "The size of array 'x' must be greater than or equal to array 'y"      \
    );                                                                         \
    for(; x_now < x + sx ; x_now += 16 , y_now += 16 , res_now += 16)          \                                                               \
        xocean_128_add(x_now , y_now , res_now , ##type## , si128);            \
    if(sy < sx)                                                                \
        xocean_i128_array_copy(res_now , x_now , sx - sy);                     \
}                                                                              \
while(false)








#if !defined(__cplusplus)
}
#endif // __cplusplus
