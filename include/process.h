#pragma once
#define __XOCEAN_PROCESS_H__

#include "thread.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOceanProcess
{
    HANDLE  process;
};
typedef struct _XOceanProcess XOceanProcess;

xocean_stat_t
XOCEAN_INTERFACE(xocean_process_adjust_priority)(
    XOceanProcess   process ,
    enum XOceanThreadPriority   priority
);

xocean_stat_t
XOCEAN_INTERFACE(xocean_process_get_priority)(
    XOceanProcess   process 
);


#if defined(__cplusplus)
}
#endif // __cplusplus