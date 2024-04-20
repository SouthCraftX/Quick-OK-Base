#pragma once

// For debug
#include "../../process.h"

#if !defined(__XOCEAN_PROCESS_H__)
#error "Do not include this file directly. Use <xocean/process.h> instead."
#endif

#define __XOCEAN_WIN32_PROCESS_H__

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

xocean_stat_t
XOCEAN_IMPL(xocean_process_adjust_priority)(
    XOceanProcess               process ,
    enum XOceanThreadPriority   priority
){
    XOCEAN_GLOBAL_LOCAL
    const DWORD priority_table[] = {
        IDEL_PRIORITY_CLASS,
        BELOW_NORMAL_PRIORITY_CLASS,
        NORMAL_PRIORITY_CLASS,
        ABOVE_NORMAL_PRIORITY_CLASS,
        HIGH_PRIORITY_CLASS,
        REALTIME_PRIORITY_CLASS
    };


}


#if defined(__cplusplus)
}
#endif // __cplusplus