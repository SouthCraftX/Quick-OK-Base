#pragma once
#define __XOC_ATOMIC_H__

#include "base.h"


#if defined(__GNUC__)
#   include "internel/gnuc_spec/atomic.h"
#elif __STDC_VER__ >= 201112L
#   include "internel/stdc_spec/atomic.h"
#else
#   error "Your complier does not support atomic operations."
#   error "Atomic operations is not implemented."
#endif

#include "internel/atomic_generic.h"


#if defined(__GNUC__)
#   include "gnuc_spec/atomic.h"
#elif __STDC_VER__ >= 201112L
#   include "stdc_spec/atomic.h"
#endif