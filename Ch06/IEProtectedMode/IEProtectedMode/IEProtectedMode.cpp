#include "stdafx.h"

#pragma comment(lib, "iepmapi")

HRESULT WriteHKCUSetting(__in_z wchar_t *pwszKey, 
                         __in_z wchar_t *pwszValue, 
                         __in_z wchar_t *pwszData) {

   BOOL bIsProtected = FALSE;
   HRESULT hr = IEIsProtectedModeProcess(&bIsProtected);
   if (SUCCEEDED(hr) && bIsProtected) {
      HKEY hLowKey = NULL;
      hr = IEGetWriteableHKCU(&hLowKey);
      if (SUCCEEDED(hr)) {
         HKEY hMyKey = NULL;
         DWORD dwDisposition = 0;
         LONG lRes = RegCreateKeyEx(
              hLowKey,      
              pwszKey,       
              0L,           
              NULL,         
              REG_OPTION_NON_VOLATILE,
              KEY_SET_VALUE,
              NULL,         
              &hMyKey,      
              &dwDisposition);
         
         if (ERROR_SUCCESS == lRes) {
            lRes = RegSetValueEx(hMyKey, 
                            pwszValue, 
                            NULL, 
                            REG_SZ,
                            (CONST BYTE*)pwszData, 
                            wcslen(pwszData + 1));
            hr = HRESULT_FROM_WIN32(lRes);
            
            RegCloseKey(hMyKey);
         } else {
            hr = HRESULT_FROM_WIN32(lRes);
         }
         
         // Close the low-integrity handle
         RegCloseKey(hLowKey);   
      }
   } else {
      // IE not in protected mode
   }

   return hr;
}

HRESULT LaunchIE(__in_z LPCWSTR pszURL) {
  PROCESS_INFORMATION pProcInfo;
  HRESULT hr = IELaunchURL(pszURL, &pProcInfo, NULL);
  if (SUCCEEDED(hr)) {
    CloseHandle(pProcInfo.hProcess);
    CloseHandle(pProcInfo.hThread);
  }
  return hr;
}

int main(int argc, char **argv) {
    LaunchIE(L"http://www.microsoft.com");
}
