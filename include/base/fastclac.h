#pragma once
#include "types.h"

struct _QODivisionInt64
{
    qo_int64_t  remainder;
    qo_int64_t  quotient;
};
typedef struct _QODivisionInt64 QODivisionInt64;

struct _QODivisionInt32
{
    qo_int32_t  remainder;
    qo_int32_t  quotient;
};
typedef struct _QODivisionInt32 QODivisionInt32;

#define QO_DIVISION_I64(r , q) \
        ((QODivisionInt64){ .quotient = (q) , .remainder = (r) })
#define QO_DIVISION_I32(r , q) \
        ((QODivisionInt32){ .quotient = (q) , .remainder = (r) })
#define QO_DIV_I64(x , y) QO_DIVISION_I64((x) % (y) , (x) / (y))
#define QO_DIV_I32(x , y) QO_DIVISION_I32((x) % (y) , (x) / (y))

#if QO_SYSTEM_BIT(64)
typedef QODivisionInt64 QODivision;
#   define QO_DIVISION  QO_DIVISION_I64
#   define QO_DIV       QO_DIV_I64
#else
typedef QODivisionInt32 QODivision;
#   define QO_DIVISION  QO_DIVISION_I32
#   define QO_DIV       QO_DIV_I32
#endif

#define QO_MAX(x,y) (((x) > (y)) ? (x) : (y))
#define QO_MIN(x,y) (((x) < (y)) ? (x) : (y))

#define QO_SQR(x) ((x)*(x))
#define QO_CUBE(x) ((x)*(x)*(x))

#define QO_ABS(x) (((x) < 0) ? -(x) : (x))

#define QO_ALIGN_UP(x,align) (((x) + (align) - 1) & ~((align) - 1))
#define QO_ALIGN_DOWN(x,align) ((x) & ~((align) - 1))

#define QO_HAS_FLAG(x,f) (x & f)

#define QO_SWAP(x,y) do { typeof(x) tmp = x; x = y; y = tmp; } while (qo_false)

#define QO_SNULL(x,t) ((x) ? (x->t) : NULL)




// Thanks to sodiumcl10
#define QO_FIND_ZEROS_INDEX64(x,n) 

#if defined(__GNUC__)
#   define QO_PARITY32(x) __builtin_parity(x)
#   define QO_POPCOUNT32(x) __builtin_popcount(x)
#   define QO_PARITY64(x) __builtin_parityll(x)
#   define QO_POPCOUNT64(x) __builtin_popcountll(x)
#else
#define QO_PARITY(x) 
#endif

#if defined(__GNUC__)
#   define QO_CAS(r,o,n) __sync_val_compare_and_swap(r,o,n)
#elif defined(_MSC_VER)
#   define QO_CAS(r,o,n) _InterlockedCompareExchange(r,n,o)
#else
#   error "QOLib: CAS not implemented:Need complier support"
#endif 