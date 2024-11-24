#pragma once

//#include "fstream.h"
#include "../base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _QOAsyncFile;
typedef struct _QOAsyncFile QOAsyncFile;

qo_stat_t
QO_INTERFACE(qo_async_file_open)(
    QOAsyncFile *   file , 
    qo_ccstring_t   path ,
    qo_flag32_t     mode
);



#if defined(__cplusplus)
}
#endif