#pragma once
#define __QO_STATIC_STRING_POOL_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _QO_LiteString
{
    qo_size_t  length;
    char        data[]; //< The string data, ending with a null character.
};
typedef struct _QO_LiteString QO_LiteString;

struct _QO_StaticStringPool;
typedef struct _QO_StaticStringPool QO_StaticStringPool;

struct _QO_StaticStringPoolInfo
{
    qo_size_t  string_count;
    qo_size_t  allocated_size;
    qo_size_t  free_size;
};
typedef struct _QO_StaticStringPoolInfo QO_StaticStringPoolInfo;

/// @brief  Create a static string pool.
/// @param  first_alloc_size The initial allocation size of the pool. Set it 0
///         to use the default value. Note that the size of meta data is
///         not included in this size.
/// @return Pointer to the created static string pool. NULL if the creation
///         failed.
QO_StaticStringPool* 
QO_INTERFACE(qo_static_string_pool_new)(
    qo_size_t  first_alloc_size
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
qo_stat_t
QO_INTERFACE(qo_static_string_pool_reserve)(
    QO_StaticStringPool *  pool ,
    qo_ssize_t             delta_size
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
qo_stat_t
QO_INTERFACE(qo_static_string_pool_add)(
    QO_StaticStringPool ** p_pool ,
    qo_size_t              size ,
    qo_ccstring_t          string ,
    QO_LiteString const* * p_out_string
) QO_NONNULL(1 , 3 , 4);

/// @brief Delete a static string pool.
/// @param pool The static string pool to delete. NULL is allowed, in that case,
///        the function does nothing.
/// @note  All strings in the pool can not be used after this function is called.
void
QO_INTERFACE(qo_static_string_pool_delete)(
    QO_StaticStringPool *  pool
);

#if defined(__cplusplus)
}
#endif // __cplusplus