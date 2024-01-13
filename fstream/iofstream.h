#pragma once
#include "ifstream.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOceanIOFStream
{
    XOceanIFStream  ifstream;
    xocean_size_t   (*fn_write) (XOceanIOFStream *, xocean_byte_t *, xocean_ssize_t ssize);
};
typedef struct _XOceanIOFStream XOceanIOFStream;

XOCEAN_FORCE_INLINE
xocean_size_t xocean_iofstream_write(
    XOceanIOFStream *fstream, xocean_byte_t *buffer , xocean_ssize_t ssize
){
    return fstream->fn_write(fstream, buffer, ssize);
}

#if XOCEAN_PLATFORM(WINDOWS)

XOCEAN_FORCE_INLINE 
void xocean_iofstream_init(XOceanIOFStream *fstream)
{
    fstream->fn_write = _xocean_win_iostream_write;
    fstream->ifstream.fn_read = _xocean_win_iostream_read;
}

xocean_size_t _xocean_win_iostream_write32(
    XOceanIOFStream * stream, xocean_byte_t * buf , xocean_ssize_t ssize
){
    DWORD bytes_written;
    return WriteFile((HANDLE)((XOceanFileStreamBase *)stream)->handle , 
                     buf , ssize , &bytes_written, NULL) ? bytes_written : 0;
}




#endif // 

#if defined(__cplusplus)
}
#endif // __cplusplus