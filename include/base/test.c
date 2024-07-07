#   warning "Warning:Your compiler is not recommanded, which means you may encounter some problems."
#   warning "Missing feature for `likely`, `unlikely`, `noinline`, `export` and `import`"
#   warning "`inline`and `fallthrough` may not work as expected."
#include <stdio.h>
#include "macros.h"
int main()
{
    printf("32bit:%i",XOC_SYSTEM_BIT(32));
    printf("\n64bit:%i",XOC_SYSTEM_BIT(64));
    printf("le:%i",XOC_ENDIAN(LITTLE));
}