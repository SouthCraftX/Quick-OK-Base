#pragma once
#define __QO_POSIX_FSTREAM_H__

#if !defined(__QO_FSTREAM_H__)
#   error "Never include this header file directly. Use <qo/fstream.h> instead."
#endif

#include <unistd.h>
#include <sys/syscall.h>
#include "common.h"

#define QO_FILE_READONLY    O_RDONLY
#define QO_FILE_WRITEONLY   O_WRONLY
#define QO_FILE_READWRITE   O_RDWR

#define QO_FILE_CLEAN_OPEN  ( O_CREAT | O_TRUNC)
#define QO_FILE_OPEN_EXISTING  O_EXCL
#define QO_FILE_TRUNCATE_EXISTING (O_TRUNC | O_EXCL)
#define QO_FILE_NO_BUFFERING  O_DIRECT
#define QO_FILE_SEQUENTIAL  0
#define QO_FILE_RANDOM_ACCESS 0

#define __QO_POSIX_ONCE_READ_LIMIT 0x7ffff000

qo_stat_t 
QO_IMPL(qo_file_open)(
    QO_File **      file ,
    qo_ccstring_t   path ,
    qo_flag32_t      access_mode ,
    qo_flag32_t      open_mode
    qo_flag32_t      hints
){
    int fd = open(path , mode);
    if (fd == -1)
    {
        return __qo_file_handle_open_error(); 
    }
    __qo_write_pointer_as_int(file , fd);
    return QO_OK;
}

QO_FORCE_INLINE
void 
QO_IMPL(qo_file_close)(
    QO_File * file
){
    if (file)
        close(__qo_read_pointer_as_int(file));
}

QO_FORCE_INLINE
qo_uint32_t 
__qo_file_read32(
    QO_File *      file ,
    qo_byte_t *    buf ,
    qo_size_t      size
){
    syscall(SYS_read  , __qo_read_pointer_as_int(file) , buf , size);
    //read(__qo_read_pointer_as_int(file) , buf , size);
}

qo_size_t 
QO_IMPL(__qo_file_read32)(
    QO_File *        file ,
    qo_byte_t *     buf ,
    qo_size_t       size
){
    qo_size_t remain_size = size , have_read = 0 , once_read;
    for (; remain_size >= __QO_POSIX_ONCE_READ_LIMIT; 
           remain_size -= __QO_POSIX_ONCE_READ_LIMIT
    ){
        once_read = __qo_file_read32(file , buf , __QO_POSIX_ONCE_READ_LIMIT);
        if (once_read)
        {
            qo_file_auto_handle_read_error(file , once_read);
            buf += once_read;
            have_read += once_read;
        }
        return have_read;
    }
    have_read += __qo_file_read32(__qo_read_pointer_as_int(file) , buf , remain_size);
    return have_read;
}

QO_FORCE_INLINE 
qo_stat_t 
__qo_auto_handle_file_seek_error(
    off_t               offset ,
    qo_offset_t *   current_offset
){
    if (offset == -1)
    {
        switch (offset)
        {
            case EINVAL:
            case EOVERFLOW: return QO_INVALID_ARG;
            case EBADF:     return QO_INVALID_HANDLE;
            case ESPIPE:    return QO_BAD_TYPE;
        }
    }

    if (current_offset)
        *current_offset = offset;

    return QO_OK;
}

QO_FORCE_INLINE
qo_stat_t
QO_IMPL(qo_file_seek)(
    QO_File *       file ,
    qo_offset_t     desired_offset ,
    qo_flag32_t     move_method ,
    qo_offset_t *   current_offset
){
    off_t off = lseek(__qo_read_pointer_as_int(file) , desired_offset , move_method);
    return __qo_auto_handle_file_seek_error(off , current_offset);
}

QO_FORCE_INLINE
qo_stat_t 
QO_IMPL(qo_fstream_prealloc)(
    QO_File *    file , 
    qo_size_t   size
){
    return fallocate(__qo_read_pointer_as_int(file) , 0 , 0 , size) ? 
           __qo_file_prealloc_error() : QO_OK;
}

#if 0

#   include <WinBase.h>

qo_stat_t qo_fstream_prealloc_handle_error()
{
    switch (GetLastError())
    {
        case ERROR_INVALID_HANDLE:
        case ERROR_INVALID_PARAMETER:
        case ERROR_BAD_LENGTH:
        case ERROR_BAD_ARGUMENTS:
        case ERROR_FILE_NOT_FOUND:
        case ERROR_INVALID_HANDLE_STATE:
            return QO_INVALID_ARG;

        case ERROR_NOT_ENOUGH_MEMORY:
            return QO_OUT_OF_MEMORY;

        case ERROR_ACCESS_DENIED:
        case ERROR_SHARING_VIOLATION:
        case ERROR_PRIVILEGE_NOT_HELD:
            return QO_PERMISSION_DENIED;

        case ERROR_BAD_FILE_TYPE:
            return QO_BAD_TYPE;

        case ERROR_FILE_OPERATION_ABORTED:
            return QO_SIGNAL_INTERRUPTED;

        case ERROR_VOLUME_FULL:
        case ERROR_VOLUME_QUOTA_EXCEEDED:
            return QO_DISK_NO_SPACE;

        case ERROR_HANDLE_TIMEOUT:
            return QO_TIMEOUT;

        case ERROR_PIPE_BUSY:
            return QO_BUSY;

        case ERROR_INSUFFICIENT_BUFFER:
            QO_BUG(0);

        default:
            return QO_UNKNOWN;
    }
}

#if 0
qo_stat_t qo_fstream_prealloc(
    QOIOFStream * stream , 
    qo_size_t size
){
    FILE_ALLOCATE_INFORMATION falloc_info;
#   if QO_SYSTEM_BIT(64)
    falloc_info.AllocationSize.QuadPart = size;
#   else
    falloc_info.AllocationSize.LowPart = size;
    falloc_info.AllocationSize.HighPart = 0;
#   endif // QO_SYSTEM_BIT
    return SetFileInformationByHandle((HANDLE)(((QO_FileStreamBase*)stream)->handle) , 
                               FileAllocationInfo , &falloc_info , 
                               sizeof(falloc_info)) ? QO_OK :
                               qo_fstream_prealloc_handle_error();

}
#endif

#endif // QO_PLATFORM