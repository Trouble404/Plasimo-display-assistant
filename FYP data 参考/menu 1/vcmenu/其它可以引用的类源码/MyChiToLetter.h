//ʵ�ֺ�����ƴ����ת��
//-----------------------------------------------------�����:ţ��ƽ
class CMyChiToLetter
{
public:
	CMyChiToLetter();
	~CMyChiToLetter();
	//TRUE:�õ�����ĸ��д
	//FALSE:�õ�����ĸСд
	BOOL m_blnFirstBig;
	//TRUE:�õ�ȫ����д
	//FALSE:�õ���ȥ��ƴ��������Сд
	BOOL m_blnAllBiG;
	//True:�õ�ȫ��ƴ��
	//FALSE:�õ���ƴ��
	BOOL m_blnSimaple;
	CString GetLetter(CString strText);
private:
	CString FindLetter(int nCode);
};