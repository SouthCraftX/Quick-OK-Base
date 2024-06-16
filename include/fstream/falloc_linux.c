#pragma once

// for debug
// #define __linux__

#include "fstream.h"

#   include <unistd.h>

xocean_stat_t 
XOCEAN_IMPL(xocean_fstream_prealloc)(
    XOceanFile *    file ,
    xocean_size_t   size
){
    switch(fallocate((int)file , 0 , 0 , size))
    {

        case 0:         return XOCEAN_OK;
        case EBADF:     return XOCEAN_INVALID_HANDLE;
        case EINVAL:    return XOCEAN_INVALID_ARG;
        case EFBIG:     return XOCEAN_FILE_TOO_BIG;
        case ENOSPC:    return XOCEAN_DISK_NO_SPACE;
        case ESPIPE:    return XOCEAN_BAD_TYPE;
        case EIO:       return XOCEAN_BROKEN_DEVICE;
        case ENOTSUP:   return XOCEAN_NOT_SUPPORTED;
        case EINPR:     return XOCEAN_SIGNAL_INTERRUPTED;
        default:        return XOCEAN_UNKNOWN_ERROR;
    }
}


