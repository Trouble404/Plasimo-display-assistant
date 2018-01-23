#include "StdAfx.h"
#include "MyPrint.h" 
//���캯��
//download by www.codefans.net
CMyPrint::CMyPrint ()
{
	m_CDC=new CDC();
	strDocName="��ӡ";
	blnVal=FALSE;
	m_rcPrintMargin.left=25;
	m_rcPrintMargin.right=25;
	m_rcPrintMargin.top=40;
	m_rcPrintMargin.bottom=30;
	nXPixelsOfInch=300;
	nYPixelsOfInch=300;
	rcContent.left=m_rcPrintMargin.left;
	rcContent.top=m_rcPrintMargin.top;
	rcContent.right=600;
	rcContent.bottom=800;
}
//��������
CMyPrint::~CMyPrint()
{
	if (m_hDevNames != NULL)
        GlobalFree(m_hDevNames);
	if (m_hDevMode != NULL)
        GlobalFree(m_hDevMode);
	if(m_CDC->m_hDC!=NULL)
	{
		m_CDC->ReleaseOutputDC();
		m_CDC->~CDC();
	}		
}
//�ͷ��ڴ�
void CMyPrint::FreeAllMemory()
{
	if (m_hDevNames != NULL)
        GlobalFree(m_hDevNames);
	if (m_hDevMode != NULL)
        GlobalFree(m_hDevMode);
	if(m_CDC->m_hDC!=NULL)
	{
		m_CDC->ReleaseOutputDC();
	}
}
//����CDCָ��
CDC* CMyPrint::GetMyCdc()
{
	//	��ӡ����
	GetPrinterDeviceDefaults();
	//	����Ĭ�ϴ�ӡ����Ϊ����
	SetPrintOrientation(blnVal);
	PRINTDLG	pd;
	memset(&pd, 0, sizeof(PRINTDLG));
	pd.lStructSize = sizeof(PRINTDLG);
	pd.Flags = PD_RETURNDC | PD_NOSELECTION;
	pd.hDC = NULL;
	pd.hwndOwner = NULL;
	pd.hInstance = NULL;
	pd.nMaxPage = 1;
	pd.nMinPage = 1;
	pd.nFromPage = 1;
	pd.nToPage = 1;
	pd.nCopies = 1;
	pd.hDevMode = NULL;
	pd.hDevNames = NULL;
	pd.hDevMode = m_hDevMode;
	//��ʾ��ӡ�Ի������û����趨ֽ�Ŵ�С�ȡ�
	if (!PrintDlg(&pd))
		return FALSE;
	ASSERT(pd.hDC != NULL);
	int nHorRes = GetDeviceCaps(pd.hDC, HORZRES); 
	int nVerRes = GetDeviceCaps(pd.hDC, VERTRES);
	nXPixelsOfInch = GetDeviceCaps(pd.hDC, LOGPIXELSX);
	nYPixelsOfInch = GetDeviceCaps(pd.hDC, LOGPIXELSY);
	//	����ҳ���д���
	rcContent.left=m_rcPrintMargin.left;
	rcContent.top=m_rcPrintMargin.top;
	rcContent.right=(long)(nHorRes*GetPrintProportionX()-m_rcPrintMargin.right);
	rcContent.bottom=(long)(nVerRes*GetPrintProportionY()-m_rcPrintMargin.bottom);
	//	��ʼ��ӡ
	DOCINFO di;
	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName =strDocName; 
	di.lpszOutput = (LPTSTR) NULL; 
	di.lpszDatatype = (LPTSTR) NULL; 
	di.fwType = 0; 
	StartDoc(pd.hDC, &di);
	if(m_CDC->m_hDC!=NULL)
	{
		m_CDC->ReleaseOutputDC();
	}
	m_CDC->m_hDC=pd.hDC;
	return m_CDC;
}
//��Ϊ�Ļ�ô�ӡ��������
CDC* CMyPrint::GetManCdc(CString strDriver,CString strDevice, CString strOutput, CONST DEVMODE* lpInitData)
{
	if(m_CDC->m_hDC!=NULL)
	{
		m_CDC->ReleaseOutputDC();
	}
	m_CDC->m_hDC=CreateDC((LPCSTR)strDriver,(LPCSTR)strDevice,(LPCSTR)strOutput,lpInitData);
	DOCINFO df={sizeof(DOCINFO),"��ӡ",NULL};
	int nHorRes = GetDeviceCaps(m_CDC->m_hDC, HORZRES); 
	int nVerRes = GetDeviceCaps(m_CDC->m_hDC, VERTRES);
	nXPixelsOfInch = GetDeviceCaps(m_CDC->m_hDC, LOGPIXELSX);
	nYPixelsOfInch = GetDeviceCaps(m_CDC->m_hDC, LOGPIXELSY);
	//	����ҳ���д���
	rcContent.left=m_rcPrintMargin.left;
	rcContent.top=m_rcPrintMargin.top;
	rcContent.right=(long)(nHorRes*GetPrintProportionX()-m_rcPrintMargin.right);
	rcContent.bottom=(long)(nVerRes*GetPrintProportionY()-m_rcPrintMargin.bottom);
	m_CDC->StartDoc(&df);
	return m_CDC;
}
//�õ�ϵͳ�Ĵ�ӡ�豸����
BOOL CMyPrint::GetPrinterDeviceDefaults(void)
{
	PRINTDLG printDlg;
	if(AfxGetApp()->GetPrinterDeviceDefaults(&printDlg))
	{
		LPDEVNAMES pDevNames =
			(LPDEVNAMES)::GlobalLock(printDlg.hDevNames);
		LPDEVMODE  pDevMode  = (LPDEVMODE)::GlobalLock(printDlg.hDevMode);		
		if (m_hDevNames != NULL)
			::GlobalFree(m_hDevNames);
		if (m_hDevMode != NULL)
			::GlobalFree(m_hDevMode);		
		m_hDevNames = ::GlobalAlloc(GPTR,
			::GlobalSize(printDlg.hDevNames));
		m_hDevMode = ::GlobalAlloc(GPTR, ::GlobalSize(printDlg.hDevMode));		
		LPDEVNAMES pNewDevNames = (LPDEVNAMES)::GlobalLock(m_hDevNames);
		LPDEVMODE  pNewDevMode  = (LPDEVMODE)::GlobalLock(m_hDevMode);		
		memcpy(pNewDevNames, pDevNames,
			(size_t)::GlobalSize(printDlg.hDevNames));
		memcpy(pNewDevMode, pDevMode,
			(size_t)::GlobalSize(printDlg.hDevMode));		
		::GlobalUnlock(printDlg.hDevNames);
		::GlobalUnlock(printDlg.hDevMode);		
		::GlobalUnlock(m_hDevNames);
		::GlobalUnlock(m_hDevMode);
		return TRUE;
	}
	else
	{
		return FALSE;
    }
}
//	���ô�ӡ����
//	TRUE:����
//	FALSE:����
BOOL CMyPrint::SetPrintOrientation(BOOL bVal)
{
	if (m_hDevMode == NULL)
		return FALSE;
	LPDEVMODE  pNewDevMode  = (LPDEVMODE)::GlobalLock(m_hDevMode);
	if (bVal)
		pNewDevMode->dmOrientation = DMORIENT_LANDSCAPE;	//	����
	else
		pNewDevMode->dmOrientation = DMORIENT_PORTRAIT;		//	����
	::GlobalUnlock(m_hDevMode);
	return TRUE;
}
//��ʼ��ӡ
void CMyPrint::DoPrint()
{
	m_CDC->EndDoc();
	m_CDC->DeleteDC();
}
//�õ�������Ӣ��ת���ı���
//����:Ӣ��=?:1
double CMyPrint::GetPrintProportionX()
{
	double pProportion;
	//�ֱ��� ÿӢ������ص� 1250
	pProportion=nXPixelsOfInch/1250.0;
	return pProportion;
}
//������ת���������Ӣ��
int CMyPrint::IntToRealIntX(int i)
{
	int iTemp;
	iTemp=int(i*1.0/GetPrintProportionX());
	return iTemp;
}
double CMyPrint::GetPrintProportionY()
{
	double pProportion;
	//�ֱ��� ÿӢ������ص� 1250
	pProportion=nYPixelsOfInch/1250.0;
	return pProportion;
}
//������ת���������Ӣ��
int CMyPrint::IntToRealIntY(int i)
{
	int iTemp;
	iTemp=int(i*1.0/GetPrintProportionY());
	return iTemp;
}