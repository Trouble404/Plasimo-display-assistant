//����:ʵ�ּ򵥵�ʱ���ʽ��ת��
//---------------------------------------------------------------�����:ţ��ƽ
class CMyTime
{
public:
	//CTime���͵�ֵ
	CTime ValueTime;
	//�����ַ�����ʽ������ʱ��
	//blnChinese:TRUE-"������ʱ����"  FALSE-"-:"
	CString GetAllString(BOOL blnChinese);
	//�����ַ�����ʽ������
	//blnChinese:TRUE-"������"  FALSE-"-"
	CString GetDateString(BOOL blnChinese);
	//�����ַ�����ʽ��ʱ��
	//blnChinese:TRUE-"ʱ����"  FALSE-":"
	CString GetTimeString(BOOL blnChinese);
	//���ؼ��ַ�����ʽ������ʱ��
	CString GetSimpleString();
	//��������"������"
	CString GetWeek();
	//�����ַ�����ʽ��ֵ
	//blnSimple:TRUE-(%Y%m%d%H%M%S) FALSE-(������ʱ�����-:)
	void SetAllString(CString Value,BOOL blnSimple);
	//���ó�����ʱ��
	void SetNow();
	//���캯��
	CMyTime();
};
