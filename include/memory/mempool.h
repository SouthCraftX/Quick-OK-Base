#pragma once
#include "../base.h"
#include "./mimalloc/include/mimalloc.h"

#define XOCEAN_MEMPOOL_CHUCK_SIZE 16
#define XOCEAN_MEMPOOL_BLOCK_MEM_SIZE ((sizeof(xocean_size_t) << 3) * XOCEAN_MEMPOOL_CHUCK_SIZE)

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOceanMempoolBlockAssistInfo
{
    bool            full;
    xocean_uint8_t  last_alloc_end;
};
typedef struct _XOceanMempoolBlockAssistInfo XOceanMempoolBlockAssistInfo;

struct _XOceanMempoolBlock
{
    XOceanMempoolBlockAssistInfo assist_info;
    xocean_size_t bitmap;
    xocean_intmax_t mem[XOCEAN_MEMPOOL_BLOCK_MEM_SIZE];
};
typedef struct _XOceanMempoolBlock XOceanMempoolBlock;

struct _XOceanMempool
{
    XOceanMempoolBlock * head;
    XOceanMempoolBlock * next;
    XOceanMempoolBlock * prev;
};
typedef struct _XOceanMempool XOceanMempool;

XOCEAN_NODISCARD
XOceanMempoolBlock * xocean_mempool_block_new(xocean_size_t size)
{
    XOceanMempoolBlock * block = (XOceanMempoolBlock *)mi_malloc(sizeof(XOceanMempoolBlock));
    if(block)
    {
        block->assist_info.full = false;
        block->assist_info.last_alloc_end = 0;
        block->bitmap = 0;
    }
    return block;
}

XOCEAN_FORCE_INLINE
void xocean_mempool_block_delete(XOceanMempoolBlock * block)
{
    mi_free(block);
}

XOCEAN_NODISCARD XOCEAN_FORCE_INLINE
bool xocean_mempool_block_is_full(XOceanMempoolBlock * block)
{
    return (block->bitmap == XOCEAN_SIZE_T_MAX);
}




#if defined(__cplusplus)
}
#endif // __cplusplus

