#pragma once

#include <opencv2/opencv.hpp>
#include"opencv/highgui.h"
#include"CvvImage.h"
#include"resource.h"
#include"MyOpenGLView.h"


class DialogGl : public CDialog
{
	DECLARE_DYNAMIC(DialogGl)

public:
	DialogGl(CWnd* pParent = NULL);  
	virtual ~DialogGl();

// data of dialog
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    
	
	DECLARE_MESSAGE_MAP()
public:
	void ShowLine(int biaohao);//Display the line chart
	void ReadCsvFile(CString pathfile, char divided);
	CMyOpenGLView *m_diaplay;
	virtual BOOL OnInitDialog();
	void DrawPicToHDC(char * pathfile, UINT ID);//load picture to widget
	CString kedu_x1;
	CString kedu_x2;
	CString kedu_x3;
	CString kedu_x4;
	CString kedu_x5;
	CString kedu_y1;
	CString kedu_y2;
	CString kedu_y3;
	CString kedu_y4;
	CString kedu_y5;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnPaint();

	float kedu[4];
	afx_msg void OnStnClickedStaticx5();
	afx_msg void OnStnClickedStaticy5();
	CString kedu_x6;
	CString kedu_y6;
	afx_msg void OnStnClickedStaticy6();
	CString m_glName;
	CString m_name;
	afx_msg void OnStnClickedStaticGl();
};
