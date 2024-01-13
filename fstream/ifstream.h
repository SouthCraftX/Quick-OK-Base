#pragma once
#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

#include "fstream_base.h"

struct _XOceanIFStream;
typedef struct _XOceanIFStream XOceanIFStream;

XOCEAN_FORCE_INLINE 
void xocean_ifstream_init(
    XOceanIFStream *fstream
);


#if XOCEAN_PLATFORM(WINDOWS)
#   include <fileapi.h>
#   include <handleapi.h>

struct _XOceanIFStream
{
    XOceanFileStreamBase base;
    xocean_size_t   file_size;
    xocean_stat_t   (*fn_open ) (XOceanIFStream *, xocean_ccstring_t);
    void            (*fn_close) (XOceanIFStream *);
    xocean_size_t   (*fn_read ) (XOceanIFStream *, xocean_byte_t *, xocean_size_t);
};

xocean_stat_t _xocean_win_istream_open(XOceanIFStream * stream, 
                                       xocean_ccstring_t path)
{
    wchar_t wc_path[MAX_PATH] = { };
    LARGE_INTEGER file_size;
    MultiByteToWideChar(CP_THREAD_ACP , 0 , path , -1 , wc_path , MAX_PATH);

    HANDLE file_handle = CreateFileW(
        wc_path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL
    );

    if (stream->base.handle == INVALID_HANDLE_VALUE)
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
    if(GetFileSizeEx(file_handle, &file_size))
    {
#   if XOCEAN_SYSTEM_BIT(64)
        stream->file_size = file_size.QuadPart;
#   else
        if(file_size.HighPart)
            return XOCEAN_FILE_TOO_BIG;
        stream->file_size = file_size.LowPart;
#   endif // XOCEAN_SYSTEM_BIT(64)
    }
    return XOCEAN_OK;
}

XOCEAN_FORCE_INLINE
xocean_size_t _xocean_win_stream_read32(
    XOceanIFStream * stream , xocean_byte_t * buf, xocean_int32_t ssize
){
    DWORD bytes_read = 0;
    return ReadFile((XOceanFileStreamBase *)stream->handle , buf ,
                     ssize, &bytes_read, NULL) ? bytes_read : 0;
}

#   if XOCEAN_SYSTEM_BIT(64)
xocean_size_t _xocean_win_stream_read64(
    XOceanIFStream *stream, xocean_byte_t *buffer, xocean_ssize_t ssize
){
    xocean_size_t total_read , once_bytes_read , once_bytes_to_read;
    for( ; ssize > 0 ; ssize -= once_bytes_to_read)
    {
        once_bytes_to_read = ssize > INT_MAX ? INT_MAX : ssize;
        once_bytes_read = _xocean_win_istream_read32(stream , buffer ,
                                                     once_bytes_to_read);
        if(once_bytes_read)
        {
            total_read += once_bytes_read;
            ssize -= once_bytes_read;
            buffer += once_bytes_read;
            continue;
        }
        return total_read;
    }
    return total_read;
}
#   endif // XOCEAN_SYSTEM_BIT(64)

void _xocean_win_stream_close(XOCeanFileStream * stream)
{
    CloseHandle((HANDLE)stream->handle);
    stream->handle = INVALID_HANDLE_VALUE;
}

XOCEAN_FORCE_INLINE
void _xocean_ifstream_init(XOceanIFStream * fstream)
{
    fstream->base.handle = INVALID_HANDLE_VALUE;
    fstream->file_size = 0;
    fstream->fn_close = _xocean_win_istream_close;
    fstream->fn_open = _xocean_win_istream_open;
#   if XOCEAN_SYSTEM_BIT(64)
    fstream->fn_read = _xocean_win_istream_read64;
#   else
    fstream->fn_read = _xocean_win_istream_read32;
#   endif // XOCEAN_SYSTEM_BIT(64)
}

#elif XOCEAN_PLATFORM(POSIX)
#   define XOCEAN_ONCE_READ_MAX_SIZE 0x7fff0000

xocean_stat_t _xocean_linux_istream_open(XOceanIFStream * stream , 
                                         xocean_ccstring_t path)
{
    switch(open((XOceanFileStreamBase *)stream->handle, path))
    {
        case 0:
            return XOCEAN_OK;

        
    }
}

xocean_stat_t _xocean_linux_stream_read_set_error(
    XOceanFileStreamBase * stream
){
    switch (errno)
    {
        case EBADF:
            xocean_class_set_stat(stream , XOCEAN_INVALID_HANDLE);

        case EFAULT:
            xocean_class_set_stat(stream , XOCEAN_ACCESS_VIOLATED);

        case EIO:
            xocean_class_set_stat(stream , XOCEAN_BROKEN_DEVICE);
    }
}

xocean_size_t _xocean_linux_stream_read32(XOceanIFStream * stream , 
                                         xocean_byte_t * buf , 
                                         xocean_int32_t ssize)
{
    xocean_int32_t ret = read((XOceanFileStreamBase *)stream->handle, buf, ssize);
    return (ret == -1) ? _xocean_linux_stream_read_set_error(stream) , 0 : ret;
}

xocean_size_t _xocean_linux_stream_read64(XOceanIFStream * stream , 
                                         xocean_byte_t * buf , 
                                         xocean_ssize_t ssize)
{
    xocean_size_t total_read , once_bytes_read;
    while(ssize > 0)
    {
        
    }
}

void _xocean_linux_istream_close(XOceanIFStream * stream)
{
    close((XOceanFileStreamBase *)stream->handle);
}


#endif // XOCEAN_PLATFORM(WINDOWS)

XOCEAN_FORCE_INLINE
xocean_stat_t xocean_fstream_open(XOceanFileStream * stream, xocean_ccstring_t path)
{
    return (*((stream(XOceanIFStream *))->fn_open))(stream, path);
}

XOCEAN_FORCE_INLINE
void xocean_fstream_close(XOceanFileStream * stream)
{
    (*((stream(XOceanIFStream *))->fn_close))(stream);
}

XOCEAN_FORCE_INLINE
xocean_size_t xocean_fstream_read(XOceanFileStream * stream, xocean_byte_t * buffer, xocean_size_t ssize)
{
    return (*(stream(XOceanIFStream *)->fn_read))(stream, buffer, ssize);
}

#if defined(__cplusplus)
}
#endif // __cplusplus