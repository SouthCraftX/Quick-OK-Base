#pragma once

// for debug
// #define __linux__

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

#include "iofstream.h"


#if XOCEAN_PLATFORM(LINUX)
#   include <unistd.h>

xocean_stat_t xocean_fstream_prealloc(
    XOceanIOFStream * stream , 
    xocean_size_t size
){
    switch(fallocate((int)((XOceanFileStreamBase *)stream->handle) , 0 , 0 , size))
    {

        case 0:
            return XOCEAN_OK;

        case EBADF:
            return XOCEAN_INVALID_HANDLE;

        case EINVAL:
            return XOCEAN_INVALID_ARG;

        case EFBIG:
            return XOCEAN_FILE_TOO_BIG;

        case ENOSPC:
            return XOCEAN_DISK_FULL;

        case ESPIPE:
            return XOCEAN_BAD_TYPE;

        case EIO:
            return XOCEAN_BROKEN_DEVICE;

        case ENOTSUP:
            return XOCEAN_NOT_SUPPORTED;

        case EINPR:
            return XOCEAN_SIGNAL_INTERRUPTED;

        default:
            return XOCEAN_UNKNOWN;
    }
}

#elif XOCEAN_PLATFORM(WINDOWS)

#   include <WinBase.h>

xocean_stat_t xocean_fstream_prealloc_handle_error()
{
    switch (GetLastError())
    {
        case ERROR_INVALID_HANDLE:
        case ERROR_INVALID_PARAMETER:
        case ERROR_BAD_LENGTH:
        case ERROR_BAD_ARGUMENTS:
        case ERROR_FILE_NOT_FOUND:
        case ERROR_INVALID_HANDLE_STATE:
            return XOCEAN_INVALID_ARG;

        case ERROR_NOT_ENOUGH_MEMORY:
            return XOCEAN_OUT_OF_MEMORY;

        case ERROR_ACCESS_DENIED:
        case ERROR_SHARING_VIOLATION:
        case ERROR_PRIVILEGE_NOT_HELD:
            return XOCEAN_PERMISSION_DENIED;
        
        case ERROR_BAD_FILE_TYPE:
            return XOCEAN_BAD_TYPE;

        case ERROR_FILE_OPERATION_ABORTED:
            return XOCEAN_SIGNAL_INTERRUPTED;

        case ERROR_VOLUME_FULL:
        case ERROR_VOLUME_QUOTA_EXCEEDED:
            return XOCEAN_DISK_FULL;

        case ERROR_HANDLE_TIMEOUT:
            return XOCEAN_TIMEOUT;

        case ERROR_PIPE_BUSY:
            return XOCEAN_BUSY;

        case ERROR_INSUFFICIENT_BUFFER:
            XOCEAN_BUG(0);

        default:
            return XOCEAN_UNKNOWN;
    }
}

xocean_stat_t xocean_fstream_prealloc(
    XOceanIOFStream * stream , 
    xocean_size_t size
){
    FILE_ALLOCATE_INFORMATION falloc_info;
#   if XOCEAN_SYSTEM_BIT(64)
    falloc_info.AllocationSize.QuadPart = size;
#   else
    falloc_info.AllocationSize.LowPart = size;
    falloc_info.AllocationSize.HighPart = 0;
#   endif // XOCEAN_SYSTEM_BIT
    return SetFileInformationByHandle((HANDLE)(((XOceanFileStreamBase*)stream)->handle) , 
                               FileAllocationInfo , &falloc_info , 
                               sizeof(falloc_info)) ? XOCEAN_OK :
                               xocean_fstream_prealloc_handle_error();

}

#endif // XOCEAN_PLATFORM

#if defined(__cplusplus)
}
#endif // __cplusplus