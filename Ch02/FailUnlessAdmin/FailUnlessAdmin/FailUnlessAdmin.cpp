#include "stdafx.h"

BOOL IsProcessVirtualized(__out BOOL *fVirt) {
	if (!fVirt) return false;
	
	HANDLE hToken = NULL;
	if (!OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY,&hToken))
		return false;

	DWORD IsVirtualized = 0;
	DWORD cbLen = 0;
	if (!GetTokenInformation(
		hToken,
		TokenVirtualizationEnabled,
		&IsVirtualized,
		sizeof IsVirtualized,
		&cbLen))
		return false;

	*fVirt = IsVirtualized ? true : false;

	return true;
}

int _tmain(int argc, _TCHAR* argv[]) {
	argc;
	argv;

	BOOL fVirt = FALSE;
	if (IsProcessVirtualized(&fVirt))
		wprintf(L"This process %s virtualized.\n",fVirt ? L"is" : L"is not");

	wchar_t szPath[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, 
                             CSIDL_PROGRAM_FILES, 
                             NULL, 
                             0, 
                             szPath))) {

		PathAppend(szPath, L"Savedgame2.xml");
		HANDLE hFile = CreateFile(
							szPath,
							GENERIC_WRITE | GENERIC_READ,
							0,
							NULL,
							CREATE_ALWAYS,
							FILE_ATTRIBUTE_NORMAL,
							NULL);

		if (hFile == INVALID_HANDLE_VALUE ) {
            wprintf(L"Failed!");
		} else {
            wprintf(L"Success!");
			CloseHandle(hFile);
			hFile = NULL;
		}
	}

	return 0;
}

