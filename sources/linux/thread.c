#include "include/thread.h"
#include <sched.h>
#include <pthread.h>


int
__xocean_thread_adjust_high_priority(
    XOceanThread                thread ,
    enum XOceanThreadPriority   priority
){
    const int crazy = sched_get_priority_max(SCHED_RR) ,
              highest = crazy * .8 ,
              high = highest >> 1;
    int priority_value;
    
    switch (priority)
    {   
        case XOCEAN_THREAD_PRIORITY_CRAZY:      
            priority_value = crazy; 
            break;

        case XOCEAN_THREAD_PRIORITY_HIGHEST:    
            priority_value = highest; 
            break;

        case XOCEAN_THREAD_PRIORITY_HIGH:
            priority_value = high; 
            break;
    }
    int ret = pthread_setschedparam(thread.thread_handle , SCHED_RR , priority_value);

}

xocean_stat_t
XOCEAN_IMPL(xocean_thread_adjust_priority)(
    XOceanThread                thread ,
    enum XOceanThreadPriority   priority
){
    
}