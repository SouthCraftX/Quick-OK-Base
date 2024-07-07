#pragma once
#include "../base.h"
#include "./mimalloc/include/mimalloc.h"

#define XOC_MEMPOOL_CHUCK_SIZE 16
#define XOC_MEMPOOL_BLOCK_MEM_SIZE ((sizeof(xoc_size_t) << 3) * XOC_MEMPOOL_CHUCK_SIZE)

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOCMempoolBlockAssistInfo
{
    bool            full;
    xoc_uint8_t  last_alloc_end;
};
typedef struct _XOCMempoolBlockAssistInfo XOCMempoolBlockAssistInfo;

struct _XOCMempoolBlock
{
    XOCMempoolBlockAssistInfo assist_info;
    xoc_size_t bitmap;
    xoc_intmax_t mem[XOC_MEMPOOL_BLOCK_MEM_SIZE];
};
typedef struct _XOCMempoolBlock XOCMempoolBlock;

struct _XOCMempool
{
    XOCMempoolBlock * head;
    XOCMempoolBlock * next;
    XOCMempoolBlock * prev;
};
typedef struct _XOCMempool XOCMempool;

XOC_NODISCARD
XOCMempoolBlock * xoc_mempool_block_new(xoc_size_t size)
{
    XOCMempoolBlock * block = (XOCMempoolBlock *)mi_malloc(sizeof(XOCMempoolBlock));
    if(block)
    {
        block->assist_info.full = false;
        block->assist_info.last_alloc_end = 0;
        block->bitmap = 0;
    }
    return block;
}

XOC_FORCE_INLINE
void xoc_mempool_block_delete(XOCMempoolBlock * block)
{
    mi_free(block);
}

XOC_NODISCARD XOC_FORCE_INLINE
bool xoc_mempool_block_is_full(XOCMempoolBlock * block)
{
    return (block->bitmap == XOC_SIZE_T_MAX);
}




#if defined(__cplusplus)
}
#endif // __cplusplus

