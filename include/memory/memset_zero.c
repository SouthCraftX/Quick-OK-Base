#include "memory_oper.h"
#include "../simd/simd.h"

#include <math.h>

XOCEAN_GLOBAL_LOCAL
void
__xocean_memory_clear_fix_head(
    xocean_pointer_t *  p_destination ,
    xocean_size_t       size ,
    xocean_int32_t      remainder
){
    xocean_pointer_t    destination = * p_destination;
    //buggy
    if(remainder & 0b1)   // odd
    {
        *(xocean_byte_t *)destination = 0;
        destination += 1;
        remainder-- , size--;
    }
    if(remainder & 0b10)  // 2的倍数
    {
        *(xocean_int16_t *)destination = 0;
        destination += 2;
        remainder -= 2 , size -= 2;
    }
    if(remainder & 0b100)  // 4的倍数
    {
        *(xocean_int32_t *)destination = 0;
        destination += 4;
        remainder -= 4 , size -= 4;
    }
    *p_destination = destination;
}

void
XOCEAN_IMPL(xocean_memory_clear)(
    xocean_pointer_t    destination ,
    xocean_size_t       size
){
#if defined(XOCEAN_WANT_SIMD_256)
    XOceanDivision32  division = XOCEAN_DIV_I32(size , 256);
    if(division.remainder)
    {
        __xocean_memory_clear_fix_head_on_256(&destination , size , division.remainder);
    }
    return XOCEAN_IMPL(xocean_memory_clear_align256)(destination , size);
#elif defined(XOCEAN_WANT_SIMD_128)

#else

#endif
}

void
XOCEAN_IMPL(xocean_memory_clear_align16)(
    xocean_pointer_t    destination ,
    xocean_size_t       size
){
    XOceanDivision  division = XOCEAN_DIV(size , 16);
    xocean_size_t   bytes_have_cleared = size - division.remainder;

#   if defined(XOCEAN_WANT_SIMD_128) || defined(XOCEAN_WANT_SIMD_256)
    if(size >= 16)
    {
        xocean_128_array_clear(destination , bytes_have_cleared);
    }
#   else
    xocean_intmax_t * end = destination + bytes_have_cleared;
    for ( ; destination <= end ; destination += sizeof(xocean_intmax_t))
    {
        *(xocean_intmax_t *)destination = 0;
    }
    
#   endif

    // Fix tail
    destination += bytes_have_cleared;
    if(division.remainder >= 8)
    {
        *(xocean_int64_t *)destination = 0;
        division.remainder -= 8;
        destination += 8;
    }

    if(division.remainder >= 4)
    {
        *(xocean_int32_t *)destination = 0;
        division.remainder -= 4;
        destination += 4;
    }
    if(division.remainder >= 2)
    {
        *(xocean_int16_t *)destination = 0;
        division.remainder -= 2;
        destination += 2;
    }
    if(division.remainder)
    {
        *(xocean_byte_t *)destination = 0;
    }
}

void
XOCEAN_IMPL(xocean_memory_clear_align32)(
    xocean_pointer_t    destination ,
    xocean_size_t       size
){
#   if defined(XOCEAN_WANT_SIMD_256)
    XOceanDivision division = XOCEAN_DIV(size , 32);
    if(size >= 32)
    {
        xocean_256_array_clear(destination , division.quotient);
    }
    XOCEAN_IMPL(xocean_memory_clear_align16)(
        destination + division.quotient , 
        division.remainder
    );
#   else
    XOCEAN_IMPL(xocean_memory_clear_align16)(destination , size);
#   endif
}

