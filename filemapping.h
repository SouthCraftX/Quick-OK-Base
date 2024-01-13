#pragma once
#include "fstream/iofstream.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOceanFileMapping;
typedef struct _XOceanFileMapping XOceanFileMapping;

#if XOCEAN_PLATFORM(WINDOWS)
#   include <filemapping.h>


#elif XOCEAN_PLATFORM(POSIX)

#else

#endif

#if defined(__cplusplus)
}
#endif 