#include "fstream.h"
#include "internal/platform_spec/posix/common.h"
#include <fcntl.h>

#define __QO_POSIX_ONCE_READ_LIMIT 0x7ffff000


#if QO_PLATFORM(LINUX)
#   include "falloc-linux.c"
#else

QO_API
qo_stat_t QO_IMPL(qo_sysfile_alloc)(
    QO_SysFileStream *    file ,
    qo_size_t   size
){
    switch(posix_fallocate(__qo_read_pointer_as_int(file) , 0 , size))
    {
        case 0:         return QO_OK;
        case ENOSPC:    return QO_DISK_NO_SPACE;
        case EFBIG:     return QO_FILE_TOO_BIG;
        case EBADF:
        case ENODEV:    return QO_INVALID_HANDLE;
        case EINVAL:    return QO_INVALID_ARG;
        case ESPIPE:    return QO_BAD_TYPE;
        case EOPNOTSUPP:return QO_NOT_SUPPORTED;
        case EINPR:     return QO_SIGNAL_INTERRUPTED;
    }
}

#endif // QO_PLATFORM(LINUX)
