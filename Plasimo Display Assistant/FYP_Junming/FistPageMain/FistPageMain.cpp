
// FistPageMain.cpp : 
//

#include "stdafx.h"
#include "FistPageMain.h"
#include "FistPageMainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFistPageMainApp

BEGIN_MESSAGE_MAP(CFistPageMainApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CFistPageMainApp 

CFistPageMainApp::CFistPageMainApp()
{
	// support restart Root Explorer
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

}



CFistPageMainApp theApp;


// CFistPageMainApp initialization

BOOL CFistPageMainApp::InitInstance()
{

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// set to common widget
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();


	CShellManager *pShellManager = new CShellManager;

	// active the management of vision
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));


	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CFistPageMainDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{

	}
	else if (nResponse == IDCANCEL)
	{

	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}


	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	return FALSE;
}

