//����:ʵ�ּ򵥵Ĵ�ӡ
//---------------------------------------------------�����:ţ��ƽ
class CMyPrint
{
public:
	//���캯��
	CMyPrint();
	//����ָ��
	CDC* GetMyCdc();
	//��Ϊ��ѡ���ӡ��
	//������ע���HKEY_CURRENT_USER\Printers\���ҵ���ص�����
	CDC* GetManCdc(CString strDriver,CString strDevice, CString strOutput, CONST DEVMODE* lpInitData);
	//��ʼ����ӡ�� 	
	BOOL GetPrinterDeviceDefaults(void);
	//���ú�������
	//TRUE--����  FALSE--����
	BOOL SetPrintOrientation(BOOL bVal);
	//��ʼ��ӡ
	void DoPrint();
	//�豸��
	HGLOBAL m_hDevNames;
	//�豸������
	HGLOBAL	m_hDevMode;
	//��ӡҳ�ı߿�հ�(����)
	CRect m_rcPrintMargin;
	//��ӡ�����صĿ�д��Χ(����)
	CRect rcContent;
	//���ô�ӡ�ļ�������
	CString strDocName;
	//���ú�������
	//TRUE--����  FALSE--����
	BOOL blnVal;
	//CDCָ��
	CDC *m_CDC;
	//��(Ӣ��)
	int nXPixelsOfInch;
	//�߶�(��դ��)
	int nYPixelsOfInch;	
	//�õ�������Ӣ��ת���ı���
	//����:Ӣ��=?:1
	double GetPrintProportionX();
	//������ת���������Ӣ��
	int IntToRealIntX(int i);
	//�õ�������Ӣ��ת���ı���
	//����:Ӣ��=?:1
	double GetPrintProportionY();
	//������ת���������Ӣ��
	int IntToRealIntY(int i);
	//�ͷ������ڴ�
	void FreeAllMemory();
	//��������
	~CMyPrint ();
};