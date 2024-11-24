#pragma once
#define __QO_WIN32_SPEC_H__

#include "base.h"

#if !QO_PLATFORM(WINDOWS)
#   error "This file is only for Windows."
#endif // !QO_PLATFORM(WINDOWS)

/// @brief   Returns whether the application is opened via double-clicked.
qo_bool_t
QO_INTERFACE(qo_is_opened_via_double_clicked)();

#include "internal/platform_spec/win32/win32spec.h"