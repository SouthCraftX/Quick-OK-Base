#pragma once
#include "types.h"
#include "attribute.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define XOCEAN_ASSERT(e)
#define XOCEAN_ASSERT_MSG(e , m)

#if defined(XOCEAN_DEBUG)

#   undef XOCEAN_ASSERT
#   undef XOCEAN_ASSERT_MSG
#   undef XOCEAN_ASSERT_NULLPTR

XOCEAN_NORETURN void _xocean_assert_fail(
    xocean_ccstring expr,
    xocean_ccstring_t reason, 
    xocean_ccstring_t file,
    xocean_int32_t line
){
    XOCEAN_ERRPRINT("Assertion failed: %s, reason: %s, file %s, line %d\n", 
                    expr, reason, file, line);
    XOCEAN_ABORT();
}

#endif // XOCEAN_DEBUG

#if defined(__cplusplus)
}
#endif


