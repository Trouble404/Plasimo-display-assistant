//˵����
//1:���еĽ������Է���Ľ����б�ĸ��ֲ���
//2:������Ӧ�����ڵ�����²���������µ���
//3:��blnMenu����ΪTRUEʱ������ʾ���в˵�
//4:���Բ�������������Ϊ
//		A:CBo�б���(ctr_Edit_Cbo):AddCboItem��RemoveCboItem	
//      B:Edit�༭��(ctr_Edit_Text)
//      C:DateTime��(ctr_Edit_DateTime)
//      E:Time��(Ctr_Edit_Time)
//      F:Date��(Ctr_Edit_Date)
//      G:������(Ctr_Edit_Num):SetNumStyle��GetNumStyle
//		H:û�б༭����(Ctr_Edit_No)
//5:ʹ�ù����г������������踺��
//----------------------------------------------------------�����:ţ��ƽ
#ifndef MYSORTLISTCTRL_H
#define MYSORTLISTCTRL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef SORTHEADERCTRL_H
	#include "MyHeaderCtrl.h"
#endif	
#ifdef _DEBUG
	#define ASSERT_VALID_STRING( str ) ASSERT( !IsBadStringPtr( str, 0xfffff ) )
#else	//	_DEBUG
	#define ASSERT_VALID_STRING( str ) ( (void)0 )
#endif	//	_DEBUG
//�˵���Դ��
#include "MyDateEdit.h"
#include "MyNumEdit.h"
#define ID_MENU_show1 WM_USER+11
#define ID_MENU_show2 WM_USER+11
#define ID_MENU_sep WM_USER+12
#define ID_MENU_icon WM_USER+13
#define ID_MENU_smallicon WM_USER+14
#define ID_MENU_list WM_USER+15
#define ID_MENU_report WM_USER+16
#define ID_MENU_No WM_USER+17
#define ID_MENU_Click WM_USER+18
#define ID_MENU_DblClick WM_USER+19
//�༭����Դ��
#define ID_EditText WM_USER+1
#define ID_EditDateTime WM_USER+2
#define ID_EditCboDown WM_USER+3
#define ID_EditCboList WM_USER+4
#define ID_EditNum WM_USER+5
#define ID_EditPoP WM_USER+6

//�б�༭ģʽ
#define ctr_Edit_No 0
#define ctr_Edit_Text 1
#define ctr_Edit_Date 2
#define ctr_Edit_DateTime 3
#define ctr_Edit_Time 4
#define ctr_Edit_CboDown 5
#define ctr_Edit_CboDownList 6
#define ctr_Edit_Num 7
//�����༭ģʽ
#define ctr_Edit_No 0
#define ctr_Edit_Click 1
#define ctr_Edit_DblClick 2
class CMyListCtrl : public CListCtrl
{
public:
	//���캯��
	CMyListCtrl();
	//ɾ��һ��
	BOOL DeleteItem( int iItem );
	//ɾ��������
	BOOL DeleteAllItems();
	//���������ַ�
	BOOL SetItemText( int nItem, int nSubItem, LPCTSTR lpszText );
	//���е���
	void Sort( int iColumn, BOOL bAscending );
	//���õ�������
	BOOL SetItemData(int nItem, DWORD dwData);
	//���ص�������
	DWORD GetItemData(int nItem) const;
	//���һ��
	//image:ͼ������
	int AddItem(int image);
	//���һ��
	//nformat:LVCFMT_CENTER
	int InsertColumnX(CString strName,int nFormat,int iWidth,int intEdit);
	//�������з�ʽ��ʽ(LVS_ICON,LVS_SMALLICON,LVS_LIST,LVS_REPORT)
	void SetMyStyle(DWORD dwNewStyle);
	//���ص�ǰ�����з�ʽ(LVS_ICON,LVS_SMALLICON,LVS_LIST,LVS_REPORT)
	DWORD GetMyStyle();
	//ע����ͷ
	BOOL SetHeader();
	//�����Ƿ���ʾ�˵�
	void SetShowMenu(BOOL blnShow);
	//���ñ༭���λ��
	void SetEditPos(BOOL blnShow,int itemX,int itemY,BOOL blnCbo);
	//�����еı༭ģʽ
	void SetColumnStyle(int item,int intEdit);
	//�õ���ı༭ģʽ
	int GetColumnStyle(int item);
	CStringArray *GetCboArrayData(int nitem);
	BOOL blnAllEdit;
	BOOL blnMenu;
	CEdit ctl_EditText;
	CMyDateEdit ctl_EditDateTime;
	CComboBox ctl_EditComboDown;
	CComboBox ctl_EditComboDownList;
	CMyNumEdit ctl_EditNum;
	BOOL m_bSortAscending;
	//0:NO 1:click 2:doubleclick
	int m_EditStyle;
	CStringArray strArrayEditStyle;
	CStringArray CboArrayIndex;
	CObArray CboArrayData;
	CStringArray NumArrayIndex;
	CObArray NumArrayData;
	CStringArray NumArrayAuto;
	CMyHeaderCtrl m_ctlHeader;
	int itemX;
	int itemY;
	void GetItemPos(CPoint point);
	BOOL Key_Shift(int& nItem,int& nSub);
	BOOL Key_Ctrl(int& nItem,int &nSub);
	//��Cbo���������
	void AddCboItem(int nItem,CString strText);
	//��Cboɾ��strText��
	void RemoveCboItem(int nitem,CString strText);
	//��Cbo���������
	void FillCboData(int nitem);
	//intLeft:��������
	//intRight:С������	
	void SetNumEditStyle(int nitem,int intLeft,int intRight);
	void SetNumEditAuto(int nitem,BOOL blnAuto);
	//���������͵��Ƿ��Զ����
	BOOL GetNumEditAuto(int nitem);
	//����Num���͵ķ�Χ
	//CPoint.X:��������
	//CPoint.y:С������
	CPoint *GetNumEditStyle(int nitem);
	//
	void SetItemFont(CFont ft);
	//{{AFX_VIRTUAL(CMyListCtrl)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
public:
	virtual ~CMyListCtrl();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditListCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	static int CALLBACK CompareFunction( LPARAM lParam1, LPARAM lParam2, LPARAM lParamData );
	void FreeItemMemory( const int iItem );
	BOOL CMyListCtrl::SetTextArray( int iItem, LPTSTR* arrpsz );
	LPTSTR* CMyListCtrl::GetTextArray( int iItem ) const;
	int m_iNumColumns;
	int m_iSortColumn;
	//{{AFX_MSG(CMyListCtrl)
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnRButtonDown( UINT nFlags, CPoint point );
	afx_msg void OnLButtonDblClk( UINT nFlags, CPoint point );
	afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
	afx_msg void OnMenuitemlist();
	afx_msg void OnMenuitemicon();
	afx_msg void OnMenuitemsmallicon();
	afx_msg void OnMenuitemreport();
	afx_msg void OnMenuNo();
	afx_msg void OnMenuClick();
	afx_msg void OnMenuDblClick();
	afx_msg void OnParentNotify(UINT message, LPARAM lParam);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // SORTLISTCTRL_H
