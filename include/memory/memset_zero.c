#include "memory_oper.h"
#include "../simd/simd.h"

#include <math.h>

QO_GLOBAL_LOCAL
void
__qo_memory_clear_fix_head(
    qo_pointer_t *  p_destination ,
    qo_size_t       size ,
    qo_int32_t      remainder
){
    qo_pointer_t    destination = * p_destination;
    //buggy
    if (remainder & 0b1)   // odd
    {
        *(qo_byte_t *)destination = 0;
        destination += 1;
        remainder-- , size--;
    }
    if (remainder & 0b10)  // 2的倍数
    {
        *(qo_int16_t *)destination = 0;
        destination += 2;
        remainder -= 2 , size -= 2;
    }
    if (remainder & 0b100)  // 4的倍数
    {
        *(qo_int32_t *)destination = 0;
        destination += 4;
        remainder -= 4 , size -= 4;
    }
    *p_destination = destination;
}

void
QO_IMPL(qo_memory_clear)(
    qo_pointer_t    destination ,
    qo_size_t       size
){
#if defined(QO_WANT_SIMD_256)
    QODivision32  division = QO_DIV_I32(size , 256);
    if (division.remainder)
    {
        __qo_memory_clear_fix_head_on_256(&destination , size , division.remainder);
    }
    return QO_IMPL(qo_memory_clear_align256)(destination , size);
#elif defined(QO_WANT_SIMD_128)

#else

#endif
}

void
QO_IMPL(qo_memory_clear_align16)(
    qo_pointer_t    destination ,
    qo_size_t       size
){
    QODivision  division = QO_DIV(size , 16);
    qo_size_t   bytes_have_cleared = size - division.remainder;

#   if defined(QO_WANT_SIMD_128) || defined(QO_WANT_SIMD_256)
    if (size >= 16)
    {
        qo_128_array_clear(destination , bytes_have_cleared);
    }
#   else
    qo_intmax_t * end = destination + bytes_have_cleared;
    for ( ; destination <= end ; destination += sizeof(qo_intmax_t))
    {
        *(qo_intmax_t *)destination = 0;
    }
    
#   endif

    // Fix tail
    destination += bytes_have_cleared;
    if (division.remainder >= 8)
    {
        *(qo_int64_t *)destination = 0;
        division.remainder -= 8;
        destination += 8;
    }

    if (division.remainder >= 4)
    {
        *(qo_int32_t *)destination = 0;
        division.remainder -= 4;
        destination += 4;
    }
    if (division.remainder >= 2)
    {
        *(qo_int16_t *)destination = 0;
        division.remainder -= 2;
        destination += 2;
    }
    if (division.remainder)
    {
        *(qo_byte_t *)destination = 0;
    }
}

void
QO_IMPL(qo_memory_clear_align32)(
    qo_pointer_t    destination ,
    qo_size_t       size
){
#   if defined(QO_WANT_SIMD_256)
    QODivision division = QO_DIV(size , 32);
    if (size >= 32)
    {
        qo_256_array_clear(destination , division.quotient);
    }
    QO_IMPL(qo_memory_clear_align16)(
        destination + division.quotient , 
        division.remainder
    );
#   else
    QO_IMPL(qo_memory_clear_align16)(destination , size);
#   endif
}

