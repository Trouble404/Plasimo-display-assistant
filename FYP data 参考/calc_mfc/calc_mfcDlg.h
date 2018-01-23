// calc_mfcDlg.h : header file
//

#if !defined(AFX_CALC_MFCDLG_H__0CE17EF1_7FEF_4416_BEA5_FFB05CBA862B__INCLUDED_)
#define AFX_CALC_MFCDLG_H__0CE17EF1_7FEF_4416_BEA5_FFB05CBA862B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCalc_mfcDlg dialog

class CCalc_mfcDlg : public CDialog
{
// Construction
public:
	CCalc_mfcDlg(CWnd* pParent = NULL);	// standard constructor
	int m_nDotNo,m_nDotSign;
	double m_dPre,m_dCur,m_dNext;
	CString m_strPre,m_strCur,m_strNext;

	void SetNum(int);
	void process();
	

// Dialog Data
	//{{AFX_DATA(CCalc_mfcDlg)
	enum { IDD = IDD_CALC_MFC_DIALOG };
	double	m_dNum;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalc_mfcDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCalc_mfcDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton0();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonDiv();
	afx_msg void OnButtonDot();
	afx_msg void OnButtonEqual();
	afx_msg void OnButtonMul();
	afx_msg void OnButtonSub();
	afx_msg void Onid1();
	afx_msg void Onid2();
	afx_msg void OnButtonAc();
	afx_msg void OnButtonSqrt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALC_MFCDLG_H__0CE17EF1_7FEF_4416_BEA5_FFB05CBA862B__INCLUDED_)
