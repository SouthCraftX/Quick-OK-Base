#include "base.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

XOC_NO_INLINE
xoc_stat_t
__xoc_file_open_error()
{
    switch (errno)
    {
        case EBADF:
        case ENOENT:        return XOC_BAD_PATH;
        case EINVAL:        return XOC_INVALID_ARG;
        case EPERM:
        case EACCES:        return XOC_PERMISSION_DENIED;
        case EEXIST:        return XOC_FILE_ALREADY_EXISTS;
        case EMFILE:        return XOC_NO_RESOURCE;
        case EBUSY:         return XOC_TARGET_BUSY;
        case ENAMETOOLONG:  return XOC_TOO_LONG;
        case ENOMEM:        return XOC_OUT_OF_MEMORY;
        case EOVERFLOW:     return XOC_FILE_TOO_BIG;
        case EFAULT:        return XOC_ACCESS_VIOLATED;
        case EINTR:         return XOC_SIGNAL_INTERRUPTED;
        default:            return XOC_UNKNOWN_ERROR;
    }
}

XOC_NO_INLINE
xoc_stat_t
__xoc_file_prealloc_error()
{
    switch (errno)
    {
        case EBADF:     return XOC_INVALID_HANDLE;
        case EINVAL:    return XOC_INVALID_ARG;
        case EFBIG:     return XOC_FILE_TOO_BIG;
        case ENOSPC:    return XOC_DISK_NO_SPACE;
        case ENODEV:
        case ESPIPE:    return XOC_BAD_TYPE;
        case EIO:       return XOC_BROKEN_DEVICE;
        case ENOSYS:
        case ENOTSUP:   return XOC_NOT_SUPPORTED;
        case EINTR:     return XOC_SIGNAL_INTERRUPTED;
        case EPERM:     return XOC_PERMISSION_DENIED;
        default:        return XOC_UNKNOWN_ERROR;
    }
}

XOC_NO_INLINE
xoc_stat_t
__xoc_file_read_error()
{
    switch (errno)
    {
        case EBADF:         return XOC_INVALID_HANDLE;
        case EFAULT:        return XOC_ACCESS_VIOLATED;
        case EINVAL:    
        case EAGAIN:
        case EWOULDBLOCK:   return XOC_INVALID_ARG;
        case EIO:           return XOC_BROKEN_DEVICE;
        case EINTR:         return XOC_SIGNAL_INTERRUPTED;
        case EISDIR:        XOC_BUG("Read from direcory");
        default:            return XOC_UNKNOWN_ERROR;
    }
}

XOC_NO_INLINE
xoc_stat_t
__xoc_file_write_error()
{
    switch (errno)
    {
        case EBADF:         return XOC_INVALID_HANDLE;
        case EFAULT:        return XOC_ACCESS_VIOLATED;
        case EAGAIN:
        case EWOULDBLOCK:
        case ENOSPC:
        case EDESTADDRREQ:  return XOC_INVALID_ARG;
        case EPERM:         return XOC_PERMISSION_DENIED;
        case EDQUOT:        return XOC_DISK_NO_SPACE;
        case EIO:           return XOC_BROKEN_DEVICE;
        case EFBIG:         return XOC_FILE_TOO_BIG;
        case EINTR:         return XOC_SIGNAL_INTERRUPTED;
        case EPIPE:         return XOC_PIPE_DISCONNECTED;
        default:            return XOC_UNKNOWN_ERROR;
    }
}