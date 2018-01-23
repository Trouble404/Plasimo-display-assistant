
// FistPageMainDlg.h 
//

#pragma once
#include "afxwin.h"

#include <opencv2/opencv.hpp>
#include"opencv/highgui.h"
#include"CvvImage.h"

using namespace cv;
// CFistPageMainDlg dialog
class CFistPageMainDlg : public CDialogEx
{
// contrctor
public:
	CFistPageMainDlg(CWnd* pParent = NULL);	
	virtual INT_PTR DoModal();;
//data of dialog
#ifdef AFX_DESIGN_TIME
	//enum { IDD = IDD_FISTPAGEMAIN_DIALOG };
	enum { IDD = IDD_DIALOG_SECOND };
#endif

		
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	
	

protected:
	HICON m_hIcon;


	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	
	DECLARE_MESSAGE_MAP()
public:
	
	void DrawPicToHDC(char * pathfile,  UINT ID);//load image to widget
	bool IsControlClick(CPoint point,UINT ID);//judge the mouse in or not in the widget
	void InitFistPictureShow();//showing iamge in the main page
	void ShowPicture(int num);//display image
	CString OpenandChooseFileFolder();//open the foler choosing dialog
	CString readInfoText(CString filepath);//read text file
	
public:
	 int  ID_SHOW_PICTURE ;
	 String szDir;//default directory

	 afx_msg void OnStnClickedPicturePersoninfo();
	 afx_msg void OnStnClickedPicture2weima();
	 afx_msg void OnStnClickedPictureShow();
	 afx_msg void OnStnClickedPicturePdf();
	 afx_msg void OnStnClickedPictureDown();
};
