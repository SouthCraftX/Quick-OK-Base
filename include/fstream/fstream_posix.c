#include "fstream.h"
#include "internel/platform_spec/posix/common.h"
#include <fcntl.h>

#define __XOC_POSIX_ONCE_READ_LIMIT 0x7ffff000


#if XOC_PLATFORM(LINUX)
#   include "falloc-linux.c"
#else

XOC_API
xoc_stat_t XOC_IMPL(xoc_file_alloc)(
    XOC_File *    file ,
    xoc_size_t   size
){
    switch(posix_fallocate(__xoc_read_ptr_as_int(file) , 0 , size))
    {
        case 0:         return XOC_OK;
        case ENOSPC:    return XOC_DISK_NO_SPACE;
        case EFBIG:     return XOC_FILE_TOO_BIG;
        case EBADF:
        case ENODEV:    return XOC_INVALID_HANDLE;
        case EINVAL:    return XOC_INVALID_ARG;
        case ESPIPE:    return XOC_BAD_TYPE;
        case EOPNOTSUPP:return XOC_NOT_SUPPORTED;
        case EINPR:     return XOC_SIGNAL_INTERRUPTED;
    }
}

#endif // XOC_PLATFORM(LINUX)
