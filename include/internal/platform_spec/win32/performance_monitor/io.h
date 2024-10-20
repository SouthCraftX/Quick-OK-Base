#pragma once
#define __XOC_WIN32_PERFORMANCE_MONITOR_IO_H__

// for debug
#include "include/performance_monitor/io.h"

#if !defined(__XOC_PERFORMANCE_MONITOR_IO_H__)
#   error Never include this file directly, include "xoc/performance_monitor/io,h" instead.
#endif 

XOC_PURE
xoc_stat_t
__xoc_io_measurer_getting_error()
{
    switch (GetLastError())
    {
        case ERROR_ACCESS_DENIED:
            return XOC_PERMISSION_DENIED;

        default:
            return XOC_UNKNOWN_ERROR;
    }
}

xoc_stat_t
XOC_IMPL(xoc_io_measurer_init)()
{
    return XOC_OK;
}

void
XOC_IMPL(xoc_io_measurer_finish)()
{
    return XOC_OK;
}

xoc_stat_t
XOC_IMPL(xoc_io_measurer_get)(
    XOC_IOStatus *  status
){
    IO_COUNTERS io_counters;
    if(GetProcessIoCounters(GetCurrentProcess(), &io_counters))
    {
        status->read_operations = io_counters.ReadOperationCount;
        status->write_operations = io_counters.WriteOperationCount;
        status->read_bytes = io_counters.ReadTransferCount;
        status->write_bytes = io_counters.WriteTransferCount;
        return XOC_OK;
    }
    return __xoc_io_measurer_getting_error();
}