#include "stdafx.h"

DWORD GetProcessIntegrityLevel(wchar_t __out_ecount_z(cbIl) *wszIl, 
                               size_t cbIl) {
    if (!wszIl) return 0xffffffff;

    memset(wszIl,0,cbIl);

    DWORD err = 0;

    try {

        HANDLE hToken = NULL;
        if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) 
            throw GetLastError();
        
        DWORD cbBuf = 0;
        if (GetTokenInformation(hToken,TokenIntegrityLevel,NULL,0,&cbBuf) != 0)
            throw GetLastError();
            
        TOKEN_MANDATORY_LABEL * pTml = 
            reinterpret_cast<TOKEN_MANDATORY_LABEL*> (new char[cbBuf]);
        if (pTml && 
            GetTokenInformation(
                        hToken,
                        TokenIntegrityLevel,
                        pTml,
                        cbBuf,
                        &cbBuf)) {

            CloseHandle(hToken);
            hToken = NULL;

            DWORD ridIl = *GetSidSubAuthority(pTml->Label.Sid, 0);

            if (ridIl < SECURITY_MANDATORY_LOW_RID)
                wcscpy_s(wszIl,cbIl,L"?");

            else if (ridIl >= SECURITY_MANDATORY_LOW_RID && ridIl < SECURITY_MANDATORY_MEDIUM_RID)
                wcscpy_s(wszIl,cbIl,L"Low");

            else if (ridIl >= SECURITY_MANDATORY_MEDIUM_RID && ridIl < SECURITY_MANDATORY_HIGH_RID)
                wcscpy_s(wszIl,cbIl,L"Medium");

            else if (ridIl >= SECURITY_MANDATORY_HIGH_RID && ridIl < SECURITY_MANDATORY_SYSTEM_RID)
                wcscpy_s(wszIl,cbIl,L"High");

            else if (ridIl >= SECURITY_MANDATORY_SYSTEM_RID)
                wcscpy_s(wszIl,cbIl,L"System");

            if (ridIl > SECURITY_MANDATORY_LOW_RID && 
                ridIl != SECURITY_MANDATORY_MEDIUM_RID && 
                ridIl != SECURITY_MANDATORY_HIGH_RID && 
                ridIl != SECURITY_MANDATORY_SYSTEM_RID)
                wcscat_s(wszIl,cbIl,L"+");

            delete [] reinterpret_cast<char*>(pTml);
            pTml = NULL;
        } else {
            throw GetLastError();
        }

    } catch(DWORD dwErr) {
        err = dwErr;
        wprintf(L"Error %d",GetLastError());
    } catch(std::bad_alloc e) {
        err = ERROR_OUTOFMEMORY;
        wprintf(L"Error %d",err);
    }

    return err;
}

int _tmain(int argc, _TCHAR* argv[]) {
    argc;
    argv;

    wchar_t il[32];
    size_t  cbIl = 32;
    if (GetProcessIntegrityLevel(il,cbIl) == 0)
        wprintf(L"Integrity lebel is %ls",il);
	return 0;
}

