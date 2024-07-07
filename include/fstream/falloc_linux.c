#pragma once

// for debug
// #define __linux__

#include "fstream.h"

#   include <unistd.h>

xoc_stat_t 
XOC_IMPL(xoc_fstream_prealloc)(
    XOC_File *    file ,
    xoc_size_t   size
){
    switch(fallocate((int)file , 0 , 0 , size))
    {

        case 0:         return XOC_OK;
        case EBADF:     return XOC_INVALID_HANDLE;
        case EINVAL:    return XOC_INVALID_ARG;
        case EFBIG:     return XOC_FILE_TOO_BIG;
        case ENOSPC:    return XOC_DISK_NO_SPACE;
        case ESPIPE:    return XOC_BAD_TYPE;
        case EIO:       return XOC_BROKEN_DEVICE;
        case ENOTSUP:   return XOC_NOT_SUPPORTED;
        case EINPR:     return XOC_SIGNAL_INTERRUPTED;
        default:        return XOC_UNKNOWN_ERROR;
    }
}


