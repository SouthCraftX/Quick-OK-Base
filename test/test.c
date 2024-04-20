#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <fileapi.h>
uint64_t f(uint64_t x,uint64_t n)
{
    uint64_t mask = ((1ull<<n)-1)<<(64-n);
    for(int i = 64 - n; ~i ;--i)
    {
        if(!(x & mask)) return i;
        mask >>=1;
    }
}

int main()
{
    int s = SEEK_CUR;
    uint64_t x = 0xff00ffffffffffff;
    printf("f(x)=%llu",64-f(x,2));
}