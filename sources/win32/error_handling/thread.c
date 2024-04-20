#include "include/platform_spec/win32/thread.h"

xocean_stat_t
__xocean_thread_priority_error()
{
    switch (GetLastError())
    {
        case ERROR_INVALID_PARAMETER:   return XOCEAN_INVALID_ARG;
        case ERROR_INVALID_HANDLE:      return XOCEAN_INVALID_HANDLE;
        case ERROR_ACCESS_DENIED:       return XOCEAN_PERMISSION_DENIED;
        case ERROR_INVALID_OPERATION:   return XOCEAN_ACCESS_VIOLATED;
        default:                        return XOCEAN_UNKNOWN_ERROR;
    }
}