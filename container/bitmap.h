#pragma once
#include "../base.h"


#if defined(__cplusplus)
extern "C" {
#endif // defined(__cplusplus)

struct _XOceanBitmap8   
{
    xocean_uint8_t data;
};
typedef _XOceanBitmap8 XOceanBitmap8;

XOCEAN_FORCE_INLINE
xocean_size_t xocean_bitmap8_get_1_count(XOceanBitmap8 bitmap)
{

}

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)