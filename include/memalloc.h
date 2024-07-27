#pragma once
#define __XOC_MEMALLOC_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif

// --- Virtual Memory Allocation ---

/// @brief  Allocate virtual memory
/// @param  size The size of the memory to allocate
/// @return A pointer to the allocated memory. NULL if no enough memory is available
/// @sa     xoc_virtual_free()
XOC_NODISCARD
xoc_pointer_t
XOC_INTERFACE(xoc_virtual_alloc)(
    xoc_size_t      size
);

/// @brief  Free virtual memory
/// @param  memory The pointer to the memory to free. NULL is allowed, in that
///         case, the function does nothing.
/// @sa     xoc_virtual_alloc()
void
XOC_INTERFACE(xoc_virtual_free)(
    xoc_pointer_t   memory
);

// --- Small Obejct Allocation ---

/// @brief  Allocate small object
/// @param  size The size of the object to allocate. It must be less than or
///         equal to the maximum small allocation size returned by 
///         xoc_get_max_small_alloc_size()
// @sa      xoc_get_max_small_alloc_size() , xoc_free()
xoc_pointer_t
XOC_INTERFACE(xoc_small_alloc)(
    xoc_size_t      size
);

/// @brief  Get the maximum small allocation size
/// @return The maximum small allocation size
XOC_NODISCARD
xoc_size_t
XOC_INTERFACE(xoc_get_max_small_alloc_size)();

// --- Generic Allocation ---

/// @brief  Allocate memory
/// @param  size The size of the memory to allocate
/// @return A pointer to the allocated memory. NULL if no enough memory is available
xoc_pointer_t
XOC_INTERFACE(xoc_alloc)(
    xoc_size_t      size
);

/// @brief  Allocate memory and initialize it to zero
/// @param  size The size of the memory to allocate
/// @return A pointer to the allocated memory. NULL if no enough memory is available
/// @sa     xoc_free()
XOC_NODISCARD
xoc_pointer_t
XOC_INTERFACE(xoc_calloc)(
    xoc_size_t      size
);

/// @brief  Reallocate memory
/// @param  memory The pointer to the memory to reallocate. NULL is allowed, 
///         in that case, the function behaves like xoc_alloc()
/// @param  new_size The new size of the memory
/// @return A pointer to the reallocated memory. 
/// @retval NULL if no enough memory is available, in that case, the original 
///         memory is perserved.
/// @sa     xoc_free()
XOC_NODISCARD
xoc_pointer_t
XOC_INTERFACE(xoc_realloc)(
    xoc_pointer_t   memory ,
    xoc_size_t      new_size
);

/// @brief  Reallocate memory and initialize the extended memory to zero(if any)
/// @param  memory The pointer to the memory to reallocate. NULL is allowed, 
///         in that case, the function behaves like xoc_calloc()
/// @param  new_size The new size of the memory
/// @return A pointer to the reallocated memory. 
/// @retval NULL if no enough memory is available, in that case, the original 
///         memory is perserved.
/// @sa     xoc_free()
xoc_pointer_t
XOC_INTERFACE(xoc_recalloc)(
    xoc_pointer_t   memory ,
    xoc_size_t      new_size
);

/// @brief  Free memory allocated by xoc_alloc() , xoc_calloc() , xoc_realloc() 
///         or xoc_recalloc()
/// @param  memory The pointer to the memory to free. NULL is allowed, in that
///         case, the function does nothing.
void
XOC_INTERFACE(xoc_free)(
    xoc_pointer_t   memory
);

#define xoc_virtual_alloc   XOC_INTERFACE(xoc_virtual_alloc)
#define xoc_vritual_free    XOC_INTERFACE(xoc_virtual_free)
#define xoc_alloc           XOC_INTERFACE(xoc_alloc)
#define xoc_calloc          XOC_INTERFACE(xoc_calloc)
#define xoc_realloc         XOC_INTERFACE(xoc_realloc)
#define xoc_recalloc        XOC_INTERFACE(xoc_recalloc)
#define xoc_small_alloc     XOC_INTERFACE(xoc_small_alloc)
#define xoc_free            XOC_INTERFACE(xoc_free)


#if defined(__cplusplus)
}
#endif

// You can implement your own memory allocation API by defining 
// XOC_MEMALLOC_API_IMPLEMENTED
// By default, the implementation is provided by mimalloc.
#if !defined(XOC_MEMALLOC_API_IMPLEMENTED)
#   include "internal/memalloc_mi.h"
#endif 