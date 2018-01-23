//
// DropTargetDlg.cpp : implementation file
//
// (C) 2001 Reetcom / <VolkerBartheld@reetcom.de>
//

#include "stdafx.h"
#include "DropTarget.h"
#include "DropTargetDlg.h"
#include "MyDropTarget.h"

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
// CDropTargetDlg dialog

CDropTargetDlg::CDropTargetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDropTargetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDropTargetDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDropTargetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDropTargetDlg)
	DDX_Control(pDX, IDC_DROPCOMBO, m_DropComboCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDropTargetDlg, CDialog)
	//{{AFX_MSG_MAP(CDropTargetDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
  ON_MESSAGE(WM_DROPACTION, OnDropAction)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDropTargetDlg message handlers

BOOL CDropTargetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
  OleInitialize(NULL);
  BOOL br = m_DropTarget.Register(this);

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
  m_DropComboCtrl.EnableWindow(false);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDropTargetDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDropTargetDlg::OnPaint() 
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
HCURSOR CDropTargetDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



LRESULT CDropTargetDlg::OnDropAction(WPARAM wParam, LPARAM lParam)
  {
  int i, iNum;
  iNum = m_DropTarget.GetNumDroppedFiles();
  if(iNum)
    {
    m_DropComboCtrl.ResetContent();
    for(i=0; i<iNum; i++)
      {
      char* pszFileName = m_DropTarget.GetDroppedFileName(i);
      if(pszFileName) m_DropComboCtrl.AddString(pszFileName);
      free(pszFileName);
      }
    m_DropComboCtrl.SetCurSel(0);
    m_DropComboCtrl.EnableWindow(true);
    }
  else
    {
    m_DropComboCtrl.ResetContent();
    m_DropComboCtrl.EnableWindow(false);
    }

  UpdateData(false);

  return(0);
  }
