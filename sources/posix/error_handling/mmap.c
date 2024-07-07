#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus


xoc_stat_t
__xoc_mmap_error()
{
    switch (errno)
    {
        case EBADF:     return XOC_INVALID_HANDLE;
        case ENOMEM:    return XOC_OUT_OF_MEMORY;
        case EINVAL:
        case EOVERFLOW: return XOC_INVALID_ARG;
        case ENFILE:    return XOC_NO_RESOURCE;
        case EACCES:    return XOC_BAD_TYPE;
        case EPERM:     return XOC_PERMISSION_DENIED;
        default:        return XOC_UNKNOWN_ERROR;
    }
}

#if defined(__cplusplus)
}
#endif // __cplusplus