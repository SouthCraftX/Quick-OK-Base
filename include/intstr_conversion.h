#pragma once
#define __QO_INTSTR_CONVERSION_H__

#include "base.h"

/// @brief Convert a string to an unsigned 64-bit integer.
/// @note  This function does not check for anything, including negative values,
///        overflow, or invalid input.
qo_uint64_t
QO_INTERFACE(qo_string_to_u64)(
    qo_ccstring_t string
) QO_NONNULL(1);

/// @brief Convert a string to an unsigned 32-bit integer.
/// @note  This function does not check for anything, including negative values,
///        overflow, or invalid input.
qo_uint32_t
QO_INTERFACE(qo_string_to_u32)(
    qo_ccstring_t string
) QO_NONNULL(1);

/// @brief Convert a string to a signed 64-bit integer.
/// @note  This function does not check for anything, including overflow, or invalid input.
qo_int64_t
QO_INTERFACE(qo_string_to_i64)(
    qo_ccstring_t string
) QO_NONNULL(1);

/// @brief Convert a string to a signed 32-bit integer.
/// @note  This function does not check for anything, including overflow, or invalid input.
qo_int32_t
QO_INTERFACE(qo_string_to_i32)(
    qo_ccstring_t string
) QO_NONNULL(1);

/// @brief  Convert a unsigned 64-bit integer to string
/// @param  value The value to convert
/// @param  string_buffer  The buffer to write the string to, to prevent buffer,
///         overflow, it is strongly recommended that the buffer
///         is at least 21 characters long.
/// @return The number of characters written to the buffer. It indicates the 
///         size of the string
qo_size_t
QO_INTERFACE(qo_u64_to_string)(
    qo_uint64_t    value ,
    qo_cstring_t   string_buffer
) QO_NONNULL(2);

/// @brief  Convert a signed 64-bit integer to string
/// @param  value The value to convert
/// @param  string_buffer  The buffer to write the string to, to prevent buffer,
///         overflow, it is strongly recommended that the buffer is at least 21
///         characters long.
/// @return The length of the string.
qo_size_t
QO_INTERFACE(qo_i64_to_string)(
    qo_int64_t     value ,
    qo_cstring_t   string_buffer
) QO_NONNULL(2);

/// @brief  Convert a unsigned 32-bit integer to string
/// @param  value The value to convert
/// @param  string_buffer  The buffer to write the string to, to prevent buffer,
///         overflow, it is strongly recommended that the buffer is at least 11
///         characters long.
/// @return The length of the string.
qo_size_t
QO_INTERFACE(qo_u32_to_string)(
    qo_uint32_t    value ,
    qo_cstring_t   string_buffer
) QO_NONNULL(2);

/// @brief  Convert a signed 32-bit integer to string
/// @param  value The value to convert
/// @param  string_buffer  The buffer to write the string to, to prevent buffer,
///         overflow, it is strongly recommended that the buffer is at least 11
///         characters long.
/// @return The length of the string.
qo_size_t
QO_INTERFACE(qo_i32_to_string)(
    qo_int32_t     value ,
    qo_cstring_t   string_buffer
) QO_NONNULL(2);