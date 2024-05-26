#include "fstream.h"

#include <fileapi.h>

static DWORD xocean_access_mode_list[] = {FILE_GENERIC_READ , FILE_GENERIC_WRITE , 
                                   FILE_GENERIC_READ | FILE_GENERIC_WRITE , 0};

XOCEAN_NOEXPORT XOCEAN_FORCE_INLINE
DWORD _xocean_file_win_translate_flag_and_attributes(
    xocean_flag32_t mode
){
    return (XOCEAN_HAS_FLAG(mode , XOCEAN_FILE_NO_CACHING) ? FILE_FLAG_NO_BUFFERING : 0) &
           (XOCEAN_HAS_FLAG(mode , XOCEAN_FILE_SEQUENTIAL) ? FILE_SEQUENTIAL_SCAN : 0) &
}

XOCEAN_NOEXPORT XOCEAN_FORCE_INLINE
DWORD _xocean_file_win_translate_open_mode(
    xocean_flag32_t mode
){
    return (mode >> 8) & 0xff;
}

XOCEAN_NOEXPORT XOCEAN_FORCE_INLINE
DWORD _xocean_file_win_translate_desired_access(
    xocean_flag32_t mode
){
    return xocean_access_mode_list[mode & 0x3];
}

XOCEAN_NOEXPORT XOCEAN_FORCE_INLINE
DWORD _xocean_file_win_translate_shared_mode(
    xocean_flag32_t mode
){
    return (XOCEAN_HAS_FLAG(mode , XOCEAN_FILE_SHARED_READ) ? FILE_SHARE_READ : 0) &
           (XOCEAN_HAS_FLAG(mode , XOCEAN_FILE_SHARED_WRITE) ? FILE_SHARE_WRITE : 0) &
           (XOCEAN_HAS_FLAG(mode , XOCEAN_FILE_SHARED_DELETE) ? FILE_SHARE_DELETE : 0);
}

xocean_uint32_t 
__xocean_file_read32(
    XOceanFile      file ,
    xocean_byte_t * buf ,
    xocean_uint32_t size
){
    DWORD have_read;
    return ReadFile(file->handle , buf , size , &have_read , NULL) ? have_read : 0;
}

#   if XOCEAN_SYSTEM_BIT(64)
XOCEAN_API
xocean_size_t xocean_file_read64(
    XOceanFile *    file ,
    xocean_byte_t * buf ,
    xocean_ssize_t  size
){
    xocean_size_t have_read , once_read;
    xocean_ssize_t remain;
    for(remain = size ; remain > 0 ; remain -= 0xffffffff)
    {
        once_read = xocean_file_read(file , buf , 0xffffffff);
        if(!once_read)
            return have_read;
        have_read += once_read;
    }
    have_read += xocean_file_read(file , buf + have_read , remain);
    return have_read;
}
#   endif

XOCEAN_API
xocean_stat_t xocean_file_open(
    XOceanFile *        file , 
    xocean_ccstring_t   path ,
    xocean_flag32_t     mode
){
    wchar_t wc_path[MAX_PATH] = { };
    LARGE_INTEGER file_size;
    MultiByteToWideChar(CP_THREAD_ACP , 0 , path , -1 , wc_path , MAX_PATH);

    HANDLE file_handle = CreateFileW(
        wc_path ,
        _xocean_file_win_translate_desired_access(mode) ,
        _xocean_file_win_translate_shared_mode(mode) , 
        NULL , 
        _xocean_file_win_translate_open_mode(mode), 
        FILE_ATTRIBUTE_NORMAL | _xocean_file_win_translate_flag_and_attributes(mode) ,
        NULL
    );

    if (file->handle == INVALID_HANDLE_VALUE)
    {
        switch(GetLastError())
        {
            case ERROR_FILE_NOT_FOUND:
            case ERROR_PATH_NOT_FOUND:
                return XOCEAN_BAD_PATH;
            case ERROR_ACCESS_DENIED:
                return XOCEAN_PERMISSION_DENIED;
            default:
                return XOCEAN_FILE_OPEN_FAILED;
        }
    }
    file->handle = file_handle;
    return XOCEAN_OK;
}

XOCEAN_API
void xocean_file_close(
    XOceanFile * file
){
    CloseHandle(file->handle);
    file->handle = INVALID_HANDLE_VALUE;
}

XOCEAN_API 
xocean_stat_t xocean_file_get_size(
    XOceanFile * file ,
    xocean_size_t * size
){
#   if XOCEAN_SYSTEM_BIT(64)
    BOOL ret = GetFileSizeEx(file->handle , (PLARGE_INTEGER)size);
#   else
    BOOL ret = GetFileSizeEx(file->handle , &(LARGE_INTEGER){.LowPart = *size , .HighPart = 0});
#   endif
    if (ret)
    {
        return XOCEAN_OK;
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

XOCEAN_FORCE_INLINE
xocean_offset_t xocean_win_large_interger_to_offset(
    LARGE_INTEGER li
){
#   if XOCEAN_SYSTEM_BIT(64)
    return li.QuadPart;
#   else
    return li.LowPart;
#   endif 
}

XOCEAN_API
xocean_offset_t xocean_file_seek(
    XOceanFile * file ,
    xocean_offset_t offset ,
    xocean_flag32_t move_method
){
    LARGE_INTEGER after_moving_offset;
#   if XOCEAN_SYSTEM_BIT(64)
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
        return xocean_win_large_interger_to_offset(after_moving_offset);
    }
    /*switch(GetLastError())
    {
        case ERROR_FILE_NOT_FOUND:
        case ERROR_INVALID_HANDLE:
            return XOCEAN_BAD_FILE;
        case ERROR_LOCK_VIOLATION:
            return XOCEAN_ACCESS_VIOLATED;
        case ERROR_INVALID_PARAMETER:
            return XOCEAN_INVALID_ARG;
        default:
            return XOCEAN_UNKNOWN;
    }*/
    return -1;
}
