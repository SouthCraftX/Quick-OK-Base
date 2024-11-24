#pragma once
#define __QO_USER_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

/// @brief  Check if the current user is root
/// @return true if the current user is root, false otherwise
qo_bool_t
QO_INTERFACE(qo_is_high_privileged)();

#if defined(__cplusplus)
}
#endif // __cplusplus