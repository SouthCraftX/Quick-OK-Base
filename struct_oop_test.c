#include <stdio.h>
#include <stdlib.h>

struct methods{
    struct methods* (*foo)(struct methods* , int);
    struct methods* (*bar)(struct methods* , int);
    struct methods* (*baz)(struct methods* , int);
};
typedef struct methods*(*fn_t)(struct methods* , int);

struct methods * Foo( struct methods* m, int x)
{
    printf("Foo: %d\n" , x);
    return m;
}

struct methods * Bar( struct methods* m, int x)
{
    printf("Bar: %d\n" , x);
    return m;
}

struct methods * Baz( struct methods* m, int x)
{
    printf("Baz: %d\n" , x);
    return m;
}
int main()
{
    struct methods m = { .foo = Foo , .bar = Bar , .baz = Baz};
    struct methods *p = &m;
    p->foo(p , 5)
     ->bar(p , 10)
     ->baz(p , 15);
}