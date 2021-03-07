#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	UNUSED(argc)
	UNUSED(argv)

    HANDLE hToken = NULL;
    BOOL f = OpenProcessToken(GetCurrentProcess(),TOKEN_READ,&hToken);
    if (f && hToken) {

    } else {
	    printf("Error getting token. Err=%d\n",GetLastError());
    }

    if (hToken) {
	    CloseHandle(hToken);
	    hToken = NULL;
    }

	return 0;
}

