#include "stdafx.h"

#pragma comment(lib,"credui")

int _tmain(int argc, _TCHAR* argv[]) {
   CREDUI_INFO ci = {0};	
   ULONG		ulAuthPkg = 0;
   void		*pAuthBuff = NULL;
   ULONG		cbAuthBuff = 0;
   void		*pOutAuthBuff = NULL;
   ULONG		cbOutAuthBuff = 0;
   BOOL		fSave = FALSE;
   DWORD		dwFlags = CREDUIWIN_CHECKBOX;

   ci.cbSize = sizeof ci;
   ci.hbmBanner = NULL;
   ci.hwndParent = NULL;
   ci.pszCaptionText = L"Writing Secure Code for Windows Vista";
   ci.pszMessageText = L"Please enter your password";

   DWORD dwErr = CredUIPromptForWindowsCredentials(
                              &ci,
                              0,
                              &ulAuthPkg,
                              pAuthBuff,
                              cbAuthBuff,
                              &pOutAuthBuff,
                              &cbOutAuthBuff,
                              &fSave,
                              dwFlags);
   if (dwErr != 0) {
      wprintf(L"CredUI failed, err = %d\n",dwErr);
      return dwErr;
   }

    WCHAR wszUsername[CREDUI_MAX_USERNAME_LENGTH + 1];
    DWORD cchUsername = _countof(wszUsername);
    WCHAR wszPassword[CREDUI_MAX_PASSWORD_LENGTH + 1];
    DWORD cchPassword = _countof(wszPassword);
    WCHAR wszDomain[CRED_MAX_DOMAIN_TARGET_NAME_LENGTH + 1];
    DWORD cchDomain = 0;

    BOOL fOK = CredUnPackAuthenticationBuffer(
                   CRED_PACK_PROTECTED_CREDENTIALS ,             
                   pOutAuthBuff, 
                   cbOutAuthBuff, 
                   wszUsername,
                   &cchUsername,
                   wszDomain,
                   &cchDomain,
                   wszPassword,
                   &cchPassword);

    if (!fOK) {
       wprintf(L"Unpack failed, err = %d\n",GetLastError());
    } else {
       // Use the creds
       SecureZeroMemory(wszPassword,sizeof wszPassword);
    }

    if (pOutAuthBuff) {
      SecureZeroMemory(pOutAuthBuff,cbOutAuthBuff);
      CoTaskMemFree(pOutAuthBuff);
      pOutAuthBuff = NULL;
    }
                    
	return 0;
}

