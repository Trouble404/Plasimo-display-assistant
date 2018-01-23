// MyDlg.h : header file
//

#if !defined(AFX_MYDLG_H__421D6646_59FC_44D3_B4CB_735E5A277579__INCLUDED_)
#define AFX_MYDLG_H__421D6646_59FC_44D3_B4CB_735E5A277579__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog
#include "MyMenu.h"
#include "MyToolBar.h"
#include "MyButton.h"
#include "MyExcel.h"
class CMyDlg : public CDialog
{
	// Construction
public:
	CMyDlg(CWnd* pParent = NULL);	// standard constructor
	CMyMenu m_mnu;
	CFont ft;
	// Dialog Data
	//{{AFX_DATA(CMyDlg)
	enum { IDD = IDD_MY_DIALOG };
	CMyButton	m_btn2;
	CMyButton	m_btn;
		
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(CMyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnNew();
	afx_msg void On2();
	afx_msg void On3();
	afx_msg void On4();
	afx_msg void On5();
	afx_msg void On6();
	afx_msg void On7();
	virtual void OnOK();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnButton1();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButton2();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnMenuitem32811();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void GetFirstLetter(CString strName, CString& strFirstLetter);
	void FirstLetter(int nCode, CString& strLetter);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDLG_H__421D6646_59FC_44D3_B4CB_735E5A277579__INCLUDED_)
