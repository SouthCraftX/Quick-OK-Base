#pragma once

// For debug
#include "../../process.h"

#if !defined(__XOC_PROCESS_H__)
#error "Do not include this file directly. Use <xoc/process.h> instead."
#endif

#define __XOC_WIN32_PROCESS_H__

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

xoc_stat_t
XOC_IMPL(xoc_process_adjust_priority)(
    XOCProcess               process ,
    enum XOC_ThreadPriority   priority
){
    XOC_GLOBAL_LOCAL
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