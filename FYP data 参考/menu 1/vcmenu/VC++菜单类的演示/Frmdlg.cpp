// Frmdlg.cpp : implementation file
//

#include "stdafx.h"
#include "my.h"
#include "Frmdlg.h"
#include "MyTime.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Frmdlg dialog


Frmdlg::Frmdlg(CWnd* pParent /*=NULL*/)
	: CDialog(Frmdlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(Frmdlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Frmdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Frmdlg)
	DDX_Control(pDX, IDC_LIST2, m_listcol);
	DDX_Control(pDX, IDC_LIST1, m_listMain);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDOK, m_btn4);
	DDX_Control(pDX, IDCANCEL, m_btn3);
	DDX_Control(pDX, IDC_BUTTON2, m_btn2);
	DDX_Control(pDX, IDC_BUTTON1, m_btn1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Frmdlg, CDialog)
	//{{AFX_MSG_MAP(Frmdlg)
	ON_WM_SIZE()
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_NOTIFY(TBN_DROPDOWN, AFX_IDW_TOOLBAR, OnToolbarDropDown)//add by yh
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Frmdlg message handlers

BOOL Frmdlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_menu.AttachMenu(GetMenu()->GetSafeHmenu(),IDR_TOOLBAR1,CSize(16,16));
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_TOOLBAR2))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_menu.EnableMenuItem(IDC_NEW,MF_GRAYED);
	RECT rt,rtMain;
	GetWindowRect(&rtMain);
	rt.left=0;
	rt.top=0;
	rt.bottom=60;
	rt.right=rtMain.right-rtMain.left+10;
	m_wndToolBar.MoveWindow(&rt,TRUE);
 	m_wndToolBar.SetDefaultStyle();
//	m_wndToolBar.SetBKImage(IDB_BITMAP4);
//	m_menu.AddToolBar(IDR_TOOLBAR1,CSize(16,15));
//	m_wndToolBar.SetBKImage(IDB_BITMAP1);
	m_btn1.SetButtonFace(1);
	m_btn2.SetButtonFace(2);
	//m_wndToolBar.SetBKColor(RGB(255,0,0));
 //	m_menu.SetTopBack(RGB(255,0,0));
	m_edit.SetClassType(edit_time);
//	m_menu.SetTopBackImage(IDB_BITMAP4);
//	m_menu.SetTopBack(RGB(255,0,0));
//  	m_btn1.SetBackColor(RGB(255,0,0));
//  	m_btn2.SetBackColor(RGB(255,0,0));
//  	m_btn3.SetBackColor(RGB(255,0,0));
// 	m_btn4.SetBackColor(RGB(255,0,0));
	m_btn1.SetTextColor(RGB(100,255,100));
	m_edit.SetNow();
	m_listMain.InsertColumnX("fff",LVCFMT_LEFT,50,ctr_Edit_Text);
	m_listMain.InsertColumnX("fff",LVCFMT_CENTER,50,ctr_Edit_Text);
	m_listMain.InsertColumnX("gg",LVCFMT_CENTER,50,ctr_Edit_CboDownList);
	m_listMain.InsertColumnX("hh",LVCFMT_RIGHT,50,ctr_Edit_Date);
	m_listMain.InsertColumnX("ll",LVCFMT_RIGHT,50,ctr_Edit_DateTime);
	m_listMain.InsertColumnX("mm",LVCFMT_RIGHT,50,ctr_Edit_Time);
	m_listMain.InsertColumnX("nn",LVCFMT_CENTER,50,ctr_Edit_Num);
	m_listMain.InsertColumnX("vv",LVCFMT_CENTER,50,ctr_Edit_CboDown);
	m_listMain.SetTextColor(RGB(255,0,0));
	for(int i=0;i<40;i++)
	{
		m_listMain.AddCboItem(2,"123");
		m_listMain.AddCboItem(7,"456");
	}
	m_listMain.AddItem(0);
	m_listMain.AddItem(0);
	m_listMain.SetHeader();
	m_listcol.InsertColumn(0,"444",LVCFMT_LEFT,100,0);
	m_listcol.InsertColumn(1,"444",LVCFMT_CENTER,100,0);
//	m_listcol.SetBkColor(RGB(120,120,120));
	m_listcol.AddItem(0,RGB(255,0,0));
	m_listcol.AddItem(0,RGB(255,255,0));
	m_listcol.SetItemText(0,0,"fff");
	m_listcol.SetItemText(1,0,"fff");
	m_listcol.SetItemText(0,1,"fff");
	m_listcol.SetItemText(1,1,"fff");
	m_listcol.SetHeader();
	m_listcol.m_blnSelect=FALSE;
//	m_wndToolBar.SetButtonStyle(1,TBBS_GROUP);
//	m_wndToolBar.GetToolBarCtrl()->SetButtonInfo()
//	m_wndToolBar.SetSizes(CSize(50,50),CSize(24,24));

	DWORD dwExStyle = TBSTYLE_EX_DRAWDDARROWS;
	m_wndToolBar.GetToolBarCtrl().SendMessage(TB_SETEXTENDEDSTYLE, 0, (LPARAM)dwExStyle);

	DWORD dwStyle = m_wndToolBar.GetButtonStyle(1);
	dwStyle |= TBSTYLE_DROPDOWN;
	m_wndToolBar.SetButtonStyle(1, dwStyle);
	m_wndToolBar.SetButtonStyle(2,TB_CHECKBUTTON);
	m_wndToolBar.GetToolBarCtrl().SetState(ID_FILE_NEW,TBSTATE_INDETERMINATE);
	TBBUTTONINFO btn;
	m_wndToolBar.GetToolBarCtrl().GetButtonInfo(2,&btn);
	btn.fsStyle=TBSTYLE_TRANSPARENT;
	m_wndToolBar.GetToolBarCtrl().SetButtonInfo(2,&btn);
	m_wndToolBar.SetShowText(TRUE);
//	m_menu.m_clrText=RGB(255,0,0);
//	m_wndToolBar.GetToolBarCtrl().SetExtendedStyle(TBSTYLE_TOOLTIPS);
//	m_edit.blnAuto=TRUE;
	return TRUE;  // return TRUE unless you set the focus to a control	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Frmdlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	m_menu.rcMain.right=cx+3;
	if(m_wndToolBar.m_hWnd!=NULL)
	{
	CRect rc;
	rc.top=rc.left=0;
	rc.right=cx;
	rc.bottom=60;
	m_wndToolBar.MoveWindow(rc);
	}
	// TODO: Add your message handler code here
	
}

void Frmdlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	m_menu.DrawItem(lpDrawItemStruct);
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void Frmdlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	m_menu.MeasureItem(lpMeasureItemStruct);
	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void Frmdlg::OnFileNew() 
{
	// TODO: Add your command handler code here
	MessageBox("aa");
}
void Frmdlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	m_wndToolBar.SetShowText(FALSE);
	m_btn1.SetXAlign(1);
	m_btn1.SetXIcon(IDI_ICON2);
}
void Frmdlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	m_wndToolBar.SetShowText(TRUE);	
	m_btn1.SetXAlign(0);
}
void Frmdlg::OnToolbarDropDown(NMTOOLBAR* pnmh, LRESULT* plRes)
{
	CWnd *pWnd;
    UINT nID;
    CMyMenu menu;
    menu.LoadMenu(IDR_MENU1);
    CMyMenu* pPopup = (CMyMenu*)menu.GetSubMenu(3);
    ASSERT(pPopup);
	pWnd=&m_wndToolBar;
    CRect rc;
    pWnd->SendMessage(TB_GETRECT, pnmh->iItem, (LPARAM)&rc);
    pWnd->ClientToScreen(&rc);
   pPopup->TrackPopupMenu( TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL,
	   rc.left, rc.bottom, this, &rc);
	AfxMessageBox(pnmh->pszText);
}

void Frmdlg::OnOK() 
{
	// TODO: Add extra validation here
	// download by http:www.codefans.net
	CDialog::OnOK();
}
