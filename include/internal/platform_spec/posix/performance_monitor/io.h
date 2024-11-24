#pragma once
#define __QO_POSIX_PERFORMANCE_MONITOR_IO_H__

// for debug
#include "include/performance_monitor/io.h"

#if !defined(__QO_PERFORMANCE_MONITOR_IO_H__)
#   error Never include this file directly, include "qo/performance_monitor/io.h" instead.
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

#define __QO_IO_INFO_MAX_SIZE 256

#include "fstream.h"

QO_File * __qo_io_info_file;

QO_FORCE_INLINE
qo_stat_t
QO_IMPL(qo_io_measurer_init)()
{
    const char io_info_path[] = "/proc/self/io";
    return qo_file_open(
        &__qo_io_info_file , io_info_path , 
        sizeof(io_info_path) , QO_FILE_READONLY ,
        QO_FILE_OPEN_EXISTING , 0
    );
}

QO_FORCE_INLINE
void
QO_IMPL(qo_io_measurer_finish)()
{
    qo_file_close(__qo_io_info_file);
}

qo_stat_t
QO_IMPL(qo_io_measurer_get)(
    QO_IOStatus * p_io_status
){
    char io_info_text[__QO_IO_INFO_MAX_SIZE];
    qo_stat_t read_ret;
    qo_size_t read_size = qo_file_read(
        __qo_io_info_file , 
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