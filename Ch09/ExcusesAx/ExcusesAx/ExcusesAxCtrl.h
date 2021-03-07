#pragma once

// ExcusesAxCtrl.h : Declaration of the CExcusesAxCtrl ActiveX Control class.


// CExcusesAxCtrl : See ExcusesAxCtrl.cpp for implementation.

class CExcusesAxCtrl : public COleControl
{
	DECLARE_DYNCREATE(CExcusesAxCtrl)

// Constructor
public:
	CExcusesAxCtrl();

// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual DWORD GetControlFlags();

// Implementation
protected:
	~CExcusesAxCtrl();

	DECLARE_OLECREATE_EX(CExcusesAxCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CExcusesAxCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CExcusesAxCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CExcusesAxCtrl)		// Type name and misc status

// Message maps
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	DECLARE_DISPATCH_MAP()

// Event maps
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
      dispidExcuse = 1L
   };
protected:
   BSTR Excuse(void);
};

