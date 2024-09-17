#pragma once
#define __XOC_WIN32_FSTREAM_H__

// for debug
#include "include/fstream.h"
#include "stringset.h"

#if !defined(__XOC_FSTREAM_H__)
#   error Never include this header file directly, use <xocean/fstream.h> instead.
#endif // __XOC_FSTREAM_H__

#include <fileapi.h>

#define __XOC_ACCESS_MODE_PACK(x) (x >> 24)
#define __XOC_FLAGS_PACK(x) (x >> 24)

#define __XOC_ACCESS_MODE_UNPACK(x) (x << 24)
#define __XOC_FLAGS_UNPACK(x) (x << 24)

// `>>24` to make them sustainable for xoc_flag8_t.
#define XOC_FILE_READ           __XOC_ACCESS_MODE_PACK(GENERIC_READ)
#define XOC_FILE_WRITE          __XOC_ACCESS_MODE_PACK(GENERIC_WRITE)
#define XOC_FILE_READ_WRITE     (XOC_FILE_READ | XOC_FILE_WRITE)

#define XOC_FILE_TRUNCATE_EXISTING  TRUNCATE_EXISTING
#define XOC_FILE_OPEN_EXISTING      OPEN_EXISTING
#define XOC_FILE_CLEAN_OPEN         CREATE_ALWAYS  

// `>>24` to make them sustainable for xoc_flag16_t.
#define XOC_FILE_SEQUENTIAL      __XOC_FLAGS_PACK(FILE_FLAG_SEQUENTIAL_SCAN)
#define XOC_FILE_RAMDOM_ACCESS   __XOC_FLAGS_PACK(FILE_FLAG_RANDOM_ACCESS)
#define XOC_FILE_NO_CACHING      __XOC_FLAGS_PACK(FILE_FLAG_NO_BUFFERING)
#define XOC_FILE_DELETE_ON_CLOSE __XOC_FLAGS_PACK(FILE_FLAG_DELETE_ON_CLOSE)

// Not 32767, to reserve some space for API consumption.
#define __XOC_IS_PATH_LEN_UNRESONABLE(path_size) (path_size > 32760)

struct ___XOC_RW32Returns
{
    DWORD operated_bytes;
    xoc_stat_t status;
};
typedef struct ___XOC_RW32Returns __XOC_RW32Returns;

xoc_stat_t
__xoc_handle_transcoding_failure()
{
#if XOC_DEBUG
    XOC_ERRPRINTF("xoc_file_open: MultiByteToWideChar failed: ");

    switch (GetLastError())
    {
        // Following 3 errors are technical errors.
        case ERROR_BUFFER_INSUFFICIENT:
            XOC_REPORT_BUG("Buffer insufficient.");
        case ERROR_INVALID_FLAGS:
            XOC_REPORT_BUG("Invalid flags specified in dwFlags.");
        case ERROR_INVALID_PARAMETER:
            XOC_REPORT_BUG("Invalid arg");

        // The only error that can be caused by user input.
        case ERROR_NO_UNICODE_TRANSLATION:
            // XOC_REPORT_BUG("Invalid unicode found in string.");
            return XOC_BAD_PATH;
    }
#else
    return XOC_BAD_PATH;
#endif
}

XOC_PURE
xoc_stat_t
__xoc_file_opening_error()
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

XOC_PURE
xoc_stat_t
__xoc_file_reading_error()
{
    
}

__XOC_RW32Returns 
__xoc_file_read32(
    XOC_File *   file ,
    xoc_byte_t * buffer ,
    xoc_uint32_t size
){
    __XOC_RW32Returns ret;
    if(!ReadFile((HANDLE)file , buffer , size , &ret.operated_bytes , NULL))
    {
        
    }
    return ret;
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
        if (!once_read)
            return have_read;
        have_read += once_read;
    }
    have_read += xoc_file_read(file , buf + have_read , remain);
    return have_read;
}
#   endif


xoc_stat_t 
XOC_IMPL(xoc_file_open)(
    XOC_File **         p_file , 
    xoc_ccstring_t      path ,
    xoc_size_t          path_size ,
    XOC_FileOpenMode    mode 
){
    LARGE_INTEGER file_size;
    const xoc_size_t long_path_prefix_len = sizeof(L"\\\\?\\") - sizeof(WCHAR);

    if (!path_size) 
        path_size = xoc_string_length(path) + sizeof(WCHAR);
    else
        path_size *= sizeof(WCHAR);

    // Check path length here, so reduce the probibility of stack overflow.
    if (__XOC_IS_PATH_LEN_UNRESONABLE(path_size))
        return XOC_TOO_LONG;
    
    WCHAR wc_path[path_size / 2];

    // Make it a UNC path to support long path.
    if (path_size > MAX_PATH * 2)
    {
        memcpy(wc_path , L"\\\\?\\UNC\\" , long_path_prefix_len);
    }
    

    const BOOL transcode_status =
    MultiByteToWideChar(
        CP_UTF8 , 0 , path , -1 , 
        wc_path + long_path_prefix_len / 2 , path_size
    );

    if (transcode_status)
    {
        return __xoc_handle_transcoding_failure();
    }
    HANDLE file_handle = CreateFileW(
        wc_path , __XOC_ACCESS_MODE_UNPACK(mode.access_mode) , 0 , NULL , 
        __XOC_ACCESS_MODE_UNPACK(mode.open_mode) , 
        __XOC_FLAGS_UNPACK(mode.hints) , NULL
    );

    if (file_handle == INVALID_HANDLE_VALUE)
    {
        return __xoc_file_opening_error();
    }
    *p_file = (XOC_File *)file_handle;
    return XOC_OK;
}

XOC_FORCE_INLINE
void xoc_file_close(
    XOC_File * file
){
    if (file)
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
    BOOL ret = SetFilePointerEx((HANDLE)file , 
                                li_offset , 
                                &after_moving_offset , 
                                move_method);
    if (ret)
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
