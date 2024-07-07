#include "include/thread.h"
#include <sched.h>
#include <pthread.h>


int
__xoc_thread_adjust_high_priority(
    XOC_Thread                thread ,
    enum XOC_ThreadPriority   priority
){
    const int crazy = sched_get_priority_max(SCHED_RR) ,
              highest = crazy * .8 ,
              high = highest >> 1;
    int priority_value;
    
    switch (priority)
    {   
        case XOC_THREAD_PRIORITY_CRAZY:      
            priority_value = crazy; 
            break;

        case XOC_THREAD_PRIORITY_HIGHEST:    
            priority_value = highest; 
            break;

        case XOC_THREAD_PRIORITY_HIGH:
            priority_value = high; 
            break;
    }
    int ret = pthread_setschedparam(thread.thread_handle , SCHED_RR , priority_value);

}

xoc_stat_t
XOC_IMPL(xoc_thread_adjust_priority)(
    XOC_Thread                thread ,
    enum XOC_ThreadPriority   priority
){
    
}