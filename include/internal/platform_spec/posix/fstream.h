#pragma once
#define __XOC_POSIX_FSTREAM_H__

#if !defined(__XOC_FSTREAM_H__)
#   error "Never include this header file directly. Use <xoc/fstream.h> instead."
#endif

#include <unistd.h>
#include <sys/syscall.h>
#include "common.h"

#define XOC_FILE_READONLY    O_RDONLY
#define XOC_FILE_WRITEONLY   O_WRONLY
#define XOC_FILE_READWRITE   O_RDWR

#define XOC_FILE_CLEAN_OPEN  ( O_CREAT | O_TRUNC)
#define XOC_FILE_OPEN_EXISTING  O_EXCL
#define XOC_FILE_TRUNCATE_EXISTING (O_TRUNC | O_EXCL)
#define XOC_FILE_NO_BUFFERING  O_DIRECT
#define XOC_FILE_SEQUENTIAL  0
#define XOC_FILE_RANDOM_ACCESS 0

#define __XOC_POSIX_ONCE_READ_LIMIT 0x7ffff000

xoc_stat_t 
XOC_IMPL(xoc_file_open)(
    XOC_File **      file ,
    xoc_ccstring_t   path ,
    xoc_flag8_t      access_mode , 
){
    int fd = open(path , mode);
    if (fd == -1)
    {
        return __xoc_file_handle_open_error(); 
    }
    __xoc_write_pointer_as_int(file , fd);
    return XOC_OK;
}

XOC_FORCE_INLINE
void 
XOC_IMPL(xoc_file_close)(
    XOC_File * file
){
    if (file)
        close(__xoc_read_pointer_as_int(file));
}

XOC_FORCE_INLINE
xoc_uint32_t 
__xoc_file_read32(
    XOC_File *      file ,
    xoc_byte_t *    buf ,
    xoc_size_t      size
){
    syscall(SYS_read  , __xoc_read_pointer_as_int(file) , buf , size);
    //read(__xoc_read_pointer_as_int(file) , buf , size);
}

xoc_size_t 
XOC_IMPL(__xoc_file_read32)(
    XOC_File *        file ,
    xoc_byte_t *     buf ,
    xoc_size_t       size
){
    xoc_size_t remain_size = size , have_read = 0 , once_read;
    for (; remain_size >= __XOC_POSIX_ONCE_READ_LIMIT; 
           remain_size -= __XOC_POSIX_ONCE_READ_LIMIT
    ){
        once_read = __xoc_file_read32(file , buf , __XOC_POSIX_ONCE_READ_LIMIT);
        if (once_read)
        {
            xoc_file_auto_handle_read_error(file , once_read);
            buf += once_read;
            have_read += once_read;
        }
        return have_read;
    }
    have_read += __xoc_file_read32(__xoc_read_pointer_as_int(file) , buf , remain_size);
    return have_read;
}

XOC_FORCE_INLINE 
xoc_stat_t 
__xoc_auto_handle_file_seek_error(
    off_t               offset ,
    xoc_offset_t *   current_offset
){
    if (offset == -1)
    {
        switch (offset)
        {
            case EINVAL:
            case EOVERFLOW: return XOC_INVALID_ARG;
            case EBADF:     return XOC_INVALID_HANDLE;
            case ESPIPE:    return XOC_BAD_TYPE;
        }
    }

    if (current_offset)
        *current_offset = offset;

    return XOC_OK;
}

XOC_FORCE_INLINE
xoc_stat_t
XOC_IMPL(xoc_file_seek)(
    XOC_File *       file ,
    xoc_offset_t     desired_offset ,
    xoc_flag32_t     move_method ,
    xoc_offset_t *   current_offset
){
    off_t off = lseek(__xoc_read_pointer_as_int(file) , desired_offset , move_method);
    return __xoc_auto_handle_file_seek_error(off , current_offset);
}

XOC_FORCE_INLINE
xoc_stat_t 
XOC_IMPL(xoc_fstream_prealloc)(
    XOC_File *    file , 
    xoc_size_t   size
){
    return fallocate(__xoc_read_pointer_as_int(file) , 0 , 0 , size) ? 
           __xoc_file_prealloc_error() : XOC_OK;
}

#if 0

#   include <WinBase.h>

xoc_stat_t xoc_fstream_prealloc_handle_error()
{
    switch (GetLastError())
    {
        case ERROR_INVALID_HANDLE:
        case ERROR_INVALID_PARAMETER:
        case ERROR_BAD_LENGTH:
        case ERROR_BAD_ARGUMENTS:
        case ERROR_FILE_NOT_FOUND:
        case ERROR_INVALID_HANDLE_STATE:
            return XOC_INVALID_ARG;

        case ERROR_NOT_ENOUGH_MEMORY:
            return XOC_OUT_OF_MEMORY;

        case ERROR_ACCESS_DENIED:
        case ERROR_SHARING_VIOLATION:
        case ERROR_PRIVILEGE_NOT_HELD:
            return XOC_PERMISSION_DENIED;

        case ERROR_BAD_FILE_TYPE:
            return XOC_BAD_TYPE;

        case ERROR_FILE_OPERATION_ABORTED:
            return XOC_SIGNAL_INTERRUPTED;

        case ERROR_VOLUME_FULL:
        case ERROR_VOLUME_QUOTA_EXCEEDED:
            return XOC_DISK_NO_SPACE;

        case ERROR_HANDLE_TIMEOUT:
            return XOC_TIMEOUT;

        case ERROR_PIPE_BUSY:
            return XOC_BUSY;

        case ERROR_INSUFFICIENT_BUFFER:
            XOC_BUG(0);

        default:
            return XOC_UNKNOWN;
    }
}

#if 0
xoc_stat_t xoc_fstream_prealloc(
    XOCIOFStream * stream , 
    xoc_size_t size
){
    FILE_ALLOCATE_INFORMATION falloc_info;
#   if XOC_SYSTEM_BIT(64)
    falloc_info.AllocationSize.QuadPart = size;
#   else
    falloc_info.AllocationSize.LowPart = size;
    falloc_info.AllocationSize.HighPart = 0;
#   endif // XOC_SYSTEM_BIT
    return SetFileInformationByHandle((HANDLE)(((XOC_FileStreamBase*)stream)->handle) , 
                               FileAllocationInfo , &falloc_info , 
                               sizeof(falloc_info)) ? XOC_OK :
                               xoc_fstream_prealloc_handle_error();

}
#endif

#endif // XOC_PLATFORM