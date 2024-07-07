#pragma once
#include "types.h"

struct _XOCDivisionInt64
{
    xoc_int64_t  remainder;
    xoc_int64_t  quotient;
};
typedef struct _XOCDivisionInt64 XOCDivisionInt64;

struct _XOCDivisionInt32
{
    xoc_int32_t  remainder;
    xoc_int32_t  quotient;
};
typedef struct _XOCDivisionInt32 XOCDivisionInt32;

#define XOC_DIVISION_I64(r , q) \
        ((XOCDivisionInt64){ .quotient = (q) , .remainder = (r) })
#define XOC_DIVISION_I32(r , q) \
        ((XOCDivisionInt32){ .quotient = (q) , .remainder = (r) })
#define XOC_DIV_I64(x , y) XOC_DIVISION_I64((x) % (y) , (x) / (y))
#define XOC_DIV_I32(x , y) XOC_DIVISION_I32((x) % (y) , (x) / (y))

#if XOC_SYSTEM_BIT(64)
typedef XOCDivisionInt64 XOCDivision;
#   define XOC_DIVISION  XOC_DIVISION_I64
#   define XOC_DIV       XOC_DIV_I64
#else
typedef XOCDivisionInt32 XOCDivision;
#   define XOC_DIVISION  XOC_DIVISION_I32
#   define XOC_DIV       XOC_DIV_I32
#endif

#define XOC_MAX(x,y) (((x) > (y)) ? (x) : (y))
#define XOC_MIN(x,y) (((x) < (y)) ? (x) : (y))

#define XOC_SQR(x) ((x)*(x))
#define XOC_CUBE(x) ((x)*(x)*(x))

#define XOC_ABS(x) (((x) < 0) ? -(x) : (x))

#define XOC_ALIGN_UP(x,align) (((x) + (align) - 1) & ~((align) - 1))
#define XOC_ALIGN_DOWN(x,align) ((x) & ~((align) - 1))

#define XOC_HAS_FLAG(x,f) (x & f)

#define XOC_SWAP(x,y) do { typeof(x) tmp = x; x = y; y = tmp; } while (false)

#define XOC_SNULL(x,t) ((x) ? (x->t) : NULL)




// Thanks to sodiumcl10
#define XOC_FIND_ZEROS_INDEX64(x,n) 

#if defined(__GNUC__)
#   define XOC_PARITY32(x) __builtin_parity(x)
#   define XOC_POPCOUNT32(x) __builtin_popcount(x)
#   define XOC_PARITY64(x) __builtin_parityll(x)
#   define XOC_POPCOUNT64(x) __builtin_popcountll(x)
#else
#define XOC_PARITY(x) 
#endif

#if defined(__GNUC__)
#   define XOC_CAS(r,o,n) __sync_val_compare_and_swap(r,o,n)
#elif defined(_MSC_VER)
#   define XOC_CAS(r,o,n) _InterlockedCompareExchange(r,n,o)
#else
#   error "XOCLib: CAS not implemented:Need complier support"
#endif 