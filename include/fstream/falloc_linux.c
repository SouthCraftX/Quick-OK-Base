#pragma once

// for debug
// #define __linux__

#include "fstream.h"

#   include <unistd.h>

qo_stat_t 
QO_IMPL(qo_fstream_prealloc)(
    QO_File *    file ,
    qo_size_t   size
){
    switch(fallocate((int)file , 0 , 0 , size))
    {

        case 0:         return QO_OK;
        case EBADF:     return QO_INVALID_HANDLE;
        case EINVAL:    return QO_INVALID_ARG;
        case EFBIG:     return QO_FILE_TOO_BIG;
        case ENOSPC:    return QO_DISK_NO_SPACE;
        case ESPIPE:    return QO_BAD_TYPE;
        case EIO:       return QO_BROKEN_DEVICE;
        case ENOTSUP:   return QO_NOT_SUPPORTED;
        case EINPR:     return QO_SIGNAL_INTERRUPTED;
        default:        return QO_UNKNOWN_ERROR;
    }
}


