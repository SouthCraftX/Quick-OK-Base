#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus


xocean_stat_t
__xocean_mmap_error()
{
    switch (errno)
    {
        case EBADF:     return XOCEAN_INVALID_HANDLE;
        case ENOMEM:    return XOCEAN_OUT_OF_MEMORY;
        case EINVAL:
        case EOVERFLOW: return XOCEAN_INVALID_ARG;
        case ENFILE:    return XOCEAN_NO_RESOURCE;
        case EACCES:    return XOCEAN_BAD_TYPE;
        case EPERM:     return XOCEAN_PERMISSION_DENIED;
        default:        return XOCEAN_UNKNOWN_ERROR;
    }
}

#if defined(__cplusplus)
}
#endif // __cplusplus