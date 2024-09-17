#pragma once
#define __XOC_USER_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

/// @brief  Check if the current user is root
/// @return true if the current user is root, false otherwise
xoc_bool_t
XOC_INTERFACE(xoc_is_high_privileged)();

#if defined(__cplusplus)
}
#endif // __cplusplus