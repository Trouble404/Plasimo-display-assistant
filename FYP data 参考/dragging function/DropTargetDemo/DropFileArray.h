// DropFileArray.h: interface for the CDropFileArray class.
//
// (C) 2001 Reetcom / <VolkerBartheld@reetcom.de>
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DROPFILEARRAY_H__B6551756_F015_11D4_ADB8_0050DA2A55E0__INCLUDED_)
#define AFX_DROPFILEARRAY_H__B6551756_F015_11D4_ADB8_0050DA2A55E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>                                                           // include support for template classes

// this struct contains info about a DropFile object
struct DROPFILE
  {
  wchar_t         wcDropFile[_MAX_PATH];                                        // name of a dropped file
  };


class CDropFileArray : public CArray<DROPFILE, DROPFILE>                        // derive the class from the CArray template class
{
public:
	CDropFileArray();
	virtual ~CDropFileArray();

};

#endif // !defined(AFX_DROPFILEARRAY_H__B6551756_F015_11D4_ADB8_0050DA2A55E0__INCLUDED_)
