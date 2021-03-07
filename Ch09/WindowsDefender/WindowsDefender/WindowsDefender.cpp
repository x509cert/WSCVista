#include "stdafx.h"

typedef HRESULT (WINAPI *WDSTATUS)(BOOL*);
typedef HRESULT (WINAPI *WDENABLE)(BOOL);

#pragma comment(lib, "shell32")

int _tmain(int argc, _TCHAR* argv[]) {
   argc;
   argv;

   wchar_t wszPath[MAX_PATH];
   HRESULT hr = SHGetFolderPathAndSubDir(
                        NULL,
                        CSIDL_PROGRAM_FILES,
                        NULL,
                        SHGFP_TYPE_CURRENT,
                        L"Windows Defender",
                        wszPath);
   if (FAILED(hr))
      return hr;

   wcscat_s(wszPath,MAX_PATH,L"\\MpClient.dll");

   HMODULE h = LoadLibrary(wszPath);
   if (!h) {
      DWORD dwErr = GetLastError();
      return dwErr;
   }

   WDSTATUS pfnWDStatus = (WDSTATUS)GetProcAddress(h,"WDStatus");
   WDENABLE pfnWDEnable = (WDENABLE)GetProcAddress(h,"WDEnable");

   if (pfnWDStatus && pfnWDEnable) {
      BOOL fEnabled = FALSE;
      hr = pfnWDStatus(&fEnabled);
      if (SUCCEEDED(hr)) {
         if (fEnabled) {
            wprintf(L"Windows Defender is already enabled.");
         } else {
            hr = pfnWDEnable(TRUE);
            if (SUCCEEDED(hr)) {
               wprintf(L"Windows Defender is now enabled.");
            } else {
               wprintf(L"Windows Defender failed to enabled, err = %X.",hr);
            }
         }
      }
   }

   FreeLibrary(h);
   h = NULL;

   return 0;
}

