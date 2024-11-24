#pragma once
#define __QO_WIN32_PERFORMANCE_MONITOR_IO_H__

// for debug
#include "include/performance_monitor/io.h"

#if !defined(__QO_PERFORMANCE_MONITOR_IO_H__)
#   error Never include this file directly, include "qo/performance_monitor/io,h" instead.
#endif 

QO_PURE
qo_stat_t
__qo_io_measurer_getting_error()
{
    switch (GetLastError())
    {
        case ERROR_ACCESS_DENIED:
            return QO_PERMISSION_DENIED;

        default:
            return QO_UNKNOWN_ERROR;
    }
}

qo_stat_t
QO_IMPL(qo_io_measurer_init)()
{
    return QO_OK;
}

void
QO_IMPL(qo_io_measurer_finish)()
{
    return QO_OK;
}

qo_stat_t
QO_IMPL(qo_io_measurer_get)(
    QO_IOStatus *  status
){
    IO_COUNTERS io_counters;
    if(GetProcessIoCounters(GetCurrentProcess(), &io_counters))
    {
        status->read_operations = io_counters.ReadOperationCount;
        status->write_operations = io_counters.WriteOperationCount;
        status->read_bytes = io_counters.ReadTransferCount;
        status->write_bytes = io_counters.WriteTransferCount;
        return QO_OK;
    }
    return __qo_io_measurer_getting_error();
}