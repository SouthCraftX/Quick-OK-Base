#ifndef XOCEAN_FSTREAM_H
#   define XOCEAN_FSTREAM_H

#   include "../base.h"

#   define XOCEAN_FILE_READ                     (1 << 0)
#   define XOCEAN_FILE_WRITE                    (1 << 1)
#   define XOCEAN_FILE_APPEND                   (1 << 2)
#   define XOCEAN_FILE_CREATE_ALWAYS            (1 << 3)
#   define XOCEAN_FILE_CREATE_WHEN_NONEXISTENT  (1 << 4)
#   define XOCEAN_FILE_OPEN_ALWAYS              (1 << 5)
#   define XOCEAN_FILE_OPEN_EXISTING            (1 << 6)
#   define XOCEAN_FILE_OPEN_TRANCATELY          (1 << 7)
#   define XOCEAN_FILE_SHARED_READ              (1 << 8)
#   define XOCEAN_FILE_SHARED_WRITE             (1 << 9)
#   define XOCEAN_FILE_SHARED_DELETE            (1 << 10)
#   define XOCEAN_FILE_NO_CACHING               (1 << 11)
#   define XOCEAN_FILE_SEQUENTIAL               (1 << 12)
#   define XOCEAN_FILE_DELETE_ON_CLOSE          (1 << 13)
#   define XOCEAN_FILE_RANDOM_ACCESS            (1 << 14)

#   define XOCEAN_FILE_MOVE_FROM_BEGIN          (0)
#   define XOCEAN_FILE_MOVE_FROM_CURRENT        (1)
#   define XOCEAN_FILE_MOVE_FROM_END            (2)

#   if defined(__cplusplus)
extern "C" {
#   endif // __cplusplus

struct _XOceanFile
{
    XOceanClassBase  base;
    xocean_pointer_t handle;
};
typedef struct _XOceanFile XOceanFile;

XOCEAN_API
xocean_stat_t xocean_file_open(
    XOceanFile *        file , 
    xocean_ccstring_t   path , 
    xocean_flag32_t     mode
);

XOCEAN_API
xocean_size_t xocean_file_read(
    XOceanFile *        file ,
    xocean_byte_t *     buf ,
    xocean_size_t       size
);

XOCEAN_API
xocean_size_t xocean_file_write(
    XOceanFile *        file ,
    xocean_byte_t *     buf ,
    xocean_size_t       size
);

XOCEAN_API
void xocean_file_close(
    XOceanFile * file
);

XOCEAN_API
xocean_stat_t xocean_file_alloc(
    XOceanFile *    file ,
    xocean_size_t   size
);

XOCEAN_API
xocean_stat_t xocean_file_seek(
    XOceanFile *    file ,
    xocean_ssize_t  offset ,
    xocean_flag32_t move_method 
);

XOCEAN_API
xocean_stat_t xocean_file_get_size(
    XOceanFile * file ,
    xocean_size_t * size
);

#   if defined(__cplusplus)
}
#   endif // __cplusplus



#endif // XOCEAN_FSTREAM_H

