

//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		


// CFistPageMainApp: 

//

class CFistPageMainApp : public CWinApp
{
public:
	CFistPageMainApp();

public:
	virtual BOOL InitInstance();


	DECLARE_MESSAGE_MAP()
};

extern CFistPageMainApp theApp;