#pragma once
#include "../base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOceanFileStreamBase
{
    XOceanClassBase base;
    xocean_intmax_t handle;
};
typedef struct _XOceanFileStreamBase XOceanFileStreamBase;
typedef struct XOCeanFileStream XOceanFileStream;


#if defined(__cplusplus)
}
#endif // __cplusplus