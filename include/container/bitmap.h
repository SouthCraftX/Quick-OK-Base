#pragma once
#include "../base.h"


#if defined(__cplusplus)
extern "C" {
#endif // defined(__cplusplus)

struct _QOBitmap8   
{
    qo_uint8_t data;
};
typedef _QOBitmap8 QOBitmap8;

QO_FORCE_INLINE
qo_size_t qo_bitmap8_get_1_count(QOBitmap8 bitmap)
{

}

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)