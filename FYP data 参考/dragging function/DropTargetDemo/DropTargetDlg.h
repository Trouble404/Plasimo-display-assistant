// DropTargetDlg.h : header file
//
// (C) 2001 Reetcom / <VolkerBartheld@reetcom.de>
//

#if !defined(AFX_DROPTARGETDLG_H__0BA4F42C_2F2C_11D5_AE0C_0050DA2A55E0__INCLUDED_)
#define AFX_DROPTARGETDLG_H__0BA4F42C_2F2C_11D5_AE0C_0050DA2A55E0__INCLUDED_

#include "MyDropTarget.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDropTargetDlg dialog

class CDropTargetDlg : public CDialog
{
// Construction
public:
	CDropTargetDlg(CWnd* pParent = NULL);	// standard constructor
// Dialog Data
	//{{AFX_DATA(CDropTargetDlg)
	enum { IDD = IDD_DROPTARGET_DIALOG };
	CComboBox	m_DropComboCtrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDropTargetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDropTargetDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG

  LRESULT OnDropAction(WPARAM wParam = 0, LPARAM lParam = 0);
	DECLARE_MESSAGE_MAP()
private:
	CMyDropTarget m_DropTarget;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DROPTARGETDLG_H__0BA4F42C_2F2C_11D5_AE0C_0050DA2A55E0__INCLUDED_)
