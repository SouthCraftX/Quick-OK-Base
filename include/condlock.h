#pragma once
#define __XOC_CONDLOCK_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus


struct _XOC_CondLock;
typedef struct _XOC_CondLock XOC_CondLock;

void 
XOC_INTERFACE(xoc_condlock_init)(
    XOC_CondLock * lock
);

void 
XOC_INTERFACE(xoc_condlock_lock)(
    XOC_CondLock * lock
);

void 
XOC_INTERFACE(xoc_condlock_unlock)(
    XOC_CondLock * lock
);

void
XOC_INTERFACE(xoc_condlock_wait)(
    XOC_CondLock * lock
);

void 
XOC_INTERFACE(xoc_condlock_wake)(
    XOC_CondLock * lock
);

void 
XOC_INTERFACE(xoc_condlock_wake_all)(
    XOC_CondLock * lock
);
    
void 
XOC_INTERFACE(xoc_condlock_destroy)(
    XOC_CondLock * lock
);


#if defined(__cplusplus)
}
#endif // __cplusplus

#if XOC_PLATFORM(WINDOWS)
#   include "platform_spec/win32/condlock.h"
#elif XOC_PLATFORM(POSIX)
#   include "platform_spec/posix/condlock.h"
#endif 

#define xoc_condlock_init        XOC_INTERFACE(xoc_condlock_init)
#define xoc_condlock_lock        XOC_INTERFACE(xoc_condlock_lock)
#define xoc_condlock_unlock      XOC_INTERFACE(xoc_condlock_unlock)
#define xoc_condlock_wait        XOC_INTERFACE(xoc_condlock_wait)
#define xoc_condlock_wake        XOC_INTERFACE(xoc_condlock_wake)
#define xoc_condlock_wake_all    XOC_INTERFACE(xoc_condlock_wake_all)
#define xoc_condlock_destroy     XOC_INTERFACE(xoc_condlock_destroy)