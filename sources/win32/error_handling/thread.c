#include "include/platform_spec/win32/thread.h"

xoc_stat_t
__xoc_thread_priority_error()
{
    switch (GetLastError())
    {
        case ERROR_INVALID_PARAMETER:   return XOC_INVALID_ARG;
        case ERROR_INVALID_HANDLE:      return XOC_INVALID_HANDLE;
        case ERROR_ACCESS_DENIED:       return XOC_PERMISSION_DENIED;
        case ERROR_INVALID_OPERATION:   return XOC_ACCESS_VIOLATED;
        default:                        return XOC_UNKNOWN_ERROR;
    }
}