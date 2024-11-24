#pragma once
#define __QOEAN_PROCESS_POSIX_H__

// for debug
#include "include/process.h"

#if !defined(__QO_PROCESS_H__)
#   error Never include this header file directly. Use <qo/process.h> instead.
#endif // !defined(__QO_PROCESS_H__)

#include <unistd.h>
#include <linux/fcntl.h>
#include "common.h"

qo_pid_t
QO_IMPL(qo_process_get_current_pid)()
{
    return getpid();
}

QO_Process *
QO_IMPL(qo_process_get_current)()
{
    QO_Process * process;
    return __qo_write_pointer_as_int(process , getpid());
}

qo_pid_t
QO_IMPL(qo_process_get_pid) (
    QO_Process * process
){
    return __qo_read_pointer_as_int(process);
}


qo_stat_t
QO_IMPL(qo_process_create)(
    QO_Process **      p_process ,
    qo_ccstring_t      application_path ,
    qo_ccstring_t      arguments_line ,
    qo_ccstring_t      environment ,
    qo_ccstring_t      working_directory ,
    qo_uint16_t        command_line_length ,
    qo_uint16_t        environment_length ,
    qo_uint16_t        working_directory_length ,
    QO_ProcessStdio *  p_stdio
){
    
    
}