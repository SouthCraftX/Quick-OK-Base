#include "static_string_pool.h"
#include "memalloc.h"
#include "stringset.h"

#include <stdlib.h>

#define FIRST_ALLOC_SIZE 128

struct _QO_StaticStringPool 
{
    QO_StaticStringPoolInfo    info;
    QO_LiteString *            free_pos;
    QO_LiteString              strings[];
};

QO_StaticStringPool *
QO_IMPL(qo_static_string_pool_new)(
    qo_size_t  first_alloc_size
){
    if(!first_alloc_size)
    {
        first_alloc_size = FIRST_ALLOC_SIZE;
    }

    QO_StaticStringPool * pool = qo_alloc(
        sizeof(QO_StaticStringPool) + first_alloc_size
    );

    if (QO_LIKELY(pool))
    {
        pool->free_pos = pool->strings;
        pool->info.free_size = first_alloc_size;
        pool->info.string_count = 0;
        pool->info.used_size = 0;
    }

    return pool;
}

void
QO_IMPL(qo_static_string_pool_delete)(
    QO_StaticStringPool * pool
){
    qo_free(pool);
}

qo_stat_t
QO_IMPL(qo_static_string_pool_add)(
    QO_StaticStringPool ** p_pool ,
    qo_size_t              size ,
    qo_ccstring_t          string ,
    QO_LiteString const* * p_out_string
) {
    if (!size)
    {
        size = qo_string_length(string) + 1;
    }
    
    // Meta
    size += sizeof(QO_LiteString);

    QO_StaticStringPool * pool = *p_pool;
    if (pool->info.free_size < size)
    {
        pool = qo_realloc(pool , pool->info.allocated_size * 2);
        if (QO_UNLIKELY(!pool))
        {
            return QO_OUT_OF_MEMORY;
        }
        *p_pool = pool;
    }
    
    QO_LiteString * new_string = pool->free_pos;
    new_string->length = size;
    memcpy(new_string->data , string , size);

    pool->free_pos += (size);
    pool->info.free_size -= size;
    pool->info.string_count++;

    *p_out_string = new_string;

    return QO_OK;
}

qo_stat_t
QO_IMPL(qo_static_string_pool_reserve)(
    QO_StaticStringPool * pool ,
    qo_size_t              size ,
);