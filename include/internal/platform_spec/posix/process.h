#pragma once
#define __XOCEAN_PROCESS_POSIX_H__

// for debug
#include "include/process.h"

#if !defined(__XOC_PROCESS_H__)
#   error Never include this header file directly. Use <xoc/process.h> instead.
#endif // !defined(__XOC_PROCESS_H__)

#include <unistd.h>
#include "common.h"

xoc_pid_t
XOC_IMPL(xoc_process_get_current_pid)()
{
    return getpid();
}

XOC_Process *
XOC_IMPL(xoc_process_get_current)()
{
    XOC_Process * process;
    return __xoc_write_pointer_as_int(process , getpid());
}

xoc_pid_t
XOC_IMPL(xoc_process_get_pid) (
    XOC_Process * process
){
    return __xoc_read_pointer_as_int(process);
}

xoc_stat_t
XOC_IMPL(xoc_process_create)(
    XOC_Process **      p_process ,
    xoc_ccstring_t      command_line ,
    xoc_ccstring_t      environment ,
    xoc_ccstring_t      working_directory ,
    xoc_uint16_t        command_line_length ,
    xoc_uint16_t        environment_length ,
    xoc_uint16_t        working_directory_length ,
    XOC_ProcessStdio *  p_stdio
){
    
}