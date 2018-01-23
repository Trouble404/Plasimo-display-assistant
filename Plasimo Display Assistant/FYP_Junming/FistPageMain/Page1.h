#pragma once

#include <opencv2/opencv.hpp>
#include"opencv/highgui.h"
#include"CvvImage.h"
#include"resource.h"


class CPage1 : public CPropertyPage
{
	DECLARE_DYNAMIC(CPage1)

public:
	CPage1();
	virtual ~CPage1();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    

	DECLARE_MESSAGE_MAP()
public:
	
public:
	bool readInfoText(CString filepath);//Read file based on address
	void  Initial();
	void DrawPicToHDC(char * pathfile, UINT ID);//load picture
	CString m_editText;
	afx_msg void OnPaint();
	afx_msg void OnEnChangeEdit1();
};
