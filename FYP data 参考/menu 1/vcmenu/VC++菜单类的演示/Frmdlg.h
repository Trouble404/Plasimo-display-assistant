#if !defined(AFX_FRMDLG_H__B9368A01_3BE6_44D0_9E3E_5FA3F879CB62__INCLUDED_)
#define AFX_FRMDLG_H__B9368A01_3BE6_44D0_9E3E_5FA3F879CB62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Frmdlg.h : header file
//
#include "MyMenu.h"
#include "MyToolBar.h"
#include "MyButton.h"
#include "MyNumEdit.h"
#include "MyDateEdit.h"
#include "MyListCtrl.h"
#include "MyColorList.h"
/////////////////////////////////////////////////////////////////////////////
// Frmdlg dialog

class Frmdlg : public CDialog
{
// Construction
public:
	Frmdlg(CWnd* pParent = NULL);   // standard constructor
	CMyMenu m_menu;
	CMyToolBar m_wndToolBar;
	CImageList imglist;
	CImageList imgHost;
// Dialog Data
	//{{AFX_DATA(Frmdlg)
	enum { IDD = IDD_DIALOG1 };
	CMyColorList m_listcol;
	CMyListCtrl	m_listMain;
	CMyDateEdit	m_edit;
	CMyButton	m_btn4;
	CMyButton	m_btn3;
	CMyButton	m_btn2;
	CMyButton	m_btn1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Frmdlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Frmdlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnFileNew();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnToolbarDropDown(NMTOOLBAR* pnmh, LRESULT* plRes);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRMDLG_H__B9368A01_3BE6_44D0_9E3E_5FA3F879CB62__INCLUDED_)
