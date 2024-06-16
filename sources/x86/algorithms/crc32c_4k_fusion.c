#include "base.h"
#include <x86intrin.h>

// Compile flags (GCC): -mvpclmulqdq -msse4.2
// Ref: https://github.com/corsix/fast-crc32


xocean_uint32_t 
__xocean_crc32c_4k_fusion(
    xocean_uint32_t     acc_a , 
    xocean_byte_t     * buf
){

    // Four chunks:
    //  Chunk A: 728 bytes from 0 through 728
    //  Chunk B: 728 bytes from 728 through 1456
    //  Chunk C: 720 bytes from 1456 through 2176
    //  Chunk D: 1920 bytes from 2176 through 4096
    // First block of 64 from D is easy.

    xocean_byte_t * buf2 = buf + 2176;
    __m128i x1 = _mm_loadu_si128((__m128i *)buf2);
    __m128i x2 = _mm_loadu_si128((__m128i *)(buf2 + 16));
    __m128i x3 = _mm_loadu_si128((__m128i *)(buf2 + 32));
    __m128i x4 = _mm_loadu_si128((__m128i *)(buf2 + 48));
    xocean_uint32_t acc_b = 0;
    xocean_uint32_t acc_c = 0;

    // Parallel fold remaining blocks of 64 from D, and 24 from each of A/B/C.
    // k1 == magic(4*128+32-1)
    // k2 == magic(4*128-32-1)
    __m128i k1k2 = _mm_setr_epi32(/*k1*/ 0x740EEF02 , 0 , /*k2*/ 0x9E4ADDF8 , 0);
    xocean_byte_t * end = buf + 4096 - 64;
    do 
    {
        acc_a = _mm_crc32_u64(acc_a , *(xocean_uint64_t *)buf);
        __m128i x5 = _mm_clmulepi64_si128(x1 , k1k2 , 0x00);
        acc_b = _mm_crc32_u64(acc_b , *(xocean_uint64_t *)(buf + 728));
        x1 = _mm_clmulepi64_si128(x1 , k1k2 , 0x11);
        acc_c = _mm_crc32_u64(acc_c , *(xocean_uint64_t *)(buf + 728*2));
        __m128i x6 = _mm_clmulepi64_si128(x2 , k1k2 , 0x00);
        acc_a = _mm_crc32_u64(acc_a , *(xocean_uint64_t *)(buf + 8));
        x2 = _mm_clmulepi64_si128(x2 , k1k2 , 0x11);
        acc_b = _mm_crc32_u64(acc_b , *(xocean_uint64_t *)(buf + 728 + 8));
        __m128i x7 = _mm_clmulepi64_si128(x3 , k1k2 , 0x00);
        acc_c = _mm_crc32_u64(acc_c , *(xocean_uint64_t *)(buf + 728*2 + 8));
        x3 = _mm_clmulepi64_si128(x3, k1k2 , 0x11);
        acc_a = _mm_crc32_u64(acc_a , *(xocean_uint64_t *)(buf + 16));
        __m128i x8 = _mm_clmulepi64_si128(x4 , k1k2 , 0x00);
        acc_b = _mm_crc32_u64(acc_b , *(xocean_uint64_t *)(buf + 728 + 16));
        x4 = _mm_clmulepi64_si128(x4, k1k2, 0x11);
        acc_c = _mm_crc32_u64(acc_c , *(xocean_uint64_t *)(buf + 728*2 + 16));
        x5 = _mm_xor_si128(x5 , _mm_loadu_si128((__m128i*)(buf2 + 64)));
        x1 = _mm_xor_si128(x1 , x5);
        x6 = _mm_xor_si128(x6 , _mm_loadu_si128((__m128i*)(buf2 + 80)));
        x2 = _mm_xor_si128(x2 , x6);
        x7 = _mm_xor_si128(x7 , _mm_loadu_si128((__m128i*)(buf2 + 96)));
        x3 = _mm_xor_si128(x3 , x7);
        x8 = _mm_xor_si128(x8 , _mm_loadu_si128((__m128i*)(buf2 + 112)));
        x4 = _mm_xor_si128(x4 , x8);
        buf2 += 64;
        buf += 24;
    } while (buf2 < end);

    // Next 24 bytes from A/B/C, and 8 more from A/B, then merge A/B/C.
    // Meanwhile, fold together D's four parallel streams.
    // k3 == magic(128+32-1)
    // k4 == magic(128-32-1)
    __m128i k3k4 = _mm_setr_epi32(/*k3*/ 0xF20C0DFE , 0 , /*k4*/ 0x493C7D27 , 0);
    acc_a = _mm_crc32_u64(acc_a , *(xocean_uint64_t *)buf);
    __m128i x5 = _mm_clmulepi64_si128(x1 , k3k4 , 0x00);
    acc_b = _mm_crc32_u64(acc_b , *(xocean_uint64_t *)(buf + 728));
    x1 = _mm_clmulepi64_si128(x1, k3k4, 0x11);
    acc_c = _mm_crc32_u64(acc_c , *(xocean_uint64_t *)(buf + 728*2));
    __m128i x6 = _mm_clmulepi64_si128(x3, k3k4, 0x00);
    acc_a = _mm_crc32_u64(acc_a , *(xocean_uint64_t *)(buf + 8));
    x3 = _mm_clmulepi64_si128(x3, k3k4, 0x11);
    acc_b = _mm_crc32_u64(acc_b , *(xocean_uint64_t *)(buf + 728 + 8));
    acc_c = _mm_crc32_u64(acc_c , *(xocean_uint64_t *)(buf + 728*2 + 8));
    acc_a = _mm_crc32_u64(acc_a , *(xocean_uint64_t *)(buf + 16));
    acc_b = _mm_crc32_u64(acc_b , *(xocean_uint64_t *)(buf + 728 + 16));
    x5 = _mm_xor_si128(x5, x2);
    acc_c = _mm_crc32_u64(acc_c , *(xocean_uint64_t *)(buf + 728*2 + 16));
    x1 = _mm_xor_si128(x1, x5);
    acc_a = _mm_crc32_u64(acc_a , *(xocean_uint64_t *)(buf + 24));
    // k5 == magic(2*128+32-1)
    // k6 == magic(2*128-32-1)
    __m128i k5k6 = _mm_setr_epi32(/*k5*/ 0x3DA6D0CB , 0 , /*k6*/ 0xBA4FC28E, 0);
    x6 = _mm_xor_si128(x6 , x4);
    x3 = _mm_xor_si128(x3 , x6);
    x5 = _mm_clmulepi64_si128(x1 , k5k6, 0x00);
    acc_b = _mm_crc32_u64(acc_b , *(xocean_uint64_t *)(buf + 728 + 24));
    x1 = _mm_clmulepi64_si128(x1 , k5k6 , 0x11);
    // kC == magic((        1920)*8-33)
    __m128i kCk0 = _mm_setr_epi32(/*kC*/ 0xF48642E9 , 0 , 0 , 0);
    __m128i vec_c = _mm_clmulepi64_si128(_mm_cvtsi32_si128(acc_c) , kCk0 , 0x00);
    // kB == magic((    720+1920)*8-33)
    // kA == magic((728+720+1920)*8-33)
    __m128i kAkB = _mm_setr_epi32(/*kA*/ 0x155AD968 , 0 , /*kB*/ 0x2E7D11A7 , 0);
    __m128i vec_a = _mm_clmulepi64_si128(_mm_cvtsi32_si128(acc_a) , kAkB , 0x00);
    __m128i vec_b = _mm_clmulepi64_si128(_mm_cvtsi32_si128(acc_b) , kAkB , 0x10);
    x5 = _mm_xor_si128(x5 , x3);
    x1 = _mm_xor_si128(x1 , x5);
    xocean_uint64_t abc = _mm_cvtsi128_si64(
        _mm_xor_si128(_mm_xor_si128(vec_c , vec_a) , vec_b)
    );
    // Apply missing <<32 and fold down to 32-bits.
    xocean_uint32_t crc = _mm_crc32_u64(0 , _mm_extract_epi64(x1 , 0));
    crc = _mm_crc32_u64(crc , abc ^ _mm_extract_epi64(x1 , 1));
    return crc;
}

