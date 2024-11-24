#pragma once
#define __QO_STRINGSET_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif

/// @brief  Calculate the length of a string.
/// @param  string  The string to calculate the length of
/// @return The length of the string.
qo_size_t
QO_INTERFACE(qo_string_length)(
    qo_ccstring_t  string
) QO_NONNULL(1);

/// @brief  Copy a string to another
/// @param  source  The source string
/// @param  destination  The destination string
/// @param  count  The number of characters to copy. 0 is allowed, in that case,
///         the string is copied until the null terminator is reached.
/// @return 
qo_size_t
QO_INTERFACE(qo_string_copy)(
    qo_ccstring_t  source ,
    qo_cstring_t   destination ,
    qo_size_t      count
) QO_NONNULL(1 , 2);

/// @brief  Duplicate a string using qo_alloc()
/// @param  string  The string to duplicate
/// @param  p_count Pointer to the count of characters to duplicate. 
///         If NULL,
///         the function will duplicate until the null terminator is reached.
///         If not NULL, 
///         *p_count indicates the number of characters to
///         duplicate. If *p_count is 0, the function will duplicate until the
///         null terminator is reached. *p_count will be written with the
///         number of characters duplicated.
/// @return The duplicated string. NULL if no enough memory to handle this
///         operation.
qo_cstring_t
QO_INTERFACE(qo_string_duplicate)(
    qo_ccstring_t  string ,
    qo_size_t *    p_count
) QO_NONNULL(1);

/// @brief  Find a character in a string
/// @param  string  The string to search
/// @param  character  The character to find 
/// @param  length  The length of the string to search
/// @return Pointer to the first occurrence of the character in the string.
qo_cstring_t
QO_INTERFACE(qo_string_find_char)(
    qo_ccstring_t  string ,
    qo_int32_t     character ,
    qo_size_t      length
) QO_NONNULL(1);

qo_ccstring_t
QO_INTERFACE(qo_string_find_substring)(
    qo_ccstring_t  string ,
    qo_ccstring_t  substring ,
    qo_size_t      length
) QO_NONNULL(1 , 2);

#if defined(__cplusplus)
}
#endif

#define qo_string_length       QO_INTERFACE(qo_string_length)
#define qo_string_copy         QO_INTERFACE(qo_string_copy)
#define qo_string_duplicate    QO_INTERFACE(qo_string_duplicate)
#define qo_string_find_char    QO_INTERFACE(qo_string_find_char)
#define qo_string_find_substring QO_INTERFACE(qo_string_find_substring)