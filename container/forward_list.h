#pragma once
#include "../base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _XOceanForwardListNode
{
    XOceanForwardListNode * next;
    xocean_byte_t data[];
};
typedef _XOceanForwardListNode XOceanForwardListNode;

struct _XOceanForwardList
{
    XOceanClassBase base;
    XOceanForwardListNode * head;
    XOceanForwardListNode * end;
    
};


#if defined(__cplusplus)
}
#endif // __cplusplus
