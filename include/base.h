#pragma once
#define __XOC_BASE_H__



#include "base/attribute.h"
#include "base/platform.h"
#include "base/types.h"
#include "base/stat.h"
#include "base/debug.h"
#include "base/basic_class.h"
#include "base/fastclac.h"
#include "base/limit.h"

#if XOC_PLATFORM(WINDOWS)
#include "base/win32_common.h"
#endif // XOC_PLATFORM(WINDOWS)