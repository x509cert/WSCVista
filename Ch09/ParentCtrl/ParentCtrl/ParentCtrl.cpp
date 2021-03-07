#include "stdafx.h"

HRESULT SidStringFromUserName(PCWSTR pcszUserName, PWSTR* ppszSID) {
    HRESULT hr = E_INVALIDARG;

    if (!pcszUserName && !ppszSID)
        return E_INVALIDARG;

    DWORD cbSID = 0, cchDomain = 0;
    SID_NAME_USE SidNameUse;

    // Call twice, first with null SID buffer.  
    // Retrieves required buffer size for account name
    LookupAccountNameW(NULL, pcszUserName, NULL, &cbSID, NULL, 
        &cchDomain, &SidNameUse);
    if (!cbSID || !cchDomain) {
        hr = E_FAIL;
    } else {
        WCHAR* pszDomain = NULL;
        pszDomain = new WCHAR[cchDomain];
        if (!pszDomain) {
            hr = E_OUTOFMEMORY;
        } else {
            PSID pSID = static_cast<PSID> (new BYTE[cbSID]); 
            if (!pSID) {
                hr = E_OUTOFMEMORY;
            } else {
                // Second call with buffers allocated and sizes set
                if (!LookupAccountName(NULL, pcszUserName, pSID, &cbSID,
                    pszDomain, &cchDomain, &SidNameUse)) {
                    hr = HRESULT_FROM_WIN32(GetLastError());
                } else {
                    // Convert PSID to SID string
                    if (!ConvertSidToStringSidW(pSID, ppszSID)) {
                        hr = HRESULT_FROM_WIN32(GetLastError());
                    } else {
                        hr = S_OK;
                    }
                }
                delete[] pSID; 
            }
            delete[] pszDomain;
        }
    }

    return hr;
}

int wmain(int argc, WCHAR* argv[]) {

    if (argc != 2 || !argv[1])
        return -1;

    PWSTR pwszSid = NULL;
    if (FAILED(SidStringFromUserName(argv[1],&pwszSid)))
        return -1;

    if (FAILED(CoInitialize(NULL)))
        return -1;

    CComPtr<IWindowsParentalControls> piWPC = NULL;
    HRESULT hr = piWPC.CoCreateInstance(__uuidof(WindowsParentalControls));
    if (SUCCEEDED(hr)) {
        //CComPtr<IWPCWebSettings> spiWeb;
        IWPCSettings* piWPCUserSettings  = NULL;
        hr = piWPC->GetUserSettings(pwszSid,&piWPCUserSettings);
        if (E_ACCESSDENIED == hr) {
            // user is probably an admin
        } else if (SUCCEEDED(hr)){
            BOOL fLoggingRequired = TRUE;
            hr = piWPCUserSettings->IsLoggingRequired(&fLoggingRequired);

			// determine if we need to wait for time limit events
			DWORD dwRestrictions = 0;
			hr = piWPCUserSettings->GetRestrictions(&dwRestrictions);
			if (SUCCEEDED(hr)) {
				if (dwRestrictions & WPCFLAG_HOURS_RESTRICTED) {
					wprintf(L"Hour restrictions\n");
				}

				if (dwRestrictions & WPCFLAG_WEB_SETTING_DOWNLOADSBLOCKED) {
					wprintf(L"Downloads restrictions\n");
				}
            }
        }
    }

    CoUninitialize();

    return 0;
}
