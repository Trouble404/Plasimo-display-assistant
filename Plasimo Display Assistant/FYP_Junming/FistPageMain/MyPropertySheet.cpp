// MyPropertySheet.cpp : 
//

#include "stdafx.h"
#include "FistPageMain.h"
#include "MyPropertySheet.h"


// MyPropertySheet

IMPLEMENT_DYNAMIC(MyPropertySheet, CPropertySheet)

MyPropertySheet::MyPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

MyPropertySheet::MyPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{

}

MyPropertySheet::~MyPropertySheet()
{
}


BEGIN_MESSAGE_MAP(MyPropertySheet, CPropertySheet)
END_MESSAGE_MAP()




BOOL MyPropertySheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	GetDlgItem(IDOK)->SetWindowText(_T("OK"));
	GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDHELP)->ShowWindow(SW_HIDE);
	GetDlgItem(0x3021)->ShowWindow(SW_HIDE);
	return bResult;
}
