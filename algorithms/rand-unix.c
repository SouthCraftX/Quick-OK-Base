#include "rand.h"
#include "../fstream/fstream.h"

XOC_GLOBAL_LOCAL XOC_File random_source;

xoc_stat_t
xoc_sys_rand_buf_init()
{
    // STOP ARGUING THE SECURITY OF /dev/urandom
    // SEE https://zhuanlan.zhihu.com/p/64680713
    return xoc_file_open(&random_source, "/dev/urandom", XOC_FILE_READ);
}

void
XOC_IMPL(xoc_sys_rand_buf)(
    xoc_pointer_t    buf ,
    xoc_size_t       size
){
    xoc_file_read(&random_source, buf, size);
}

void
xoc_sys_rand_buf_destory()
{
    xoc_file_close(&random_source);
}