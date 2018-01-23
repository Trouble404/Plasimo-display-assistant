// DialogGl.cpp 
//

#include "stdafx.h"
//#include "FistPageMain.h"
#include "DialogGl.h"
#include "afxdialogex.h"
#include"resource.h"

// DialogGl dialog

IMPLEMENT_DYNAMIC(DialogGl, CDialog)

DialogGl::DialogGl(CWnd* pParent /*=NULL*/) //constructor
	: CDialog(IDD_DIALOG_GL, pParent)
	, kedu_x1(_T(""))
	, kedu_x2(_T(""))
	, kedu_x3(_T(""))
	, kedu_x4(_T(""))
	, kedu_x5(_T(""))
	, kedu_y1(_T(""))
	, kedu_y2(_T(""))
	, kedu_y3(_T(""))
	, kedu_y4(_T(""))
	, kedu_y5(_T(""))
	, kedu_x6(_T(""))
	, kedu_y6(_T(""))
	, m_glName(_T(""))
	, m_name(_T(""))
{
	for (int i = 0; i < 4; i++)
		kedu[i] = 0;
}

DialogGl::~DialogGl()
{
}

void DialogGl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_x1, kedu_x1);
	DDX_Text(pDX, IDC_STATIC_x2, kedu_x2);
	DDX_Text(pDX, IDC_STATIC_x3, kedu_x3);
	DDX_Text(pDX, IDC_STATIC_x4, kedu_x4);
	DDX_Text(pDX, IDC_STATIC_x5, kedu_x5);
	DDX_Text(pDX, IDC_STATIC_y1, kedu_y1);
	DDX_Text(pDX, IDC_STATIC_y2, kedu_y2);
	DDX_Text(pDX, IDC_STATIC_y3, kedu_y3);
	DDX_Text(pDX, IDC_STATIC_y4, kedu_y4);
	DDX_Text(pDX, IDC_STATIC_y5, kedu_y5);

	DDX_Text(pDX, IDC_STATIC_x6, kedu_x6);
	DDX_Text(pDX, IDC_STATIC_y6, kedu_y6);
	DDX_Text(pDX, IDC_GL_STATIC, m_glName);
	DDX_Text(pDX, IDC_STATIC_name, m_name);
}


BEGIN_MESSAGE_MAP(DialogGl, CDialog)
	ON_BN_CLICKED(IDOK, &DialogGl::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &DialogGl::OnBnClickedButton1)
	ON_WM_PAINT()
	ON_STN_CLICKED(IDC_STATIC_x5, &DialogGl::OnStnClickedStaticx5)
	ON_STN_CLICKED(IDC_STATIC_y5, &DialogGl::OnStnClickedStaticy5)
	ON_STN_CLICKED(IDC_STATIC_y6, &DialogGl::OnStnClickedStaticy6)
	ON_STN_CLICKED(IDC_STATIC_GL, &DialogGl::OnStnClickedStaticGl)
END_MESSAGE_MAP()


BOOL DialogGl::OnInitDialog()
{
	CDialog::OnInitDialog();


	m_diaplay = new CMyOpenGLView();
	CRect  rect;
	GetDlgItem(IDC_STATIC_GL)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	m_diaplay->Create(NULL, NULL, WS_VISIBLE, rect, this, 0);

	
	return TRUE;  // return TRUE unless you set the focus to a control
				
}
void DialogGl::DrawPicToHDC(char * pathfile, UINT ID)
{

	IplImage *image = NULL; //Original image

	if (image) cvReleaseImage(&image);
	image = cvLoadImage(pathfile, 1); //Display image
	//Transfor this image to Cvvimage format
	CDC *pDC = GetDlgItem(ID)->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cimg;
	cimg.CopyOf(image); // copy this image
	cimg.DrawToHDC(hDC, &rect); // draw this image to widget
	ReleaseDC(pDC);
}
void DialogGl::ShowLine(int biaohao)
{
	for (int i = 0; i < 4; i++)
		kedu[i] = 0;
	 m_diaplay->ShowLine(biaohao, kedu);
}
void DialogGl::ReadCsvFile(CString pathfile, char divided)
{

	m_diaplay->ReadFile(pathfile, divided);
}

void DialogGl::OnBnClickedOk()
{

	CDialog::OnOK();
}


void DialogGl::OnBnClickedButton1()
{

	//this->ShowWindow(false);
	CDialog::OnOK();
}


void DialogGl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
				
				
	
	DrawPicToHDC("externResouce\\FirstPicture\\x¿Ì¶È.png", IDC_PICTURE_X);
	DrawPicToHDC("externResouce\\FirstPicture\\y¿Ì¶È.png", IDC_PICTURE_Y);

	
		kedu_x1.Format("%.2e", kedu[0]);
		kedu_x2.Format("%.2e", kedu[0] + (kedu[1] - kedu[0]) / 5);
		kedu_x3.Format("%.2e", kedu[0] + 2 * (kedu[1] - kedu[0]) / 5);
		kedu_x4.Format("%.2e", kedu[0] + 3 * (kedu[1] - kedu[0]) / 5);
		kedu_x5.Format("%.2e", kedu[0] + 4 * (kedu[1] - kedu[0]) / 5);
		kedu_x6.Format("%.2e", kedu[0] + 5 * (kedu[1] - kedu[0]) / 5);
		                                                               // Divide the number to 6 areas to mark the scale
		kedu_y1.Format("%.2e", kedu[2]);
		kedu_y2.Format("%.2e", kedu[2] + (kedu[3] - kedu[2]) / 5);
		kedu_y3.Format("%.2e", kedu[2] + 2 * (kedu[3] - kedu[2]) / 5);
		kedu_y4.Format("%.2e", kedu[2] + 3 * (kedu[3] - kedu[2]) / 5);
		kedu_y5.Format("%.2e", kedu[2] + 4 * (kedu[3] - kedu[2]) / 5);
		kedu_y6.Format("%.2e", kedu[2] + 5 * (kedu[3] - kedu[2]) / 5);
		
		UpdateData(FALSE);
	  
		int a = 0;
}


void DialogGl::OnStnClickedStaticx5()
{
	
}


void DialogGl::OnStnClickedStaticy5()
{

}


void DialogGl::OnStnClickedStaticy6()
{

}


void DialogGl::OnStnClickedStaticGl()
{

}
