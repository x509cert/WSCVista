// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0600	// Change this to the appropriate value to target other versions of Windows.
#endif						

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

#include <atlbase.h>
#include <atlstr.h>
#include <msfeeds.h>



// TODO: reference additional headers your program requires here
