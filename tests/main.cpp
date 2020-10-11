#include <iostream>

#include "libinject.h"

int main()
{
    if (!inject(
        99999,                      // process id     
        "C:\\path\\to\\mylib.dll",  // path to dll
        false                       // handle elevation
    ))
    {
        printf("[!] injection failed GetLastError: (0x%lX)\n",
            GetLastError());
        return -1;
    }

    printf("[+] injected successfully!\n");
    return 0;
}