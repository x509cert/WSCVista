#include "stdafx.h"

bool IsTokenVirtualized(__out bool& fVirt ) {
   
	HANDLE hToken = NULL;
    bool fRet = false;
	if (!OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY,&hToken))
		return fRet;

	DWORD IsVirtualized = 0;
	DWORD cbLen = 0;
	if (GetTokenInformation (
		hToken,
		TokenVirtualizationEnabled,
		&IsVirtualized,
		sizeof IsVirtualized,
		&cbLen)) {
      fVirt = !!IsVirtualized;
      fRet = true;
    }
		
	if(hToken)
       CloseHandle(hToken);

	return fRet;
}


int _tmain(int argc, _TCHAR* argv[]) {
    argc;
    argv;

    bool fVirt = false;
    if (IsTokenVirtualized(fVirt)) {
        // cool!
    }
	return 0;
}

