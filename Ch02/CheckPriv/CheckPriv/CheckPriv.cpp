#include "stdafx.h"

DWORD HasPrivilege(wchar_t *wszPriv, __out LPBOOL fResult) {

      if(!fResult || !wszPriv)
            return ERROR_INVALID_DATA;
 
      HANDLE hToken = NULL;
      HRESULT hr = ERROR_SUCCESS;

	  if(OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {

            PRIVILEGE_SET privImpersonate = {0};
            privImpersonate.PrivilegeCount = 1;
            privImpersonate.Control = PRIVILEGE_SET_ALL_NECESSARY;

            if(LookupPrivilegeValue(NULL, wszPriv, &privImpersonate.Privilege[0].Luid)) {
				if(!PrivilegeCheck(hToken, &privImpersonate, fResult)) {
					hr = GetLastError();
				}
			} else 
                  hr = GetLastError();
		   
            CloseHandle(hToken);
      } else {
            hr = GetLastError();
      }

      return hr;
}

int _tmain(int argc, _TCHAR* argv[]) {

	BOOL fRet = 0;
	wprintf(L"Privilege %S.",(HasPrivilege(SE_UNDOCK_NAME,&fRet)==ERROR_SUCCESS && fRet) ? "held" : "not held");

	return 0;
}

