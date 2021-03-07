// ExcusesAx.cpp : Implementation of CExcusesAxApp and DLL registration.

#include "stdafx.h"
#include "ExcusesAx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CExcusesAxApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x42C2C810, 0x17D, 0x4FF5, { 0xBF, 0xFE, 0xE6, 0x2F, 0xA0, 0xD0, 0xDB, 0xFE } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CExcusesAxApp::InitInstance - DLL initialization

BOOL CExcusesAxApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CExcusesAxApp::ExitInstance - DLL termination

int CExcusesAxApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
