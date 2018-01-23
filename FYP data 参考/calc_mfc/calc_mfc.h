// calc_mfc.h : main header file for the CALC_MFC application
//

#if !defined(AFX_CALC_MFC_H__29EFD6E7_CC6A_49B3_84A3_FB5013FECFD7__INCLUDED_)
#define AFX_CALC_MFC_H__29EFD6E7_CC6A_49B3_84A3_FB5013FECFD7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCalc_mfcApp:
// See calc_mfc.cpp for the implementation of this class
//

class CCalc_mfcApp : public CWinApp
{
public:
	CCalc_mfcApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalc_mfcApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCalc_mfcApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALC_MFC_H__29EFD6E7_CC6A_49B3_84A3_FB5013FECFD7__INCLUDED_)
