//-----------------------------------------------------����ˣ�ţ��ƽ
#ifndef AFX_MYCOLORLISTCTRL_H__9FC7D36B_FC88_42FD_8DAA_2F70016038BA__INCLUDED_
#define AFX_MYCOLORLISTCTRL_H__9FC7D36B_FC88_42FD_8DAA_2F70016038BA__INCLUDED_
#include "MyHeaderCtrl.h"
#include <comdef.h>
//Item����ɫ����
struct CMyColor
{
	COLORREF colText;
	COLORREF colBack;
	COLORREF colSelect;
};
class CMyColorList : public CListCtrl
{
	//�洢ITEM����ɫ����
	CObArray m_ArrayCol;
	//�洢�еĶ��뷽ʽ
	CStringArray m_ArrayHeaderAlign;
public:
	CMyColorList();
	//��ͷ���ػ�
	CMyHeaderCtrl m_ctlHeader;
	//�����Ƿ��ѡ
	BOOL m_blnSelect;
	//������ͷ
	void SetHeader();
	//���һ��
    int AddItem(int image,COLORREF colText);
	//���һ��
    int AddItem(int image,COLORREF colText,COLORREF colBack,COLORREF colSelect);
	//����ITEM����ɫ
	void SetItemColor(int nitem,COLORREF colText,COLORREF colBack,COLORREF colSelect);
	void SetItemColor(int nitem,COLORREF colText);
	//����ITEM����ɫ
	CMyColor GetItemColor(int nitem);
public:
	virtual ~CMyColorList();
	virtual void PreSubclassWindow();
	virtual	void DeleteAllItems();
	virtual void DeleteItem(int nItem);
	virtual void InsertColumn(int nCol, LPCTSTR lpszColumnHeading, int nFormat /* = LVCFMT_LEFT */, int nWidth /* = -1 */, int nSubItem /* = -1 */);
	virtual void InsertItem(int nItem, LPCTSTR lpszItem, int nImage);
protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//{{AFX_MSG(CMyColorList)
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif // AFX_COLORLISTCTRL_H__9FC7D36B_FC88_42FD_8DAA_2F70016038BA__INCLUDED_
