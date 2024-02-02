#include "fstream.h"
#include <fcntl.h>

#define XOCEAN_POSIX_ONCE_READ_LIMIT 0x7ffff000

XOCEAN_FORCE_INLINE
int xocean_file_get_fd(
    XOceanFile * file
){
    return (int)file->handle;
}

XOCEAN_FORCE_INLINE
void xocean_file_set_fd(
    XOceanFile *    file ,
    int             fd
){
    file->handle = (xocean_pointer_t)fd;
}

XOCEAN_API
xocean_stat_t XOCEAN_IMPL(xocean_file_open)(
    XOceanFile *        file ,
    xocean_ccstring_t   path ,
    xocean_flag32_t     mode 
){
    O_CREAT;
    int fd = open(path , mode);
    if(fd == -1)
    {

    }
    xocean_file_set_fd(file , fd);
    return XOCEAN_OK;
}

XOCEAN_API
void XOCEAN_IMPL(xocean_file_close)(
    XOceanFile * file
){
    close(xocean_file_get_fd(file));
}

XOCEAN_FORCE_INLINE
xocean_uint32_t xocean_file_read32(
    XOceanFile *    file ,
    xocean_byte_t * buf ,
    xocean_size_t   size
){
    read(xocean_file_get_fd(file) , buf , size);
}

XOCEAN_FORCE_INLINE
void xocean_file_auto_handle_read_error(
    XOceanFile *    file ,
    xocean_uint32_t once_read
){
    // @todo
}

XOCEAN_API
xocean_size_t XOCEAN_IMPL(xocean_file_read)(
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
    have_read += xocean_file_read32(file , buf , remain_size);
    return have_read;
}

XOCEAN_FORCE_INLINE
xocean_stat_t xocean_auto_handle_file_seek_error(
    off_t offset
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
    return offset;
}

XOCEAN_API
xocean_offset_t XOCEAN_IMPL(xocean_file_seek)(
    XOceanFile *    file ,
    xocean_offset_t offset ,
    xocean_flag32_t move_method
){
    off_t off = lseek(xocean_file_get_fd(file) , offset , move_method);
    return xocean_auto_handle_file_seek_error(off);
}

#if XOCEAN_PLATFORM(LINUX)
#   include "falloc-linux.c"
#else

XOCEAN_API
xocean_stat_t XOCEAN_IMPL(xocean_file_alloc)(
    XOceanFile *    file ,
    xocean_size_t   size
){
    switch(posix_fallocate(xocean_file_get_fd(file) , 0 , size))
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
