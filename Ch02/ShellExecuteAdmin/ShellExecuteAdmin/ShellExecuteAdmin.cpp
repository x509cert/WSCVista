#include "stdafx.h"

#pragma comment(lib,"shell32")

int _tmain(int argc, _TCHAR* argv[]) {

    argc;
    argv;

wchar_t wszDir[MAX_PATH];
GetSystemDirectory(wszDir,_countof(wszDir));
wcscat_s(wszDir,_countof(wszDir),L"\\cmd.exe");
HINSTANCE h = ShellExecute(0,
           L"runas",
           wszDir,
           0, 
           0, 
           SW_SHOWNORMAL);
	return reinterpret_cast<int>(h);
}

