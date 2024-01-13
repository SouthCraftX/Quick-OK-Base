#pragma once
#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

xocean_stat_t xocean_enable_huge_page();
void xocean_disable_huge_page();
xocean_size_t xocean_get_huge_page_size();

#if XOCEAN_PLATFORM(WINDOWS)
#     include <securitybaseapi.h> // AdjustTokenPrivileges



xocean_bool_t xocean_enable_huge_page()
{
    TOKEN_PRIVILEGES privilege = { 
        .PrivilegeCount = 1,
        .Privileges[0].Attributes = SE_PRIVILEGE_ENABLED
    };
    LookUpPrivilegeValue(NULL, SE_LOCK_MEMORY_NAME, &privilege.Privileges[0].Luid);
    return AdjustTokenPrivileges(
        OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &token_handle), 
        FALSE, &privilege, 0, NULL, NULL
    );
}

// return 0 if huge page is not enabled.
XOCEAN_FORCE_INLINE
xocean_size_t xocean_get_huge_page_size()
{
    return GetLargePageMinimum();
}

#elif XOCEAN_PLATFORM(LINUX)



#else 

#endif // XOCEAN_PLATFORM

#if defined(__cplusplus)
}
#endif // __plusplus