#include "stdafx.h"

#pragma comment(lib, "urlmon")

int wmain(int argc, wchar_t* argv[]) {
   if (argc != 2) {
      wprintf(L"Please enter a URL.");
        return -1;
   }

    wchar_t *pwszUri = argv[1];

    IUri *pIUri = NULL;
    HRESULT hr = CreateUri(
        pwszUri,                    
        Uri_CREATE_ALLOW_RELATIVE,  
        0,                          
        &pIUri);

    if (SUCCEEDED(hr)) {

        BSTR bstrSchemeName;
        if (SUCCEEDED(pIUri->GetSchemeName(&bstrSchemeName))) {
            wprintf(L"Scheme: %s\n",bstrSchemeName);
            SysFreeString(bstrSchemeName);
        }

        BSTR bstrHost = NULL;
        if (SUCCEEDED(pIUri->GetHost(&bstrHost))) {
            wprintf(L"Host  : %s\n",bstrHost);
            SysFreeString(bstrHost);
        }

        DWORD dwPort=0;
        if (SUCCEEDED(pIUri->GetPort(&dwPort))) {
            wprintf(L"Port  : %d\n",dwPort);
        }
    }

    if (pIUri)
        pIUri->Release();

	return 0;
}

