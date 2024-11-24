#include "base.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

QO_NO_INLINE
qo_stat_t
__qo_sysfile_open_error()
{
    switch (errno)
    {
        case EBADF:
        case ENOENT:        return QO_BAD_PATH;
        case EINVAL:        return QO_INVALID_ARG;
        case EPERM:
        case EACCES:        return QO_PERMISSION_DENIED;
        case EEXIST:        return QO_ALREADY_EXISTS;
        case EMFILE:        return QO_NO_RESOURCE;
        case EBUSY:         return QO_TARGET_BUSY;
        case ENAMETOOLONG:  return QO_TOO_LONG;
        case ENOMEM:        return QO_OUT_OF_MEMORY;
        case EOVERFLOW:     return QO_FILE_TOO_BIG;
        case EFAULT:        return QO_ACCESS_VIOLATED;
        case EINTR:         return QO_SIGNAL_INTERRUPTED;
        default:            return QO_UNKNOWN_ERROR;
    }
}

QO_NO_INLINE
qo_stat_t
__qo_sysfile_prealloc_error()
{
    switch (errno)
    {
        case EBADF:     return QO_INVALID_HANDLE;
        case EINVAL:    return QO_INVALID_ARG;
        case EFBIG:     return QO_FILE_TOO_BIG;
        case ENOSPC:    return QO_DISK_NO_SPACE;
        case ENODEV:
        case ESPIPE:    return QO_BAD_TYPE;
        case EIO:       return QO_BROKEN_DEVICE;
        case ENOSYS:
        case ENOTSUP:   return QO_NOT_SUPPORTED;
        case EINTR:     return QO_SIGNAL_INTERRUPTED;
        case EPERM:     return QO_PERMISSION_DENIED;
        default:        return QO_UNKNOWN_ERROR;
    }
}

QO_NO_INLINE
qo_stat_t
__qo_sysfile_read_error()
{
    switch (errno)
    {
        case EBADF:         return QO_INVALID_HANDLE;
        case EFAULT:        return QO_ACCESS_VIOLATED;
        case EINVAL:    
        case EAGAIN:
        case EWOULDBLOCK:   return QO_INVALID_ARG;
        case EIO:           return QO_BROKEN_DEVICE;
        case EINTR:         return QO_SIGNAL_INTERRUPTED;
        case EISDIR:        QO_BUG("Read from direcory");
        default:            return QO_UNKNOWN_ERROR;
    }
}

QO_NO_INLINE
qo_stat_t
__qo_sysfile_write_error()
{
    switch (errno)
    {
        case EBADF:         return QO_INVALID_HANDLE;
        case EFAULT:        return QO_ACCESS_VIOLATED;
        case EAGAIN:
        case EWOULDBLOCK:
        case ENOSPC:
        case EDESTADDRREQ:  return QO_INVALID_ARG;
        case EPERM:         return QO_PERMISSION_DENIED;
        case EDQUOT:        return QO_DISK_NO_SPACE;
        case EIO:           return QO_BROKEN_DEVICE;
        case EFBIG:         return QO_FILE_TOO_BIG;
        case EINTR:         return QO_SIGNAL_INTERRUPTED;
        case EPIPE:         return QO_PIPE_DISCONNECTED;
        default:            return QO_UNKNOWN_ERROR;
    }
}