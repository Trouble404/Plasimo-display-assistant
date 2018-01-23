// PrintView.cpp : implementation file
//

#include "stdafx.h"
#include "PrintView.h"
#include "PrintFrame.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
IMPLEMENT_DYNCREATE(CPrintView, CView)
CPrintView::CPrintView()
{
	m_bPrint = TRUE;
}
CPrintView::~CPrintView()
{
}
BEGIN_MESSAGE_MAP(CPrintView, CView)
	//{{AFX_MSG_MAP(CPrintView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
void CPrintView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
}
#ifdef _DEBUG
void CPrintView::AssertValid() const
{
	CView::AssertValid();
}

void CPrintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG
void CPrintView::OnMyPrint()
{
	GetParent()->ShowWindow(SW_SHOWMINIMIZED);
	m_bPrint = TRUE;
	CView::OnFilePrint();
}
void CPrintView::OnMyPrintPreview()
{
	GetParent()->ShowWindow(SW_SHOWMAXIMIZED);
	m_bPrint=FALSE;
	CView::OnFilePrintPreview();	
}
BOOL CPrintView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	if(DoPreparePrinting(pInfo))
		return TRUE;
	else
	{
		GetParent()->DestroyWindow();
		return FALSE;
	}
	AfxMessageBox("ff");
}
void CPrintView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	CView::OnBeginPrinting(pDC, pInfo);
	CPrintFrame *pFrame =(CPrintFrame *)GetParent();
	pFrame->m_pCallerDlg->SendMessage(WM_BEGIN_PRINTING,(WPARAM) pDC, (LPARAM) pInfo);
}
void CPrintView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	CView::OnEndPrinting(pDC, pInfo);
	CPrintFrame *pFrame =(CPrintFrame *)GetParent();
	pFrame->m_pCallerDlg->SendMessage(WM_END_PRINTING,(WPARAM) pDC, (LPARAM) pInfo);
	if(m_bPrint)		//ֱ�Ӵ�ӡ������Ԥ��
		GetParent()->DestroyWindow();
}
void CPrintView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	CPrintFrame *pFrame =(CPrintFrame *)GetParent();
	pFrame->m_pCallerDlg->SendMessage(WM_MY_PRINT,(WPARAM) pDC, (LPARAM) pInfo) ;
}
void CPrintView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	CView::OnEndPrintPreview(pDC, pInfo, point, pView);
	GetParent()->DestroyWindow();
}