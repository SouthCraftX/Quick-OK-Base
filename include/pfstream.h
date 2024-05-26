#include "fstream.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus    

struct _XOceanPrefetchedFile
{
    xocean_pointer_t    data;
    xocean_pointer_t    end;
    xocean_pointer_t    cur;
    xocean_size_t       size;
};
typedef struct _XOceanPrefetchedFile XOceanPrefetchedFile;

xocean_stat_t
XOCEAN_INTERFACE(xocean_prefetched_file_open)(
    XOceanPrefetchedFile *  file ,
    xocean_ccstring_t       path ,
    const xocean_offset_t   offset ,
    const xocean_size_t     size
);

xocean_size_t
XOCEAN_INTERFACE(xocean_prefetched_file_copyread)(
    XOceanPrefetchedFile *  file ,
    xocean_pointer_t        buf ,
    xocean_size_t           size
);

XOCEAN_FORCE_INLINE
xocean_offset_t
__xocean_prefetched_file_fix_offset(
    const XOceanPrefetchedFile *    file ,
    const xocean_offset_t           offset
){
    xocean_pointer_t pos = file->cur + offset;
    if (pos > file->end)
    {
        return pos - file->end;
    }
    if (pos < file->data)
    {
        return file->data - pos;
    }
    return offset;
}

XOCEAN_FORCE_INLINE
xocean_size_t
xocean_prefetched_file_read(
    XOceanPrefetchedFile *  file ,
    xocean_pointer_t *      p_buf ,
    xocean_size_t           size
);

XOCEAN_FORCE_INLINE
xocean_offset_t
xocean_prefetched_file_seek(
    XOceanPrefetchedFile *  file ,
    const xocean_offset_t   offset ,
    const xocean_stat_t     move_method
){
    switch (move_method)
    {
        case XOCEAN_FILE_MOVE_FROM_BEGIN:

        case XOCEAN_FILE_MOVE_FROM_CURRENT:


    }
}


#if defined(__cplusplus)
}
#endif // __cplusplus