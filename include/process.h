#pragma once
#define __XOC_PROCESS_H__

#include "thread.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOCProcess
{
    HANDLE  process;
};
typedef struct _XOCProcess XOCProcess;

xoc_stat_t
XOC_INTERFACE(xoc_process_adjust_priority)(
    XOCProcess   process ,
    enum XOC_ThreadPriority   priority
);

xoc_stat_t
XOC_INTERFACE(xoc_process_get_priority)(
    XOCProcess   process 
);


#if defined(__cplusplus)
}
#endif // __cplusplus