#pragma once
#include "../base.h"
#include "./mimalloc/include/mimalloc.h"

#define QO_MEMPOOL_CHUCK_SIZE 16
#define QO_MEMPOOL_BLOCK_MEM_SIZE ((sizeof(qo_size_t) << 3) * QO_MEMPOOL_CHUCK_SIZE)

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _QOMempoolBlockAssistInfo
{
    bool            full;
    qo_uint8_t  last_alloc_end;
};
typedef struct _QOMempoolBlockAssistInfo QOMempoolBlockAssistInfo;

struct _QOMempoolBlock
{
    QOMempoolBlockAssistInfo assist_info;
    qo_size_t bitmap;
    qo_intmax_t mem[QO_MEMPOOL_BLOCK_MEM_SIZE];
};
typedef struct _QOMempoolBlock QOMempoolBlock;

struct _QOMempool
{
    QOMempoolBlock * head;
    QOMempoolBlock * next;
    QOMempoolBlock * prev;
};
typedef struct _QOMempool QOMempool;

QO_NODISCARD
QOMempoolBlock * qo_mempool_block_new(qo_size_t size)
{
    QOMempoolBlock * block = (QOMempoolBlock *)mi_malloc(sizeof(QOMempoolBlock));
    if (block)
    {
        block->assist_info.full = false;
        block->assist_info.last_alloc_end = 0;
        block->bitmap = 0;
    }
    return block;
}

QO_FORCE_INLINE
void qo_mempool_block_delete(QOMempoolBlock * block)
{
    mi_free(block);
}

QO_NODISCARD QO_FORCE_INLINE
bool qo_mempool_block_is_full(QOMempoolBlock * block)
{
    return (block->bitmap == QO_SIZE_T_MAX);
}




#if defined(__cplusplus)
}
#endif // __cplusplus

