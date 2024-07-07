#pragma once
#include "../base.h"


#if defined(__cplusplus)
extern "C" {
#endif // defined(__cplusplus)

struct _XOCBitmap8   
{
    xoc_uint8_t data;
};
typedef _XOCBitmap8 XOCBitmap8;

XOC_FORCE_INLINE
xoc_size_t xoc_bitmap8_get_1_count(XOCBitmap8 bitmap)
{

}

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)