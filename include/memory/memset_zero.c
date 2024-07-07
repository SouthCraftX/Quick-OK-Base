#include "memory_oper.h"
#include "../simd/simd.h"

#include <math.h>

XOC_GLOBAL_LOCAL
void
__xoc_memory_clear_fix_head(
    xoc_pointer_t *  p_destination ,
    xoc_size_t       size ,
    xoc_int32_t      remainder
){
    xoc_pointer_t    destination = * p_destination;
    //buggy
    if(remainder & 0b1)   // odd
    {
        *(xoc_byte_t *)destination = 0;
        destination += 1;
        remainder-- , size--;
    }
    if(remainder & 0b10)  // 2的倍数
    {
        *(xoc_int16_t *)destination = 0;
        destination += 2;
        remainder -= 2 , size -= 2;
    }
    if(remainder & 0b100)  // 4的倍数
    {
        *(xoc_int32_t *)destination = 0;
        destination += 4;
        remainder -= 4 , size -= 4;
    }
    *p_destination = destination;
}

void
XOC_IMPL(xoc_memory_clear)(
    xoc_pointer_t    destination ,
    xoc_size_t       size
){
#if defined(XOC_WANT_SIMD_256)
    XOCDivision32  division = XOC_DIV_I32(size , 256);
    if(division.remainder)
    {
        __xoc_memory_clear_fix_head_on_256(&destination , size , division.remainder);
    }
    return XOC_IMPL(xoc_memory_clear_align256)(destination , size);
#elif defined(XOC_WANT_SIMD_128)

#else

#endif
}

void
XOC_IMPL(xoc_memory_clear_align16)(
    xoc_pointer_t    destination ,
    xoc_size_t       size
){
    XOCDivision  division = XOC_DIV(size , 16);
    xoc_size_t   bytes_have_cleared = size - division.remainder;

#   if defined(XOC_WANT_SIMD_128) || defined(XOC_WANT_SIMD_256)
    if(size >= 16)
    {
        xoc_128_array_clear(destination , bytes_have_cleared);
    }
#   else
    xoc_intmax_t * end = destination + bytes_have_cleared;
    for ( ; destination <= end ; destination += sizeof(xoc_intmax_t))
    {
        *(xoc_intmax_t *)destination = 0;
    }
    
#   endif

    // Fix tail
    destination += bytes_have_cleared;
    if(division.remainder >= 8)
    {
        *(xoc_int64_t *)destination = 0;
        division.remainder -= 8;
        destination += 8;
    }

    if(division.remainder >= 4)
    {
        *(xoc_int32_t *)destination = 0;
        division.remainder -= 4;
        destination += 4;
    }
    if(division.remainder >= 2)
    {
        *(xoc_int16_t *)destination = 0;
        division.remainder -= 2;
        destination += 2;
    }
    if(division.remainder)
    {
        *(xoc_byte_t *)destination = 0;
    }
}

void
XOC_IMPL(xoc_memory_clear_align32)(
    xoc_pointer_t    destination ,
    xoc_size_t       size
){
#   if defined(XOC_WANT_SIMD_256)
    XOCDivision division = XOC_DIV(size , 32);
    if(size >= 32)
    {
        xoc_256_array_clear(destination , division.quotient);
    }
    XOC_IMPL(xoc_memory_clear_align16)(
        destination + division.quotient , 
        division.remainder
    );
#   else
    XOC_IMPL(xoc_memory_clear_align16)(destination , size);
#   endif
}

