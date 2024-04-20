#pragma once
#define __XOCEAN_CONDLOCK_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus


struct _XOceanCondLock;
typedef struct _XOceanCondLock XOceanCondLock;

void 
XOCEAN_INTERFACE(xocean_condlock_init)(
    XOceanCondLock * lock
);

void 
XOCEAN_INTERFACE(xocean_condlock_lock)(
    XOceanCondLock * lock
);

void 
XOCEAN_INTERFACE(xocean_condlock_unlock)(
    XOceanCondLock * lock
);

void
XOCEAN_INTERFACE(xocean_condlock_wait)(
    XOceanCondLock * lock
);

void 
XOCEAN_INTERFACE(xocean_condlock_wake)(
    XOceanCondLock * lock
);

void 
XOCEAN_INTERFACE(xocean_condlock_wake_all)(
    XOceanCondLock * lock
);
    
void 
XOCEAN_INTERFACE(xocean_condlock_destroy)(
    XOceanCondLock * lock
);


#if defined(__cplusplus)
}
#endif // __cplusplus

#if XOCEAN_PLATFORM(WINDOWS)
#   include "platform_spec/win32/condlock.h"
#elif XOCEAN_PLATFORM(POSIX)
#   include "platform_spec/posix/condlock.h"
#endif 

#define xocean_condlock_init        XOCEAN_INTERFACE(xocean_condlock_init)
#define xocean_condlock_lock        XOCEAN_INTERFACE(xocean_condlock_lock)
#define xocean_condlock_unlock      XOCEAN_INTERFACE(xocean_condlock_unlock)
#define xocean_condlock_wait        XOCEAN_INTERFACE(xocean_condlock_wait)
#define xocean_condlock_wake        XOCEAN_INTERFACE(xocean_condlock_wake)
#define xocean_condlock_wake_all    XOCEAN_INTERFACE(xocean_condlock_wake_all)
#define xocean_condlock_destroy     XOCEAN_INTERFACE(xocean_condlock_destroy)