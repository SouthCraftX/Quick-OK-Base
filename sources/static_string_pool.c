#include "static_string_pool.h"
#include "memalloc.h"
#include "stringset.h"

#include <stdlib.h>

#define FIRST_ALLOC_SIZE 128

struct _XOC_StaticStringPool 
{
    XOC_StaticStringPoolInfo    info;
    XOC_LiteString *            free_pos;
    XOC_LiteString              strings[];
};

XOC_StaticStringPool *
XOC_IMPL(xoc_static_string_pool_new)(
    xoc_size_t  first_alloc_size
){
    if(!first_alloc_size)
    {
        first_alloc_size = FIRST_ALLOC_SIZE;
    }

    XOC_StaticStringPool * pool = xoc_alloc(
        sizeof(XOC_StaticStringPool) + first_alloc_size
    );

    if (XOC_LIKELY(pool))
    {
        pool->free_pos = pool->strings;
        pool->info.free_size = first_alloc_size;
        pool->info.string_count = 0;
        pool->info.used_size = 0;
    }

    return pool;
}

void
XOC_IMPL(xoc_static_string_pool_delete)(
    XOC_StaticStringPool * pool
){
    xoc_free(pool);
}

xoc_stat_t
XOC_IMPL(xoc_static_string_pool_add)(
    XOC_StaticStringPool ** p_pool ,
    xoc_size_t              size ,
    xoc_ccstring_t          string ,
    XOC_LiteString const* * p_out_string
) {
    if (!size)
    {
        size = xoc_string_length(string) + 1;
    }
    
    // Meta
    size += sizeof(XOC_LiteString);

    XOC_StaticStringPool * pool = *p_pool;
    if (pool->info.free_size < size)
    {
        pool = xoc_realloc(pool , pool->info.allocated_size * 2);
        if (XOC_UNLIKELY(!pool))
        {
            return XOC_OUT_OF_MEMORY;
        }
        *p_pool = pool;
    }
    
    XOC_LiteString * new_string = pool->free_pos;
    new_string->length = size;
    memcpy(new_string->data , string , size);

    pool->free_pos += (size);
    pool->info.free_size -= size;
    pool->info.string_count++;

    *p_out_string = new_string;

    return XOC_OK;
}

xoc_stat_t
XOC_IMPL(xoc_static_string_pool_reserve)(
    XOC_StaticStringPool * pool ,
    xoc_size_t              size ,
);