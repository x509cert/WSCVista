// ExcusesAxCtrl.cpp : Implementation of the CExcusesAxCtrl ActiveX Control class.

#include "stdafx.h"
#include "ExcusesAx.h"
#include "ExcusesAxCtrl.h"
#include "ExcusesAxPropPage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CExcusesAxCtrl, COleControl)



// Message map

BEGIN_MESSAGE_MAP(CExcusesAxCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()



// Dispatch map

BEGIN_DISPATCH_MAP(CExcusesAxCtrl, COleControl)
   DISP_FUNCTION_ID(CExcusesAxCtrl, "Excuse", dispidExcuse, Excuse, VT_BSTR, VTS_NONE)
END_DISPATCH_MAP()



// Event map

BEGIN_EVENT_MAP(CExcusesAxCtrl, COleControl)
END_EVENT_MAP()



// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CExcusesAxCtrl, 1)
	PROPPAGEID(CExcusesAxPropPage::guid)
END_PROPPAGEIDS(CExcusesAxCtrl)



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CExcusesAxCtrl, "EXCUSESAX.ExcusesAxCtrl.1",
	0x20b97d1a, 0x2cc7, 0x451e, 0x9b, 0x6c, 0x2c, 0x70, 0x2f, 0x2b, 0x69, 0xf)



// Type library ID and version

IMPLEMENT_OLETYPELIB(CExcusesAxCtrl, _tlid, _wVerMajor, _wVerMinor)



// Interface IDs

const IID BASED_CODE IID_DExcusesAx =
		{ 0xA8B105B4, 0x1272, 0x484D, { 0xB9, 0x74, 0x41, 0x8, 0x6, 0x1D, 0x8E, 0x41 } };
const IID BASED_CODE IID_DExcusesAxEvents =
		{ 0x51837D80, 0x92C2, 0x47DF, { 0x98, 0x85, 0x56, 0xE2, 0xD0, 0xC6, 0x62, 0xC7 } };



// Control type information

static const DWORD BASED_CODE _dwExcusesAxOleMisc =
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CExcusesAxCtrl, IDS_EXCUSESAX, _dwExcusesAxOleMisc)



// CExcusesAxCtrl::CExcusesAxCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CExcusesAxCtrl

BOOL CExcusesAxCtrl::CExcusesAxCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_EXCUSESAX,
			IDB_EXCUSESAX,
			afxRegApartmentThreading,
			_dwExcusesAxOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CExcusesAxCtrl::CExcusesAxCtrl - Constructor

CExcusesAxCtrl::CExcusesAxCtrl()
{
	InitializeIIDs(&IID_DExcusesAx, &IID_DExcusesAxEvents);
	// TODO: Initialize your control's instance data here.
}



// CExcusesAxCtrl::~CExcusesAxCtrl - Destructor

CExcusesAxCtrl::~CExcusesAxCtrl()
{
	// TODO: Cleanup your control's instance data here.
}



// CExcusesAxCtrl::OnDraw - Drawing function

void CExcusesAxCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}



// CExcusesAxCtrl::DoPropExchange - Persistence support

void CExcusesAxCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
}



// CExcusesAxCtrl::GetControlFlags -
// Flags to customize MFC's implementation of ActiveX controls.
//
DWORD CExcusesAxCtrl::GetControlFlags()
{
	DWORD dwFlags = COleControl::GetControlFlags();


	// The control can activate without creating a window.
	// TODO: when writing the control's message handlers, avoid using
	//		the m_hWnd member variable without first checking that its
	//		value is non-NULL.
	dwFlags |= windowlessActivate;
	return dwFlags;
}



// CExcusesAxCtrl::OnResetState - Reset control to default state

void CExcusesAxCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}



// CExcusesAxCtrl message handlers

BSTR CExcusesAxCtrl::Excuse(void)
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());

   CString strResult;

   // TODO: Add your dispatch handler code here

   return strResult.AllocSysString();
}
