#pragma once

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0600	// Change this to the appropriate value to target other versions of Windows.
#endif						

// dup definitions
#pragma warning(disable: 4005)

#include <stdio.h>
#include <tchar.h>
#include "ntstatus.h"
#include "windows.h"
#include "new"

