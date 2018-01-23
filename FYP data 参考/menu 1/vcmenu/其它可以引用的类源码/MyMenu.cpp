#include "stdafx.h"
#include "MyMenu.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
CMyMenu::CMyMenu()
{
	//����
	m_topStyle=1;
	m_clrSelectLeft=RGB(97,244,78);
	m_clrSelectRight=RGB(52,148,39);
	m_clrTop=RGB(161,192,245);
	m_clrText=RGB(0,0,0);
}

CMyMenu::~CMyMenu()
{
	//����
}
/**********************************************************
��  ��  ��:GetImageFromToolBar
��      ��:�ӹ�������ȡ��ͼƬ
��  ��  ��:UINT uToolBarID, CSize sz, CImageList *pImageList,  CUIntArray *uIDArray
��	��  ֵ:���� ImageCount
***********************************************************/
int		CMyMenu::GetImageFromToolBar(UINT uToolBarID, CSize sz, CImageList *pImageList,  CUIntArray *uIDArray)
{
	if(uToolBarID <= 0 || pImageList == NULL || uIDArray == NULL)
		return -1;
	CToolBar wndToolBar;
	if(!wndToolBar.Create(AfxGetMainWnd()) || !wndToolBar.LoadToolBar(uToolBarID))
	{
		return -1;
	}
	int nCount = wndToolBar.GetCount();
	if(nCount <= 0)
	{
		return -1;
	}
	COLORREF Maskcol=RGB(192,192,192);
	pImageList->Create(uToolBarID, sz.cx, sz.cy, Maskcol);
	int nImageCount = pImageList->GetImageCount();
	for(int i = 0; i < nCount; i ++)
	{
		UINT uID = wndToolBar.GetItemID(i);
		if(uID != ID_SEPARATOR)
		{
			uIDArray->Add(uID);
		}
	}
	int nSize = uIDArray->GetSize();
	ASSERT(nSize == nImageCount);
	return nSize;
}
/**********************************************************
��  ��  ��:GetIconIndexByID
��      ��:��ImageList ��ȡ��ͼ�������
��  ��  ��:UINT uID
��	��  ֵ:�ɹ�ʱ�������������򷵻�-1
***********************************************************/
int		CMyMenu::GetIconIndexByID(UINT uID)
{	
	for(int i = 0; i < m_menuIDs.GetSize(); i ++)
	{
		if(uID == m_menuIDs[i])
		{
			ASSERT(i < m_ImageList.GetImageCount());
			return i;
		}
	}
	return -1;
}
/**********************************************************
��  ��  ��:ChangeMenuStyle
��      ��:�ı����˵��ķ��
��  ��  ��:HMENU hMenu, BOOL bTop
��	��  ֵ:BOOL,dndn�ɹ�ʱ�����棬ʧ��ʱ����
***********************************************************/
BOOL	CMyMenu::ChangeMenuStyle(HMENU hMenu, BOOL bTop = FALSE)
{
	CMenu *pMenu = CMenu::FromHandle(hMenu);
	if(pMenu != NULL)
	{
		for(UINT i = 0; i < pMenu->GetMenuItemCount(); i ++)
		{
			CMenuItemContext *lpMenu = new CMenuItemContext;
			lpMenu->nMenuID = pMenu->GetMenuItemID(i);
			if(lpMenu->nMenuID < 0 && bTop)
			{
				lpMenu->nMenuID = -2;
			}
			pMenu->GetMenuString(i, lpMenu->strText, MF_BYPOSITION);
			pMenu->ModifyMenu(i, MF_BYPOSITION | MF_OWNERDRAW,
				lpMenu->nMenuID, LPCTSTR(lpMenu));
			CMenu *pSubMenu = pMenu->GetSubMenu(i);
			if(pSubMenu && lpMenu->nMenuID != -2 && !bTop)
			{
				lpMenu->nMenuID = -1;
			}
			if(pSubMenu)
			{
				ChangeMenuStyle(pSubMenu->GetSafeHmenu());
			}
		}
	}
	return TRUE;
}
/**********************************************************
��  ��  ��:AttachMenu
��      ��:����ǰ���ڵĲ˵����ҵĲ˵�����
��  ��  ��:HMENU hMenu,UINT uToolBarID,CSize sz
��	��  ֵ:BOOL,dndn�ɹ�ʱ�����棬ʧ��ʱ����
***********************************************************/
BOOL	CMyMenu::AttachMenu(HMENU hMenu,UINT uToolBarID,CSize sz)
{
	Attach(hMenu);
	ChangeMenuStyle(GetSafeHmenu(), TRUE);
	if(uToolBarID!=0)
	GetImageFromToolBar(uToolBarID, sz, &m_ImageList, &m_menuIDs);
	return TRUE;
}
void CMyMenu::LoadMenu(UINT nIDResource)
{
	ChangeMenuStyle(GetSafeHmenu(), TRUE);
	CMenu::LoadMenu(nIDResource);
}
/**********************************************************
��  ��  ��:AddToolBar
��      ��:���б����
��  ��  ��:UINT uToolBarID, CSize sz
��	��  ֵ:������ӵĸ���
***********************************************************/
UINT	CMyMenu::AddToolBar(UINT uToolBarID, CSize sz=CSize(16,15))
{
	CImageList Image;
	CUIntArray IDArray;
	int nRet = GetImageFromToolBar(uToolBarID, sz, &Image, &IDArray);
	if(nRet > 0)
	{
		for(int i = 0; i < Image.GetImageCount(); i ++)
		{
			HICON hIcon = Image.ExtractIcon(i);
			if(hIcon != NULL)
			{
				m_ImageList.Add(hIcon);
				m_menuIDs.Add(IDArray[i]);
			}
		}
	}
	return nRet;
	
}
/**********************************************************
��  ��  ��:DrawBestRect
��      ��:������������Ч����
��  ��  ��:CDC *pDC, CRect rect, COLORREF cr1,COLORREF cr2, BOOL bHor
��	��  ֵ:NULL
***********************************************************/
void	CMyMenu::DrawBestRect(CDC *pDC, CRect rect, COLORREF cr1,COLORREF cr2, BOOL bHor)
{
	int r1 = GetRValue(cr1);//Red color1
	int g1 = GetGValue(cr1);//Green color1
	int b1 = GetBValue(cr1);//blue color1
	int r2 = GetRValue(cr2);//red color2
	int g2 = GetGValue(cr2);//green color2
	int b2 = GetBValue(cr2);//blue color2
	if(bHor)
	{
		float dr = ((float)(r2 - r1))/(float)(rect.Width());
		float dg = ((float)(g2 - g1))/(float)(rect.Width());
		float db = ((float)(b2 - b1))/(float)(rect.Width());
		for(int i = rect.left; i < rect.right; i ++)
		{
			int r = r1 + (int)(dr*((float)(i - rect.left)));
			int g = g1 + (int)(dg*((float)(i - rect.left)));
			int b = b1 + (int)(db*((float)(i - rect.left)));
			CPen pen(PS_SOLID, 1, RGB(r, g, b));
			CPen *old = pDC->SelectObject(&pen);
			pDC->MoveTo(i, rect.top);
			pDC->LineTo(i, rect.bottom);
			pDC->SelectObject(old);
		}
	}
	else
	{
		float dr = ((float)(r2 - r1))/(float)(rect.Height());
		float dg = ((float)(g2 - g1))/(float)(rect.Height());
		float db = ((float)(b2 - b1))/(float)(rect.Height());
		for(int i = rect.top; i < rect.bottom; i ++)
		{
			int r = r1 + (int)(dr*((float)(i - rect.top)));
			int g = g1 + (int)(dg*((float)(i - rect.top)));
			int b = b1 + (int)(db*((float)(i - rect.top)));
			CPen pen(PS_SOLID, 1, RGB(r, g, b));
			CPen *old = pDC->SelectObject(&pen);
			pDC->MoveTo(rect.left, i);
			pDC->LineTo(rect.right, i);
			pDC->SelectObject(old);
		}
	}
}
/**********************************************************
��  ��  ��:DrawTop
��      ��:����˲˵�
��  ��  ��:CDC *pDC,CRect rect,BOOL bSelected
��	��  ֵ:NULL
***********************************************************/
void	CMyMenu::DrawTop(CDC *pDC,CRect rect,BOOL bSelected)
{	
	rcMain.top=rect.top;
	rcMain.bottom=rect.bottom;
	DrawTopBack(pDC);
	if(bSelected)
	{
		DrawBGColor(pDC,rect,TRUE);
	}
	else
	{
		DrawTopBack(pDC,rect);
	}
}
/**********************************************************
��  ��  ��:DrawBGColor
��      ��:�˵���ı������������
��  ��  ��:CDC* pDC, CRect rect, BOOL bSelected
��	��  ֵ:NULL
***********************************************************/
void	CMyMenu::DrawBGColor(CDC* pDC, CRect rect, BOOL bSelected)
{
	if(bSelected)
	{
		pDC->SelectStockObject(NULL_BRUSH);
		pDC->SelectStockObject(BLACK_PEN);
		pDC->Rectangle(&rect);
		rect.DeflateRect(1, 1);
		DrawBestRect(pDC,rect,m_clrSelectLeft,m_clrSelectRight,TRUE);
	}
	else
	{
		CRect rcGray(rect);
		rcGray.right = rcGray.left + Public_Area;
		int r1=GetRValue(m_clrTop);
		int g1=GetGValue(m_clrTop);
		int b1=GetBValue(m_clrTop);
		for(int i=rcGray.Width()/2;i>=0;i--)
		{
			r1=(r1+5)>255?255:(r1+5);
			g1=(g1+5)>255?255:(g1+5);
			b1=(b1+5)>255?255:(b1+5);
			CPen pen(PS_SOLID, 1, RGB(r1, g1, b1));
			CPen *old = pDC->SelectObject(&pen);
			pDC->MoveTo(rcGray.left+i,rcGray.top);
			pDC->LineTo(rcGray.left+i,rcGray.bottom);
			pDC->MoveTo(rcGray.right-i,rcGray.top);
			pDC->LineTo(rcGray.right-i,rcGray.bottom);
			pDC->SelectObject(old);
		}	
		CRect rcWhite(rect);
		rcWhite.left = rcGray.right;
		pDC->FillSolidRect(&rcWhite,RGB(0x000000F9, 0x000000F8, 0x000000F7));
	}
}
/**********************************************************
��  ��  ��:DrawIcon
��      ��:����ͼ��
��  ��  ��:CDC* pDC, CRect rect, UINT uIndex, BOOL IsEnabled
��	��  ֵ:NULL
***********************************************************/
void	CMyMenu::DrawIcon(CDC* pDC, CRect rect, UINT uIndex, BOOL IsEnabled)
{
	rect.DeflateRect(3, 3, 3, 3);
	UINT	uStyle =ILD_TRANSPARENT;	//CImageList::Draw()����λͼ�ķ��
	if(IsEnabled)
	{
		uStyle |=ILD_BLEND50;//�˵���Ч����λͼҲҪ��������
	}
	else
	{
		uStyle |=ILD_BLEND25	;
	}
	m_ImageList.Draw(pDC, uIndex, CPoint(rect.left, rect.top), uStyle);
	//	HICON hIcon = m_ImageList.ExtractIcon(uIndex);
}
/**********************************************************
��  ��  ��:DrawText
��      ��:�����˵�����ı�
��  ��  ��:CDC* pDC, CRect rect, CString sText
��	��  ֵ:NULL
***********************************************************/
void	CMyMenu::DrawText(CDC* pDC, CRect rect, CString sText)
{
	rect.DeflateRect(4,0,0,0);
	pDC->SetTextColor(m_clrText);
	pDC->DrawText(sText, &rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	
}
/**********************************************************
��  ��  ��:DrawGray
��      ��:�����Ч�˵�����ı�
��  ��  ��:CDC* pDC, CRect rect, CString sText
��	��  ֵ:NULL
***********************************************************/
void	CMyMenu::DrawGray(CDC* pDC, CRect rect, CString sText)
{
	rect.DeflateRect(4, 0, 0, 0);
	CRect	rt(rect);
	int nMode =pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(127,127,127));
	pDC->DrawText(sText,&rect,DT_EXPANDTABS|DT_VCENTER|DT_SINGLELINE);
	
}
/**********************************************************
��  ��  ��:DrawItem
��      ��:�ֿ���ÿһ�˵���
��  ��  ��:LPDRAWITEMSTRUCT  lpDIS���˵�������
��	��  ֵ:NULL
***********************************************************/
void	CMyMenu::DrawItem(LPDRAWITEMSTRUCT  lpDIS)
{	
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);	// get dc
	VERIFY(pDC);pDC->SetBkMode(TRANSPARENT);// get position
	CRect rcItem = lpDIS->rcItem;// get states
	UINT uState = lpDIS->itemState;	// the data of menu item is NULL then return
	if(lpDIS->itemData == NULL)	return;
	CString strText     = ((CMenuItemContext*)(lpDIS->itemData))->strText;
	CMenuItemContext *p=((CMenuItemContext*)(lpDIS->itemData));
	UINT nMenuID        = ((CMenuItemContext*)(lpDIS->itemData))->nMenuID;
	CRect rcIcon(rcItem);
	rcIcon.right = rcIcon.left + Public_Area;
	CRect rcText(rcItem);
	rcText.left  = rcIcon.right;
	switch(nMenuID)
	{
	case -2:// -2:����˵��� 
		if(uState&ODS_SELECTED)
		{
			DrawTop(pDC,rcItem,TRUE);
		}
		else
		{
			DrawTop(pDC,rcItem,FALSE);
		}
		DrawText(pDC,rcItem,strText);
		break;
	case -1://-1:�����˵�  
		strText= "\t   "+strText;
		if(uState&ODS_SELECTED)//��ѡ��
		{
			DrawBestRect(pDC,rcItem,m_clrSelectLeft,m_clrSelectRight,TRUE);
		}
		else
		{
			DrawBGColor(pDC,rcItem,FALSE);//
		}
		//DrawTop(pDC,rcItem,FALSE);
		rcText.left=2.5;
		DrawText(pDC,rcText,strText);
		break;
	case 0://0:�ָ���  
		rcText.top =rcText.Height()/2+rcText.top ;
		rcText.bottom =rcText.top +2;
		rcText.left +=2;
		rcText.right -=2;
		DrawBGColor(pDC,rcItem,FALSE);
		pDC->Draw3dRect(rcText,RGB(64,0,128),RGB(255,255,255));
		break;
	default://>0:һ��Ĳ˵�	
		if(uState&ODS_SELECTED)//��ѡ��
		{
			DrawBGColor(pDC,rcItem,TRUE);
		}
		else
		{
			DrawBGColor(pDC,rcItem,FALSE);//
		}
		int nIndex = GetIconIndexByID(nMenuID);
		if(uState&ODS_GRAYED)
		{
			if(nIndex >= 0) 
			{
				if(m_ImageList.GetImageCount()>0)
				DrawIcon(pDC,rcItem,nIndex,TRUE);
			}
			DrawGray(pDC,rcText,strText);
			break;
		}
		else
		{
			if(nIndex >= 0) 
			{
				if(m_ImageList.GetImageCount()>0)
				if(uState&ODS_SELECTED)
				{
					CRect rcMy(rcItem);
					rcMy.left=rcMy.left-2;
					rcMy.top=rcMy.top-2;
					DrawIcon(pDC,rcMy,nIndex,FALSE);
				}
				else 
				{
					DrawIcon(pDC,rcItem,nIndex,FALSE);
				}

			}
		}
		if(uState&ODS_CHECKED)//�Ǳ�check����,
		{
			DrawText(pDC,rcItem,"��");
			DrawText(pDC,rcText,strText);//��ǰ״̬��check!
			break;
		}
		else
		{
			DrawText(pDC,rcText,strText);//δѡȡ
			break;
		}
		
		break;
	}
}
/**********************************************************
��  ��  ��:MeasureItem
��      ��:����ÿһ��ķ���
��  ��  ��:LPMEASUREITEMSTRUCT lpMISҪ�õ��Ľṹ
��	��  ֵ:NULL
***********************************************************/
void	CMyMenu::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
{	
	lpMIS->itemWidth = 60;
	lpMIS->itemHeight = 24;
	UINT nMenuID= ((CMenuItemContext*)(lpMIS->itemData))->nMenuID;
	//dc.SelectObject();
	//CSize sz=
	switch(nMenuID)
	{
	case -2:// -2:����˵���  
		lpMIS->itemWidth =80;
		rcMain.left=this->GetMenuItemCount()*(lpMIS->itemWidth+12.8);
		break;
	case -1://-1:�����˵�  
		lpMIS->itemWidth =((CMenuItemContext*)(lpMIS->itemData))->strText.GetLength()*10;
		break;
	case 0://0:�ָ���
		lpMIS->itemHeight =5;
		break;
	default://>0:һ��Ĳ˵�
		lpMIS->itemWidth =((CMenuItemContext*)(lpMIS->itemData))->strText.GetLength()*10;
		break;	//	lpMIS->itemWidth =30;
	}
}
void CMyMenu::SetTopBack(COLORREF clr)
{
	m_topStyle=BACK_COLOR;
	m_clrTop=clr;
}
void CMyMenu::DrawTopBack(CDC* pDC,CRect rcSourse)
{
	pDC->MoveTo(rcSourse.left,rcSourse.top);
	pDC->LineTo(rcSourse.right,rcSourse.top);
	if(m_topStyle==BACK_COLOR)
	{
		int r1=GetRValue(m_clrTop);
		int g1=GetGValue(m_clrTop);
		int b1=GetBValue(m_clrTop);
		for(int i=rcSourse.Height()/2;i>0;i--)
		{
			r1=(r1+4)>255?255:(r1+4);
			g1=(g1+4)>255?255:(g1+4);
			b1=(b1+4)>255?255:(b1+4);
			CPen pen(PS_SOLID, 1, RGB(r1, g1, b1));
			CPen *old = pDC->SelectObject(&pen);
			pDC->MoveTo(rcSourse.left,rcSourse.top+i);
			pDC->LineTo(rcSourse.right,rcSourse.top+i);
			pDC->MoveTo(rcSourse.left,rcSourse.bottom-i);
			pDC->LineTo(rcSourse.right,rcSourse.bottom-i);
			pDC->SelectObject(old);
		}	
	}
	else if(m_topStyle==BACK_PICTURE)
	{
		pDC->FillRect(rcSourse,&m_backbrush);
	}
}
void CMyMenu::DrawTopBack(CDC* pDC)
{
	if(m_topStyle==BACK_COLOR)
	{
		DrawTopBack(pDC,rcMain);
	}
	else if(m_topStyle==BACK_PICTURE)
	{
		pDC->FillRect(rcMain,&m_backbrush);
	}
}
void CMyMenu::SetTopBackImage(UINT nIDResource)
{
	CBitmap tmp;
	m_topStyle=BACK_PICTURE;
	tmp.LoadBitmap(nIDResource);
	m_backbrush.DeleteObject();
	m_backbrush.CreatePatternBrush(&tmp); 
}