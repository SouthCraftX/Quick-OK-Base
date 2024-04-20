#pragma once

#include "../../atomic.h" // for debug

#if !defined(__XOCEAN_ATOMIC_H__)
#   error "Never include this header directly! Use <xocean/atomic.h> instead."alignas
#endif 

#include <winnt.h>  // It provides the atomic operations.

#include "atomic_i32.h"