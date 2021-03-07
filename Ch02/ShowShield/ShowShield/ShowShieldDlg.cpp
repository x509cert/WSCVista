// ShowShieldDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ShowShield.h"
#include "ShowShieldDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CShowShieldDlg dialog
CShowShieldDlg::CShowShieldDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShowShieldDlg::IDD, pParent) {
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShowShieldDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CShowShieldDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDCANCEL, &CShowShieldDlg::OnBnClickedCancel)
    ON_STN_CLICKED(IDC_SHIELD, &CShowShieldDlg::OnStnClickedShield)
    ON_BN_CLICKED(IDC_ELEVATED, &CShowShieldDlg::OnBnClickedElevated)
    ON_EN_CHANGE(IDC_EDIT1, &CShowShieldDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()

BOOL IsElevated() {
    BOOL fRet = FALSE;
    TOKEN_ELEVATION Elevation;
    HANDLE hToken;
    if (OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY,&hToken)) {
        DWORD cbSize = sizeof TOKEN_ELEVATION;
        if (GetTokenInformation(hToken,
                   TokenElevation,
                   &Elevation,
                   sizeof(Elevation),
			        &cbSize)) 
            fRet = Elevation.TokenIsElevated;
    }

    return fRet;
}

BOOL CShowShieldDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

    SetIcon(m_hIcon, TRUE);
	
    SHSTOCKICONINFO si = {0};
	si.cbSize = sizeof(si);
	HRESULT hr = SHGetStockIconInfo(SIID_SHIELD, SHGSI_ICON | SHGSI_LARGEICON, &si);
	if (hr == S_OK) {
		HICON hiconShield  = si.hIcon;
        this->SetIcon(hiconShield,0);
        ((CStatic*)(GetDlgItem(IDC_SHIELD)))->SetIcon(hiconShield);
	}

    CWnd *pBtn = GetDlgItem(IDC_ELEVATED);
    Button_SetElevationRequiredState(pBtn->GetSafeHwnd(),!IsElevated());

    HWND hWnd = GetDlgItem(IDC_EDIT1)->m_hWnd;
    ::SendMessage(hWnd,
                            (UINT)EM_SETCUEBANNER,
                            !0,
                            (LPARAM)(LPCWSTR)L"Enter a command");
    GetDlgItem(IDC_EDIT1)->SetFocus();

    return FALSE;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CShowShieldDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

void CShowShieldDlg::OnBnClickedElevated() {
    CString sCmd;
    GetDlgItemTextW(IDC_EDIT1,sCmd);

    if (sCmd.GetLength() == 0)
        return;

    wchar_t wszDir[MAX_PATH];
    GetSystemDirectory(wszDir,_countof(wszDir));
    wcscat_s(wszDir,_countof(wszDir),L"\\");
    wcscat_s(wszDir,sCmd.GetBuffer());
    HINSTANCE h = 
        ShellExecute(0,
               L"runas",
               wszDir,
               0, 
               0, 
               SW_SHOWNORMAL);

    if ((int)h<=32) {
        wchar_t wszError[128];
        wsprintf(wszError,L"Failed to load %ls, error is %d.",wszDir,GetLastError());
        MessageBox(wszError,L"Oops!",MB_OK | MB_ICONEXCLAMATION);
    }
}

void CShowShieldDlg::OnEnChangeEdit1()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CShowShieldDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CShowShieldDlg::OnBnClickedCancel()
{
	OnCancel();
}

void CShowShieldDlg::OnStnClickedShield()
{
    // TODO: Add your control notification handler code here
}

