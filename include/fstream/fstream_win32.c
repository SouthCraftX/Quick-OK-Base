#include "fstream.h"

#include <fileapi.h>
#include <ntifs.h>

QO_GLOBAL_LOCAL 
DWORD qo_access_mode_list[] = {
    FILE_GENERIC_READ , FILE_GENERIC_WRITE , 
    FILE_GENERIC_READ | FILE_GENERIC_WRITE , 0
};

QO_GLOBAL_LOCAL QO_FORCE_INLINE
DWORD 
_qo_file_win_translate_flag_and_attributes(
    qo_flag32_t mode
){
    return (QO_HAS_FLAG(mode , QO_FILE_NO_CACHING) ? FILE_FLAG_NO_BUFFERING : 0) &
           (QO_HAS_FLAG(mode , QO_FILE_SEQUENTIAL) ? FILE_SEQUENTIAL_SCAN : 0) &
}

QO_GLOBAL_LOCAL QO_FORCE_INLINE
DWORD 
_qo_file_win_translate_open_mode(
    qo_flag32_t mode
){
    return (mode >> 8) & 0xff;
}

QO_NOEXPORT QO_FORCE_INLINE
DWORD 
_qo_file_win_translate_desired_access(
    qo_flag32_t mode
){
    return qo_access_mode_list[mode & 0x3];
}


qo_uint32_t 
__qo_file_read32(
    QO_File * file ,
    qo_byte_t * buf ,
    qo_uint32_t size
){
    DWORD have_read;
    return ReadFile((HANDLE)file , buf , size , &have_read , NULL) ? have_read : 0;
}

#if QO_SYSTEM_BIT(64)

QO_GLOBAL_LOCAL QO_FORCE_INLINE
qo_size_t 
__qo_file_read64(
    QO_File *    file ,
    qo_byte_t * buf ,
    qo_ssize_t  size
){
    qo_size_t have_read , once_read;
    qo_ssize_t remain;
    for(remain = size ; remain > 0 ; remain -= 0xffffffff)
    {
        once_read = __qo_file_read32(file , buf , 0xffffffff);
        if (!once_read)
            return have_read;
        have_read += once_read;
    }
    have_read += __qo_file_read32(file , buf + have_read , remain);
    return have_read;
}

qo_size_t
QO_IMPL(qo_file_read)(
    QO_File *    file , 
    qo_byte_t * buf ,
    qo_size_t   size
){
    return __qo_file_read64(file , buf , size);
}

#else

qo_size_t
QO_IMPL(qo_file_read)(
    QO_File *    file ,
    qo_byte_t * buf ,
    qo_size_t   size
){
    return __qo_file_read32(file , buf , size);
}

#endif

qo_stat_t 
QO_IMPL(qo_file_open)(
    QO_File **       file , 
    qo_ccstring_t   path ,
    qo_flag32_t     mode
){
    wchar_t wc_path[MAX_PATH] = { };
    LARGE_INTEGER file_size;
    MultiByteToWideChar(CP_THREAD_ACP , 0 , path , -1 , wc_path , MAX_PATH);

    HANDLE file_handle = CreateFileW(
        wc_path ,
        _qo_file_win_translate_desired_access(mode) ,
        FILE_SHARE_READ | FILE_SHARE_WRITE , 
        NULL , 
        _qo_file_win_translate_open_mode(mode), 
        FILE_ATTRIBUTE_NORMAL | _qo_file_win_translate_flag_and_attributes(mode) ,
        NULL
    );

    if (file_handle == INVALID_HANDLE_VALUE)
    {
        switch(GetLastError())
        {
            case ERROR_FILE_NOT_FOUND:
            case ERROR_PATH_NOT_FOUND:
                return QO_BAD_PATH;
            case ERROR_ACCESS_DENIED:
                return QO_PERMISSION_DENIED;
            default:
                return QO_FILE_OPEN_FAILED;
        }
    }
    (HANDLE)*file = file_handle;
    return QO_OK;
}


void 
QO_IMPL(qo_file_close)(
    QO_File * file
){
    CloseHandle((HANDLE)file);
}

QO_API 
qo_stat_t 
QO_IMPL(qo_file_get_size)(
    QO_File *    file ,
    qo_size_t * size
){
#   if QO_SYSTEM_BIT(64)
    BOOL ret = GetFileSizeEx((HANDLE)file , (PLARGE_INTEGER)size);
#   else
    BOOL ret = GetFileSizeEx(
        (HANDLE)file 
        &(LARGE_INTEGER){.LowPart = *size , .HighPart = 0}
    );
#   endif
    if (ret)
    {
        return QO_OK;
    }
    switch (GetLastError())
    {
        case ERROR_INVALID_HANDLE:  return QO_INVALID_HANDLE;
        case ERROR_FILE_NOT_FOUND:  return QO_BAD_PATH;
        default:                    return QO_UNKNOWN_ERROR;
    }
}

QO_FORCE_INLINE
qo_offset_t 
qo_win_large_interger_to_offset(
    LARGE_INTEGER li
){
#   if QO_SYSTEM_BIT(64)
    return li.QuadPart;
#   else
    return li.LowPart;
#   endif 
}

qo_offset_t 
QO_IMPL(qo_file_seek)(
    QO_File *    file ,
    qo_offset_t offset ,
    qo_flag32_t move_method
){
    LARGE_INTEGER after_moving_offset;
#   if QO_SYSTEM_BIT(64)
    LARGE_INTEGER li_offset = {.QuadPart = offset};
#   else
    LARGE_INTEGER li_offset = {.LowPart = offset , .HighPart = 0};
#   endif
    BOOL ret = SetFilePointerEx((HANDLE)file , 
                                li_offset , 
                                &after_moving_offset , 
                                move_method);
    if (ret)
    {
        return qo_win_large_interger_to_offset(after_moving_offset);
    }
    switch(GetLastError())
    {
        case ERROR_FILE_NOT_FOUND:
        case ERROR_INVALID_HANDLE:      return QO_BAD_FILE;
        case ERROR_LOCK_VIOLATION:      return QO_ACCESS_VIOLATED;
        case ERROR_INVALID_PARAMETER:   return QO_INVALID_ARG;
        default:                        return QO_UNKNOWN_ERROR;
    }
    return -1;
}

qo_stat_t 
__qo_fstream_prealloc_handle_error()
{
    switch (GetLastError())
    {
        case ERROR_INVALID_HANDLE:
        case ERROR_INVALID_PARAMETER:
        case ERROR_BAD_LENGTH:
        case ERROR_BAD_ARGUMENTS:
        case ERROR_FILE_NOT_FOUND:
        case ERROR_INVALID_HANDLE_STATE:    return QO_INVALID_ARG;
        case ERROR_NOT_ENOUGH_MEMORY:       return QO_OUT_OF_MEMORY;
        case ERROR_ACCESS_DENIED:
        case ERROR_SHARING_VIOLATION:
        case ERROR_PRIVILEGE_NOT_HELD:      return QO_PERMISSION_DENIED; 
        case ERROR_BAD_FILE_TYPE:           return QO_BAD_TYPE;
        case ERROR_OPERATION_ABORTED:       return QO_SIGNAL_INTERRUPTED;
        case ERROR_HANDLE_DISK_FULL:
        case ERROR_DISK_FULL:               return QO_DISK_NO_SPACE;
        case ERROR_HANDLE_TIMEOUT:          return QO_TIMEOUT;
        case ERROR_PIPE_BUSY:               return QO_TARGET_BUSY;
        case ERROR_INSUFFICIENT_BUFFER:     QO_BUG(0);
        default:                            return QO_UNKNOWN_ERROR;
    }
}

qo_stat_t 
qo_fstream_prealloc(
    QO_File *    file , 
    qo_size_t   size
){
    FILE_ALLOCATE_INFORMATION falloc_info;
    
#   if QO_SYSTEM_BIT(64)
    falloc_info.AllocationSize.QuadPart = size;
#   else
    falloc_info.AllocationSize.LowPart = size;
    falloc_info.AllocationSize.HighPart = 0;
#   endif // QO_SYSTEM_BIT

    return SetFileInformationByHandle(
        (HANDLE)file , 
        FileAllocationInfo , 
        &falloc_info , 
        sizeof(falloc_info)
    ) ? QO_OK : __qo_fstream_prealloc_handle_error();

}


