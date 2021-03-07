// ExcusesAxPropPage.cpp : Implementation of the CExcusesAxPropPage property page class.

#include "stdafx.h"
#include "ExcusesAx.h"
#include "ExcusesAxPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CExcusesAxPropPage, COlePropertyPage)



// Message map

BEGIN_MESSAGE_MAP(CExcusesAxPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CExcusesAxPropPage, "EXCUSESAX.ExcusesAxPropPage.1",
	0x5af9269b, 0xe158, 0x43cc, 0x8a, 0xb5, 0x7, 0x1b, 0xca, 0x89, 0x8a, 0x19)



// CExcusesAxPropPage::CExcusesAxPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CExcusesAxPropPage

BOOL CExcusesAxPropPage::CExcusesAxPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_EXCUSESAX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CExcusesAxPropPage::CExcusesAxPropPage - Constructor

CExcusesAxPropPage::CExcusesAxPropPage() :
	COlePropertyPage(IDD, IDS_EXCUSESAX_PPG_CAPTION)
{
}



// CExcusesAxPropPage::DoDataExchange - Moves data between page and properties

void CExcusesAxPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CExcusesAxPropPage message handlers
