//
//ʱ��������͵������͵�����
//-------------------------------------------------------����ˣ�ţ��ƽ
#ifndef _MYNUMDEFINE_
#define _MYNUMDEFINE_
//����������ʽ����������
class CMyNumEdit : public CEdit
{
	DECLARE_DYNAMIC(CMyNumEdit)
public:
	CMyNumEdit();
public:
	CString m_strText;
	int m_intLeft;
	int m_intRight;
	int m_Point;
	BOOL blnAuto;
	//����
public:
	//��������
	//intRightΪС����λ��
	void SetNumType(int intLeft,int intRight);
	//�����ַ���
	CString GetText();
	//�����ַ�������
	void SetText(CString strText);
	//��������
	virtual ~CMyNumEdit();
	//��������͵��ַ�
	BOOL CheckInt(char nchar,int StartPos,int StartEnd);
	//���ʱ���Ե��ַ�
	BOOL CheckFloat(char nchar,int StartPos,int StratEnd);
protected:
	//{{AFX_MSG(CMaskEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LONG OnCut(UINT, LONG);
	afx_msg LONG OnClear(UINT wParam, LONG lParam);
	afx_msg LONG OnPaste(UINT, LONG);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif
