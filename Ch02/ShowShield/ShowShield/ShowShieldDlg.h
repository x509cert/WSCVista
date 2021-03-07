// ShowShieldDlg.h : header file
//

#pragma once


// CShowShieldDlg dialog
class CShowShieldDlg : public CDialog
{
// Construction
public:
	CShowShieldDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SHOWSHIELD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
    afx_msg void OnStnClickedShield();
    afx_msg void OnBnClickedElevated();
    afx_msg void OnEnChangeEdit1();
};
