#pragma once



// MyPropertySheet

class MyPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(MyPropertySheet)

public:
	MyPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	MyPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~MyPropertySheet();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};


