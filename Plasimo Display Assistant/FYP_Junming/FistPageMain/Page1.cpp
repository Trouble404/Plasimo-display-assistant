// Page1.cpp : 
//

#include "stdafx.h"
#include "FistPageMain.h"
#include "Page1.h"
#include "afxdialogex.h"


// CPage1 

IMPLEMENT_DYNAMIC(CPage1, CPropertyPage)

CPage1::CPage1()
	: CPropertyPage(IDD_PAGE1)
	
	, m_editText(_T(""))
{
	
}

CPage1::~CPage1()
{
}

void CPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT1, m_editText);
}


BEGIN_MESSAGE_MAP(CPage1, CPropertyPage)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_EDIT1, &CPage1::OnEnChangeEdit1)
END_MESSAGE_MAP()

//--------------------------------------------
bool CPage1::readInfoText(CString filepath)//read file based on address
{

	if (!PathFileExists(filepath + "\\" + "info.out"))
		return false;
	
	
	CFile   file(filepath + "\\" + "info.out", CFile::modeRead);//open text file for noly read
	char   *pBuf;
	int   iLen = file.GetLength(); //get the length of file
	pBuf = new   char[iLen + 1];
	file.Read(pBuf, iLen);
	pBuf[iLen] = 0;//add 0 to the last new row
	file.Close();

	SetDlgItemText(IDC_EDIT1, pBuf);
	

	free(pBuf); //release memory

	return  true;
}
void CPage1::DrawPicToHDC(char * pathfile, UINT ID)
{

	IplImage *image = NULL; //The original image
	if (image) cvReleaseImage(&image);

	image = cvLoadImage(pathfile, 1); //display the image

	CDC *pDC = GetDlgItem(ID)->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cimg;
	cimg.CopyOf(image); // copyy
	cimg.DrawToHDC(hDC, &rect); // put image to widget
	ReleaseDC(pDC);
}
void  CPage1::Initial()
{
	DrawPicToHDC("externResouce\\FirstPicture\\Background.png", IDC_PICTURE1_BACKGROUND);//background

}

void CPage1::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   
	Initial();		   
}


void CPage1::OnEnChangeEdit1()
{

}
