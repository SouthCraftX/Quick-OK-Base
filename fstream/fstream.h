#ifndef XOCEAN_FSTREAM_H
#   define XOCEAN_FSTREAM_H

#   include "../base.h"

#   define XOCEAN_FILE_READ                     (0)
#   define XOCEAN_FILE_WRITE                    (1)
#   define XOCEAN_FILE_READ_WRITE               (2)

#   define XOCEAN_FILE_MOVE_FROM_BEGIN          (0)
#   define XOCEAN_FILE_MOVE_FROM_CURRENT        (1)
#   define XOCEAN_FILE_MOVE_FROM_END            (2)

#   define XOCEAN_FILE_APPEND                   (1 << 2)
#   define XOCEAN_FILE_CREATE_NEW               (1 << 8)
#   define XOCEAN_FILE_CREATE_ALWAYS            (2 << 8)
#   define XOCEAN_FILE_OPEN_EXISTING            (3 << 8)
#   define XOCEAN_FILE_OPEN_ALWAYS              (4 << 8)
#   define XOCEAN_FILE_OPEN_TRANCATELY          (5 << 8)

#   define XOCEAN_FILE_SHARED_READ              (1 << 16)
#   define XOCEAN_FILE_SHARED_WRITE             (2 << 16)
#   define XOCEAN_FILE_SHARED_DELETE            (1 << 16)
#   define XOCEAN_FILE_NO_CACHING               (1 << 11)
#   define XOCEAN_FILE_SEQUENTIAL               (1 << 12)
#   define XOCEAN_FILE_DELETE_ON_CLOSE          (1 << 13)
#   define XOCEAN_FILE_RANDOM_ACCESS            (1 << 14)


#   if defined(__cplusplus)
extern "C" {
#   endif // __cplusplus

struct _XOceanFile
{
    XOceanClassBase  base;
    xocean_pointer_t handle;
};
typedef struct _XOceanFile XOceanFile;

xocean_stat_t 
XOCEAN_INTERFACE(xocean_file_open)(
    XOceanFile *        file , 
    xocean_ccstring_t   path , 
    xocean_flag32_t     mode
);

xocean_size_t 
XOCEAN_INTERFACE(xocean_file_read)(
    XOceanFile *        file ,
    xocean_byte_t *     buf ,
    xocean_size_t       size
);


xocean_size_t
XOCEAN_INTERFACE(xocean_file_write)(
    XOceanFile *        file ,
    xocean_byte_t *     buf ,
    xocean_size_t       size
);

void 
XOCEAN_INTERFACE(xocean_file_close)(
    XOceanFile * file
);

XOCEAN_API
xocean_stat_t XOCEAN_INTERFACE(xocean_file_alloc)(
    XOceanFile *    file ,
    xocean_size_t   size
);

XOCEAN_API
xocean_offset_t XOCEAN_INTERFACE(xocean_file_seek)(
    XOceanFile *    file ,
    xocean_offset_t offset ,
    xocean_flag32_t move_method 
);

XOCEAN_FORCE_INLINE
xocean_offset_t XOCEAN_INTERFACE(xocean_file_get_pos)(
    XOceanFile *    file
){
    return XOCEAN_INTERFACE(xocean_file_seek)(file , 0 , XOCEAN_FILE_MOVE_FROM_CURRENT);
}

XOCEAN_API
xocean_stat_t XOCEAN_INTERFACE(xocean_file_get_size)(
    XOceanFile *    file ,
    xocean_size_t * size
);

#   define  xocean_file_open        XOCEAN_INTERFACE(xocean_file_open)
#   define  xocean_file_read        XOCEAN_INTERFACE(xocean_file_read)
#   define  xocean_file_write       XOCEAN_INTERFACE(xocean_file_write)
#   define  xocean_file_close       XOCEAN_INTERFACE(xocean_file_close)
#   define  xocean_file_alloc       XOCEAN_INTERFACE(xocean_file_alloc)
#   define  xocean_file_seek        XOCEAN_INTERFACE(xocean_file_seek)
#   define  xocean_file_get_pos     XOCEAN_INTERFACE(xocean_file_get_pos)
#   define  xocean_file_get_size    XOCEAN_INTERFACE(xocean_file_get_size)

#   if defined(__cplusplus)
}
#   endif // __cplusplus



#endif // XOCEAN_FSTREAM_H

