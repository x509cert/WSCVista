#include "stdafx.h"

////////////////////////////////////////////////////////////////////
void ShowApiError(__in_z const wchar_t *wszError) {
    wprintf(L"%ls failed. Error = %d",wszError,GetLastError());
}

static bool IsThisVista() {
   OSVERSIONINFO rInfo;
	rInfo.dwOSVersionInfoSize = sizeof(rInfo);
	if (!::GetVersionEx(&rInfo))
		return false;

	return rInfo.dwMajorVersion >= 6;
}

////////////////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[]) {
    if (!IsThisVista()) {
        wprintf(L"This tool runs only on Windows Vista and later.");
        return -1;
    }

    bool fVerbose = false;
    if (argc==2 && *argv[1]==L'-' && *++argv[1]==L'v')
        fVerbose = true;

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, GetCurrentProcessId());
    if (hProcess == NULL) {
        ShowApiError(L"OpenProcess");
        return -1;
    }

    HANDLE hToken = NULL;
    if (!OpenProcessToken(hProcess, TOKEN_QUERY, &hToken)) {
        ShowApiError(L"OpenProcessToken");
    }

    DumpToken(hToken,fVerbose);
    HANDLE hLinkedToken = HandleLinkedToken(hToken);
    if (hLinkedToken)
        DumpToken(hLinkedToken,fVerbose);

    if (hToken)
        CloseHandle(hToken);

    if (hProcess)
        CloseHandle(hProcess);


	return 0;
}

