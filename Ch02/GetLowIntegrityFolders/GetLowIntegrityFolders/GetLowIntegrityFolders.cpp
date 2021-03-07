#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[]) {
    wchar_t *wszPath;
    SHGetKnownFolderPath(
        FOLDERID_LocalAppDataLow,
        //FOLDERID_LocalAppData,
        KF_FLAG_DEFAULT_PATH,
        NULL,
        &wszPath);

    wprintf(L"%ls",wszPath);
    // path is in wszPath

    CoTaskMemFree (wszPath);

    _getch();
	return 0;
}

