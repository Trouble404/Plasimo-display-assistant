#include "StdAfx.h"
#include "ADOConn.h"
//����:���캯��
//strData:���ݿ������
//download by www.codefans.net
CString CADOConn::GetAppPath()
{
	char lpFileName[MAX_PATH];
	GetModuleFileName(AfxGetInstanceHandle(),lpFileName,MAX_PATH);

	CString strFileName = lpFileName;
	int nIndex = strFileName.ReverseFind ('\\');
	
	CString strPath;

	if (nIndex > 0)
		strPath = strFileName.Left (nIndex);
	else
		strPath = "";
	return strPath;
}
CADOConn::CADOConn(CString strData)
{
	CString strValue;
	strData.TrimLeft();
	strData.TrimRight();
	m_strData=_bstr_t(strData);
	strValue=strData.Right(3);
	if(strValue=="mdb") m_DataType=1;
	if(strValue=="xls") m_DataType=2;
}
CADOConn::CADOConn()
{
	m_DataType=3;
}
//����:��������
CADOConn::~CADOConn()
{

}
//����:��ʼ�����ݿ�����
void  CADOConn::OnInitCADOConn()
{
	// ��ʼ��OLE/COM�⻷��
	::CoInitialize(NULL);
 	try
	{
		//��ʼ��ָ��
		m_pConnection=NULL;
		//��ʼ��ָ��
		m_pRecordset=NULL;
		// ����Connection����
		m_pConnection.CreateInstance("ADODB.Connection");
		// ���������ַ�����������BSTR�ͻ���_bstr_t����	
		_bstr_t strConnect;
		switch(m_DataType)
		{
		case 1://ACCESS
			strConnect=_bstr_t("Provider=Microsoft.Jet.OLEDB.4.0;");
			strConnect=strConnect+_bstr_t("Data Source=");
			strConnect=strConnect+_bstr_t(GetAppPath())+_bstr_t("\\");
			strConnect=strConnect+m_strData;
			break;
		case 2://EXCEL
			strConnect=_bstr_t("Provider=Microsoft.Jet.OLEDB.4.0;");
			strConnect=strConnect+_bstr_t("Data Source=");
			strConnect=strConnect+_bstr_t(GetAppPath())+_bstr_t("\\");
			strConnect=strConnect+m_strData;
			strConnect=strConnect+";Extended Properties=Excel 8.0";		
			break;			
		case 3://SQLSERVER
			strConnect=_bstr_t("Provider=Microsoft.Jet.OLEDB.4.0;");
			strConnect=strConnect+_bstr_t("Data Source=D:\\FECG\\");
			strConnect=strConnect+";Extended Properties=Excel 8.0";					
			break;
		}
		m_pConnection->Open(strConnect,_bstr_t(""),_bstr_t(""),adModeUnknown);
	}
	// ��׽�쳣
	catch(_com_error e)
	{	
		// ��ʾ������Ϣ
		AfxMessageBox(e.Description());
	}
	ASSERT(m_pConnection != NULL);
}
//����:ִ�в�ѯ
//����ֵ:�ֶμ���ָ��
_RecordsetPtr&  CADOConn::GetRecordSet(CString strSQL)
{

	try
	{
		// �������ݿ⣬���Connection����Ϊ�գ��������������ݿ�
		if(m_pConnection==NULL)OnInitCADOConn();	
		strSQL.TrimLeft();
		strSQL.TrimRight();
		// ������¼������
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		// ȡ�ñ��еļ�¼
		m_pRecordset->Open(_bstr_t(strSQL),m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	// ��׽�쳣
	catch(_com_error e)
	{
		// ��ʾ������Ϣ
		AfxMessageBox(e.Description());
	}
	ASSERT(m_pRecordset!= NULL);
	// ���ؼ�¼��
	return m_pRecordset;
}
//����:���ַ���
//����ֵ:TRUE:�ɹ� FALSE:ʧ��
BOOL CADOConn::Open(CString strSQL)
{
	try
	{
		// �������ݿ⣬���Connection����Ϊ�գ��������������ݿ�
		if(m_pConnection==NULL) OnInitCADOConn();		
		strSQL.TrimLeft();
		strSQL.TrimRight();
		// ������¼������
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		// ȡ�ñ��еļ�¼
		m_pRecordset->Open(_bstr_t(strSQL),m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	// ��׽�쳣
	catch(_com_error e)
	{
		// ��ʾ������Ϣ
		AfxMessageBox(e.Description());
		return FALSE;
	}
	// ���ؼ�¼��
	ASSERT(m_pRecordset!= NULL);
	return TRUE;	
}
//����:��¼������ͷ
//����ֵ:TRUE:�ɹ� FALSE:ʧ��
BOOL CADOConn::MoveFirst()
{
	if(m_pRecordset==NULL) 
		return FALSE;
	else
	{
		m_pRecordset->MoveFirst();
		return TRUE;
	}

}
//����:��¼�������ƶ�
//����ֵ:TRUE:�ɹ� FALSE:ʧ��
BOOL CADOConn::MoveNext()
{
	if(m_pRecordset==NULL) 
		return FALSE;
	else
	{
		if (!m_pRecordset->adoEOF)
		{
			m_pRecordset->MoveNext();
			return TRUE;
		}
		else
			return FALSE;		
	}

}
//����:ȡ���ֶ��е��ַ���
//index:�ֶμ��е�����
//strSum:���ص��ַ��ĳ���(<=ʵ��:����ȫ������,>ʵ��:�󲹿ո�)
CString CADOConn::GetValueString(int index,int strSum)
{
	_variant_t vValue;//var�ͷ���ֵ
	_variant_t vIndex;//����
	CString strValue,strType,str;//strValue:��ʼ����ֵ strType:��ʽ���ַ��� str:���շ���ֵ
	vIndex.vt=VT_I2;
	vIndex.iVal=index;
	vValue=m_pRecordset->Fields->GetItem(vIndex)->Value;
	switch(vValue.vt)
	{
	case VT_NULL:
		str="";
		break;
	case VT_ERROR:
		str="";
		break;	
	case VT_EMPTY:
		str="";
		break;
	default:
		str=(LPCSTR)_bstr_t(vValue);
	}
	strType.Format("%d",strSum);
	strType="%"+strType+"s";
	strValue.Format(strType,str);
	return strValue;
	
}
//����:ȡ���ֶ��е��ֽ�������
//index:�ֶμ��е�����
byte CADOConn::GetValueByte(int index)
{
	_variant_t vValue;//var�ͷ���ֵ
	_variant_t vIndex;//����
	byte bValue;//��ֵ����ֵ
	vIndex.vt=VT_I2;
	vIndex.iVal=index;
	vValue=m_pRecordset->Fields->GetItem(vIndex)->Value;
	switch(vValue.vt)
	{
	case VT_NULL:
		bValue=0;
		break;
	case VT_ERROR:
		bValue=0;
		break;
	case VT_EMPTY:
		bValue=0;
		break;
	default:
		bValue=vValue.bVal;
	}
	return bValue;
}
//����:ȡ���ֶ��е��ֽ����������ַ�����ʽ
//index:�ֶμ��е�����
//strSum:���ص��ַ��ĳ���(<=ʵ��:����ȫ������,>ʵ��:�󲹿ո�)
CString CADOConn::GetValueByteStr (int index,int strSum)
{
	_variant_t vValue;//var�ͷ���ֵ
	_variant_t vIndex;//����
	byte bValue;//��ֵ����ֵ
	CString strValue,strType;//strValue:�ַ�������ֵ strType:��ʽ���ַ���
	vIndex.vt=VT_I2;
	vIndex.iVal=index;
	vValue=m_pRecordset->Fields->GetItem(vIndex)->Value;
	switch(vValue.vt)
	{
	case VT_NULL:
		bValue=0;
		break;
	case VT_ERROR:
		bValue=0;
		break;
	case VT_EMPTY:
		bValue=0;
		break;
	default:
		bValue=vValue.bVal;
	}
	strType.Format("%d",strSum);
	strType="%"+strType+"d";
	strValue.Format(strType,bValue);
	return strValue;
}
//����:ȡ���ֶ��еĶ���������
//index:�ֶμ��е�����
int CADOConn::GetValueInt(int index)
{
	_variant_t vValue;//var�ͷ���ֵ
	_variant_t vIndex;//����
	int iValue;//��ֵ����ֵ
	vIndex.vt=VT_I2;
	vIndex.iVal=index;
	vValue=m_pRecordset->Fields->GetItem(vIndex)->Value;
	switch(vValue.vt)
	{
	case VT_NULL:
		iValue=0;
		break;
	case VT_ERROR:
		iValue=0;
		break;
	case VT_EMPTY:
		iValue=0;
		break;
	default:
		iValue=vValue.iVal;
	}
	return iValue;
}
//����:ȡ���ֶ��еĶ������������ַ�����ʽ
//index:�ֶμ��е�����
//strSum:���ص��ַ��ĳ���(<=ʵ��:����ȫ������,>ʵ��:�󲹿ո�)
CString CADOConn::GetValueIntStr(int index,int strSum)
{
	_variant_t vValue;//var�ͷ���ֵ
	_variant_t vIndex;//����
	int iValue;//��ֵ����ֵ
	CString strValue,strType;//strValue:�ַ�������ֵ strType:��ʽ���ַ���
	vIndex.vt=VT_I2;
	vIndex.iVal=index;
	vValue=m_pRecordset->Fields->GetItem(vIndex)->Value;
	switch(vValue.vt)
	{
	case VT_NULL:
		iValue=0;
		break;
	case VT_ERROR:
		iValue=0;
		break;
	case VT_EMPTY:
		iValue=0;
		break;
	default:
		iValue=vValue.iVal;
	}
	strType.Format("%d",strSum);
	strType="%"+strType+"d";
	strValue.Format(strType,iValue);
	return strValue;	
}
//����:ȡ���ֶ��е�˫���ȸ�����
//index:�ֶμ��е�����
double CADOConn::GetValueDouble(int index)
{
	_variant_t vValue;//var�ͷ���ֵ
	_variant_t vIndex;//����
	double dValue;//��ֵ����ֵ
	vIndex.vt=VT_I2;
	vIndex.iVal=index;
	vValue=m_pRecordset->Fields->GetItem(vIndex)->Value;
	switch(vValue.vt)
	{
	case VT_NULL:
		dValue=0;
		break;
	case VT_ERROR:
		dValue=0;
		break;
	case VT_EMPTY:
		dValue=0;
		break;
	default:
		dValue=vValue.dblVal;
	}
	return dValue;
}
//����:ȡ���ֶ��е�˫���ȸ��������ַ�����ʽ
//index:�ֶμ��е�����
//strLSum(��������):���ص��������ֵĳ���(<=ʵ��:����ȫ������,>ʵ��:�󲹿ո�)
//strRSum(С������):���ص�С�����ֵĳ���(<=ʵ��:����ȫ������,>ʵ��:�Ҳ��ո�)
CString CADOConn::GetValueDoubleStr(int index,int strLSum,int strRSum)
{
	_variant_t vValue;//var�ͷ���ֵ
	_variant_t vIndex;//����
	double dValue;//��ֵ����ֵ
	CString strValue,strType;//strValue:�ַ�������ֵ strType:��ʽ���ַ���
	vIndex.vt=VT_I2;
	vIndex.iVal=index;
	vValue=m_pRecordset->Fields->GetItem(vIndex)->Value;
	switch(vValue.vt)
	{
	case VT_NULL:
		dValue=0;
		break;
	case VT_ERROR:
		dValue=0;
		break;
	case VT_EMPTY:
		dValue=0;
		break;
	default:
		dValue=vValue.dblVal;
	}
	strType.Format("%d.%d",strLSum,strRSum);
	strType="%"+strType+"f";
	strValue.Format(strType,dValue);
	return strValue;
}
//����:ȡ���ֶ��еĵ����ȸ�����
//index:�ֶμ��е�����
float CADOConn::GetValueFloat(int index)
{
	_variant_t vValue;//var�ͷ���ֵ
	_variant_t vIndex;//����
	float fValue;//��ֵ����ֵ
	vIndex.vt=VT_I2;
	vIndex.iVal=index;
	vValue=m_pRecordset->Fields->GetItem(vIndex)->Value;
	switch(vValue.vt)
	{
	case VT_NULL:
		fValue=0;
		break;
	case VT_ERROR:
		fValue=0;
		break;
	case VT_EMPTY:
		fValue=0;
		break;
	default:
		fValue=vValue.fltVal;
	}
	return fValue;
}
//����:ȡ���ֶ��еĵ����ȸ��������ַ�����ʽ
//index:�ֶμ��е�����
//strLSum(��������):���ص��������ֵĳ���(<=ʵ��:����ȫ������,>ʵ��:�󲹿ո�)
//strRSum(С������):���ص�С�����ֵĳ���(<=ʵ��:����ȫ������,>ʵ��:�Ҳ��ո�)
CString CADOConn::GetValueFloatStr(int index,int strLSum,int strRSum)
{
	_variant_t vValue;//var�ͷ���ֵ
	_variant_t vIndex;//����
	float fValue;//��ֵ����ֵ
	CString strValue,strType;//strValue:�ַ�������ֵ strType:��ʽ���ַ���
	vIndex.vt=VT_I2;
	vIndex.iVal=index;
	vValue=m_pRecordset->Fields->GetItem(vIndex)->Value;
	switch(vValue.vt)
	{
	case VT_NULL:
		fValue=0;
		break;
	case VT_ERROR:
		fValue=0;
		break;
	case VT_EMPTY:
		fValue=0;
		break;
	default:
		fValue=vValue.fltVal;
	}
	strType.Format("%d.%d",strLSum,strRSum);
	strType="%"+strType+"f";
	strValue.Format(strType,fValue);
	return strValue;
}
//����:ȡ���ֶ��еĳ������������ַ���
//index:�ֶμ��е�����
long CADOConn::GetValueLong(int index)
{
	_variant_t vValue;//var�ͷ���ֵ
	_variant_t vIndex;//����
	long lValue;//��ֵ����ֵ
	vIndex.vt=VT_I2;
	vIndex.iVal=index;
	vValue=m_pRecordset->Fields->GetItem(vIndex)->Value;
	switch(vValue.vt)
	{
	case VT_NULL:
		lValue=0;
		break;
	case VT_ERROR:
		lValue=0;
		break;
	case VT_EMPTY:
		lValue=0;
		break;
	default:
		lValue=vValue.lVal;
	}
	return lValue;
}
//����:ȡ���ֶ��еĳ������������ַ�����ʽ
//index:�ֶμ��е�����
//strSum:���ص��ַ��ĳ���(<=ʵ��:����ȫ������,>ʵ��:�󲹿ո�)
CString CADOConn::GetValueLongStr(int index,int strSum)
{
	_variant_t vValue;//var�ͷ���ֵ
	_variant_t vIndex;//����
	long lValue;//��ֵ����ֵ
	CString strValue,strType;//strValue:�ַ�������ֵ strType:��ʽ���ַ���
	vIndex.vt=VT_I2;
	vIndex.iVal=index;
	vValue=m_pRecordset->Fields->GetItem(vIndex)->Value;
	switch(vValue.vt)
	{
	case VT_NULL:
		lValue=0;
		break;
	case VT_ERROR:
		lValue=0;
		break;
	case VT_EMPTY:
		lValue=0;
		break;
	default:
		lValue=vValue.lVal;
	}
	strType.Format("%d",strSum);
	strType="%"+strType+"d";
	strValue.Format(strType,lValue);
	return strValue;	
}
//����ʱ����ֵ
//���ݿ��д�ĸ�ʽΪ�ַ���(yyyy-mm-dd HH-MM-SS)
CTime CADOConn::GetValueDate(int index)
{
	_variant_t vValue;//var�ͷ���ֵ
	_variant_t vIndex;//����
	CString strValue;//��ֵ����ֵ
	vIndex.vt=VT_I2;
	vIndex.iVal=index;
	vValue=m_pRecordset->Fields->GetItem(vIndex)->Value;
	switch(vValue.vt)
	{
	case VT_NULL:
		strValue="1980-08-08";
		break;
	case VT_ERROR:
		strValue="1980-08-08";
		break;
	case VT_EMPTY:
		strValue="1980-08-08";
		break;
	default:
		strValue=(LPCSTR)_bstr_t(vValue);
		break;
	}
	CString strYear,strMonth,strDay,strHour,strMin,strSec;
	strYear=strValue.Mid(0,4);
	strMonth=strValue.Mid(5,2);
	strDay=strValue.Mid(8,2);
	if(strValue.GetLength()>10)
	{
		strHour=strValue.Mid(11,2);
		strMin=strValue.Mid(14,2);
		strSec=strValue.Mid(17,2);
	}
	else
	{
		strHour="0";
		strMin="0";
		strSec="0";
	}
	CTime TValue(atoi(strYear),atoi(strMonth),atoi(strDay),atoi(strHour),atoi(strMin),atoi(strSec));
	return TValue;
}
//����ʱ����ֵ���ַ���
//���ݿ��д�ĸ�ʽΪ�ַ���(yyyy-mm-dd HH-MM-SS)
CString CADOConn::GetValueDateStr(int index,CString strType)
{
	_variant_t vValue;//var�ͷ���ֵ
	_variant_t vIndex;//����
	CString strValue="";//��ֵ����ֵ
	vIndex.vt=VT_I2;
	vIndex.iVal=index;
	vValue=m_pRecordset->Fields->GetItem(vIndex)->Value;
	switch(vValue.vt)
	{
	case VT_NULL:
		strValue="1980-08-08";
		break;
	case VT_ERROR:
		strValue="1980-08-08";
		break;
	case VT_EMPTY:
		strValue="1980-08-08";
		break;
	default:
		strValue=(LPCSTR)_bstr_t(vValue);
		break;
	}
	CString strYear,strMonth,strDay,strHour,strMin,strSec;
	strYear=strValue.Mid(0,4);
	strMonth=strValue.Mid(5,2);
	strDay=strValue.Mid(8,2);
	if(strValue.GetLength()>10)
	{
		strHour=strValue.Mid(11,2);
		strMin=strValue.Mid(14,2);
		strSec=strValue.Mid(17,2);
	}
	else
	{
		strHour="0";
		strMin="0";
		strSec="0";
	}
	CTime TValue(atoi(strYear),atoi(strMonth),atoi(strDay),atoi(strHour),atoi(strMin),atoi(strSec));
	CString str=TValue.Format(strType);
	return str;	
}
//����:ִ��SQL���(Insert Update delete)
//strSQL:SQL���
//����ֵ:TRUE:�ɹ� FALSE:ʧ��
BOOL CADOConn::ExecuteSQL(CString strSQL)
{
	try
	{
		// �Ƿ��Ѿ��������ݿ�
		if(m_pConnection == NULL) OnInitCADOConn();
		strSQL.TrimLeft();
		strSQL.TrimRight();
		m_pConnection->Execute(_bstr_t(strSQL),NULL,adCmdText);
		return TRUE;
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}
}
//����:�˳�����
void CADOConn::ExitConnect()
{
	try
	{
	if (m_pRecordset !=NULL) m_pRecordset->Close();
	if (m_pConnection !=NULL) m_pConnection->Close();
	// �ͷŻ���
	::CoUninitialize();
	}
	catch (_com_error e) 
	{
		AfxMessageBox(e.Description());
	}
}
//����:��һ�������һ������
//strTable:����
//strSum:�����ֶμ�����Ŀ
//pszText...:strSum�������ַ���
//����ֵ:TRUE:�ɹ� FALSE:����
BOOL CADOConn::AddItem(CString strTable,int strSum,LPCTSTR pszText, ... )
{
	strTable.TrimLeft();
	strTable.TrimRight();
	CString strSQL="select * from "+strTable;
	CString strFirst=pszText;
	LPTSTR* arrpsz = new LPTSTR[strSum];//��ʼ��һ�б�������
	arrpsz[ 0 ] = new TCHAR[ lstrlen( pszText ) + 1 ];
	(void)lstrcpy( arrpsz[ 0 ], pszText );
 	va_list list;
	va_start( list, pszText );//���б��������
	Open(strSQL);//�ַ������͵Ĳ���
	strSQL="insert into "+strTable+" values(";
	int iType;
	iType=GetValueType(0);
	if (iType==ado_Field_Str||iType==ado_Field_Text||iType==ado_Field_Date)
		strSQL=strSQL+"'"+strFirst+"',";//�ַ���
	else
	{
		if(strFirst=="") strFirst="0";
		strSQL=strSQL+strFirst+",";//������
	}
	for( int iColumn = 1; iColumn <strSum; iColumn++ )
	{
		pszText = va_arg( list, LPCTSTR );
		ASSERT_VALID_STRING( pszText );
		iType=GetValueType(iColumn);
		if (iType==ado_Field_Str||iType==ado_Field_Text||iType==ado_Field_Date)
			strSQL=strSQL+"'"+pszText+"',";
		else
		{
			CString strValue=pszText;
			if(strValue=="") strValue="0";
			strSQL=strSQL+strValue+",";
		}
		arrpsz[ iColumn ] = new TCHAR[ lstrlen( pszText ) + 1 ];
		(void)lstrcpy( arrpsz[ iColumn ], pszText );
	}

	va_end( list );
	//��ʼִ��
	strSQL=strSQL.Left(strSQL.GetLength()-1)+")";
	try
	{
		//ִ�в������
		m_pConnection->Execute(_bstr_t(strSQL),NULL,adCmdText);
		return TRUE;
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}
}
//����:��������ΪIndexʱ�����ݵ�����
//����ֵ:��������
int CADOConn::GetValueType(int index)
{
	_variant_t vIndex;
	int Tpye;
	vIndex.vt=VT_I2;
	vIndex.iVal=index;
	Tpye=m_pRecordset->Fields->GetItem(vIndex)->GetType();
	return Tpye;	
}
//����:�ж��ֶμ��Ƿ����
//����ֵ:TRUE:���� FALSE:δ����
BOOL CADOConn::adoEOF()
{
	if(m_pRecordset->adoEOF)
		return TRUE;
	else
		return FALSE;
}
//����:����б�
//listMain:�б�ָ�� ColOpenEnd:����չ��������
//����ֵ:TRUE:�ɹ���FALSE:ʧ��
BOOL CADOConn::FillList(CListCtrl *listMain,int ColOpenEnd)
{
	int i,iType,iRow=0,listWidth=0;//iType:�ֶμ����������� listWidth:�б����еĿ��
	long lMax=0;
	_variant_t vIndex;
	lMax=m_pRecordset->Fields->Count;
	vIndex.vt=VT_I2;
	listMain->SetExtendedStyle( LVS_EX_FULLROWSELECT);
	listMain->DeleteAllItems();
	for(i=0;i<100;i++)
		listMain->DeleteColumn(i);
	for(i=0;i<lMax;i++)
	{	
		CString strTitle="";
		vIndex.iVal=i;
		strTitle=(LPCTSTR)m_pRecordset->Fields->GetItem(vIndex)->GetName();
		listMain->InsertColumn(i,strTitle,LVCFMT_CENTER,100,0);
	}
	if(!m_pRecordset->adoEOF)
	{	
		MoveFirst();
		while (!m_pRecordset->adoEOF)
		{
			for (i=0;i<lMax;i++)
			{
				CString strValue="";
				vIndex.iVal=i;
				iType=m_pRecordset->Fields->GetItem(vIndex)->GetType();
				switch(iType)
				{
				case ado_Field_Str:
				case ado_Field_Text:
					strValue=GetValueString(i,0);
					break;
				case ado_Field_Long:
					strValue=GetValueLongStr(i,0);
					break;
				case ado_Field_Int:
					strValue=GetValueIntStr(i,0);
					break;
				case ado_Field_Float:
					strValue=GetValueFloatStr(i,0,2);
					break;
				case ado_Field_Double:
					strValue=GetValueDoubleStr(i,0,2);
					break;
				case ado_Field_Byte:
					strValue=GetValueByteStr(i,0);
					break;
				case ado_Field_Date:
					strValue=GetValueString(i,0);
					break;
				default:
					strValue="";
					break;
				}
				if(m_DataType==2)
					strValue=GetValueString(i,0);
				if(i==0)
					listMain->InsertItem(iRow,strValue,0);
				else
					listMain->SetItemText(iRow,i,strValue);
			}
			m_pRecordset->MoveNext();
			iRow=iRow+1;
		}
		//����ͷ
		MoveFirst();
	}
	if(listMain->GetItemCount()>0)
	{			
		if(ColOpenEnd>0)
		{
			for(int i=0;i<ColOpenEnd;i++)
			{
				listMain->SetColumnWidth(i,LVSCW_AUTOSIZE);
				listWidth=listMain->GetColumnWidth(i);
				listMain->SetColumnWidth(i,LVSCW_AUTOSIZE_USEHEADER);
				if(listWidth<listMain->GetColumnWidth(i))
					listMain->SetColumnWidth(i,LVSCW_AUTOSIZE_USEHEADER);
			}	
		}
		else
		{
			listMain->SetColumnWidth(i,LVSCW_AUTOSIZE_USEHEADER);
		}

	}
	else
	{
		for(i=0;i<lMax;i++)
		{
			listMain->SetColumnWidth(i,LVSCW_AUTOSIZE_USEHEADER);
			listWidth=listWidth+listMain->GetColumnWidth(i);
		}
		RECT rectList;
		listMain->GetWindowRect(&rectList);
		if(listWidth<(rectList.right-rectList.left))
		{
			listWidth=(rectList.right-rectList.left-listWidth)/11;
			listMain->SetColumnWidth(i,listMain->GetColumnWidth(i)+listWidth);
		}
	}
	return TRUE;
}
//����:��ʼ���Զ������б�
//CListCtrl:�б�ָ��;colSum:�б����Ѿ���������
BOOL CADOConn::InitList(CListCtrl *listMain,int colSum)
{
	int intWidth=0;
	int i;
	for(i=0;i<colSum;i++)
	{
		listMain->SetColumnWidth(i,LVSCW_AUTOSIZE_USEHEADER);
		intWidth=intWidth+listMain->GetColumnWidth(i);
	}
	RECT rectList;
	listMain->GetWindowRect(&rectList);
	if(intWidth<(rectList.right-rectList.left))
	{
		intWidth=(rectList.right-rectList.left-intWidth)/colSum;
		listMain->SetColumnWidth(i,listMain->GetColumnWidth(i)+intWidth);
	}
	return TRUE;
}
