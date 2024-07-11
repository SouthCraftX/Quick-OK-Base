#include "fstream.h"

#include <fileapi.h>

#define XOC_FILE_READ           GENERIC_READ
#define XOC_FILE_WRITE          GENERIC_WRITE
#define XOC_FILE_READ_WRITE     (GENERIC_READ | GENERIC_WRITE)

#define XOC_FILE_TRUNCATE_EXISTING  TRUNCATE_EXISTING
#define XOC_FILE_OPEN_EXISTING      OPEN_EXISTING
#define XOC_FILE_CLEAN_OPEN         CREATE_ALWAYS  

// Hints
#define XOC_FILE_SEQUENTIAL      FILE_FLAG_SEQUENTIAL_SCAN
#define XOC_FILE_RAMDOM_ACCESS   FILE_FLAG_RANDOM_ACCESS

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
    XOC_File *          file , 
    xoc_ccstring_t      path ,
    xoc_flag32_t        access_mode ,
    xoc_flag32_t        open_mode ,
    xoc_flag32_t        hints
){
    wchar_t wc_path[MAX_PATH] = { };
    LARGE_INTEGER file_size;
    MultiByteToWideChar(CP_THREAD_ACP , 0 , path , -1 , wc_path , MAX_PATH);

    HANDLE file_handle = CreateFileW(
        wc_path , access_mode , 0 , NULL , open_mode , hints , NULL
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
    (HANDLE)file = file_handle;
    return XOC_OK;
}

XOC_FORCE_INLINE
void xoc_file_close(
    XOC_File * file
){
    CloseHandle((HANDLE)handle);
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
