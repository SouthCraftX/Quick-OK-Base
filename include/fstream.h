/*******************************************************************************
 *  @file       include/fstream.h
 *  @addtogroup Headers under the MIT License
 *  @author     XOcean <https://github.com/SouthCraftX>
 * 
 *  @addtogroup Simple System-API Redirecting Layer
 *  @addtogroup File Stream 
 */

#pragma once
#define __XOC_FSTREAM_H__

#   include "../base.h"

// implementation-defined
// #define XOC_FILE_READ                     (0)
// #define XOC_FILE_WRITE                    (1)
// #define XOC_FILE_READ_WRITE               (2)
// 
// #define XOC_FILE_MOVE_FROM_BEGIN          (0)
// #define XOC_FILE_MOVE_FROM_CURRENT        (1)
// #define XOC_FILE_MOVE_FROM_END            (2)
// 
// #define XOC_FILE_APPEND                   (1 << 2)
// #define XOC_FILE_CREATE_NEW               (1 << 8)
// #define XOC_FILE_CREATE_ALWAYS            (2 << 8)
// #define XOC_FILE_OPEN_EXISTING            (3 << 8)
// #define XOC_FILE_OPEN_ALWAYS              (4 << 8)
// #define XOC_FILE_OPEN_TRANCATELY          (5 << 8)
// 
// #define XOC_FILE_SHARED_READ              (1 << 16)
// #define XOC_FILE_SHARED_WRITE             (2 << 16)
// #define XOC_FILE_SHARED_DELETE            (1 << 16)
// #define XOC_FILE_NO_CACHING               (1 << 11)
// #define XOC_FILE_SEQUENTIAL               (1 << 12)
// #define XOC_FILE_DELETE_ON_CLOSE          (1 << 13)
// #define XOC_FILE_RANDOM_ACCESS            (1 << 14)


#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOC_File;
typedef struct _XOC_File XOC_File;

/// @brief  Open a file
/// @param  p_file A pointer to a file object.
/// @param  path   The path of the file.
/// @return The status of the operation.
/// @sa     xoc_file_close()
xoc_stat_t 
XOC_INTERFACE(xoc_file_open)(
    XOC_File **     p_file , 
    xoc_ccstring_t  path , 
    xoc_flag32_t    access_mode ,
    xoc_flag32_t    open_mode ,
    xoc_flag32_t    hint
) XOC_NONNULL(1 , 2);

xoc_size_t 
XOC_INTERFACE(xoc_file_read_explicit)(
    XOC_File *       file ,
    xoc_byte_t *     buf ,
    xoc_size_t       desired_size ,
    xoc_size_t *     have_read_size
) XOC_NONNULL(1 , 2);

XOC_FORCE_INLINE
xoc_stat_t
XOC_INTERFACE(xoc_file_write_implicit)(
    XOC_File *       file ,
    xoc_byte_t *     buf ,
    xoc_size_t       desired_size
) {
    return XOC_INTERFACE(xoc_file_write_explicit)(
        file , buf , desired_size , NULL
    );
}

xoc_size_t
XOC_INTERFACE(xoc_file_write_explicit)(
    XOC_File *       file ,
    xoc_byte_t *     buf ,
    xoc_size_t       desired_size ,
    xoc_stat_t *     error
) XOC_NONNULL(1 , 2);

XOC_FORCE_INLINE
xoc_stat_t
XOC_INTERFACE(xoc_file_read_implicit)(
    XOC_File *       file ,
    xoc_byte_t *     buf ,
    xoc_size_t       desired_size
){
    return XOC_INTERFACE(xoc_file_read_explicit)(file , buf , desired_size , NULL);
}

void 
XOC_INTERFACE(xoc_file_close)(
    XOC_File *    file
) XOC_NONNULL(1);

xoc_stat_t 
XOC_INTERFACE(xoc_file_alloc)(
    XOC_File *   file ,
    xoc_size_t   size
) XOC_NONNULL(1);

xoc_offset_t 
XOC_INTERFACE(xoc_file_seek)(
    XOC_File *   file ,
    xoc_offset_t offset ,
    xoc_flag32_t move_method 
) XOC_NONNULL(1);

XOC_FORCE_INLINE
xoc_offset_t XOC_INTERFACE(xoc_file_get_pos)(
    XOC_File *    file
){
    return XOC_INTERFACE(xoc_file_seek)(file , 0 , XOC_FILE_MOVE_FROM_CURRENT);
}

/// @brief  Get the size of a file.
/// @param  file The file object.
/// @param  p_size A pointer to size.
/// @return The status of the operation.
/// @retval XOC_OK The operation is successful.
/// @retval XOC_
/// @note   Only file or device that supports file-like operations can use this
///         function. 
xoc_stat_t 
XOC_INTERFACE(xoc_file_get_size)(
    XOC_File *      file ,
    xoc_size_t *    p_size
) XOC_NONNULL(1 , 2);

// Make operated size optional.
#define __XOC_FILE_RW_SELECT(file , buf , desired_size , have_operated_size , \
                                __target , ...) __target

#define xoc_file_read(...)                                               \
        __XOC_FILE_RW_SELECT                                             \
        (                                                                   \
            __VA_ARGS__ ,                                                   \
            XOC_INTERFACE(xoc_file_read_explicit) ,                   \
            XOC_INTERFACE(xoc_file_read_implicit)                     \
        ) (__VA_ARGS__)

#define xoc_file_write(...)                                              \
        __XOC_FILE_RW_SELECT                                             \
        (                                                                   \ 
            __VA_ARGS__ ,                                                   \
            XOC_INTERFACE(xoc_file_read_explicit) ,                   \
            XOC_INTERFACE(xoc_file_write_implicit)                    \
        ) (__VA_ARGS__)

#define  xoc_file_open        XOC_INTERFACE(xoc_file_open)
#define  xoc_file_close       XOC_INTERFACE(xoc_file_close)
#define  xoc_file_alloc       XOC_INTERFACE(xoc_file_alloc)
#define  xoc_file_seek        XOC_INTERFACE(xoc_file_seek)
#define  xoc_file_get_pos     XOC_INTERFACE(xoc_file_get_pos)
#define  xoc_file_get_size    XOC_INTERFACE(xoc_file_get_size)

#if defined(__cplusplus)
}
#endif // __cplusplus

#if XOC_PLATFORM(WINDOWS)
#   include "internal/platform_spec/win32/fstream.h"
#elif XOC_PLATFORM(POSIX)
#   include "internal/platform_spec/posix/fstream.h"
#else
#   error "XOCLib: File stream interfaces not implemented"
#endif // 