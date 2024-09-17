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

/// @brief  Struct indicates how to open a file.
/// @sa     xoc_file_open()
struct _XOC_FileOpenMode
{
    /// @brief  The access mode of the file.
    /// @sa     XOC_FILE_READ, XOC_FILE_WRITE, XOC_FILE_READ_WRITE
    xoc_flag8_t access_mode;

    /// @brief  The open mode of the file.
    /// @sa
    xoc_flag8_t open_mode;

    /// @brief  The hints of the file. It may not be used if current platform 
    ///         does not support it. Set the first bit to 1 to force applying
    ///         the hints(x & 0x8000), in that case, xoc_file_read() will fail 
    ///         if not supported.
    /// @sa     XOC_FILE_NO_CACHING, XOC_FILE_SEQUENTIAL
    xoc_flag16_t hints;
};
typedef struct _XOC_FileOpenMode XOC_FileOpenMode;

/// @brief  Open a file
/// @param  p_file A pointer to a file object.
/// @param  path   The path of the file. UTF-8 encoding is required.
/// @param  path_size The size of the path. 0 is allowed, in that case the size 
///         of the path will be calculated automatically.
/// @return The status of the operation.
/// @sa     xoc_file_close()
xoc_stat_t 
XOC_INTERFACE(xoc_file_open)(
    XOC_File **         p_file , 
    xoc_ccstring_t      path , 
    xoc_size_t          path_size ,
    XOC_FileOpenMode    mode
) XOC_NONNULL(1 , 2);

/// @brief  Read data from a file
/// @param  file The file object.
/// @param  buffer A buffer that can hold the data at least `desired_size` bytes.
/// @param  desired_size The size of the data to be read.
/// @param  p_error A pointer to a status code. If the operation succeeds, the 
///         status code will be set to `XOC_OK`. Other error codes may be set.
///         NULL is allowed, in that case the status code will not be set.
/// @return The size of the data that has been read. 0 will be returned 
///         if the operation fails.
xoc_size_t 
XOC_INTERFACE(xoc_file_read_explicit)(
    XOC_File *       file ,
    xoc_byte_t *     buffer ,
    xoc_size_t       desired_size ,
    xoc_stat_t *     p_error
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

/// @brief  Close a file
/// @param  file The file object. NULL is allowed, in that case the function
///         will do nothing.
void 
XOC_INTERFACE(xoc_file_close)(
    XOC_File *    file
);

/// @brief  Allocate a file
/// @param  file The file object.
/// @param  size The size of the file.
/// @return The status of the operation.
xoc_stat_t 
XOC_INTERFACE(xoc_file_alloc)(
    XOC_File *   file ,
    xoc_size_t   size
) XOC_NONNULL(1);

/// @brief  Move the file pointer.
/// @param  file The file object.
/// @param  offset The offset to move.
/// @param  move_method The method to move the file pointer.
/// @param  p_error A pointer to a status code. If the operation succeeds, the 
///         status code will be set to `XOC_OK`. Other error codes may be set.
///         NULL is allowed, in that case the status code will not be set.
/// @return The offset of the file pointer after the operation.
xoc_offset_t 
XOC_INTERFACE(xoc_file_seek)(
    XOC_File *      file ,
    xoc_offset_t    offset ,
    xoc_flag32_t    move_method ,
    xoc_stat_t *    p_error
) XOC_NONNULL(1);

/// @brief  Get the current position of the file pointer.
/// @param  file The file object.
/// @return 
XOC_FORCE_INLINE
xoc_offset_t 
XOC_INTERFACE(xoc_file_get_position)(
    XOC_File *    file ,
    xoc_stat_t *  p_error
) {
    return XOC_INTERFACE(xoc_file_seek)(file , 0 , XOC_FILE_MOVE_FROM_CURRENT);
} XOC_NONNULL(1);

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

/// @brief  Get the maximum length of a path.
/// @return The maximum length of a path that XOceanLib can handle.
/// @note   The size is implementation-defined. Usually it is greater than 255.
///         In Windows 1607 or later with long path support enabled, the size
///         is 32767. In early Windows, the size is MAX_PATH, which is defined
///         as 260. In GNU/Linux, the size is 4096.
///         Of note, you may fail to open a file before reaching the maximum
///         length of a path, as many file systems limit a file name to 255
///         characters, which may be smaller than the maximum length.
/// @sa     xoc_file_open()
XOC_PURE
xoc_size_t
XOC_INTERFACE(xoc_get_path_max_length)();

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

// Make p_error optional for xoc_file_read and xoc_file_write
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