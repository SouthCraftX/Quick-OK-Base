#pragma once

//#include "fstream.h"
#include "../base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOCAsyncFile;
typedef struct _XOCAsyncFile XOCAsyncFile;

xoc_stat_t
XOC_INTERFACE(xoc_async_file_open)(
    XOCAsyncFile *   file , 
    xoc_ccstring_t   path ,
    xoc_flag32_t     mode
);



#if defined(__cplusplus)
}
#endif