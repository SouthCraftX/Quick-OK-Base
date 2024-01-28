#include "rand.h"
#include "../fstream/fstream.h"

XOCEAN_GLOBAL_LOCAL XOceanFile random_source;

xocean_stat_t
xocean_sys_rand_buf_init()
{
    // STOP ARGUING THE SECURITY OF /dev/urandom
    // SEE https://zhuanlan.zhihu.com/p/64680713
    return xocean_file_open(&random_source, "/dev/urandom", XOCEAN_FILE_READ);
}

void
XOCEAN_IMPL(xocean_sys_rand_buf)(
    xocean_pointer_t    buf ,
    xocean_size_t       size
){
    xocean_file_read(&random_source, buf, size);
}

void
xocean_sys_rand_buf_destory()
{
    xocean_file_close(&random_source);
}