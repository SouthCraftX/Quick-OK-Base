#include "rand.h"
#include "../fstream/fstream.h"

QO_GLOBAL_LOCAL QO_File random_source;

qo_stat_t
qo_sys_rand_buf_init()
{
    // STOP ARGUING THE SECURITY OF /dev/urandom
    // SEE https://zhuanlan.zhihu.com/p/64680713
    return qo_sysfile_open(&random_source, "/dev/urandom", QO_FILE_READ);
}

void
QO_IMPL(qo_sys_rand_buf)(
    qo_pointer_t    buf ,
    qo_size_t       size
){
    qo_sysfile_read(&random_source, buf, size);
}

void
qo_sys_rand_buf_destory()
{
    qo_sysfile_close(&random_source);
}