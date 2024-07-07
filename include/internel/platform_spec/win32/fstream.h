#include "fstream.h"

#include <fileapi.h>

static DWORD xoc_access_mode_list[] = {FILE_GENERIC_READ , FILE_GENERIC_WRITE , 
                                   FILE_GENERIC_READ | FILE_GENERIC_WRITE , 0};

XOC_NOEXPORT XOC_FORCE_INLINE
DWORD _xoc_file_win_translate_flag_and_attributes(
    xoc_flag32_t mode
){
    return (XOC_HAS_FLAG(mode , XOC_FILE_NO_CACHING) ? FILE_FLAG_NO_BUFFERING : 0) &
           (XOC_HAS_FLAG(mode , XOC_FILE_SEQUENTIAL) ? FILE_SEQUENTIAL_SCAN : 0) &
}

XOC_NOEXPORT XOC_FORCE_INLINE
DWORD _xoc_file_win_translate_open_mode(
    xoc_flag32_t mode
){
    return (mode >> 8) & 0xff;
}

XOC_NOEXPORT XOC_FORCE_INLINE
DWORD _xoc_file_win_translate_desired_access(
    xoc_flag32_t mode
){
    return xoc_access_mode_list[mode & 0x3];
}

XOC_NOEXPORT XOC_FORCE_INLINE
DWORD _xoc_file_win_translate_shared_mode(
    xoc_flag32_t mode
){
    return (XOC_HAS_FLAG(mode , XOC_FILE_SHARED_READ) ? FILE_SHARE_READ : 0) &
           (XOC_HAS_FLAG(mode , XOC_FILE_SHARED_WRITE) ? FILE_SHARE_WRITE : 0) &
           (XOC_HAS_FLAG(mode , XOC_FILE_SHARED_DELETE) ? FILE_SHARE_DELETE : 0);
}

xoc_uint32_t 
__xoc_file_read32(
    XOC_File      file ,
    xoc_byte_t * buf ,
    xoc_uint32_t size
){
    DWORD have_read;
    return ReadFile(file->handle , buf , size , &have_read , NULL) ? have_read : 0;
}

#   if XOC_SYSTEM_BIT(64)
XOC_API
xoc_size_t xoc_file_read64(
    XOC_File *    file ,
    xoc_byte_t * buf ,
    xoc_ssize_t  size
){
    xoc_size_t have_read , once_read;
    xoc_ssize_t remain;
    for(remain = size ; remain > 0 ; remain -= 0xffffffff)
    {
        once_read = xoc_file_read(file , buf , 0xffffffff);
        if(!once_read)
            return have_read;
        have_read += once_read;
    }
    have_read += xoc_file_read(file , buf + have_read , remain);
    return have_read;
}
#   endif

XOC_API
xoc_stat_t xoc_file_open(
    XOC_File *        file , 
    xoc_ccstring_t   path ,
    xoc_flag32_t     mode
){
    wchar_t wc_path[MAX_PATH] = { };
    LARGE_INTEGER file_size;
    MultiByteToWideChar(CP_THREAD_ACP , 0 , path , -1 , wc_path , MAX_PATH);

    HANDLE file_handle = CreateFileW(
        wc_path ,
        _xoc_file_win_translate_desired_access(mode) ,
        _xoc_file_win_translate_shared_mode(mode) , 
        NULL , 
        _xoc_file_win_translate_open_mode(mode), 
        FILE_ATTRIBUTE_NORMAL | _xoc_file_win_translate_flag_and_attributes(mode) ,
        NULL
    );

    if (file->handle == INVALID_HANDLE_VALUE)
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
    file->handle = file_handle;
    return XOC_OK;
}

XOC_API
void xoc_file_close(
    XOC_File * file
){
    CloseHandle(file->handle);
    file->handle = INVALID_HANDLE_VALUE;
}

XOC_API 
xoc_stat_t xoc_file_get_size(
    XOC_File * file ,
    xoc_size_t * size
){
#   if XOC_SYSTEM_BIT(64)
    BOOL ret = GetFileSizeEx(file->handle , (PLARGE_INTEGER)size);
#   else
    BOOL ret = GetFileSizeEx(file->handle , &(LARGE_INTEGER){.LowPart = *size , .HighPart = 0});
#   endif
    if (ret)
    {
        return XOC_OK;
    }
    switch (GetLastError())
    {
        // TODO
        case /* constant-expression */:
            /* code */
            break;

        default:
            break;
    }
}

XOC_FORCE_INLINE
xoc_offset_t xoc_win_large_interger_to_offset(
    LARGE_INTEGER li
){
#   if XOC_SYSTEM_BIT(64)
    return li.QuadPart;
#   else
    return li.LowPart;
#   endif 
}

XOC_API
xoc_offset_t xoc_file_seek(
    XOC_File * file ,
    xoc_offset_t offset ,
    xoc_flag32_t move_method
){
    LARGE_INTEGER after_moving_offset;
#   if XOC_SYSTEM_BIT(64)
    LARGE_INTEGER li_offset = {.QuadPart = offset};
#   else
    LARGE_INTEGER li_offset = {.LowPart = offset , .HighPart = 0};
#   endif
    BOOL ret = SetFilePointerEx(file->handle , 
                                li_offset , 
                                &after_moving_offset , 
                                move_method);
    if(ret)
    {
        return xoc_win_large_interger_to_offset(after_moving_offset);
    }
    /*switch(GetLastError())
    {
        case ERROR_FILE_NOT_FOUND:
        case ERROR_INVALID_HANDLE:
            return XOC_BAD_FILE;
        case ERROR_LOCK_VIOLATION:
            return XOC_ACCESS_VIOLATED;
        case ERROR_INVALID_PARAMETER:
            return XOC_INVALID_ARG;
        default:
            return XOC_UNKNOWN;
    }*/
    return -1;
}
