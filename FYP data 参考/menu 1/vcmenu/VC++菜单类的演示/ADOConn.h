//ʹ��˵��:
//1.���캯��:�����ʼ�����ݿ�����,���ݿ��Ĭ��·��Ϊ�����г��������·��
//2.����:����ʹ��ExitConnect�˳�
//3.���롢ɾ��������:
//4.��ѯ:ʹ��open���ַ�������ʹ��Get...�ĺ���
//5.����б�:ʹ��open���ַ���,Ȼ�����
//---------------------------------------------------------�����:ţ��ƽ
#import "c:\program files\common files\system\ado\msado15.dll" \
	no_namespace \
	rename ("EOF", "adoEOF")
//�������͵ĺ궨��
#define ado_Field_Str 202
#define ado_Field_Byte 17
#define ado_Field_Int 2
#define ado_Field_Long 3
#define ado_Field_Float 4 
#define ado_Field_Double 5  
#define ado_Field_Text 203 
#define ado_Field_Date 7
#ifdef _DEBUG
	#define ASSERT_VALID_STRING( str ) ASSERT( !IsBadStringPtr( str, 0xfffff ) )
#else	//	_DEBUG
	#define ASSERT_VALID_STRING( str ) ( (void)0 )
#endif	//	_DEBUG
class CADOConn  
{
// �������
public:
	//���һ��ָ��Connection�����ָ��:
	_ConnectionPtr m_pConnection;
	//���һ��ָ��Recordset�����ָ��:
	_RecordsetPtr m_pRecordset;
	_bstr_t m_strData;
	int m_DataType;
	CADOConn(CString strData);
	CADOConn();
	virtual ~CADOConn();
	//��ʼ�����������ݿ�
	void  OnInitCADOConn();
	//ִ�в�ѯ
	_RecordsetPtr& GetRecordSet(CString strSQL);
	//ִ��SQL��䣬Insert Update delete
	BOOL ExecuteSQL(CString strSQL);
	//�˳�����
	void ExitConnect();
	//�ֶμ�����ͷ
	BOOL MoveFirst();
	//�ֶμ�������
	BOOL MoveNext();
	//���ֶμ�
	BOOL Open(CString strSQL);
	//�ַ�������(�������;���ͨ���˷��ش����͵��ַ���)
	CString GetValueString(int index,int strSum);//�ַ�
	//�ֽ�������BYTE
	byte GetValueByte(int index);
	//��������INT
	int GetValueInt(int index);
	//˫������DOUBLE
	double GetValueDouble(int index);
	//��������FLOAT
	float GetValueFloat(int index);
	//��������LONG
	long GetValueLong(int index);
	//ʱ����CTime
	CTime GetValueDate(int index);
	//�ֽ�������BYTE��ֵ�ַ�
	CString GetValueByteStr(int index,int strSum);
	//��������INT��ֵ�ַ�
	CString GetValueIntStr(int index,int strSum);
	//˫������DOUBLE��ֵ�ַ�
	CString GetValueDoubleStr(int index,int strLSum,int strRSum);
	//��������FLOAT��ֵ�ַ�
	CString GetValueFloatStr(int index,int strLSum,int strRSum);
	//��������LONG��ֵ�ַ�
	CString GetValueLongStr(int index,int strSum);
	//ʱ����CTime��ֵ�ַ�
	CString GetValueDateStr(int index,CString strType);
	//��ӵ�������
	BOOL AddItem(CString strTable,int strSum,LPCTSTR pszText, ... );
	//�õ��ֶ������ݵ�����
	int GetValueType(int index);
	//�ֶμ��Ľ����ж�
	BOOL adoEOF();
	//����б�(ColOpenEnd����չ��������)
	BOOL FillList(CListCtrl *listMain,int ColOpenEnd);
	//��ʼ���б�
	BOOL InitList(CListCtrl *listMain,int colSum);
	//�õ�Ӧ�ó������ڵ��ļ���
	CString GetAppPath();
};
