#pragma once
#define __QO_WIN32_FSTREAM_H__

// for debug
#include "include/fstream.h"
#include "stringset.h"

#if !defined(__QO_FSTREAM_H__)
#   error Never include this header file directly, use <qoean/fstream.h> instead.
#endif // __QO_FSTREAM_H__

#include <fileapi.h>

#define __QO_ACCESS_MODE_PACK(x) (x >> 24)
#define __QO_FLAGS_PACK(x) (x >> 24)

#define __QO_ACCESS_MODE_UNPACK(x) (x << 24)
#define __QO_FLAGS_UNPACK(x) (x << 24)

// `>>24` to make them sustainable for qo_flag8_t.
#define QO_FILE_READ           __QO_ACCESS_MODE_PACK(GENERIC_READ)
#define QO_FILE_WRITE          __QO_ACCESS_MODE_PACK(GENERIC_WRITE)
#define QO_FILE_READ_WRITE     (QO_FILE_READ | QO_FILE_WRITE)

#define QO_FILE_TRUNCATE_EXISTING  TRUNCATE_EXISTING
#define QO_FILE_OPEN_EXISTING      OPEN_EXISTING
#define QO_FILE_CLEAN_OPEN         CREATE_ALWAYS  

// `>>24` to make them sustainable for qo_flag16_t.
#define QO_FILE_SEQUENTIAL      __QO_FLAGS_PACK(FILE_FLAG_SEQUENTIAL_SCAN)
#define QO_FILE_RAMDOM_ACCESS   __QO_FLAGS_PACK(FILE_FLAG_RANDOM_ACCESS)
#define QO_FILE_NO_CACHING      __QO_FLAGS_PACK(FILE_FLAG_NO_BUFFERING)
#define QO_FILE_DELETE_ON_CLOSE __QO_FLAGS_PACK(FILE_FLAG_DELETE_ON_CLOSE)

// Not 32767, to reserve some space for API consumption.
#define __QO_IS_PATH_LEN_UNRESONABLE(path_size) (path_size > 32760)

struct ___QO_RW32Returns
{
    DWORD operated_bytes;
    qo_stat_t status;
};
typedef struct ___QO_RW32Returns __QO_RW32Returns;

qo_stat_t
__qo_handle_transcoding_failure()
{
#if QO_DEBUG
    QO_ERRPRINTF("qo_file_open: MultiByteToWideChar failed: ");

    switch (GetLastError())
    {
        // Following 3 errors are technical errors.
        case ERROR_BUFFER_INSUFFICIENT:
            QO_REPORT_BUG("Buffer insufficient.");
        case ERROR_INVALID_FLAGS:
            QO_REPORT_BUG("Invalid flags specified in dwFlags.");
        case ERROR_INVALID_PARAMETER:
            QO_REPORT_BUG("Invalid arg");

        // The only error that can be caused by user input.
        case ERROR_NO_UNICODE_TRANSLATION:
            // QO_REPORT_BUG("Invalid unicode found in string.");
            return QO_BAD_PATH;
    }
#else
    return QO_BAD_PATH;
#endif
}

QO_PURE
qo_stat_t
__qo_file_opening_error()
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

QO_PURE
qo_stat_t
__qo_file_reading_error()
{
    
}

__QO_RW32Returns 
__qo_file_read32(
    QO_File *   file ,
    qo_byte_t * buffer ,
    qo_uint32_t size
){
    __QO_RW32Returns ret;
    if(!ReadFile((HANDLE)file , buffer , size , &ret.operated_bytes , NULL))
    {
        
    }
    return ret;
}

#   if QO_SYSTEM_BIT(64)
QO_API
qo_size_t qo_file_read64(
    QO_File *    file ,
    qo_byte_t * buf ,
    qo_ssize_t  size
){
    qo_size_t have_read , once_read;
    qo_ssize_t remain;
    for(remain = size ; remain > 0 ; remain -= 0xffffffff)
    {
        once_read = qo_file_read(file , buf , 0xffffffff);
        if (!once_read)
            return have_read;
        have_read += once_read;
    }
    have_read += qo_file_read(file , buf + have_read , remain);
    return have_read;
}
#   endif


qo_stat_t 
QO_IMPL(qo_file_open)(
    QO_File **         p_file , 
    qo_ccstring_t      path ,
    qo_size_t          path_size ,
    QO_FileOpenMode    mode 
){
    LARGE_INTEGER file_size;
    const qo_size_t long_path_prefix_len = sizeof(L"\\\\?\\") - sizeof(WCHAR);

    if (!path_size) 
        path_size = qo_string_length(path) + sizeof(WCHAR);
    else
        path_size *= sizeof(WCHAR);

    // Check path length here, so reduce the probibility of stack overflow.
    if (__QO_IS_PATH_LEN_UNRESONABLE(path_size))
        return QO_TOO_LONG;
    
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
        return __qo_handle_transcoding_failure();
    }
    HANDLE file_handle = CreateFileW(
        wc_path , __QO_ACCESS_MODE_UNPACK(mode.access_mode) , 0 , NULL , 
        __QO_ACCESS_MODE_UNPACK(mode.open_mode) , 
        __QO_FLAGS_UNPACK(mode.hints) , NULL
    );

    if (file_handle == INVALID_HANDLE_VALUE)
    {
        return __qo_file_opening_error();
    }
    *p_file = (QO_File *)file_handle;
    return QO_OK;
}

QO_FORCE_INLINE
void qo_file_close(
    QO_File * file
){
    if (file)
        CloseHandle((HANDLE)handle);
}

QO_API 
qo_stat_t qo_file_get_size(
    QO_File * file ,
    qo_size_t * size
){
#   if QO_SYSTEM_BIT(64)
    BOOL ret = GetFileSizeEx(file->handle , (PLARGE_INTEGER)size);
#   else
    BOOL ret = GetFileSizeEx(file->handle , &(LARGE_INTEGER){.LowPart = *size , .HighPart = 0});
#   endif
    if (ret)
    {
        return QO_OK;
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

QO_FORCE_INLINE
qo_offset_t qo_win_large_interger_to_offset(
    LARGE_INTEGER li
){
#   if QO_SYSTEM_BIT(64)
    return li.QuadPart;
#   else
    return li.LowPart;
#   endif 
}

QO_API
qo_offset_t qo_file_seek(
    QO_File * file ,
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
    /*switch(GetLastError())
    {
        case ERROR_FILE_NOT_FOUND:
        case ERROR_INVALID_HANDLE:
            return QO_BAD_FILE;
        case ERROR_LOCK_VIOLATION:
            return QO_ACCESS_VIOLATED;
        case ERROR_INVALID_PARAMETER:
            return QO_INVALID_ARG;
        default:
            return QO_UNKNOWN;
    }*/
    return -1;
}
