#pragma once
#define __XOC_WIN32_SPEC_H__

#include "base.h"

#if !XOC_PLATFORM(WINDOWS)
#   error "This file is only for Windows."
#endif // !XOC_PLATFORM(WINDOWS)

/// @brief   Returns whether the application is opened via double-clicked.
xoc_bool_t
XOC_INTERFACE(xoc_is_opened_via_double_clicked)();

#include "internal/platform_spec/win32/win32spec.h"