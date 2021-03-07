#include "stdafx.h"

HRESULT  IsSplitToken(BOOL *fIsSplit) {
    HRESULT hr = S_OK;
    HANDLE hToken = NULL;
    HANDLE hProcess = NULL;
    DWORD cbData =0;
    TOKEN_LINKED_TOKEN LinkedToken = {0};

    *fIsSplit = FALSE;

    if ((hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, GetCurrentProcessId())) != NULL) {
        if (OpenProcessToken(hProcess, TOKEN_QUERY, &hToken)) {
            if (GetTokenInformation(hToken,
                                     TokenLinkedToken,
                                     &LinkedToken,
                                     sizeof(LinkedToken),
                                     &cbData)) {
                HANDLE hSplitToken = LinkedToken.LinkedToken;
                *fIsSplit = TRUE;
            } else {
                DWORD err = GetLastError();
                if (ERROR_NO_SUCH_LOGON_SESSION  != err)
                    hr = HRESULT_FROM_WIN32(err);
            }

            CloseHandle(hToken);
        }
        else
            hr = HRESULT_FROM_WIN32(GetLastError());
        
        CloseHandle(hProcess);
    }
    else
        hr = HRESULT_FROM_WIN32(GetLastError());
    
    return hr;
}

int _tmain(int argc, _TCHAR* argv[]) {
    BOOL fSplit = 0;
    HRESULT hr = IsSplitToken(&fSplit);
    wprintf(L"Token %ls split.",fSplit ? L"is" : L"is not");
	return 0;
}

