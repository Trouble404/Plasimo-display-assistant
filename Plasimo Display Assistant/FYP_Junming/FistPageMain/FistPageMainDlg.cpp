
// FistPageMainDlg.cpp : 
//

#include "stdafx.h"
#include "FistPageMain.h"
#include "FistPageMainDlg.h"
#include "afxdialogex.h"
#include"resource.h"
#include"Page1.h"
#include"MyPropertySheet.h"
#include"MenuDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//******************************** generate automatic*****************************************//

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// data of dialog
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFistPageMainDlg dialog



CFistPageMainDlg::CFistPageMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FISTPAGEMAIN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	ID_SHOW_PICTURE = 0;
}

void CFistPageMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	

	
}

BEGIN_MESSAGE_MAP(CFistPageMainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CFistPageMainDlg::OnBnClickedButtonLoad)
	ON_STN_CLICKED(IDC_PICTURE_PERSONINFO, &CFistPageMainDlg::OnStnClickedPicturePersoninfo)
	ON_STN_CLICKED(IDC_PICTURE_2WEIMA, &CFistPageMainDlg::OnStnClickedPicture2weima)
	ON_STN_CLICKED(IDC_PICTURE_SHOW, &CFistPageMainDlg::OnStnClickedPictureShow)
	ON_STN_CLICKED(IDC_PICTURE_PDF, &CFistPageMainDlg::OnStnClickedPicturePdf)
	ON_STN_CLICKED(IDC_PICTURE_DOWN, &CFistPageMainDlg::OnStnClickedPictureDown)
END_MESSAGE_MAP()


// CFistPageMainDlg information process

BOOL CFistPageMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}	
	}


	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		

	return TRUE;  
}

//******************************** generate automatic*****************************************//

void CFistPageMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// Add minimum button

INT_PTR CFistPageMainDlg::DoModal()
{

	return CDialogEx::DoModal();
}

void CFistPageMainDlg::OnPaint()
{
	InitFistPictureShow();//Showing image of main page

	if (IsIconic())
	{
		CPaintDC dc(this); // draw the device

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// make sure the work space on the middle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//obtain the cursor when user dragging the minimum window

HCURSOR CFistPageMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//click“Load”
void CFistPageMainDlg::OnBnClickedButtonLoad()
{
	// TODO: 在此添加控件通知处理程序代码
	MyPropertySheet sh(_T("Plasimo Display Assistant"), this, 2); // Default display in third page
	CPage1 p1;
	
	// add one page
	sh.AddPage(&p1);

	

	CString szDir = OpenandChooseFileFolder();//Open infor.out
	if (szDir == "")
	     return;
	CString infor_text = readInfoText(szDir);//Read infor.out
	if (infor_text == "")
		return;

	p1.m_editText = infor_text;
	sh.DoModal();              //information display

	//display the menu
	MenuDlg Menudlg;
	Menudlg.m_OpenFileFolder = szDir;
	Menudlg.DoModal();
}
//Click action
void CFistPageMainDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	if (IsControlClick(point, IDC_PICTURE_2WEIMA))//click QR image
	{
		    ShellExecute(NULL, _T("open"), _T("http://fypforjunmingzhang.blogspot.co.uk/"), NULL, NULL, SW_SHOW);
	}
		
	if (IsControlClick(point, IDC_PICTURE_UP))//click < button
	{ 
		
		

		if (--ID_SHOW_PICTURE <= 0)
			ID_SHOW_PICTURE = 0;
		ShowPicture(ID_SHOW_PICTURE);
		
		
	}
	if (IsControlClick(point, IDC_PICTURE_DOWN))//click > button
	{
		if (++ID_SHOW_PICTURE >= 2)
			ID_SHOW_PICTURE = 2;
			
		ShowPicture(ID_SHOW_PICTURE);
		
	}
	if (IsControlClick(point, IDC_PICTURE_PDF))//click help button
	{
				TCHAR szFilter[] = _T("文本文件(*.pdf)|*.pdf|");
				CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
				CString strFilePath;   

				{
					system("ProgramSpecification.pdf");
					system("close");
					// if click help button, it will onpen "programSpecification" file   
				}
	}
	CDialogEx::OnLButtonDown(nFlags, point);//realize
}
//////////---------------------------------------------------------------------------------------------------
//loading images
void CFistPageMainDlg::DrawPicToHDC(char * pathfile, UINT ID)
{

	IplImage *image = NULL; //initial image
	if (image) cvReleaseImage(&image);

	image = cvLoadImage(pathfile, 1); //display image

	CDC *pDC = GetDlgItem(ID)->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cimg;
	cimg.CopyOf(image); // copy image
	cimg.DrawToHDC(hDC, &rect); // move this image to right widget area 
	ReleaseDC(pDC);
}
//To judge the mouse area weather into the widget
bool CFistPageMainDlg::IsControlClick(CPoint point, UINT ID)
{
	CRect rect;
	GetDlgItem(ID)->GetWindowRect(&rect);
	ScreenToClient(rect);
	CPoint pt = (rect.TopLeft());

	GetDlgItem(ID)->GetClientRect(&rect);

	if (point.x > pt.x && point.x < (int)pt.x + rect.Width() &&
		point.y > pt.y && point.y < (int)pt.y + rect.Height()
		)
	{

		return true;
	}

	return  false;

}
//open the choose folder function
CString  CFistPageMainDlg::OpenandChooseFileFolder()//load file
{
	TCHAR           szFolderPath[MAX_PATH] = { 0 };
	CString         strFolderPath = TEXT("");
	
	 BROWSEINFO      sInfo;
	::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
	sInfo.pidlRoot = 0;
	sInfo.lpszTitle = _T("Please choose the data folder：");
	sInfo.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE | BIF_EDITBOX;
	sInfo.lpfn = NULL;

	// display the dialog of choosing a folder  
	LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);
	if (lpidlBrowse != NULL)
	{
		// get the name of folder   
		if (::SHGetPathFromIDList(lpidlBrowse, szFolderPath))
		{
			strFolderPath = szFolderPath;
		}
	}
	if (lpidlBrowse != NULL)
	{
		::CoTaskMemFree(lpidlBrowse);
	}
	
	return   strFolderPath;
}
//Read text files
CString  CFistPageMainDlg::readInfoText(CString filepath)//find the folder address and read text files
{

	if (!PathFileExists(filepath + "\\" + "info.out"))
		return "";


	CFile   file(filepath + "\\" + "info.out", CFile::modeRead);//open information text only for read
	char   *pBuf;
	int   iLen = file.GetLength(); //get the length of text
	pBuf = new   char[iLen + 1];
	file.Read(pBuf, iLen);
	pBuf[iLen] = 0;//relise memory
	file.Close();

	CString A; A.Format("%s", pBuf);

	free(pBuf);

	return  A;
}
//-------------------------------------------------------------------------------------------
//Display initial iamges
void CFistPageMainDlg::InitFistPictureShow()//initialization
{
	DrawPicToHDC("externResouce\\FirstPicture\\Background.png", IDC_Pitcture_one);//background image
	DrawPicToHDC("externResouce\\FirstPicture\\91-100.png", IDC_PICTURE_2WEIMA);//QR code
	DrawPicToHDC("externResouce\\FirstPicture\\50-125.png", IDC_PICTURE_PERSONINFO);//my contact way
	DrawPicToHDC("externResouce\\FirstPicture\\25-25-up.png", IDC_PICTURE_UP);//< button
	DrawPicToHDC("externResouce\\FirstPicture\\25-25-down.png", IDC_PICTURE_DOWN);//> button
	DrawPicToHDC("externResouce\\FirstPicture\\25-25-PDF.png", IDC_PICTURE_PDF);//help button

	DrawPicToHDC("externResouce\\FirstPicture\\FirstPicture.JPG", IDC_PICTURE_SHOW);//background image
}
void CFistPageMainDlg::ShowPicture(int num)
{
	switch (num)
	{
	
	case 0:
		DrawPicToHDC("externResouce\\FirstPicture\\FirstPicture.JPG", IDC_PICTURE_SHOW);//first image
		break;
	case 1:
		DrawPicToHDC("externResouce\\FirstPicture\\SecondPicture.JPG", IDC_PICTURE_SHOW);//second image
		break;
	case 2:
		DrawPicToHDC("externResouce\\FirstPicture\\ThirdPicture.JPG", IDC_PICTURE_SHOW);//third image
		break;
	default:
		
		break;
	}

}




void CFistPageMainDlg::OnStnClickedPicturePersoninfo()
{

}


void CFistPageMainDlg::OnStnClickedPicture2weima()
{

}


void CFistPageMainDlg::OnStnClickedPictureShow()
{

}


void CFistPageMainDlg::OnStnClickedPicturePdf()
{

}


void CFistPageMainDlg::OnStnClickedPictureDown()
{

}
