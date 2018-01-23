// MenuDlg.cpp 
//

#include "stdafx.h"
#include "FistPageMain.h"
#include "MenuDlg.h"
#include "afxdialogex.h"

// MenuDlg 

IMPLEMENT_DYNAMIC(MenuDlg, CDialog)

MenuDlg::MenuDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent),m_OpenFileFolder("")
	, m_EditShowTxt(_T(""))
{

}

MenuDlg::~MenuDlg()
{
}

void MenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//DDX_Control(pDX, IDC_OCX1, m_Player);
	DDX_Text(pDX, IDC_EDIT_SHOWTXT, m_EditShowTxt);
}


BEGIN_MESSAGE_MAP(MenuDlg, CDialog)
	ON_COMMAND(ID_ELECTRON_MEANENERGY, &MenuDlg::OnElectronMeanenergy)
	ON_COMMAND(ID_ELECTRON_MEANENERGYDENSITY, &MenuDlg::OnElectronMeanenergydensity)
	ON_COMMAND(ID_ELECTRON_ELASTICENERGYLOSSES, &MenuDlg::OnElectronElasticenergylosses)
	ON_COMMAND(ID_ELECTRON_ELASTICENERGYLINEARISEDLOSSES, &MenuDlg::OnElectronElasticenergylinearisedlosses)
	ON_COMMAND(ID_ELECTRON_MEA, &MenuDlg::OnElectronMea)
	ON_COMMAND(ID_ELECTRON_MEANENERGYLINEARISEDSOURCE, &MenuDlg::OnElectronMeanenergylinearisedsource)
	ON_COMMAND(ID_ELECTRON_MEANENERGYFLUXDENSITY, &MenuDlg::OnElectronMeanenergyfluxdensity)
	ON_COMMAND(ID_ELECTRON_MEANENERGYFLUXDENSITY32782, &MenuDlg::OnElectronMeanenergyfluxdensity32782)
	ON_COMMAND(ID_ELECTRON_REDUCEDFIELD, &MenuDlg::OnElectronReducedfield)
	ON_COMMAND(ID_ELECTRON_REDUCEDFIELD32784, &MenuDlg::OnElectronReducedfield32784)
	ON_COMMAND(ID_ELECTRON_ENERGYTABLE, &MenuDlg::OnElectronEnergytable)
	ON_COMMAND(ID_ELECTRON_ELASTICLOSSTABLE, &MenuDlg::OnElectronElasticlosstable)
	ON_COMMAND(ID_EMREGION_POTENTIAL, &MenuDlg::OnEmregionPotential)
	ON_COMMAND(ID_EMREGION_CURRENTDENSITY, &MenuDlg::OnEmregionCurrentdensity)
	ON_COMMAND(ID_EMREGION_EX, &MenuDlg::OnEmregionEx)
	ON_COMMAND(ID_EMREGION_EY, &MenuDlg::OnEmregionEy)
	ON_COMMAND(ID_EMREGION_POWERDISSIPATION, &MenuDlg::OnEmregionPowerdissipation)
	ON_COMMAND(ID_EMREGION_V, &MenuDlg::OnEmregionV)
	ON_COMMAND(ID_EMREGION_VOLUMECHARGEDENSITY, &MenuDlg::OnEmregionVolumechargedensity)
	ON_COMMAND(ID_EMREGION_VOLUMECHARGEDENSITY32902, &MenuDlg::OnEmregionVolumechargedensity32902)
	ON_COMMAND(ID_GENERAL_CONFIGURATION, &MenuDlg::OnGeneralConfiguration)
	ON_COMMAND(ID_GEOMETRY_CONFIGURATION, &MenuDlg::OnGeometryConfiguration)
	ON_COMMAND(ID_GEOMETRY_CVVOLUMES, &MenuDlg::OnGeometryCvvolumes)
	ON_COMMAND(ID_GEOMETRY_CVAREAS, &MenuDlg::OnGeometryCvareas)
	ON_COMMAND(ID_GEOMETRY_CVAREAS32871, &MenuDlg::OnGeometryCvareas32871)
	//ON_COMMAND(ID_LINECHART_DT, &MenuDlg::OnLinechartDt)
	ON_COMMAND(ID_LINECHART_ER, &MenuDlg::OnLinechartEr)
	ON_COMMAND(ID_LINECHART_EPSILON, &MenuDlg::OnLinechartEpsilon)
	ON_COMMAND(ID_LINECHART_N0, &MenuDlg::OnLinechartN0)
	ON_COMMAND(ID_LINECHART_N1, &MenuDlg::OnLinechartN1)
	ON_COMMAND(ID_LINECHART_N2, &MenuDlg::OnLinechartN2)
	ON_COMMAND(ID_LINECHART_N3, &MenuDlg::OnLinechartN3)
	ON_COMMAND(ID_LINECHART_N4, &MenuDlg::OnLinechartN4)
	ON_COMMAND(ID_LINECHART_N5, &MenuDlg::OnLinechartN5)
	ON_COMMAND(ID_LINECHART_ELASLOSS, &MenuDlg::OnLinechartElasloss)
	ON_COMMAND(ID_LINECHART_R0, &MenuDlg::OnLinechartR0)
	ON_COMMAND(ID_LINECHART_R1, &MenuDlg::OnLinechartR1)
	ON_COMMAND(ID_LINECHART_R2, &MenuDlg::OnLinechartR2)
	ON_COMMAND(ID_LINECHART_R3, &MenuDlg::OnLinechartR3)
	ON_COMMAND(ID_LINECHART_R4, &MenuDlg::OnLinechartR4)
	ON_COMMAND(ID_LINECHART_R5, &MenuDlg::OnLinechartR5)
	ON_COMMAND(ID_LINECHART_R6, &MenuDlg::OnLinechartR6)
	ON_COMMAND(ID_LINECHART_R7, &MenuDlg::OnLinechartR7)
	ON_COMMAND(ID_LINECHART_V1, &MenuDlg::OnLinechartV1)
	ON_COMMAND(ID_LINECHART_V2, &MenuDlg::OnLinechartV2)
	ON_COMMAND(ID_LINECHART_V4, &MenuDlg::OnLinechartV4)
	ON_COMMAND(ID_LINECHART_I1, &MenuDlg::OnLinechartI1)
	ON_COMMAND(ID_LINECHART_IC1, &MenuDlg::OnLinechartIc1)
	ON_COMMAND(ID_LINECHART_I2, &MenuDlg::OnLinechartI2)
	ON_COMMAND(ID_LINECHART_IC2, &MenuDlg::OnLinechartIc2)
	ON_COMMAND(ID_LINECHART_I4, &MenuDlg::OnLinechartI4)
	ON_COMMAND(ID_LINECHART_IC4, &MenuDlg::OnLinechartIc4)
	ON_COMMAND(ID_GASTEMPERATURE_GASTEMPERATURE, &MenuDlg::OnGastemperatureGastemperature)
	ON_COMMAND(ID_REACTIONS_E, &MenuDlg::OnReactionsE)
	ON_COMMAND(ID_REACTIONS_E32789, &MenuDlg::OnReactionsE32789)
	ON_COMMAND(ID_REACTIONS_E32790, &MenuDlg::OnReactionsE32790)
	ON_COMMAND(ID_REACTIONS_E32791, &MenuDlg::OnReactionsE32791)
	ON_COMMAND(ID_REACTIONS_E32792, &MenuDlg::OnReactionsE32792)
	ON_COMMAND(ID_REACTIONS_E32793, &MenuDlg::OnReactionsE32793)
	ON_COMMAND(ID_REACTIONS_HE, &MenuDlg::OnReactionsHe)
	ON_COMMAND(ID_REACTIONS_HE32795, &MenuDlg::OnReactionsHe32795)
	ON_COMMAND(ID_REACTIONS_HE32796, &MenuDlg::OnReactionsHe32796)
	ON_COMMAND(ID_REACTIONS_HE32797, &MenuDlg::OnReactionsHe32797)
	ON_COMMAND(ID_REACTIONS_HE32798, &MenuDlg::OnReactionsHe32798)
	ON_COMMAND(ID_REACTIONS_HE32799, &MenuDlg::OnReactionsHe32799)
	ON_COMMAND(ID_REACTIONS_HE32800, &MenuDlg::OnReactionsHe32800)
	ON_COMMAND(ID_REACTIONS_HE32801, &MenuDlg::OnReactionsHe32801)
	ON_COMMAND(ID_REACTIONS_HE2, &MenuDlg::OnReactionsHe2)
	ON_COMMAND(ID_REACTIONS_HE3, &MenuDlg::OnReactionsHe3)
	ON_COMMAND(ID_HE_HE, &MenuDlg::OnHeHe)
	ON_COMMAND(ID_HE_HE32810, &MenuDlg::OnHeHe32810)
	ON_COMMAND(ID_HE_HE32811, &MenuDlg::OnHeHe32811)
	ON_COMMAND(ID_HE_HE32812, &MenuDlg::OnHeHe32812)
	ON_COMMAND(ID_HE_HE32813, &MenuDlg::OnHeHe32813)
	ON_COMMAND(ID_HE_HE32814, &MenuDlg::OnHeHe32814)
	ON_COMMAND(ID_HE_HE32815, &MenuDlg::OnHeHe32815)
	ON_COMMAND(ID_HE_HE32816, &MenuDlg::OnHeHe32816)
	ON_COMMAND(ID_HE_HE32817, &MenuDlg::OnHeHe32817)
	ON_COMMAND(ID_HE_HE32818, &MenuDlg::OnHeHe32818)
	ON_COMMAND(ID_HE_HE32819, &MenuDlg::OnHeHe32819)
	ON_COMMAND(ID_HE_HE32820, &MenuDlg::OnHeHe32820)
	ON_COMMAND(ID_HE_HE32821, &MenuDlg::OnHeHe32821)
	ON_COMMAND(ID_HE_HE32822, &MenuDlg::OnHeHe32822)
	ON_COMMAND(ID_HE_HE32823, &MenuDlg::OnHeHe32823)
	ON_COMMAND(ID_HE_HE32824, &MenuDlg::OnHeHe32824)
	ON_COMMAND(ID_HE_HE32825, &MenuDlg::OnHeHe32825)
	ON_COMMAND(ID_HE_HE32826, &MenuDlg::OnHeHe32826)
	ON_COMMAND(ID_HE2_HE2, &MenuDlg::OnHe2He2)
	ON_COMMAND(ID_HE2_HE3, &MenuDlg::OnHe2He3)
	ON_COMMAND(ID_HE2_HE4, &MenuDlg::OnHe2He4)
	ON_COMMAND(ID_HE2_HE5, &MenuDlg::OnHe2He5)
	ON_COMMAND(ID_HE2_HE6, &MenuDlg::OnHe2He6)
	ON_COMMAND(ID_HE2_HE7, &MenuDlg::OnHe2He7)
	ON_COMMAND(ID_HE2_HE8, &MenuDlg::OnHe2He8)
	ON_COMMAND(ID_HE2_HE9, &MenuDlg::OnHe2He9)
	ON_COMMAND(ID_HE2_HE10, &MenuDlg::OnHe2He10)
	ON_COMMAND(ID_E_EDENSITY, &MenuDlg::OnEEdensity)
	ON_COMMAND(ID_E_EDIFFUSIONCOEF, &MenuDlg::OnEEdiffusioncoef)
	ON_COMMAND(ID_E_EMOBILITY, &MenuDlg::OnEEmobility)
	ON_COMMAND(ID_E_ESOURCE, &MenuDlg::OnEEsource)
	ON_COMMAND(ID_E_ELINEARISEDSOURCE, &MenuDlg::OnEElinearisedsource)
		ON_COMMAND(ID_E_EFLUXX, &MenuDlg::OnEEfluxx)
		ON_COMMAND(ID_E_EFLUXY, &MenuDlg::OnEEfluxy)
		ON_COMMAND(ID_E_EPOWERDISSIPATION, &MenuDlg::OnEEpowerdissipation)
		ON_COMMAND(ID_E_EMOBILITYTABLE, &MenuDlg::OnEEmobilitytable)
		ON_COMMAND(ID_E_E, &MenuDlg::OnEE)
		ON_COMMAND(ID_E_E32846, &MenuDlg::OnEE32846)
		ON_COMMAND(ID_E_E32847, &MenuDlg::OnEE32847)
		ON_COMMAND(ID_E_E32848, &MenuDlg::OnEE32848)
		ON_COMMAND(ID_E_E32849, &MenuDlg::OnEE32849)
		ON_COMMAND(ID_E_E32850, &MenuDlg::OnEE32850)
		ON_COMMAND(ID_E_E32851, &MenuDlg::OnEE32851)
		ON_COMMAND(ID_E_E32852, &MenuDlg::OnEE32852)
		ON_COMMAND(ID_E_E32853, &MenuDlg::OnEE32853)
		ON_COMMAND(ID_LINECHART_Q1, &MenuDlg::OnLinechartQ1)
		ON_COMMAND(ID_LINECHART_Q2, &MenuDlg::OnLinechartQ2)
		ON_COMMAND(ID_LINECHART_Q4, &MenuDlg::OnLinechartQ4)
		ON_COMMAND(ID_LINECHART_P0, &MenuDlg::OnLinechartP0)
		ON_EN_CHANGE(IDC_EDIT_SHOWTXT, &MenuDlg::OnEnChangeEditShowtxt)
		END_MESSAGE_MAP()


// MenuDlg 


BOOL MenuDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_diaplay = new CMyOpenGLView1();
	CRect  rect = new CRect(30,30,700,600);
	//GetDlgItem(IDC_STATIC_GLTu)->GetWindowRect(&rect);
	//ScreenToClient(&rect);
	m_diaplay->Create(NULL, NULL, WS_VISIBLE, rect, this, 0);

	CMenu* m_menu = new CMenu();
	m_menu->LoadMenu(IDR_MENU_PAGE2);
	this->SetMenu(m_menu);
	//

	//
	char pFileName[MAX_PATH];
	int nPos = GetCurrentDirectory(MAX_PATH, pFileName);

	CString csFullPath(pFileName);
	
	int col, row;
	m_FileName = CSVRead::ReadCsvFile("NameManagement\\DataName.csv" ,',',&row,&col);
	
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
				
}

////------------1
void MenuDlg::OnElectronMeanenergy()
{

	ShowFile(0);
}


void MenuDlg::OnElectronMeanenergydensity()
{
	ShowFile(1);
}


void MenuDlg::OnElectronElasticenergylosses()
{
	ShowFile(2);
}


void MenuDlg::OnElectronElasticenergylinearisedlosses()
{
	ShowFile(3);
}


void MenuDlg::OnElectronMea()
{
	ShowFile(4);
}


void MenuDlg::OnElectronMeanenergylinearisedsource()
{
	ShowFile(5);
}


void MenuDlg::OnElectronMeanenergyfluxdensity()
{
	ShowFile(6);
}


void MenuDlg::OnElectronMeanenergyfluxdensity32782()
{
	ShowFile(7);
}


void MenuDlg::OnElectronReducedfield()
{
	ShowFile(8);
}


void MenuDlg::OnElectronReducedfield32784()
{
	ShowFile(9);
}


void MenuDlg::OnElectronEnergytable()
{
	ShowFile(10);
}


void MenuDlg::OnElectronElasticlosstable()
{
	ShowFile(11);
}
void MenuDlg::OnGastemperatureGastemperature()
{
	ShowFile(12);
}


void MenuDlg::OnReactionsE()
{
	ShowFile(13);
}


void MenuDlg::OnReactionsE32789()
{
	ShowFile(14);
}


void MenuDlg::OnReactionsE32790()
{
	ShowFile(15);
}


void MenuDlg::OnReactionsE32791()
{
	ShowFile(16);
}


void MenuDlg::OnReactionsE32792()
{
	ShowFile(17);
}


void MenuDlg::OnReactionsE32793()
{
	ShowFile(18);
}


void MenuDlg::OnReactionsHe()
{
	ShowFile(19);
}


void MenuDlg::OnReactionsHe32795()
{
	ShowFile(20);
}


void MenuDlg::OnReactionsHe32796()
{
	ShowFile(21);
}


void MenuDlg::OnReactionsHe32797()
{
	ShowFile(22);
}


void MenuDlg::OnReactionsHe32798()
{
	ShowFile(23);
}


void MenuDlg::OnReactionsHe32799()
{
	ShowFile(24);
}


void MenuDlg::OnReactionsHe32800()
{
	ShowFile(25);
}


void MenuDlg::OnReactionsHe32801()
{
	ShowFile(26);
}


void MenuDlg::OnReactionsHe2()
{
	ShowFile(27);
}


void MenuDlg::OnReactionsHe3()
{
	ShowFile(28);
}


void MenuDlg::OnHeHe()
{
	ShowFile(29);
}


void MenuDlg::OnHeHe32810()
{
	ShowFile(30);
}


void MenuDlg::OnHeHe32811()
{
	ShowFile(31);
}


void MenuDlg::OnHeHe32812()
{
	ShowFile(32);
}


void MenuDlg::OnHeHe32813()
{
	ShowFile(33);
}


void MenuDlg::OnHeHe32814()
{
	ShowFile(34);
}


void MenuDlg::OnHeHe32815()
{
	ShowFile(35);
}


void MenuDlg::OnHeHe32816()
{
	ShowFile(36);
}


void MenuDlg::OnHeHe32817()
{
	ShowFile(37);
}


void MenuDlg::OnHeHe32818()
{
	ShowFile(38);
}


void MenuDlg::OnHeHe32819()
{
	ShowFile(39);
}


void MenuDlg::OnHeHe32820()
{
	ShowFile(40);
}


void MenuDlg::OnHeHe32821()
{
	ShowFile(41);
}


void MenuDlg::OnHeHe32822()
{
	ShowFile(42);
}


void MenuDlg::OnHeHe32823()
{
	ShowFile(43);
}


void MenuDlg::OnHeHe32824()
{
	ShowFile(44);
}


void MenuDlg::OnHeHe32825()
{
	ShowFile(45);
}


void MenuDlg::OnHeHe32826()
{
	ShowFile(46);
}


void MenuDlg::OnHe2He2()
{
	ShowFile(47);
}


void MenuDlg::OnHe2He3()
{
	ShowFile(48);
}


void MenuDlg::OnHe2He4()
{
	ShowFile(49);
}


void MenuDlg::OnHe2He5()
{
	ShowFile(50);
}


void MenuDlg::OnHe2He6()
{
	ShowFile(51);
}


void MenuDlg::OnHe2He7()
{
	ShowFile(52);
}


void MenuDlg::OnHe2He8()
{
	ShowFile(53);
}


void MenuDlg::OnHe2He9()
{
	ShowFile(54);
}


void MenuDlg::OnHe2He10()
{
	ShowFile(55);
}


void MenuDlg::OnEEdensity()
{
	ShowFile(56);
}


void MenuDlg::OnEEdiffusioncoef()
{
	ShowFile(57);
}


void MenuDlg::OnEEmobility()
{
	ShowFile(58);
}


void MenuDlg::OnEEsource()
{
	ShowFile(59);
}


void MenuDlg::OnEElinearisedsource()
{
	ShowFile(60);
}


void MenuDlg::OnEEfluxx()
{
	ShowFile(61);
}


void MenuDlg::OnEEfluxy()
{
	ShowFile(62);
}


void MenuDlg::OnEEpowerdissipation()
{
	ShowFile(63);
}


void MenuDlg::OnEEmobilitytable()
{
	ShowFile(64);
}


void MenuDlg::OnEE()
{
	ShowFile(65);
}


void MenuDlg::OnEE32846()
{
	ShowFile(66);
}


void MenuDlg::OnEE32847()
{
	ShowFile(67);
}


void MenuDlg::OnEE32848()
{
	ShowFile(68);
}


void MenuDlg::OnEE32849()
{
	ShowFile(69);
}


void MenuDlg::OnEE32850()
{
	ShowFile(70);
}


void MenuDlg::OnEE32851()
{
	ShowFile(71);
}


void MenuDlg::OnEE32852()
{
	ShowFile(72);
}


void MenuDlg::OnEE32853()
{
	ShowFile(73);
}

//------------------------------------2----------------------------
void MenuDlg::OnEmregionPotential()
{
	ShowFile(74);
}


void MenuDlg::OnEmregionCurrentdensity()
{
	ShowFile(75);
}


void MenuDlg::OnEmregionEx()
{
	ShowFile(76);
}


void MenuDlg::OnEmregionEy()
{
	ShowFile(77);
}


void MenuDlg::OnEmregionPowerdissipation()
{
	ShowFile(78);
}


void MenuDlg::OnEmregionV()
{
	ShowFile(79);
}


void MenuDlg::OnEmregionVolumechargedensity()
{
	ShowFile(80);
}


void MenuDlg::OnEmregionVolumechargedensity32902()
{
	ShowFile(81);
}

//----------------------------3----------------------------------------
void MenuDlg::OnGeneralConfiguration()
{
	ShowFile(82);
}

//----------------------------4----------------------------------------
void MenuDlg::OnGeometryConfiguration()
{
	ShowFile(83);
}


void MenuDlg::OnGeometryCvvolumes()
{
	ShowFile(84);
}


void MenuDlg::OnGeometryCvareas()
{
	ShowFile(85);
}


void MenuDlg::OnGeometryCvareas32871()
{
	ShowFile(86);
}
//----------------------------5----------------------------------------

//void MenuDlg::OnLinechartDt()
//{
//	//AfxMessageBox("hello");
//	ShowLine(1);
//}


void MenuDlg::OnLinechartEr()
{
	ShowLine(2);
}


void MenuDlg::OnLinechartEpsilon()
{
	ShowLine(3);
}


void MenuDlg::OnLinechartN0()
{
	ShowLine(4);
}


void MenuDlg::OnLinechartN1()
{
	ShowLine(5);
}


void MenuDlg::OnLinechartN2()
{
	ShowLine(6);
}


void MenuDlg::OnLinechartN3()
{
	ShowLine(7);
}


void MenuDlg::OnLinechartN4()
{
	ShowLine(8);
}


void MenuDlg::OnLinechartN5()
{
	ShowLine(9);
}


void MenuDlg::OnLinechartElasloss()
{
	ShowLine(10);
}


void MenuDlg::OnLinechartR0()
{
	ShowLine(11);
}


void MenuDlg::OnLinechartR1()
{
	ShowLine(12);
}


void MenuDlg::OnLinechartR2()
{
	ShowLine(13);
}


void MenuDlg::OnLinechartR3()
{
	ShowLine(14);
}


void MenuDlg::OnLinechartR4()
{
	ShowLine(15);
}

void MenuDlg::OnLinechartR5()
{
	ShowLine(16);
}


void MenuDlg::OnLinechartR6()
{
	ShowLine(17);
}


void MenuDlg::OnLinechartR7()
{
	ShowLine(18);
}


void MenuDlg::OnLinechartV1()
{
	ShowLine(19);
}


void MenuDlg::OnLinechartV2()
{
	ShowLine(20);
}


void MenuDlg::OnLinechartV4()
{
	ShowLine(21);
}


void MenuDlg::OnLinechartI1()
{
	ShowLine(22);
}


void MenuDlg::OnLinechartIc1()
{
	ShowLine(23);
}


void MenuDlg::OnLinechartI2()
{
     ShowLine(24);
}


void MenuDlg::OnLinechartIc2()
{
	ShowLine(25);
}


void MenuDlg::OnLinechartI4()
{
	ShowLine(26);
}


void MenuDlg::OnLinechartIc4()
{
	ShowLine(27);
	
}

void MenuDlg::OnLinechartQ1()
{
	ShowLine(28);
}


void MenuDlg::OnLinechartQ2()
{
	ShowLine(29);
}


void MenuDlg::OnLinechartQ4()
{
	ShowLine(30);
}


void MenuDlg::OnLinechartP0()
{
	ShowLine(31);
}

//--------------------------------------------------------------------------------------------------------------
CString  MenuDlg::GetExtensionOfFile(CString filePath)//return the type of file based on suffix
{
	int dotPos = filePath.ReverseFind('.');
	return (filePath.Right(filePath.GetLength() - dotPos-1));
}
CString  MenuDlg::readInfoText(CString filepath)//Read text file based on name
{

	if (!PathFileExists(filepath ))
		return "";


	CFile   file(filepath, CFile::modeRead);//open text file only for read 
	char   *pBuf;
	int   iLen = file.GetLength(); //get the length of data
	pBuf = new   char[iLen + 1];
	file.Read(pBuf, iLen);
	pBuf[iLen] = 0;//add 0 at the end 
	file.Close();

	CString A; 
	A.Format("%s", pBuf);
	
	free(pBuf);
	m_EditShowTxt = A;
	UpdateData(FALSE);
	return  A;
}

CString  ** MenuDlg::ReadCsvFile(CString filepath)//obtain the data name from the csv file
{

	CStringArray * Array = NULL;

	if (!PathFileExists(filepath))
		return NULL;
	CSVRead read(filepath);

	int Rowcount = read.FileRowCount();
	Array = read.CSVInf(' ');
	int Columcount = Array->GetSize();

	CString **p = new CString *[Rowcount];
	for (int i = 0; i < Rowcount; i++)
		p[i] = new CString[Columcount];
	for (int i = 0; i < Columcount; i++)
		p[0][i] = Array->GetAt(i);


	for (int i = 1; i<Rowcount; i++)
	{
		Array = read.CSVInf(' ');
		for (int j = 0; j < Columcount; j++)
			p[i][j] = Array->GetAt(j);

	}

	return p;

}
void   MenuDlg::ShowFile(int id)
{

	if (!PathFileExists(m_OpenFileFolder + "\\" + m_FileName[id][0])|| m_FileName[id][0]=="")// if not find the name of related text file
		m_EditShowTxt = "No Data Available";
	else 
	{
		m_EditShowTxt = readInfoText(m_OpenFileFolder + "\\" + m_FileName[id][0]);
		if(id != 82)
		m_diaplay->Readtxt(m_OpenFileFolder + "\\" + m_FileName[id][0]);
	}
	UpdateData(FALSE);
	

	

	
}
//loading image
void MenuDlg::DrawPicToHDC(char * pathfile, UINT ID)
{

	IplImage *image = NULL; 
	if (image) cvReleaseImage(&image);

	image = cvLoadImage(pathfile, 1); 

	CDC *pDC = GetDlgItem(ID)->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cimg;
	cimg.CopyOf(image); 
	cimg.DrawToHDC(hDC, &rect); 
	ReleaseDC(pDC);
}
void DialogName(DialogGl * m_dialoggl, int biaohao)
{
	switch (biaohao)
	{
	case 1:
		m_dialoggl->m_glName = "dt";
		m_dialoggl->m_name = "S";
		break;
	case 2:
		m_dialoggl->m_glName = "Er";
		m_dialoggl->m_name = "Vm-1*Pa-1";
		break;
	case 3:
		m_dialoggl->m_glName = "Epsilon";
		m_dialoggl->m_name = "J";
		break;
	case 4:
		m_dialoggl->m_glName = "no";
		m_dialoggl->m_name = "J ";
		break;
	case 5:
		m_dialoggl->m_glName = "n1";
		m_dialoggl->m_name = " J";
		break;
	case 6:
		m_dialoggl->m_glName = "n2";
		m_dialoggl->m_name = "J*m-3";
		break;
	case 7:
		m_dialoggl->m_glName = "n3";
		m_dialoggl->m_name = "J*m-3";
		break;
	case 8:
		m_dialoggl->m_glName = "n4";
		m_dialoggl->m_name = "J*m-3";
		break;
	case 9:
		m_dialoggl->m_glName = "n5";
		m_dialoggl->m_name = "J*m-3";
		break;
	case 10:
		m_dialoggl->m_glName = "ElasLoss";
		m_dialoggl->m_name = "J";
		break;
	case 11:
		m_dialoggl->m_glName = "r0";
		m_dialoggl->m_name = "J";
		break;
	case 12:
		m_dialoggl->m_glName = "r1";
		m_dialoggl->m_name = "J";
		break;
	case 13:
		m_dialoggl->m_glName = "r2";
		m_dialoggl->m_name = "J";
		break;
	case 14:
		m_dialoggl->m_glName = "r3";
		m_dialoggl->m_name = "m-3*s-1";
		break;
	case 15:
		m_dialoggl->m_glName = "r5";
		m_dialoggl->m_name = "m-3*s-1";
		break;
	case 16:
		m_dialoggl->m_glName = "r6";
		m_dialoggl->m_name = "m-3*s-1";
		break;
	case 17:
		m_dialoggl->m_glName = "r7";
		m_dialoggl->m_name = "m-3*s-1";
		break;
	case 18:
		m_dialoggl->m_glName = "V1";
		m_dialoggl->m_name = "m-3*s-1";
		break;
	case 19:
		m_dialoggl->m_glName = "V2";
		m_dialoggl->m_name = "V";
		break;
	case 20:
		m_dialoggl->m_glName = "V4";
		m_dialoggl->m_name = "V";
		break;
	case 21:
		m_dialoggl->m_glName = "I1";
		m_dialoggl->m_name = "V";
		break;
	case 22:
		m_dialoggl->m_glName = "Ic1";
		m_dialoggl->m_name = "V";
		break;
	case 23:
		m_dialoggl->m_glName = "I2";
		m_dialoggl->m_name = "A";
		break;
	case 24:
		m_dialoggl->m_glName = "Ic2";
		m_dialoggl->m_name = "A";
		break;
	case 25:
		m_dialoggl->m_glName = "I4";
		m_dialoggl->m_name = "A";
		break;
	case 26:
		m_dialoggl->m_glName = "Ic4";
		m_dialoggl->m_name = "A";
		break;
	case 27:
		m_dialoggl->m_glName = "Q1";
		m_dialoggl->m_name = "A";
		break;
	case 28:
		m_dialoggl->m_glName = "Q2";
		m_dialoggl->m_name = "C";
		break;
	case 29:
		m_dialoggl->m_glName = "Q4";
		m_dialoggl->m_name = "C";
		break;
	case 30:
		m_dialoggl->m_glName = "P0";
		m_dialoggl->m_name = "W*m-3";
		break;
	case 31:
		break;
	default:
		break;
	}



}
void MenuDlg::ShowLine(int biaohao)
{
	DialogGl * m_dialoggl = new DialogGl();;
	DialogName(m_dialoggl, biaohao);

	m_dialoggl->Create(IDD_DIALOG_GL);
	m_dialoggl->ShowWindow(true);

	m_dialoggl->ReadCsvFile(m_OpenFileFolder + "\\history.out", ' ');
	m_dialoggl->ShowLine(biaohao);
	
	
}




void MenuDlg::OnEnChangeEditShowtxt()
{

}
