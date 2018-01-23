// MyDropTarget.h: interface for the CMyDropTarget class.
//
// (C) 2001 Reetcom / <VolkerBartheld@reetcom.de>
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYDROPTARGET_H__0BA4F434_2F2C_11D5_AE0C_0050DA2A55E0__INCLUDED_)
#define AFX_MYDROPTARGET_H__0BA4F434_2F2C_11D5_AE0C_0050DA2A55E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxole.h>
#include "DropFileArray.h"


class CMyDropTarget : public COleDropTarget
{
public:
	int GetNumDroppedFiles();
	char* GetFirstDroppedFileName();
  char* GetDroppedFileName(int iNum=0);
	wchar_t* GetDroppedFileNameW(int iNum=0);
  wchar_t* GetFirstDroppedFileNameW();
	BOOL OnDrop( CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point );
	DROPEFFECT OnDragOver( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point );
	DROPEFFECT OnDragEnter( CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point );
	CMyDropTarget();
	virtual ~CMyDropTarget();
private:
	int m_iNumDroppedFiles;
  CDropFileArray m_arDropFiles;
};

#endif // !defined(AFX_MYDROPTARGET_H__0BA4F434_2F2C_11D5_AE0C_0050DA2A55E0__INCLUDED_)
