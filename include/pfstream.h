#include "fstream.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus    

struct _QOPrefetchedFile
{
    qo_pointer_t    data;
    qo_pointer_t    end;
    qo_pointer_t    cur;
    qo_size_t       size;
};
typedef struct _QOPrefetchedFile QOPrefetchedFile;

qo_stat_t
QO_INTERFACE(qo_prefetched_file_open)(
    QOPrefetchedFile *  file ,
    qo_ccstring_t       path ,
    const qo_offset_t   offset ,
    const qo_size_t     size
);

qo_size_t
QO_INTERFACE(qo_prefetched_file_copyread)(
    QOPrefetchedFile *  file ,
    qo_pointer_t        buf ,
    qo_size_t           size
);

QO_FORCE_INLINE
qo_offset_t
__qo_prefetched_file_fix_offset(
    const QOPrefetchedFile *    file ,
    const qo_offset_t           offset
){
    qo_pointer_t pos = file->cur + offset;
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

QO_FORCE_INLINE
qo_size_t
qo_prefetched_file_read(
    QOPrefetchedFile *  file ,
    qo_pointer_t *      p_buf ,
    qo_size_t           size
);

QO_FORCE_INLINE
qo_offset_t
qo_prefetched_file_seek(
    QOPrefetchedFile *  file ,
    const qo_offset_t   offset ,
    const qo_stat_t     move_method
){
    switch (move_method)
    {
        case QO_FILE_MOVE_FROM_BEGIN:

        case QO_FILE_MOVE_FROM_CURRENT:


    }
}


#if defined(__cplusplus)
}
#endif // __cplusplus