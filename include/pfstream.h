#include "fstream.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus    

struct _XOCPrefetchedFile
{
    xoc_pointer_t    data;
    xoc_pointer_t    end;
    xoc_pointer_t    cur;
    xoc_size_t       size;
};
typedef struct _XOCPrefetchedFile XOCPrefetchedFile;

xoc_stat_t
XOC_INTERFACE(xoc_prefetched_file_open)(
    XOCPrefetchedFile *  file ,
    xoc_ccstring_t       path ,
    const xoc_offset_t   offset ,
    const xoc_size_t     size
);

xoc_size_t
XOC_INTERFACE(xoc_prefetched_file_copyread)(
    XOCPrefetchedFile *  file ,
    xoc_pointer_t        buf ,
    xoc_size_t           size
);

XOC_FORCE_INLINE
xoc_offset_t
__xoc_prefetched_file_fix_offset(
    const XOCPrefetchedFile *    file ,
    const xoc_offset_t           offset
){
    xoc_pointer_t pos = file->cur + offset;
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

XOC_FORCE_INLINE
xoc_size_t
xoc_prefetched_file_read(
    XOCPrefetchedFile *  file ,
    xoc_pointer_t *      p_buf ,
    xoc_size_t           size
);

XOC_FORCE_INLINE
xoc_offset_t
xoc_prefetched_file_seek(
    XOCPrefetchedFile *  file ,
    const xoc_offset_t   offset ,
    const xoc_stat_t     move_method
){
    switch (move_method)
    {
        case XOC_FILE_MOVE_FROM_BEGIN:

        case XOC_FILE_MOVE_FROM_CURRENT:


    }
}


#if defined(__cplusplus)
}
#endif // __cplusplus