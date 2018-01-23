// MyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "My.h"
#include "MyDlg.h"
#include "MyMenu.h"
#include "Frmdlg.h"
#include "MyPrint.h"
#include "MyChiToLetter.h"
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
// CMyDlg dialog

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
: CDialog(CMyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlg)
	DDX_Control(pDX, IDC_BUTTON2, m_btn2);
	DDX_Control(pDX, IDC_BUTTON1, m_btn);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
//{{AFX_MSG_MAP(CMyDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_WM_DRAWITEM()
ON_WM_MEASUREITEM()
ON_COMMAND(IDC_NEW, OnNew)
ON_COMMAND(10002, On2)
ON_COMMAND(10003, On3)
ON_COMMAND(10004, On4)
ON_COMMAND(10005, On5)
ON_COMMAND(10006, On6)
ON_COMMAND(10007, On7)
ON_WM_SHOWWINDOW()
ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
ON_WM_SIZE()
ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
ON_WM_KILLFOCUS()
	ON_COMMAND(ID_MENUITEM32811, OnMenuitem32811)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg message handlers

BOOL CMyDlg::OnInitDialog()
{
	ft.CreateFont(50,0,0,0,
	FW_NORMAL,FALSE,FALSE,FALSE,
	ANSI_CHARSET,
	OUT_DEFAULT_PRECIS,
	CLIP_DEFAULT_PRECIS,
	DEFAULT_QUALITY,
	DEFAULT_PITCH|FF_MODERN,
	"MS Sans Serif");
	CDialog::OnInitDialog();
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	m_mnu.AttachMenu(GetMenu()->GetSafeHmenu(),IDR_TOOLBAR1,CSize(16,15));
	m_mnu.m_clrTop=RGB(255,0,0);
	m_mnu.m_clrSelectLeft=RGB(100,100,100);
	m_mnu.m_clrText=RGB(0,255,255);
//	m_mnu.CheckMenuItem(ID_MENUITEM32811,MF_CHECKED);
//	m_btn.SetFlatBack(RGB(255,0,0));
 //	m_btn.SetBackColor(RGB(0,0,0));
	m_btn.SetFlatBack(RGB(255,0,0));
//	m_btn.SetBackImage(IDB_BITMAP2);
	m_btn2.SetBackColor(RGB(0,0,0));
//	m_btn.SetTextColor(RGB(255,255,255));
	m_btn2.SetTextColor(RGB(255,255,255));
//	m_btn.SetButtonFace(1);
//	m_btn.SetFont(&ft,TRUE);
	m_btn.SetXIcon(IDI_ICON2);
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, NULL);	
//	m_static1.SetFontSize(50);
//	m_static1.SetFont(&ft);
//	m_static.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON2));
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMyDlg::OnPaint() 
{		
	static BOOL bln;
	CRect rect;
	GetClientRect(&rect);
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);

		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
	CDialog::OnPaint();		
	}
//	CRect rcItem;
//	CDC *pDC=GetDlgItem(IDC_STATIC2)->GetDC();
//	if(!bln)
//	{
//	m_btn3.GetClientRect(rcItem);
//	rcItem.right=rect.right;
//	rcItem.bottom=rect.bottom;
//	m_btn3.MoveWindow(rcItem,TRUE);
// 	pDC->FillSolidRect(rcItem,RGB(255,0,0));
//	bln=TRUE;
//	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMyDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default	
//	CRect rect;
//	GetClientRect(&rect);
//		CClientDC dc2(this);
// 	dc2.FillSolidRect(rect,RGB(255,0,0));
	m_mnu.DrawItem(lpDrawItemStruct);


	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CMyDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	m_mnu.MeasureItem(lpMeasureItemStruct);
	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CMyDlg::OnNew() 
{
	MessageBox("人生苦短","");
	On2();
	On3();
	On4();
	On5();
	On6();
	On7();
}
void CMyDlg::On2() 
{
	MessageBox("不要留下遗憾","");
}
void CMyDlg::On3() 
{
	MessageBox("遇到好的女孩子","");
}
void CMyDlg::On4() 
{
	MessageBox("赶快放马过去，追呀！","");
}
void CMyDlg::On5() 
{
	MessageBox("就算是不成功","");
}
void CMyDlg::On6() 
{
	MessageBox("也不会有多丢人！","");
}
void CMyDlg::On7() 
{
	MessageBox("说完了！","我不想说了！");
}

BOOL CMyDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(wParam==10001)
	{
		MessageBox("注意了！","");
	}
	return CDialog::OnCommand(wParam, lParam);
}

void CMyDlg::OnOK() 
{
	// TODO: Add extra validation her
	//	CDialog::OnOK();
}

void CMyDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	// TODO: Add your message handler code here

}

void CMyDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	Frmdlg dlg;
	dlg.DoModal();
	Invalidate(TRUE);
}

void CMyDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_mnu.rcMain.right=cx+3;
}

void CMyDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
//	CMyPrint dlg;
//	CDC *pdc=dlg.GetMyCdc();
//	pdc->TextOut(10,10,"fadsf");
// 	pdc->EndDoc();
    CString strName, strRes;
	CMyChiToLetter ChiToletter1;
  //  strName ="中45645国24564564人民45645共和45645国";
	GetDlgItem(IDC_EDIT1)->GetWindowText(strName);
	if(strName!="")
//	ChiToletter1.m_blnSimaple=TRUE;
	ChiToletter1.m_blnFirstBig=FALSE;
	ChiToletter1.m_blnAllBiG=FALSE;
    strRes=ChiToletter1.GetLetter(strName);
	if(strRes!="") MessageBox(strRes);
}

void CMyDlg::OnKillFocus(CWnd* pNewWnd) 
{
	CDialog::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	Invalidate(TRUE);
}

void CMyDlg::OnMenuitem32811() 
{
	// TODO: Add your command handler code here
	static BOOL bln;
	bln=!bln;
	if(bln)
	m_mnu.CheckMenuItem(ID_MENUITEM32811,MF_CHECKED);
	else
	m_mnu.CheckMenuItem(ID_MENUITEM32811,MF_UNCHECKED);
}

HBRUSH CMyDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
// 	HBITMAP hbm=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),
// 		                             MAKEINTRESOURCE(IDB_BITMAP2),
// 									 IMAGE_BITMAP,
// 									 0,0,
// 									LR_CREATEDIBSECTION |LR_LOADMAP3DCOLORS);
// 	HBRUSH hbr1=CreatePatternBrush(hbm);
// 	HBRUSH hbr1=CreateSolidBrush(RGB(255,0,0));
// 	pDC->SetBkMode(TRANSPARENT);
//	return hbr1;
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
void CMyDlg::GetFirstLetter(CString strName, CString& strFirstLetter)
{
    TBYTE ucHigh, ucLow;
    int  nCode;
    CString strRet;

    strFirstLetter.Empty();
	int j=strName.GetLength();
    for (int i=0; i<strName.GetLength(); i++)
    {
        if ( (TBYTE)strName[i] < 0x80 )
		{
			strFirstLetter=strFirstLetter+strName[i];
            continue;
		}
        ucHigh = (TBYTE)strName[i];
        ucLow  = (TBYTE)strName[i+1];
        if ( ucHigh < 0xa1 || ucLow < 0xa1)
            continue;
        else
            // Treat code by section-position as an int type parameter,
            // so make following change to nCode.
            nCode = (ucHigh - 0xa0) * 100 + ucLow - 0xa0;

        FirstLetter(nCode, strRet);
        strFirstLetter += strRet;
        i++;
    }
}
void CMyDlg::FirstLetter(int nCode, CString& strLetter)
{
   if(nCode >= 1601 && nCode < 1637) strLetter = _T("A");
   if(nCode >= 1637 && nCode < 1833) strLetter = _T("B");
   if(nCode >= 1833 && nCode < 2078) strLetter = _T("C");
   if(nCode >= 2078 && nCode < 2274) strLetter = _T("D");
   if(nCode >= 2274 && nCode < 2302) strLetter = _T("E");
   if(nCode >= 2302 && nCode < 2433) strLetter = _T("F");
   if(nCode >= 2433 && nCode < 2594) strLetter = _T("G");
   if(nCode >= 2594 && nCode < 2787) strLetter = _T("H");
   if(nCode >= 2787 && nCode < 3106) strLetter = _T("J");
   if(nCode >= 3106 && nCode < 3212) strLetter = _T("K");
   if(nCode >= 3212 && nCode < 3472) strLetter = _T("L");
   if(nCode >= 3472 && nCode < 3635) strLetter = _T("M");
   if(nCode >= 3635 && nCode < 3722) strLetter = _T("N");
   if(nCode >= 3722 && nCode < 3730) strLetter = _T("O");
   if(nCode >= 3730 && nCode < 3858) strLetter = _T("P");
   if(nCode >= 3858 && nCode < 4027) strLetter = _T("Q");
   if(nCode >= 4027 && nCode < 4086) strLetter = _T("R");
   if(nCode >= 4086 && nCode < 4390) strLetter = _T("S");
   if(nCode >= 4390 && nCode < 4558) strLetter = _T("T");
   if(nCode >= 4558 && nCode < 4684) strLetter = _T("W");
   if(nCode >= 4684 && nCode < 4925) strLetter = _T("X");
   if(nCode >= 4925 && nCode < 5249) strLetter = _T("Y");
   if(nCode >= 5249 && nCode < 5590) strLetter = _T("Z");
}

void CMyDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	CFile myFile1("新建 文本文档 (2).txt",CFile::modeRead);
	CFile myFile2("text3.txt",CFile::modeCreate|CFile::modeWrite);
	CArchive arLoad(&myFile1,CArchive::load);
	CArchive arWrite(&myFile2,CArchive::store);
	CString str3;
	CString strValue;
	CString strText;
	while(str3!="END")
	{
		arLoad.ReadString(str3);
		if(str3==""||str3==" ") 
			continue;
		else if(atoi(str3)>5590)
		{		
			strValue=str3.Left(4);
			strValue="case "+strValue+":";
			arWrite.WriteString(strValue);
			arWrite.WriteString("\n");
		}
		else if(atoi(str3)>=1601&& atoi(str3)<=3167)
		{
			continue;
		}
		else
		{	
			if(strText!="")
			{	
				arWrite.WriteString(strText);
				arWrite.WriteString("\n");
				arWrite.WriteString("    break;");
				arWrite.WriteString("\n");
			}
			strText.Format("    strValue=\"%s\";",str3);
		}
	}

}
