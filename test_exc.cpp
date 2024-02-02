#include <iostream>

using namespace std;

#define IMPL(f) _##f
#define DBG(f) _##f##_dbg
#define INTERFACE(f) DBG(f)


void IMPL(foo)()
{
    cout << "impl" << '\n';
}

void DBG(foo)()
{
    cout << "dbg" << '\n';
    IMPL(foo)();
}
int main()
{
    INTERFACE(foo)();
}