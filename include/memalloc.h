#pragma once
#define __QO_MEMALLOC_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif

// --- Virtual Memory Allocation ---

/// @brief  Allocate virtual memory
/// @param  size The size of the memory to allocate
/// @return A pointer to the allocated memory. NULL if no enough memory is available
/// @sa     qo_virtual_free()
QO_NODISCARD
qo_pointer_t
QO_INTERFACE(qo_virtual_alloc)(
    qo_size_t      size
);

/// @brief  Free virtual memory
/// @param  memory The pointer to the memory to free. NULL is allowed, in that
///         case, the function does nothing.
/// @sa     qo_virtual_alloc()
void
QO_INTERFACE(qo_virtual_free)(
    qo_pointer_t   memory
);

// --- Small Obejct Allocation ---

/// @brief  Allocate small object
/// @param  size The size of the object to allocate. It must be less than or
///         equal to the maximum small allocation size returned by 
///         qo_get_max_small_alloc_size()
// @sa      qo_get_max_small_alloc_size() , qo_free()
qo_pointer_t
QO_INTERFACE(qo_small_alloc)(
    qo_size_t      size
);

/// @brief  Get the maximum small allocation size
/// @return The maximum small allocation size
QO_NODISCARD
qo_size_t
QO_INTERFACE(qo_get_max_small_alloc_size)();

// --- Generic Allocation ---

/// @brief  Allocate memory
/// @param  size The size of the memory to allocate
/// @return A pointer to the allocated memory. NULL if no enough memory is available
qo_pointer_t
QO_INTERFACE(qo_alloc)(
    qo_size_t      size
);

/// @brief  Allocate memory and initialize it to zero
/// @param  size The size of the memory to allocate
/// @return A pointer to the allocated memory. NULL if no enough memory is available
/// @sa     qo_free()
QO_NODISCARD
qo_pointer_t
QO_INTERFACE(qo_calloc)(
    qo_size_t      size
);

/// @brief  Reallocate memory
/// @param  memory The pointer to the memory to reallocate. NULL is allowed, 
///         in that case, the function behaves like qo_alloc()
/// @param  new_size The new size of the memory
/// @return A pointer to the reallocated memory. 
/// @retval NULL if no enough memory is available, in that case, the original 
///         memory is perserved.
/// @sa     qo_free()
QO_NODISCARD
qo_pointer_t
QO_INTERFACE(qo_realloc)(
    qo_pointer_t   memory ,
    qo_size_t      new_size
);

/// @brief  Reallocate memory and initialize the extended memory to zero(if any)
/// @param  memory The pointer to the memory to reallocate. NULL is allowed, 
///         in that case, the function behaves like qo_calloc()
/// @param  new_size The new size of the memory
/// @return A pointer to the reallocated memory. 
/// @retval NULL if no enough memory is available, in that case, the original 
///         memory is perserved.
/// @sa     qo_free()
QO_NODISCARD
qo_pointer_t
QO_INTERFACE(qo_recalloc)(
    qo_pointer_t   memory ,
    qo_size_t      new_size
);

/// @brief  Free memory allocated by qo_alloc() , qo_calloc() , qo_realloc() 
///         or qo_recalloc()
/// @param  memory The pointer to the memory to free. NULL is allowed, in that
///         case, the function does nothing.
void
QO_INTERFACE(qo_free)(
    qo_pointer_t   memory
);

#define qo_virtual_alloc   QO_INTERFACE(qo_virtual_alloc)
#define qo_vritual_free    QO_INTERFACE(qo_virtual_free)
#define qo_alloc           QO_INTERFACE(qo_alloc)
#define qo_calloc          QO_INTERFACE(qo_calloc)
#define qo_realloc         QO_INTERFACE(qo_realloc)
#define qo_recalloc        QO_INTERFACE(qo_recalloc)
#define qo_small_alloc     QO_INTERFACE(qo_small_alloc)
#define qo_free            QO_INTERFACE(qo_free)


#if defined(__cplusplus)
}
#endif

// You can implement your own memory allocation API by defining 
// QO_MEMALLOC_API_IMPLEMENTED
// By default, the implementation is provided by mimalloc.
#if !defined(QO_MEMALLOC_API_IMPLEMENTED)
#   include "internal/memalloc_mi.h"
#endif 