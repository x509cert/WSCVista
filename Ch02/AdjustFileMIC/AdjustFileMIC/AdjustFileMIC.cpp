#include "stdafx.h"

void Usage() {
	wprintf(L"AdjustFileMIC <filename>");
}

int _tmain(int argc, _TCHAR* argv[]) {
	if (argc !=2) {
		Usage();
		return -1;
	}

	char bSacl[256];
	PACL pSacl = reinterpret_cast<PACL>(bSacl);
	if (!InitializeAcl(pSacl,sizeof bSacl,ACL_REVISION)) {
		wprintf(L"InitializeAcl failed %d",GetLastError());
		return -1;
	}

	DWORD dw = SetNamedSecurityInfo(
					argv[1],
					SE_FILE_OBJECT,
					LABEL_SECURITY_INFORMATION,
					NULL,NULL,NULL,
					pSacl);
	if (dw != ERROR_SUCCESS) {
		wprintf(L"Unable to open %s, error is %d\n",argv[1],dw);
		return -1;
	}

	return 0;
}

