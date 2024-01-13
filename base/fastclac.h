#pragma once

#define XOCEAN_MAX(x,y) (((x) > (y)) ? (x) : (y))
#define XOCEAN_MIN(x,y) (((x) < (y)) ? (x) : (y))

#define XOCEAN_SQR(x) ((x)*(x))
#define XOCEAN_CUBE(x) ((x)*(x)*(x))

#define XOCEAN_ABS(x) (((x) < 0) ? -(x) : (x))

#define XOCEAN_ALIGN_UP(x,align) (((x) + (align) - 1) & ~((align) - 1))
#define XOCEAN_ALIGN_DOWN(x,align) ((x) & ~((align) - 1))

#define XOCEAN_HAS_FLAG(x,f) (x & f)

#define XOCEAN_SWAP(x,y) do { typeof(x) tmp = x; x = y; y = tmp; } while (false)

// Thanks to sodiumcl10
#define XOCEAN_FIND_ZEROS_INDEX64(x,n) 

#if defined(__GNUC__)
#   define XOCEAN_PARITY32(x) __builtin_parity(x)
#   define XOCEAN_POPCOUNT32(x) __builtin_popcount(x)
#   define XOCEAN_PARITY64(x) __builtin_parityll(x)
#   define XOCEAN_POPCOUNT64(x) __builtin_popcountll(x)
#else
#define XOCEAN_PARITY(x) 
#endif