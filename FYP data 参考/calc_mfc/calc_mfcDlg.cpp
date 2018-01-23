// calc_mfcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "calc_mfc.h"
#include "calc_mfcDlg.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalc_mfcDlg dialog

CCalc_mfcDlg::CCalc_mfcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalc_mfcDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalc_mfcDlg)
	m_dNum = 0.0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalc_mfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalc_mfcDlg)
	DDX_Text(pDX, IDC_EDIT1, m_dNum);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCalc_mfcDlg, CDialog)
	//{{AFX_MSG_MAP(CCalc_mfcDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_0, OnButton0)
	ON_BN_CLICKED(IDC_BUTTON_1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON_3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON_4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON_5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON_6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON_7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON_8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON_9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DIV, OnButtonDiv)
	ON_BN_CLICKED(IDC_BUTTON_DOT, OnButtonDot)
	ON_BN_CLICKED(IDC_BUTTON_EQUAL, OnButtonEqual)
	ON_BN_CLICKED(IDC_BUTTON_MUL, OnButtonMul)
	ON_BN_CLICKED(IDC_BUTTON_SUB, OnButtonSub)
	ON_COMMAND(menu_id1, Onid1)
	ON_COMMAND(menu_id2, Onid2)
	ON_BN_CLICKED(IDC_BUTTON_AC, OnButtonAc)
	ON_BN_CLICKED(IDC_BUTTON_SQRT, OnButtonSqrt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalc_mfcDlg message handlers

BOOL CCalc_mfcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_dPre=0;
	m_dCur=0;
	m_dNext=0;
	m_strPre=_T("");
	m_strCur=_T("");
	m_strNext=_T("");
	m_nDotSign=0;
	m_nDotNo=0;

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCalc_mfcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCalc_mfcDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCalc_mfcDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCalc_mfcDlg::OnButton0() 
{
	// TODO: Add your control notification handler code here
	SetNum(0);
	
}

void CCalc_mfcDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	SetNum(1);
}

void CCalc_mfcDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	SetNum(2);
}

void CCalc_mfcDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	SetNum(3);
}

void CCalc_mfcDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	SetNum(4);
}

void CCalc_mfcDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
	SetNum(5);
}

void CCalc_mfcDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	SetNum(6);
}

void CCalc_mfcDlg::OnButton7() 
{
	// TODO: Add your control notification handler code here
	SetNum(7);
}

void CCalc_mfcDlg::OnButton8() 
{
	// TODO: Add your control notification handler code here
	SetNum(8);
}

void CCalc_mfcDlg::OnButton9() 
{
	// TODO: Add your control notification handler code here
	SetNum(9);
}

void CCalc_mfcDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	if(m_dPre==0)
	{
		m_dPre=m_dCur;
		m_strPre="+";
		m_strCur=m_strPre;
	}
	else
	{
		process();
		m_strPre="+";
		m_strCur=m_strPre;
	}
	m_dNum=m_dPre;
	m_dCur=0;
	m_nDotSign=0;
	m_nDotNo=0;
	UpdateData(false);
}

void CCalc_mfcDlg::OnButtonDiv() 
{
	// TODO: Add your control notification handler code here
		if(m_dPre==0)
	{
		m_dPre=m_dCur;
		m_strPre="/";
		m_strCur=m_strPre;
	}
	else
	{
		process();
		m_strPre="/";
		m_strCur=m_strPre;
	}
	m_dNum=m_dPre;
	m_dCur=0;
	m_nDotSign=0;
	m_nDotNo=0;
	UpdateData(false);
}

void CCalc_mfcDlg::OnButtonDot() 
{
	// TODO: Add your control notification handler code here
	m_nDotSign=1;
	m_nDotNo=1;
	
}

void CCalc_mfcDlg::OnButtonEqual() 
{
	// TODO: Add your control notification handler code here
		if(m_dPre==0)
	{
		m_dPre=m_dCur;
		m_strPre="=";
		m_strCur=m_strPre;
	}
	else
	{
		process();
		m_strPre="=";
		m_strCur=m_strPre;
	}
	m_dNum=m_dPre;
	m_dCur=0;
	m_nDotSign=0;
	m_nDotNo=0;
	UpdateData(false);
}

void CCalc_mfcDlg::OnButtonMul() 
{
	// TODO: Add your control notification handler code here
		if(m_dPre==0)
	{
		m_dPre=m_dCur;
		m_strPre="*";
		m_strCur=m_strPre;
	}
	else
	{
		process();
		m_strPre="*";
		m_strCur=m_strPre;
	}
	m_dNum=m_dPre;
	m_dCur=0;
	m_nDotSign=0;
	m_nDotNo=0;
	UpdateData(false);
}

void CCalc_mfcDlg::OnButtonSub() 
{
	// TODO: Add your control notification handler code here
		if(m_dPre==0)
	{
		m_dPre=m_dCur;
		m_strPre="-";
		m_strCur=m_strPre;
	}
	else
	{
		process();
		m_strPre="-";
		m_strCur=m_strPre;
	}
	m_dNum=m_dPre;
	m_dCur=0;
	m_nDotSign=0;
	m_nDotNo=0;
	UpdateData(false);
}

void CCalc_mfcDlg::SetNum(int i)
{
	if(m_strCur=="")
	{
		if(m_nDotSign==1)
		{
			m_dCur=m_dCur+i/(pow(10,m_nDotNo));
			m_nDotNo++;
		}
		else
			m_dCur=m_dCur*10+i;
	}
	else
	{
		m_dCur=0;
		if(m_nDotSign==1)
		{
			m_dCur=m_dCur*10+i;
		}
		else
			m_dCur=m_dCur*10+i;
	}
	m_dNum=m_dCur;
	UpdateData(false);
	m_strCur=_T("");
}

void CCalc_mfcDlg::process()
{
	if(m_strPre=="+")m_dPre+=m_dCur;
	if(m_strPre=="-")m_dPre-=m_dCur;
	if(m_strPre=="*")m_dPre*=m_dCur;
	if(m_strPre=="/")
	{
		if(m_dCur==0)m_dCur=1;
		m_dPre/=m_dCur;
	}
}





void CCalc_mfcDlg::OnButtonAc() 
{
	// TODO: Add your control notification handler code here
	m_dNum=0;
	m_dPre=0;
	m_dCur=0;
	m_dNext=0;
	m_strPre=_T("");
	m_strCur=_T("");
	m_strNext=_T("");
	m_nDotSign=0;
	m_nDotNo=0;
	UpdateData(false);
}

void CCalc_mfcDlg::OnButtonSqrt() 
{
	// TODO: Add your control notification handler code here
	m_dNum=sqrt(m_dNum);
    UpdateData(false);
}

void CCalc_mfcDlg::Onid1() 
{
	// TODO: Add your command handler code here
	OnButtonAc();
}

void CCalc_mfcDlg::Onid2() 
{
	// TODO: Add your command handler code here
	CAboutDlg dlg;
	dlg.DoModal();
}
