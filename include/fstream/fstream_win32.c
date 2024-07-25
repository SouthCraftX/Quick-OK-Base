#include "fstream.h"

#include <fileapi.h>
#include <ntifs.h>

XOC_GLOBAL_LOCAL 
DWORD xoc_access_mode_list[] = {
    FILE_GENERIC_READ , FILE_GENERIC_WRITE , 
    FILE_GENERIC_READ | FILE_GENERIC_WRITE , 0
};

XOC_GLOBAL_LOCAL XOC_FORCE_INLINE
DWORD 
_xoc_file_win_translate_flag_and_attributes(
    xoc_flag32_t mode
){
    return (XOC_HAS_FLAG(mode , XOC_FILE_NO_CACHING) ? FILE_FLAG_NO_BUFFERING : 0) &
           (XOC_HAS_FLAG(mode , XOC_FILE_SEQUENTIAL) ? FILE_SEQUENTIAL_SCAN : 0) &
}

XOC_GLOBAL_LOCAL XOC_FORCE_INLINE
DWORD 
_xoc_file_win_translate_open_mode(
    xoc_flag32_t mode
){
    return (mode >> 8) & 0xff;
}

XOC_NOEXPORT XOC_FORCE_INLINE
DWORD 
_xoc_file_win_translate_desired_access(
    xoc_flag32_t mode
){
    return xoc_access_mode_list[mode & 0x3];
}


xoc_uint32_t 
__xoc_file_read32(
    XOC_File * file ,
    xoc_byte_t * buf ,
    xoc_uint32_t size
){
    DWORD have_read;
    return ReadFile((HANDLE)file , buf , size , &have_read , NULL) ? have_read : 0;
}

#if XOC_SYSTEM_BIT(64)

XOC_GLOBAL_LOCAL XOC_FORCE_INLINE
xoc_size_t 
__xoc_file_read64(
    XOC_File *    file ,
    xoc_byte_t * buf ,
    xoc_ssize_t  size
){
    xoc_size_t have_read , once_read;
    xoc_ssize_t remain;
    for(remain = size ; remain > 0 ; remain -= 0xffffffff)
    {
        once_read = __xoc_file_read32(file , buf , 0xffffffff);
        if (!once_read)
            return have_read;
        have_read += once_read;
    }
    have_read += __xoc_file_read32(file , buf + have_read , remain);
    return have_read;
}

xoc_size_t
XOC_IMPL(xoc_file_read)(
    XOC_File *    file , 
    xoc_byte_t * buf ,
    xoc_size_t   size
){
    return __xoc_file_read64(file , buf , size);
}

#else

xoc_size_t
XOC_IMPL(xoc_file_read)(
    XOC_File *    file ,
    xoc_byte_t * buf ,
    xoc_size_t   size
){
    return __xoc_file_read32(file , buf , size);
}

#endif

xoc_stat_t 
XOC_IMPL(xoc_file_open)(
    XOC_File **       file , 
    xoc_ccstring_t   path ,
    xoc_flag32_t     mode
){
    wchar_t wc_path[MAX_PATH] = { };
    LARGE_INTEGER file_size;
    MultiByteToWideChar(CP_THREAD_ACP , 0 , path , -1 , wc_path , MAX_PATH);

    HANDLE file_handle = CreateFileW(
        wc_path ,
        _xoc_file_win_translate_desired_access(mode) ,
        FILE_SHARE_READ | FILE_SHARE_WRITE , 
        NULL , 
        _xoc_file_win_translate_open_mode(mode), 
        FILE_ATTRIBUTE_NORMAL | _xoc_file_win_translate_flag_and_attributes(mode) ,
        NULL
    );

    if (file_handle == INVALID_HANDLE_VALUE)
    {
        switch(GetLastError())
        {
            case ERROR_FILE_NOT_FOUND:
            case ERROR_PATH_NOT_FOUND:
                return XOC_BAD_PATH;
            case ERROR_ACCESS_DENIED:
                return XOC_PERMISSION_DENIED;
            default:
                return XOC_FILE_OPEN_FAILED;
        }
    }
    (HANDLE)*file = file_handle;
    return XOC_OK;
}


void 
XOC_IMPL(xoc_file_close)(
    XOC_File * file
){
    CloseHandle((HANDLE)file);
}

XOC_API 
xoc_stat_t 
XOC_IMPL(xoc_file_get_size)(
    XOC_File *    file ,
    xoc_size_t * size
){
#   if XOC_SYSTEM_BIT(64)
    BOOL ret = GetFileSizeEx((HANDLE)file , (PLARGE_INTEGER)size);
#   else
    BOOL ret = GetFileSizeEx(
        (HANDLE)file 
        &(LARGE_INTEGER){.LowPart = *size , .HighPart = 0}
    );
#   endif
    if (ret)
    {
        return XOC_OK;
    }
    switch (GetLastError())
    {
        case ERROR_INVALID_HANDLE:  return XOC_INVALID_HANDLE;
        case ERROR_FILE_NOT_FOUND:  return XOC_BAD_PATH;
        default:                    return XOC_UNKNOWN_ERROR;
    }
}

XOC_FORCE_INLINE
xoc_offset_t 
xoc_win_large_interger_to_offset(
    LARGE_INTEGER li
){
#   if XOC_SYSTEM_BIT(64)
    return li.QuadPart;
#   else
    return li.LowPart;
#   endif 
}

xoc_offset_t 
XOC_IMPL(xoc_file_seek)(
    XOC_File *    file ,
    xoc_offset_t offset ,
    xoc_flag32_t move_method
){
    LARGE_INTEGER after_moving_offset;
#   if XOC_SYSTEM_BIT(64)
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
        return xoc_win_large_interger_to_offset(after_moving_offset);
    }
    switch(GetLastError())
    {
        case ERROR_FILE_NOT_FOUND:
        case ERROR_INVALID_HANDLE:      return XOC_BAD_FILE;
        case ERROR_LOCK_VIOLATION:      return XOC_ACCESS_VIOLATED;
        case ERROR_INVALID_PARAMETER:   return XOC_INVALID_ARG;
        default:                        return XOC_UNKNOWN_ERROR;
    }
    return -1;
}

xoc_stat_t 
__xoc_fstream_prealloc_handle_error()
{
    switch (GetLastError())
    {
        case ERROR_INVALID_HANDLE:
        case ERROR_INVALID_PARAMETER:
        case ERROR_BAD_LENGTH:
        case ERROR_BAD_ARGUMENTS:
        case ERROR_FILE_NOT_FOUND:
        case ERROR_INVALID_HANDLE_STATE:    return XOC_INVALID_ARG;
        case ERROR_NOT_ENOUGH_MEMORY:       return XOC_OUT_OF_MEMORY;
        case ERROR_ACCESS_DENIED:
        case ERROR_SHARING_VIOLATION:
        case ERROR_PRIVILEGE_NOT_HELD:      return XOC_PERMISSION_DENIED; 
        case ERROR_BAD_FILE_TYPE:           return XOC_BAD_TYPE;
        case ERROR_OPERATION_ABORTED:       return XOC_SIGNAL_INTERRUPTED;
        case ERROR_HANDLE_DISK_FULL:
        case ERROR_DISK_FULL:               return XOC_DISK_NO_SPACE;
        case ERROR_HANDLE_TIMEOUT:          return XOC_TIMEOUT;
        case ERROR_PIPE_BUSY:               return XOC_TARGET_BUSY;
        case ERROR_INSUFFICIENT_BUFFER:     XOC_BUG(0);
        default:                            return XOC_UNKNOWN_ERROR;
    }
}

xoc_stat_t 
xoc_fstream_prealloc(
    XOC_File *    file , 
    xoc_size_t   size
){
    FILE_ALLOCATE_INFORMATION falloc_info;
    
#   if XOC_SYSTEM_BIT(64)
    falloc_info.AllocationSize.QuadPart = size;
#   else
    falloc_info.AllocationSize.LowPart = size;
    falloc_info.AllocationSize.HighPart = 0;
#   endif // XOC_SYSTEM_BIT

    return SetFileInformationByHandle(
        (HANDLE)file , 
        FileAllocationInfo , 
        &falloc_info , 
        sizeof(falloc_info)
    ) ? XOC_OK : __xoc_fstream_prealloc_handle_error();

}


