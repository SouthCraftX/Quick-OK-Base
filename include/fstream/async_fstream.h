#pragma once

//#include "fstream.h"
#include "../base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOceanAsyncFile;
typedef struct _XOceanAsyncFile XOceanAsyncFile;

xocean_stat_t
XOCEAN_INTERFACE(xocean_async_file_open)(
    XOceanAsyncFile *   file , 
    xocean_ccstring_t   path ,
    xocean_flag32_t     mode
);



#if defined(__cplusplus)
}
#endif