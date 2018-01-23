//ʹ��˵��
//1:����״̬������:
//		A:������ȱʡ״̬���ö԰�ť���κ�����
//		B:����ΪDisable��NotifyΪ��̬���ı�
//		C:����ΪFlatΪ�����ε�
//2:���ö��뷽ʽ(SetXAlign)
//		A:�������� 0 
//		B:�������� 1
//		C:�������� 2
//		D:�������� 3
//3:����ͼ��(SetXico)
//------------------------------------------------------�����:ţ��ƽ
#if !defined(AFX_MyButton_H__5254170E_59CF_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_MyButton_H__5254170E_59CF_11D1_ABBA_00A0243D1382__INCLUDED_
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
class CMyButton : public CButton
{
// Construction
public:
	CMyButton();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyButton();
	//��״����������
	CRgn   m_rgn;
	//Ч��ɫ1
	COLORREF m_clrLeft;
	//Ч��ɫ2
	COLORREF m_clrRight;
	//�ı�ɫ
	COLORREF m_clrText;
	//����ɫ
	COLORREF m_clrBack;
	//����ΪFlatʱ�ı���ɫ
	COLORREF m_clrFlatBack;
	//��ʾ��ʽ
	//�ı� 0 ͼ�� 1 ;
	int intStyle;
	//���뷽ʽ
	//�������� 0  ��������1 ��������2 �������� 3
	int	intAlgin;
	//����Ƿ��ǰ���״̬
	BOOL m_blnMouseOn;
	//���ð�ť��ʽ
	//0-���� 1-��Բ 2-��Բ
	int intButtonFace;
	//ͼ��
	HICON Xicon;
	//ͼ��ĸ߶�
	DWORD dwIconHeight;
	//ͼ��Ŀ��
	DWORD dwIconWidth;
	//���ñ���ɫ
	void SetBackColor(COLORREF color);
	//�����ı�ɫ
	void SetTextColor(COLORREF color);
	//����Ч��ɫ
	void SetMaskColor(COLORREF colLeft,COLORREF colRight);
	//��������ΪFlatʱ�ı���ɫ
	void SetFlatBack(COLORREF colFlat);
	//����뿪��ťʱ����
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	//����ͼ��
	void SetXIcon(UINT nIDResource);
	//��ʾ��ʽ
	//�������� 0  ��������1 ��������2 �������� 3
	void SetXAlign(int Align);
	//ͼ���б�
	CImageList m_imgList;
	//ͼ���С
	CSize m_imgSize;
	//�ı� 0 ͼ�� 1;
	void SetXStyle(int Style);
	//���ñ���
	void SetBackImage(UINT nIDResource);
	//���ð�ť��ʽ
	void SetButtonFace(int intStyle);
	//����ͼ��ť
	void SetForeImage(UINT nIDResource,CSize sz);
	// Generated message map functions
protected:
	//{{AFX_MSG(CMyButton)
	//}}AFX_MSG
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
private:
	//��ͼ��
	void DrawIconX(CDC *pDC,CRect rcItem);
	//����ͼ�꣬�ͷ��ڴ�
	void DestroyXIcon();
	//�õ�ͼ�����Ϣ
	void GetXiconInf();
	void DrawImgX(CDC *pDC,CRect rcItem);
	//������ˢ
	CBrush m_BackBrush;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MyButton_H__5254170E_59CF_11D1_ABBA_00A0243D1382__INCLUDED_)
