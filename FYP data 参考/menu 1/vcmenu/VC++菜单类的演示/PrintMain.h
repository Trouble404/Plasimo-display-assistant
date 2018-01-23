	CDlgPrintDlg dlg;
	m_pMainWnd = &dlg;
	/////
	LRESULT OnBeginPrinting(WPARAM wParam,LPARAM lParam);
	LRESULT OnEndPrinting(WPARAM wParam,LPARAM lParam);
	LRESULT OnMyPrint(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
	////////
BEGIN_MESSAGE_MAP(CDlgPrintDlg, CDialog)	
	ON_MESSAGE(WM_BEGIN_PRINTING,OnBeginPrinting)
	ON_MESSAGE(WM_END_PRINTING,OnEndPrinting)
	ON_MESSAGE(WM_MY_PRINT,OnMyPrint)
END_MESSAGE_MAP()
////////
LRESULT CDlgPrintDlg::OnBeginPrinting(WPARAM wParam,LPARAM lParam)
{

	CDC* pDC			= (CDC*)wParam;
	CPrintInfo* pInfo	= (CPrintInfo *)lParam;	
	m_Grid.OnBeginPrinting(pDC,pInfo);
	return TRUE;
}
LRESULT CDlgPrintDlg::OnEndPrinting(WPARAM wParam,LPARAM lParam)
{
	CDC* pDC			= (CDC*)wParam;
	CPrintInfo* pInfo	= (CPrintInfo *)lParam;
	m_Grid.OnEndPrinting(pDC,pInfo);
	return TRUE;
}
LRESULT CDlgPrintDlg::OnMyPrint(WPARAM wParam,LPARAM lParam)
{
	CDC* pDC			= (CDC*)wParam;
	CPrintInfo* pInfo	= (CPrintInfo *)lParam;
	m_Grid.OnPrint(pDC,pInfo);
return TRUE;
}
//////
	CPrintFrame *pFrame = new CPrintFrame;
	pFrame->m_pCallerDlg = this;
	pFrame->Create(NULL,"Curve Print Preview",WS_OVERLAPPEDWINDOW,CRect(0,0,0,0));
	pFrame->m_pView->OnMyPrintPreview();