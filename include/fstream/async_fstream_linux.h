#include "async_fstream.h"
#include <libaio.h>
#include <fcntl.h>
#include <unistd.h>

struct _XOCAsyncFile
{
    io_context_t        io_ctx;
    struct iocb        *iocb_list;
    struct kiocb *      req;
    int                 fd;
    xoc_uint32_t     nr_events;
};
