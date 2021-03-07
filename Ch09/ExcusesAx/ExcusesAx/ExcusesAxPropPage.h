#pragma once

// ExcusesAxPropPage.h : Declaration of the CExcusesAxPropPage property page class.


// CExcusesAxPropPage : See ExcusesAxPropPage.cpp for implementation.

class CExcusesAxPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CExcusesAxPropPage)
	DECLARE_OLECREATE_EX(CExcusesAxPropPage)

// Constructor
public:
	CExcusesAxPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_EXCUSESAX };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

