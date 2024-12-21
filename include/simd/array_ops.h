#pragma once
#define __XOC_SIMD_ARRAY_OPS_H__

#include "../base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

/* Unsigned 64-bit Array Operations */

void
xoc_u64array_add(
    const xoc_uint64_t *    source ,
    xoc_uint64_t *          destionation ,
    xoc_size_t              length
) XOC_NONNULL(1 , 2);

void
xoc_u64array_sub(
    const xoc_uint64_t *    source ,
    xoc_uint64_t *          destionation ,
    xoc_size_t              length
) XOC_NONNULL(1 , 2);

void
xoc_u64array_mul(
    const xoc_uint64_t *    source ,
    xoc_uint64_t *          destionation ,
    xoc_size_t              length
) XOC_NONNULL(1 , 2);

void
xoc_u64array_div(
    const xoc_uint64_t *    source ,
    xoc_uint64_t *          destionation ,
    xoc_size_t              length
) XOC_NONNULL(1 , 2);

/* Signed 64-bit Array Operations */
void
xoc_i64array_add(
    const xoc_uint64_t *    source ,
    xoc_uint64_t *          destionation ,
    xoc_size_t              length
) XOC_NONNULL(1 , 2);

void
xoc_i64array_sub(
    const xoc_uint64_t *    source ,
    xoc_uint64_t *          destionation ,
    xoc_size_t              length
) XOC_NONNULL(1 , 2);

void
xoc_i64array_mul(
    const xoc_uint64_t *    source ,
    xoc_uint64_t *          destionation ,
    xoc_size_t              length
) XOC_NONNULL(1 , 2);

void
xoc_i64array_div(
    const xoc_uint64_t *    source ,
    xoc_uint64_t *          destionation ,
    xoc_size_t              length
) XOC_NONNULL(1 , 2);



#if defined(__cplusplus)
}
#endif //__cplusplus