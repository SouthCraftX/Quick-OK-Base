#include <iostream>
#include <cstdlib>
#include <windows.h>

using namespace std;

int main()
{
    size_t sz = 0xffffffff;
    DWORD rd;
    void * m = malloc(sz);

    if(!m)
    {
        cout << "alloc failed";
        abort();
    }
    HANDLE file = CreateFileW(L"H:/la", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if(file == INVALID_HANDLE_VALUE)
    {
        cout << "open file failed";
        free(m);
        abort();
    }

    ReadFile(file , m , sz , &rd , NULL);
    cout << "read " << rd << " bytes" << endl;
    cin.get(   );
    free(m);
}
