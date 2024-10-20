#pragma once
#define __XOC_POSIX_PERFORMANCE_MONITOR_IO_H__

// for debug
#include "include/performance_monitor/io.h"

#if !defined(__XOC_PERFORMANCE_MONITOR_IO_H__)
#   error Never include this file directly, include "xoc/performance_monitor/io.h" instead.
#endif

/*
    /proc/[pid]/io output like: (Total 222 characters)
    rchar: 18446744073709551615
    wchar: 18446744073709551615
    syscr: 18446744073709551615
    syscw: 18446744073709551615
    read_bytes: 18446744073709551615
    write_bytes: 18446744073709551615
    cancelled_write_bytes: 18446744073709551615
*/

#define __XOC_IO_INFO_MAX_SIZE 256

#include "fstream.h"

XOC_File * __xoc_io_info_file;

XOC_FORCE_INLINE
xoc_stat_t
XOC_IMPL(xoc_io_measurer_init)()
{
    const char io_info_path[] = "/proc/self/io";
    return xoc_file_open(
        &__xoc_io_info_file , io_info_path , 
        sizeof(io_info_path) , XOC_FILE_READONLY ,
        XOC_FILE_OPEN_EXISTING , 0
    );
}

XOC_FORCE_INLINE
void
XOC_IMPL(xoc_io_measurer_finish)()
{
    xoc_file_close(__xoc_io_info_file);
}

xoc_stat_t
XOC_IMPL(xoc_io_measurer_get)(
    XOC_IOStatus * p_io_status
){
    char io_info_text[__XOC_IO_INFO_MAX_SIZE];
    xoc_stat_t read_ret;
    xoc_size_t read_size = xoc_file_read(
        __xoc_io_info_file , 
        io_info_text , 
        sizeof(io_info_text) , 
        &read_ret
    );
    if (read_ret)
    {
        return read_ret;
    }
    // str to int at offset 7
}