//---------------------------------------------------------�����:ţ��ƽ
#ifndef MYSORTHEADERCTRL_H
#define MYSORTHEADERCTRL_H

#if _MSC_VER > 1000
#pragma once
#endif
class CMyHeaderCtrl : public CHeaderCtrl
{
public:
	CMyHeaderCtrl();
	//{{AFX_VIRTUAL(CMyHeaderCtrl)
	public:
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL
public:
	virtual ~CMyHeaderCtrl();
	//��������
	void SetSortArrow( const int iColumn, const BOOL bAscending );
	//��ʼ��ʱ������ͷ�ػ�
	void SetDefault();
	//����ɫ
	COLORREF m_clrBack;
	//Ч��ɫ1
	COLORREF m_clrLeft;
	//Ч��ɫ2
	COLORREF m_clrRight;
protected:
	void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );
	//�ж���
	int m_iSortColumn;
	//�����뽵��
	BOOL m_bSortAscending;
	//�Ƿ��ʼ���ػ�
	BOOL m_blnDefault;
	//{{AFX_MSG(CMyHeaderCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // SORTHEADERCTRL_H
