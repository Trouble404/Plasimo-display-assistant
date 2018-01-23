// My.h : main header file for the MY application
//

#if !defined(AFX_MY_H__B58D34B7_1DB5_4DFB_850F_DFE4A952E8AE__INCLUDED_)
#define AFX_MY_H__B58D34B7_1DB5_4DFB_850F_DFE4A952E8AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyApp:
// See My.cpp for the implementation of this class
//

class CMyApp : public CWinApp
{
public:
	CMyApp();
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyApp)
public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	
	// Implementation
	
	//{{AFX_MSG(CMyApp)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MY_H__B58D34B7_1DB5_4DFB_850F_DFE4A952E8AE__INCLUDED_)
