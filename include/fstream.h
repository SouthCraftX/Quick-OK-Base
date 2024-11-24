/*******************************************************************************
 *  @file       include/fstream.h
 *  @addtogroup Headers under the MIT License
 *  @author     XOcean <https://github.com/SouthCraftX>
 * 
 *  @addtogroup Simple System-API Redirecting Layer
 *  @addtogroup File Stream 
 */

#pragma once
#define __QO_FSTREAM_H__

#   include "../base.h"

// implementation-defined
// #define QO_FILE_READ                     (0)
// #define QO_FILE_WRITE                    (1)
// #define QO_FILE_READ_WRITE               (2)
// 
// #define QO_FILE_MOVE_FROM_BEGIN          (0)
// #define QO_FILE_MOVE_FROM_CURRENT        (1)
// #define QO_FILE_MOVE_FROM_END            (2)
// 
// #define QO_FILE_APPEND                   (1 << 2)
// #define QO_FILE_CREATE_NEW               (1 << 8)
// #define QO_FILE_CREATE_ALWAYS            (2 << 8)
// #define QO_FILE_OPEN_EXISTING            (3 << 8)
// #define QO_FILE_OPEN_ALWAYS              (4 << 8)
// #define QO_FILE_OPEN_TRANCATELY          (5 << 8)
// 
// #define QO_FILE_SHARED_READ              (1 << 16)
// #define QO_FILE_SHARED_WRITE             (2 << 16)
// #define QO_FILE_SHARED_DELETE            (1 << 16)
// #define QO_FILE_NO_CACHING               (1 << 11)
// #define QO_FILE_SEQUENTIAL               (1 << 12)
// #define QO_FILE_DELETE_ON_CLOSE          (1 << 13)
// #define QO_FILE_RANDOM_ACCESS            (1 << 14)


#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _QO_SysFileStream;
typedef struct _QO_SysFileStream QO_SysFileStream;

/// @brief  Struct indicates how to open a file.
/// @sa     qo_sysfile_open()
struct _QO_FileOpenMode
{
    /// @brief  The access mode of the file.
    /// @sa     QO_FILE_READ, QO_FILE_WRITE, QO_FILE_READ_WRITE
    qo_flag8_t access_mode;

    /// @brief  The open mode of the file.
    /// @sa
    qo_flag8_t open_mode;

    /// @brief  The hints of the file. It may not be used if current platform 
    ///         does not support it. Set the first bit to 1 to force applying
    ///         the hints(x & 0x8000), in that case, qo_sysfile_read() will fail 
    ///         if not supported.
    /// @sa     QO_FILE_NO_CACHING, QO_FILE_SEQUENTIAL
    qo_flag16_t hints;
};
typedef struct _QO_FileOpenMode QO_FileOpenMode;

/// @brief  Open a file
/// @param  p_file A pointer to a file object.
/// @param  path   The path of the file. UTF-8 encoding is required.
/// @param  path_size The size of the path. 0 is allowed, in that case the size 
///         of the path will be calculated automatically.
/// @return The status of the operation.
/// @sa     qo_sysfile_close()
qo_stat_t 
QO_INTERFACE(qo_sysfile_open)(
    QO_SysFileStream **         p_file , 
    qo_ccstring_t      path , 
    qo_size_t          path_size ,
    qo_flag32_t        access_mode ,
    qo_flag32_t        open_mode ,
    qo_flag32_t        hints
) QO_NONNULL(1 , 2);

/// @brief  Read data from a file
/// @param  file The file object.
/// @param  buffer A buffer that can hold the data at least `desired_size` bytes.
/// @param  desired_size The size of the data to be read.
/// @param  p_error A pointer to a status code. If the operation succeeds, the 
///         status code will be set to `QO_OK`. Other error codes may be set.
///         NULL is allowed, in that case the status code will not be set.
/// @return The size of the data that has been read. 0 will be returned 
///         if the operation fails.
qo_size_t 
QO_INTERFACE(qo_sysfile_read_explicit)(
    QO_SysFileStream *       file ,
    qo_byte_t *     buffer ,
    qo_size_t       desired_size ,
    qo_stat_t *     p_error
) QO_NONNULL(1 , 2);

QO_FORCE_INLINE
qo_stat_t
QO_INTERFACE(qo_sysfile_write_implicit)(
    QO_SysFileStream *       file ,
    qo_byte_t *     buf ,
    qo_size_t       desired_size
) {
    return QO_INTERFACE(qo_sysfile_write_explicit)(
        file , buf , desired_size , NULL
    );
}

qo_size_t
QO_INTERFACE(qo_sysfile_write_explicit)(
    QO_SysFileStream *       file ,
    qo_byte_t *     buf ,
    qo_size_t       desired_size ,
    qo_stat_t *     error
) QO_NONNULL(1 , 2);

QO_FORCE_INLINE
qo_stat_t
QO_INTERFACE(qo_sysfile_read_implicit)(
    QO_SysFileStream *       file ,
    qo_byte_t *     buf ,
    qo_size_t       desired_size
){
    return QO_INTERFACE(qo_sysfile_read_explicit)(file , buf , desired_size , NULL);
}

/// @brief  Close a file
/// @param  file The file object. NULL is allowed, in that case the function
///         will do nothing.
void 
QO_INTERFACE(qo_sysfile_close)(
    QO_SysFileStream *    file
);

/// @brief  Allocate a file
/// @param  file The file object.
/// @param  size The size of the file.
/// @return The status of the operation.
qo_stat_t 
QO_INTERFACE(qo_sysfile_alloc)(
    QO_SysFileStream *   file ,
    qo_size_t   size
) QO_NONNULL(1);

/// @brief  Move the file pointer.
/// @param  file The file object.
/// @param  offset The offset to move.
/// @param  move_method The method to move the file pointer.
/// @param  p_error A pointer to a status code. If the operation succeeds, the 
///         status code will be set to `QO_OK`. Other error codes may be set.
///         NULL is allowed, in that case the status code will not be set.
/// @return The offset of the file pointer after the operation.
qo_offset_t 
QO_INTERFACE(qo_sysfile_seek)(
    QO_SysFileStream *      file ,
    qo_offset_t    offset ,
    qo_flag32_t    move_method ,
    qo_stat_t *    p_error
) QO_NONNULL(1);

/// @brief  Get the current position of the file pointer.
/// @param  file The file object.
/// @return 
QO_FORCE_INLINE
qo_offset_t 
QO_INTERFACE(qo_sysfile_get_position)(
    QO_SysFileStream *    file ,
    qo_stat_t *  p_error
) {
    return QO_INTERFACE(qo_sysfile_seek)(file , 0 , QO_FILE_MOVE_FROM_CURRENT);
} QO_NONNULL(1);

/// @brief  Get the size of a file.
/// @param  file The file object.
/// @param  p_size A pointer to size.
/// @return The status of the operation.
/// @retval QO_OK The operation is successful.
/// @retval QO_
/// @note   Only file or device that supports file-like operations can use this
///         function. 
qo_stat_t 
QO_INTERFACE(qo_sysfile_get_size)(
    QO_SysFileStream *      file ,
    qo_size_t *    p_size
) QO_NONNULL(1 , 2);

/// @brief  Get the maximum length of a path.
/// @return The maximum length of a path that XOceanLib can handle.
/// @note   The size is implementation-defined. Usually it is greater than 255.
///         In Windows 1607 or later with long path support enabled, the size
///         is 32767. In early Windows, the size is MAX_PATH, which is defined
///         as 260. In GNU/Linux, the size is 4096.
///         Of note, you may fail to open a file before reaching the maximum
///         length of a path, as many file systems limit a file name to 255
///         characters, which may be smaller than the maximum length.
/// @sa     qo_sysfile_open()
QO_PURE
qo_size_t
QO_INTERFACE(qo_get_path_max_length)();

#if defined(__cplusplus)
}
#endif // __cplusplus

#if QO_PLATFORM(WINDOWS)
#   include "internal/platform_spec/win32/fstream.h"
#elif QO_PLATFORM(POSIX)
#   include "internal/platform_spec/posix/fstream.h"
#else
#   error "QOLib: File stream interfaces not implemented"
#endif // 

// Make p_error optional for qo_sysfile_read and qo_sysfile_write
#define __QO_FILE_RW_SELECT(file , buf , desired_size , have_operated_size , \
                                __target , ...) __target

#define qo_sysfile_read(...)                                               \
        __QO_FILE_RW_SELECT                                             \
        (                                                                   \
            __VA_ARGS__ ,                                                   \
            QO_INTERFACE(qo_sysfile_read_explicit) ,                   \
            QO_INTERFACE(qo_sysfile_read_implicit)                     \
        ) (__VA_ARGS__)

#define qo_sysfile_write(...)                                              \
        __QO_FILE_RW_SELECT                                             \
        (                                                                   \ 
            __VA_ARGS__ ,                                                   \
            QO_INTERFACE(qo_sysfile_read_explicit) ,                   \
            QO_INTERFACE(qo_sysfile_write_implicit)                    \
        ) (__VA_ARGS__)

#define  qo_sysfile_open        QO_INTERFACE(qo_sysfile_open)
#define  qo_sysfile_close       QO_INTERFACE(qo_sysfile_close)
#define  qo_sysfile_alloc       QO_INTERFACE(qo_sysfile_alloc)
#define  qo_sysfile_seek        QO_INTERFACE(qo_sysfile_seek)
#define  qo_sysfile_get_pos     QO_INTERFACE(qo_sysfile_get_pos)
#define  qo_sysfile_get_size    QO_INTERFACE(qo_sysfile_get_size)