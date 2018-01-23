//
//ʱ��������͵������͵�����
//-------------------------------------------------------����ˣ�ţ��ƽ
#ifndef _MYMASKDEFINE_
#define _MYMASKDEFINE_
//����������ʽ����������
#define edit_date 1
#define edit_time 2
#define edit_datetime 3
#include<comdef.h>
class CMyDateEdit : public CEdit
{
	DECLARE_DYNAMIC(CMyDateEdit)
public:
	CMyDateEdit();
public:
	//�Ƿ�ʹ������
	BOOL m_bUseMask;
	//�Ƿ������ڸ�ʽ
	BOOL m_isDate;
	//�Ƿ���ʱ���ʽ
	BOOL m_isTime;
	//�Ƿ�������ʱ���ʽ
	BOOL m_isDateTime; 
	//�洢�û�������ַ���
	CString m_str;
	//����
	CString m_strMask;
	//��ʾĳλ�Ƿ�����룬��_����ʾ������
	CString m_strLiteral;
	//�洢Ԥ����ַ��������û������˸����ʱ��ʹ��
	CString m_strMaskLiteral;
	BOOL m_bMaskKeyInProgress;
public:
	//ȱʡ
	void SetDefault();
	//���óɵ�ǰʱ��
	void SetNow();
	//��������
	void Reset();
	//��������
	void SetClassType(int intStyle);
	//�����ַ���
	CString GetText();
	//�����ַ�������
	void SetText(CString strText);
	//���ü����ȷ��ʱ��
	void SetDetectText(CString strText);
	//�õ������ȷ��ʱ��
	CString GetDetectText();
	//����ʱ��ֵ�����Զ�����ת����������ַ���
	void SetTimeValue(COleDateTime tm);
	//ģ�ⷢ��һ�ַ����в���
	void SendChar(UINT nChar);
	//����ַ��Ϸ���
	BOOL CheckChar(UINT nChar);
	//��������
	virtual ~CMyDateEdit();
	//ճ������
    LONG OnPaste(UINT, LONG);
	//��������
    LONG OnCut(UINT, LONG);
	//�������
    LONG OnClear(UINT, LONG);
	//��������͵��ַ�
	BOOL CheckDate(char nchar,int StartPos,int StartEnd);
	//���ʱ���Ե��ַ�
	BOOL CheckTime(char nchar,int StartPos,int StratEnd);
protected:
	//{{AFX_MSG(CMaskEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif
