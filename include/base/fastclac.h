#pragma once
#include "types.h"

struct _XOceanDivisionInt64
{
    xocean_int64_t  remainder;
    xocean_int64_t  quotient;
};
typedef struct _XOceanDivisionInt64 XOceanDivisionInt64;

struct _XOceanDivisionInt32
{
    xocean_int32_t  remainder;
    xocean_int32_t  quotient;
};
typedef struct _XOceanDivisionInt32 XOceanDivisionInt32;

#define XOCEAN_DIVISION_I64(r , q) \
        ((XOceanDivisionInt64){ .quotient = (q) , .remainder = (r) })
#define XOCEAN_DIVISION_I32(r , q) \
        ((XOceanDivisionInt32){ .quotient = (q) , .remainder = (r) })
#define XOCEAN_DIV_I64(x , y) XOCEAN_DIVISION_I64((x) % (y) , (x) / (y))
#define XOCEAN_DIV_I32(x , y) XOCEAN_DIVISION_I32((x) % (y) , (x) / (y))

#if XOCEAN_SYSTEM_BIT(64)
typedef XOceanDivisionInt64 XOceanDivision;
#   define XOCEAN_DIVISION  XOCEAN_DIVISION_I64
#   define XOCEAN_DIV       XOCEAN_DIV_I64
#else
typedef XOceanDivisionInt32 XOceanDivision;
#   define XOCEAN_DIVISION  XOCEAN_DIVISION_I32
#   define XOCEAN_DIV       XOCEAN_DIV_I32
#endif

#define XOCEAN_MAX(x,y) (((x) > (y)) ? (x) : (y))
#define XOCEAN_MIN(x,y) (((x) < (y)) ? (x) : (y))

#define XOCEAN_SQR(x) ((x)*(x))
#define XOCEAN_CUBE(x) ((x)*(x)*(x))

#define XOCEAN_ABS(x) (((x) < 0) ? -(x) : (x))

#define XOCEAN_ALIGN_UP(x,align) (((x) + (align) - 1) & ~((align) - 1))
#define XOCEAN_ALIGN_DOWN(x,align) ((x) & ~((align) - 1))

#define XOCEAN_HAS_FLAG(x,f) (x & f)

#define XOCEAN_SWAP(x,y) do { typeof(x) tmp = x; x = y; y = tmp; } while (false)

#define XOCEAN_SNULL(x,t) ((x) ? (x->t) : NULL)




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

#if defined(__GNUC__)
#   define XOCEAN_CAS(r,o,n) __sync_val_compare_and_swap(r,o,n)
#elif defined(_MSC_VER)
#   define XOCEAN_CAS(r,o,n) _InterlockedCompareExchange(r,n,o)
#else
#   error "XOceanLib: CAS not implemented:Need complier support"
#endif 