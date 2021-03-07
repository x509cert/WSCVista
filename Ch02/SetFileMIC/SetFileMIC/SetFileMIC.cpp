#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[]) {
	argc;
	argv;

    SECURITY_ATTRIBUTES sa = {0};
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = FALSE;
    wchar_t *szSacl = L"S:(ML;;NW;;;LO)";

    if (ConvertStringSecurityDescriptorToSecurityDescriptor(
        szSacl,
        SDDL_REVISION_1, 
        &(sa.lpSecurityDescriptor), 
        NULL)) {
		    wchar_t *szFilename = L"foo.txt";
		    HANDLE h = CreateFile(szFilename,
					    GENERIC_WRITE,
					    0,
					    &sa,
					    CREATE_ALWAYS,
					    0,
					    NULL);
		    if (INVALID_HANDLE_VALUE == h) {
			    wprintf(L"CreateFile failed (%d)", GetLastError());
		    } else {
                char *szT = "Hello, World!";
                DWORD cb = 0;
                WriteFile(h,szT,strlen(szT)+1,&cb,NULL);
			    CloseHandle(h);
			    h = NULL;
		    }
    } else {
	    wprintf(L"SDDL Conversion failed (%d)", GetLastError());
    }
				
	return 0;
}

