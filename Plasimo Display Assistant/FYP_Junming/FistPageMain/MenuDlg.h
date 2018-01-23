#pragma once


#include <opencv2/opencv.hpp>
#include"opencv/highgui.h"
#include"CvvImage.h"
#include"resource.h"
#include"SVRead.h"
#include"MyOpenGLView1.h"
#include"DialogGl.h"
class MenuDlg : public CDialog
{
	DECLARE_DYNAMIC(MenuDlg)

public:
	MenuDlg(CWnd* pParent = NULL);   
	virtual ~MenuDlg();


#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);   

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnElectronMeanenergy();
	afx_msg void OnElectronMeanenergydensity();
	afx_msg void OnElectronElasticenergylosses();
	afx_msg void OnElectronElasticenergylinearisedlosses();
	afx_msg void OnElectronMea();
	afx_msg void OnElectronMeanenergylinearisedsource();
	afx_msg void OnElectronMeanenergyfluxdensity();
	afx_msg void OnElectronMeanenergyfluxdensity32782();
	afx_msg void OnElectronReducedfield();
	afx_msg void OnElectronReducedfield32784();
	afx_msg void OnElectronEnergytable();
	afx_msg void OnElectronElasticlosstable();
	
	
	
	
	afx_msg void OnEmregionPotential();
	afx_msg void OnEmregionCurrentdensity();
	afx_msg void OnEmregionEx();
	afx_msg void OnEmregionEy();
	afx_msg void OnEmregionPowerdissipation();
	afx_msg void OnEmregionV();
	afx_msg void OnEmregionVolumechargedensity();
	afx_msg void OnEmregionVolumechargedensity32902();
	afx_msg void OnGeneralConfiguration();
	afx_msg void OnGeometryConfiguration();
	afx_msg void OnGeometryCvvolumes();
	afx_msg void OnGeometryCvareas();
	afx_msg void OnGeometryCvareas32871();

	//afx_msg void OnLinechartDt();
	afx_msg void OnLinechartEr();
	afx_msg void OnLinechartEpsilon();
	afx_msg void OnLinechartN0();
	afx_msg void OnLinechartN1();
	afx_msg void OnLinechartN2();
	afx_msg void OnLinechartN3();
	afx_msg void OnLinechartN4();
	afx_msg void OnLinechartN5();
	afx_msg void OnLinechartElasloss();
	afx_msg void OnLinechartR0();
	afx_msg void OnLinechartR1();
	afx_msg void OnLinechartR2();
	afx_msg void OnLinechartR3();
	afx_msg void OnLinechartR4();
		
	afx_msg void OnLinechartR5();
	afx_msg void OnLinechartR6();
	afx_msg void OnLinechartR7();
	afx_msg void OnLinechartV1();
	afx_msg void OnLinechartV2();
	afx_msg void OnLinechartV4();
	afx_msg void OnLinechartI1();
	afx_msg void OnLinechartIc1();
	afx_msg void OnLinechartI2();
	afx_msg void OnLinechartIc2();
	afx_msg void OnLinechartI4();
	afx_msg void OnLinechartIc4();
	afx_msg void OnGastemperatureGastemperature();
	afx_msg void OnReactionsE();
	afx_msg void OnReactionsE32789();
	afx_msg void OnReactionsE32790();
	afx_msg void OnReactionsE32791();
	afx_msg void OnReactionsE32792();
	afx_msg void OnReactionsE32793();
	afx_msg void OnReactionsHe();
	afx_msg void OnReactionsHe32795();
	afx_msg void OnReactionsHe32796();
	afx_msg void OnReactionsHe32797();
	afx_msg void OnReactionsHe32798();
	afx_msg void OnReactionsHe32799();
	afx_msg void OnReactionsHe32800();
	afx_msg void OnReactionsHe32801();
	afx_msg void OnReactionsHe2();
	afx_msg void OnReactionsHe3();
	afx_msg void OnHeHe();
	afx_msg void OnHeHe32810();
	afx_msg void OnHeHe32811();
	afx_msg void OnHeHe32812();
	afx_msg void OnHeHe32813();
	afx_msg void OnHeHe32814();
	afx_msg void OnHeHe32815();
	afx_msg void OnHeHe32816();
	afx_msg void OnHeHe32817();
	afx_msg void OnHeHe32818();
	afx_msg void OnHeHe32819();
	afx_msg void OnHeHe32820();
	afx_msg void OnHeHe32821();
	afx_msg void OnHeHe32822();
	afx_msg void OnHeHe32823();
	afx_msg void OnHeHe32824();
	afx_msg void OnHeHe32825();
	afx_msg void OnHeHe32826();
	afx_msg void OnHe2He2();
	afx_msg void OnHe2He3();
	afx_msg void OnHe2He4();
	afx_msg void OnHe2He5();
	afx_msg void OnHe2He6();
	afx_msg void OnHe2He7();
	afx_msg void OnHe2He8();
	afx_msg void OnHe2He9();
	afx_msg void OnHe2He10();
	afx_msg void OnEEdensity();
	afx_msg void OnEEdiffusioncoef();
	afx_msg void OnEEmobility();
	afx_msg void OnEEsource();
	afx_msg void OnEElinearisedsource();
	afx_msg void OnEEfluxx();
	afx_msg void OnEEfluxy();
	afx_msg void OnEEpowerdissipation();
	afx_msg void OnEEmobilitytable();
	afx_msg void OnEE();
	afx_msg void OnEE32846();
	afx_msg void OnEE32847();
	afx_msg void OnEE32848();
	afx_msg void OnEE32849();
	afx_msg void OnEE32850();
	afx_msg void OnEE32851();
	afx_msg void OnEE32852();
	afx_msg void OnEE32853();
public:

	CString m_OpenFileFolder;
	CString m_EditShowTxt;//Display the data in text file
	CString **m_FileName;//Read the name from csv file
	
public:
	CMyOpenGLView1 *m_diaplay;
	virtual BOOL OnInitDialog();
	CString  GetExtensionOfFile(CString filePath);//return the type of file based on suffix
	CString readInfoText(CString filepath);//Read the text file based on name
	CString ** ReadCsvFile(CString filepath);//Read the data in the csv file
	void  ShowFile(int id);//display different data of text file
	void DrawPicToHDC(char * pathfile, UINT ID);//loading image
	void ShowLine(int biaohao);
	
	afx_msg void OnLinechartQ1();
	afx_msg void OnLinechartQ2();
	afx_msg void OnLinechartQ4();
	afx_msg void OnLinechartP0();
	afx_msg void OnEnChangeEditShowtxt();
};
