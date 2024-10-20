#pragma once
#define __XOC_STATIC_STRING_POOL_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOC_LiteString
{
    xoc_size_t  length;
    char        data[]; //< The string data, ending with a null character.
};
typedef struct _XOC_LiteString XOC_LiteString;

struct _XOC_StaticStringPool;
typedef struct _XOC_StaticStringPool XOC_StaticStringPool;

struct _XOC_StaticStringPoolInfo
{
    xoc_size_t  string_count;
    xoc_size_t  allocated_size;
    xoc_size_t  free_size;
};
typedef struct _XOC_StaticStringPoolInfo XOC_StaticStringPoolInfo;

/// @brief  Create a static string pool.
/// @param  first_alloc_size The initial allocation size of the pool. Set it 0
///         to use the default value. Note that the size of meta data is
///         not included in this size.
/// @return Pointer to the created static string pool. NULL if the creation
///         failed.
XOC_StaticStringPool* 
XOC_INTERFACE(xoc_static_string_pool_new)(
    xoc_size_t  first_alloc_size
);

/// @brief  Reserve a specified space in the static string pool.
/// @param  delta_size The size to reserve. If it is positive, the function will
///         reserve the specified space. If it is negative, the function will
///         shrink the specified space.
/// @return The status of the operation.
/// @note   This function is intended to be used to reserve space, to reduce
///         the number of memory allocations, or shrink the unused space.
///         If no enough memory to handle the request, the function will fail,
///         and the pool will be unchanged. If size is too small that no enough
///         space to shrink, the function will shrink all the space and succeed.
xoc_stat_t
XOC_INTERFACE(xoc_static_string_pool_reserve)(
    XOC_StaticStringPool *  pool ,
    xoc_ssize_t             delta_size
);

/// @brief  Add a string to the static string pool.
/// @param  p_pool Pointer to the static string pool. 
/// @param  size The size of the string to add, including the null character.
///         0 is allowed, in that case, the function will calculate the size
/// @param  string The string to add.
/// @param  out_string The output parameter to receive the pointer to the added
///         string. If the function succeeds, the pointer will be valid until
///         the pool is deleted. NULL is allowed if you don't need this information
/// @note   You can't remove a string once it was added to the pool. But you
///         can remove all strings at deleting the pool.
xoc_stat_t
XOC_INTERFACE(xoc_static_string_pool_add)(
    XOC_StaticStringPool ** p_pool ,
    xoc_size_t              size ,
    xoc_ccstring_t          string ,
    XOC_LiteString const* * p_out_string
) XOC_NONNULL(1 , 3 , 4);

/// @brief Delete a static string pool.
/// @param pool The static string pool to delete. NULL is allowed, in that case,
///        the function does nothing.
/// @note  All strings in the pool can not be used after this function is called.
void
XOC_INTERFACE(xoc_static_string_pool_delete)(
    XOC_StaticStringPool *  pool
);

#if defined(__cplusplus)
}
#endif // __cplusplus