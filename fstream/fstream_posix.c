#include "fstream.h"
#include <fcntl.h>

#define XOCEAN_POSIX_ONCE_READ_LIMIT 0x7ffff000


XOCEAN_GLOBAL_LOCAL XOCEAN_FORCE_INLINE 
xocean_stat_t
__xocean_file_handle_open_error()
{
    switch (errno)
    {
        case EBADF:
        case ENOENT:        return XOCEAN_BAD_PATH;
        case EINVAL:        return XOCEAN_INVALID_ARG;
        case EPERM:
        case EACCES:        return XOCEAN_PERMISSION_DENIED;
        case EEXIST:        return XOCEAN_FILE_ALREADY_EXISTS;
        case EMFILE:        return XOCEAN_NO_RESOURCE;
        case EBUSY:         return XOCEAN_TARGET_BUSY;
        case ENAMETOOLONG:  return XOCEAN_TOO_LONG;
        case ENOMEM:        return XOCEAN_OUT_OF_MEMORY;
        case EOVERFLOW:     return XOCEAN_FILE_TOO_BIG;
        case EFAULT:        return XOCEAN_ACCESS_VIOLATED;
        case EINTR:         return XOCEAN_SIGNAL_INTERRUPTED;
        default:            return XOCEAN_UNKNOWN_ERROR;
    }
}

xocean_stat_t 
XOCEAN_IMPL(xocean_file_open)(
    XOceanFile **       file ,
    xocean_ccstring_t   path ,
    xocean_flag32_t     mode 
){
    int fd = open(path , mode);
    if(fd == -1)
    {
        return __xocean_file_handle_open_error(); 
    }
    *((xocean_intmax_t *)file) = fd;
    return XOCEAN_OK;
}

XOCEAN_API
void XOCEAN_IMPL(xocean_file_close)(
    XOceanFile * file
){
    close((int)file);
}

XOCEAN_FORCE_INLINE
xocean_uint32_t xocean_file_read32(
    XOceanFile *    file ,
    xocean_byte_t * buf ,
    xocean_size_t   size
){
    read((int)fd , buf , size);
}


XOCEAN_API
xocean_size_t 
XOCEAN_IMPL(xocean_file_read32)(
    XOceanFile *        file ,
    xocean_byte_t *     buf ,
    xocean_size_t       size
){
    xocean_size_t remain_size = size , have_read = 0 , once_read;
    for (; remain_size >= XOCEAN_POSIX_ONCE_READ_LIMIT; 
           remain_size -= XOCEAN_POSIX_ONCE_READ_LIMIT
    ){
        once_read = xocean_file_read32(file , buf , XOCEAN_POSIX_ONCE_READ_LIMIT);
        if(once_read)
        {
            xocean_file_auto_handle_read_error(file , once_read);
            buf += once_read;
            have_read += once_read;
        }
        return have_read;
    }
    have_read += xocean_file_read32((int)file , buf , remain_size);
    return have_read;
}

XOCEAN_GLOBAL_LOCAL XOCEAN_FORCE_INLINE 
xocean_stat_t 
__xocean_auto_handle_file_seek_error(
    off_t               offset ,
    xocean_offset_t *   current_offset
){
    if (offset == -1)
    {
        switch (offset)
        {
            case EINVAL:
            case EOVERFLOW: return XOCEAN_INVALID_ARG;
            case EBADF:     return XOCEAN_INVALID_HANDLE;
            case ESPIPE:    return XOCEAN_BAD_TYPE;
        }
    }

    if(current_offset)
        *current_offset = offset;

    return XOCEAN_OK;
}


xocean_stat_t
XOCEAN_IMPL(xocean_file_seek)(
    XOceanFile *        file ,
    xocean_offset_t     desired_offset ,
    xocean_flag32_t     move_method ,
    xocean_offset_t *   current_offset
){
    off_t off = lseek((int)file , desired_offset , move_method);
    return __xocean_auto_handle_file_seek_error(off , current_offset);
}

#if XOCEAN_PLATFORM(LINUX)
#   include "falloc-linux.c"
#else

XOCEAN_API
xocean_stat_t XOCEAN_IMPL(xocean_file_alloc)(
    XOceanFile *    file ,
    xocean_size_t   size
){
    switch(posix_fallocate((int)file , 0 , size))
    {
        case 0:         return XOCEAN_OK;
        case ENOSPC:    return XOCEAN_DISK_NO_SPACE;
        case EFBIG:     return XOCEAN_FILE_TOO_BIG;
        case EBADF:
        case ENODEV:    return XOCEAN_INVALID_HANDLE;
        case EINVAL:    return XOCEAN_INVALID_ARG;
        case ESPIPE:    return XOCEAN_BAD_TYPE;
        case EOPNOTSUPP:return XOCEAN_NOT_SUPPORTED;
        case EINPR:     return XOCEAN_SIGNAL_INTERRUPTED;
    }
}

#endif // XOCEAN_PLATFORM(LINUX)
