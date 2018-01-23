//��ɶԲ˵����ػ�
//����������ΪRGB(192,192,192)
//------------------------------------------------�����:ţ��ƽ
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_MYCOOLMENU_H__061B4615_4569_4278_9F86_6DFF6FCEA45F__INCLUDED_)
#define AFX_MYCOOLMENU_H__061B4615_4569_4278_9F86_6DFF6FCEA45F__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifndef Public_Area
#define Public_Area 20 //����߻�ɫ������
#endif
#define BACK_COLOR 1
#define BACK_PICTURE 2
class CMenuItemContext//����˵��������й���Ϣ
{
public:
	int     nMenuID; 
	//-2:����˵��� //-1:�����˵�
	//0:�ָ���      //>0:һ��Ĳ˵�
	UINT    U_icon;
	CString strText;//menu text 
	
};
class CMyMenu : public CMenu  
{
public:
	//�洢ID����
	CUIntArray m_menuIDs;
	//�洢ͼ������
	CImageList   m_ImageList;
	//������ɫ
	COLORREF m_clrTop;
	//����ͼƬ
	BITMAP m_btmTop;
	//���˵�����
	//BACK_COLOR 1
	//BACK_PICTURE 2
	int    m_topStyle;
	//���˵Ĵ�С
	CRect rcMain;
	//Ч��ɫ1
	COLORREF m_clrSelectLeft;
	//Ч��ɫ2
	COLORREF m_clrSelectRight;
	//�ı�ɫ
	COLORREF m_clrText;
	//���˱�����ˢ
	CBrush m_backbrush;
	CMyMenu();
	virtual ~CMyMenu();
	int			GetImageFromToolBar(UINT uToolBarID, CSize sz, CImageList *pImageList,  CUIntArray *uIDArray);
	int			GetIconIndexByID(UINT uID);
	BOOL		ChangeMenuStyle(HMENU hMenu, BOOL bTop);
	BOOL		AttachMenu(HMENU hMenu,UINT uToolBarID,CSize sz);
	UINT		AddToolBar(UINT uToolBarID, CSize sz);
	void		DrawBestRect(CDC *pDC, CRect rect, COLORREF cr1,COLORREF cr2, BOOL bHor);
	void		DrawTop(CDC *pDC,CRect rect,BOOL bSelected);
	void		DrawBGColor(CDC* pDC, CRect rect, BOOL bSelected);
	void		DrawIcon(CDC* pDC, CRect rect, UINT uIndex, BOOL IsEnabled);
	void		DrawText(CDC* pDC, CRect rect, CString sText);
	void		DrawGray(CDC* pDC, CRect rect, CString sText);
	void		DrawTopBack(CDC* pDC,CRect rcSourse);
	void		DrawTopBack(CDC* pDC);
	void        SetTopBack(COLORREF clr);
	virtual		void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	virtual		void MeasureItem(LPMEASUREITEMSTRUCT lpMIS);
	virtual     void LoadMenu(UINT nIDResource);
	void		SetTopBackImage(UINT nIDResource);
};
#endif // !defined(AFX_MYCOOLMENU_H__061B4615_4569_4278_9F86_6DFF6FCEA45F__INCLUDED_)
