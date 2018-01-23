// SplashScreen.cpp: implementation of the CSplashScreen class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "SplashScreen.h"
#include <crtdbg.h>	// for _ASSERT()
#include <stdio.h>	// for vsprintf
#include <stdarg.h>	// for vsprintf

#ifndef ASSERT
#define ASSERT(x) _ASSERT(x)
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//static CSplashScreen *gDlg;
CSplashScreen* CSplashScreen::m_pSplashWnd = NULL;
ATOM CSplashScreen::m_szWindowClass = 0;
BOOL CSplashScreen::m_useStderr = FALSE;

LPTSTR CSplashScreen::m_productNameString = NULL;
LPTSTR CSplashScreen::m_companyNameString = NULL;
LPTSTR CSplashScreen::m_versionNumberString = NULL;
LPTSTR CSplashScreen::m_versionString = NULL;
LPTSTR CSplashScreen::m_copyrightString = NULL;
LPTSTR CSplashScreen::m_commentsString = NULL;
LPTSTR CSplashScreen::m_statusMessage = NULL;

int CSplashScreen::m_millisecondsToDisplay = 0;					// 0 ==> until mouse click or keystroke

// create rectangle that product name has to fit in
const int CSplashScreen::m_productNameVerticalOffset = 160;		// empty space between top border and Product Name
const int CSplashScreen::m_productNameVerticalHeight = 70;		// maximum height of Product Name
const int CSplashScreen::m_productNameLeftMargin = 20;			// distance from left side to place Product Name
const int CSplashScreen::m_productNameRightMargin = 20;			// distance from right side to place Product Name
const LPCTSTR CSplashScreen::m_productNameFontName = "Arial";	// name of font for Product Name
SIZE CSplashScreen::m_productNamePointSize = {-1,-1};			// point size used for the Product Name, (-1,-1) ==> Calculate point size
COLORREF CSplashScreen::m_productNameTextColor = RGB(109,140,44); // color used for Product Name

const BOOL CSplashScreen::m_displayCompanyName = FALSE;			// true if displaying companyName
const BOOL CSplashScreen::m_displayVersion = TRUE;				// true if displaying version
const BOOL CSplashScreen::m_displayCopyright = TRUE;			// true if displaying copyright
const BOOL CSplashScreen::m_displayComments = TRUE;				// true if displaying comments


// create rectangle that strings in body have to fit in
const int CSplashScreen::m_bodyVerticalOffset = 280;			// empty space between top border and top of body
const int CSplashScreen::m_bodyVerticalHeight = 100;			// maximum height of body
const int CSplashScreen::m_bodyLeftMargin = 120;				// distance from left side to place company name, copyright, version and comment
const int CSplashScreen::m_bodyRightMargin = 10;				// distance from right side to place company name, copyright, version and comment
const LPCTSTR CSplashScreen::m_bodyFontName = "Arial";			// name of font for company name, copyright and version	
SIZE CSplashScreen::m_bodyPointSize = {-1,-1};					// point size used for company name, copyright and version, (-1,-1) ==> Calculate point size	
COLORREF CSplashScreen::m_bodyTextColor = RGB(109,140,44);		// color used for company name, copyright and version (-1 ==> use Product Name color)

// create rectangle for status line string
const int CSplashScreen::m_statusVerticalOffset = 390;			// empty space between top border and top of status string
const int CSplashScreen::m_statusVerticalHeight = 50;			// maximum height of status string
const int CSplashScreen::m_statusLeftMargin = 50;				// distance from left side to place status string
const int CSplashScreen::m_statusRightMargin = 10;				// distance from right side to place status string
const LPCTSTR CSplashScreen::m_statusMessageFontName = "Arial";	// name of font for status string	
SIZE CSplashScreen::m_statusMessagePointSize = {-1,-1};			// point size used for status string, (-1,-1) ==> Calculate point size	
COLORREF CSplashScreen::m_statusMessageTextColor = RGB(0,0,255);// color used for status string (-1 ==> use Product Name color)


CSplashScreen::CSplashScreen( HWND parentWnd )
{
	m_hParentWnd = parentWnd;

	GetVersionStrings();
}

CSplashScreen::~CSplashScreen()
{
	if ( m_statusMessage ) {
		delete m_statusMessage;
		m_statusMessage = NULL;
	}
}
void CSplashScreen::HideSplashScreen()
{

	// Destroy the window, and update the mainframe.
	if ( m_pSplashWnd != NULL ) {
		HWND hParentWnd = m_pSplashWnd->m_hParentWnd;
		::DestroyWindow( m_pSplashWnd->m_hWnd );
		if ( hParentWnd && ::IsWindow( hParentWnd ) )
			::UpdateWindow( hParentWnd );
	}
}

void CSplashScreen::ShowSplashScreen(  HWND pParentWnd /*= NULL*/, LPCTSTR statusMessage /*= NULL*/, int millisecondsToDisplay /*= 0*/ )
{
	if ( m_statusMessage ) {
		delete m_statusMessage;
		m_statusMessage = NULL;
	}

	if ( statusMessage ) {
		m_statusMessage = new char[strlen(statusMessage) + 1];
		strcpy ( m_statusMessage, statusMessage );
	}

	m_millisecondsToDisplay = millisecondsToDisplay;

	// Allocate a new splash screen, and create the window.
	if ( m_pSplashWnd == NULL ) {
		m_pSplashWnd = new CSplashScreen ( pParentWnd );
		if (!m_pSplashWnd->Create(pParentWnd)) {
			delete m_pSplashWnd;
			m_pSplashWnd = NULL;
		}
	}
	if ( pParentWnd ) {
		UpdateWindow( pParentWnd);
	}

	// Set a timer to destroy the splash screen.
	if ( m_millisecondsToDisplay ) {
		SetTimer(m_pSplashWnd->m_hWnd, 1, m_millisecondsToDisplay, NULL);
	}

	ShowWindow ( m_pSplashWnd->m_hWnd, SW_SHOW );
	UpdateWindow( m_pSplashWnd->m_hWnd );
	InvalidateRect( m_pSplashWnd->m_hWnd, NULL, FALSE );
	
	// make sure paint message happens
	m_pSplashWnd->ClearMessageQueue();
}
void CSplashScreen::ReportError( LPCTSTR format, ... )
{
	TCHAR buffer[4096];
	va_list argp;
	va_start(argp, format);
	vsprintf(buffer, format, argp);
	va_end(argp);
	if (m_useStderr) {
		fprintf(stderr, buffer);
	} else {
		// OutputDebugString(buffer);
		MessageBox ( m_hWnd, buffer, "Error", MB_ICONERROR );
	}
}
BOOL CSplashScreen::RegisterClass( LPCTSTR szWindowClassName )
{
	m_instance = GetModuleHandle ( NULL );

	// register class
	DWORD lastError;
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= m_instance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClassName;
	wcex.hIconSm		= NULL;

	m_szWindowClass = RegisterClassEx(&wcex);
	if ( m_szWindowClass == 0 ) {
		lastError = ::GetLastError();
		char errorBuffer[_MAX_PATH];
		sprintf( errorBuffer, "Failed to register class - error %d", lastError );
		ReportError ( errorBuffer );
		return FALSE;
	}
	return TRUE;
}

BOOL CSplashScreen::Create( HWND pParentWnd /*= NULL*/)
{
	m_instance = GetModuleHandle ( NULL );

	m_bitmap = LoadBitmap ( m_instance, MAKEINTRESOURCE (IDB_SPLASH) );

	HWND hwndDesktop = GetDesktopWindow(); 
    HDC hdcDesktop = GetDC(hwndDesktop); 

	BITMAPINFO bitmapInfo;
	memset ( &bitmapInfo, 0, sizeof(BITMAPINFOHEADER) );
	bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	int scanLines = GetDIBits(hdcDesktop,		// handle to DC
							  m_bitmap,			// handle to bitmap
							  0,				// first scan line to set
							  0,				// number of scan lines to copy
							  NULL,				// array for bitmap bits
							  &bitmapInfo,		// bitmap data buffer
							  DIB_RGB_COLORS );	// RGB or palette index

	LPCTSTR szTitle = "";
	LPCTSTR szWindowClassName = "SplashScreen";

	// register splash window class if not already registered
	if ( m_szWindowClass == 0 ) {
		BOOL result = RegisterClass( szWindowClassName );
		if ( !result )
			return FALSE;
	}

	DWORD exStyle = 0;
	int xPos = 0;
	int yPos = 0;
	int width = bitmapInfo.bmiHeader.biWidth;
	int height = bitmapInfo.bmiHeader.biHeight;

	// if parent window, center it on the parent window. otherwise center it on the screen
	RECT parentRect;
	if ( pParentWnd == NULL ) {
		::GetWindowRect ( GetDesktopWindow(), &parentRect );
	} else {
		::GetWindowRect ( pParentWnd, &parentRect );
	}
	HWND hwnd = GetDesktopWindow();

	xPos = parentRect.left + (parentRect.right - parentRect.left)/2 - (width/2);
	yPos = parentRect.top + (parentRect.bottom - parentRect.top)/2 - (height/2);

	HMENU menu = NULL;
	m_hWnd = CreateWindowEx( exStyle, szWindowClassName, szTitle, WS_POPUP | WS_VISIBLE,
      xPos, yPos, width, height, pParentWnd, menu, m_instance, this);
	
	if ( m_hWnd == NULL ) {
		DWORD lastError = ::GetLastError();
		char errorBuffer[_MAX_PATH];
		sprintf( errorBuffer, "Failed to create window- error %d", lastError );
		ReportError ( errorBuffer );
		return FALSE;
	}

	// if no parent window, make it a topmost, so eventual application window will appear under it
	if ( pParentWnd == NULL ) {
		::SetWindowPos( m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
	}


	return TRUE;
}
void CSplashScreen::ClearMessageQueue()
{
	MSG msg;
    while (PeekMessage(&msg, m_hWnd,  0, 0, PM_REMOVE)) { 
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK CSplashScreen::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {

	case WM_PAINT:
		m_pSplashWnd->OnPaint ( hWnd );
		break;

	case WM_NCDESTROY:
		delete m_pSplashWnd;
		m_pSplashWnd = NULL;
		break;

	case WM_TIMER:
		m_pSplashWnd->HideSplashScreen();
		break;

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_NCLBUTTONDOWN:
	case WM_NCRBUTTONDOWN:
	case WM_NCMBUTTONDOWN:
		m_pSplashWnd->HideSplashScreen();
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}
HFONT CSplashScreen::CreatePointFont( int pointSize, LPCTSTR fontName, HDC dc)
{
	HFONT font;

	LOGFONT logicalFont;
	memset ( &logicalFont, 0, sizeof(LOGFONT) );
	strcpy ( logicalFont.lfFaceName, fontName );
	
	logicalFont.lfHeight = -MulDiv(pointSize, GetDeviceCaps(dc, LOGPIXELSY), 72); //pointSize * 10;
	font = CreateFontIndirect( &logicalFont );
	return font;
}

SIZE CSplashScreen::FindFontPointSize( HDC paintDC, LPCTSTR fontName, char **stringsToCheck, int numberOfStringsToCheck, SIZE maximumSize )
{
	HFONT font;
	int pointSize = 8;
	SIZE previousLargest;
	SIZE largest;
	previousLargest.cx = 0;
	previousLargest.cy = 0;
	largest.cx = 0;
	largest.cy = 0;

	LOGFONT logicalFont;
	memset ( &logicalFont, 0, sizeof(LOGFONT) );
	strcpy ( logicalFont.lfFaceName, fontName );

	maximumSize.cy /= numberOfStringsToCheck;
	while ( 1 ) {
	
		logicalFont.lfHeight = -MulDiv(pointSize, GetDeviceCaps(paintDC, LOGPIXELSY), 72); //pointSize * 10;
		font = CreateFontIndirect( &logicalFont );
		HFONT originalFont = (HFONT)SelectObject( paintDC, font );

		char **stringsPtr = stringsToCheck;
		for ( int i=0; i<numberOfStringsToCheck; i++ ) { 
			LPCTSTR string = *stringsPtr++;
			int stringLength = strlen ( string );
			SIZE szString;
			GetTextExtentPoint32( paintDC, string, stringLength, &szString );
			if (  largest.cx < szString.cx ) {
				previousLargest = largest;
				largest.cx = szString.cx;
				largest.cy = szString.cy;
			}
		}

		SelectObject( paintDC, originalFont );
		DeleteObject( font );

		if ( largest.cx > maximumSize.cx )
			break;
		if ( largest.cy > maximumSize.cy )
			break;

		pointSize += 2;

	}
	pointSize -= 2;
	SIZE ret;
	ret.cx = previousLargest.cy;		// in cx, return actual height of font in device units
	ret.cy = pointSize;
	return ret;
}

void CSplashScreen::DisplayProductName( HDC paintDC, int windowWidth, int windowHeight )
{
	SIZE sectionSize;

	int productNameLeftMargin = m_productNameLeftMargin;
	int productNameRightMargin = windowWidth - m_productNameRightMargin;
	int widthOfProductName = productNameRightMargin - productNameLeftMargin;
	sectionSize.cx = widthOfProductName;
	sectionSize.cy = m_productNameVerticalHeight;

	if ( (m_productNamePointSize.cx == -1) && (m_productNamePointSize.cy == -1) ) {
		ASSERT ( m_productNameString );	// Check Resources: version : ProductName
		m_productNamePointSize = FindFontPointSize( paintDC, m_productNameFontName, &m_productNameString, 1, sectionSize );
	}

	int topOfText = m_productNameVerticalOffset; 
	int bottomOfText = topOfText + m_productNameVerticalHeight; 
	RECT productNameRect;
	productNameRect.left = productNameLeftMargin;
	productNameRect.top = topOfText;
	productNameRect.right = productNameRightMargin;
	productNameRect.bottom = bottomOfText;

	HFONT productNameFont = CreatePointFont( m_productNamePointSize.cy, m_productNameFontName, paintDC );
	HFONT originalFont = (HFONT)SelectObject( paintDC, productNameFont );

	SetTextColor( paintDC, m_productNameTextColor );
	SetBkMode( paintDC, TRANSPARENT);
	DrawText( paintDC, m_productNameString, strlen(m_productNameString), &productNameRect, DT_VCENTER|DT_CENTER|DT_SINGLELINE );

	SelectObject( paintDC, originalFont);
	DeleteObject( productNameFont );
}


void CSplashScreen::DisplayBody( HDC paintDC, int windowWidth, int windowHeight )
{
	SIZE sectionSize;
	int bodyLeftMargin = m_bodyLeftMargin;
	int bodyRightMargin = windowWidth - m_bodyRightMargin;
	int widthOfBody = bodyRightMargin - bodyLeftMargin;
	sectionSize.cx = widthOfBody;
	sectionSize.cy = m_bodyVerticalHeight;


	char * stringsToCheck[6];
	char ** pStringsToCheck = &stringsToCheck[0];
	//int stringsInBody = (int)m_displayCompanyName + (int)m_displayVersion + (int)m_displayCopyright + (int)m_displayComments;
	if ( (m_bodyPointSize.cx == -1) && (m_bodyPointSize.cy == -1) ) {
		if ( m_displayCompanyName && m_companyNameString ) //by chen
			*pStringsToCheck++ = m_companyNameString;
		if ( m_displayVersion && m_versionString ) //by chen
			*pStringsToCheck++ = m_versionString;
		if ( m_displayCopyright && m_copyrightString ) //by chen
			*pStringsToCheck++ = m_copyrightString;
		if ( m_displayComments && m_commentsString ) //by chen
			*pStringsToCheck++ = m_commentsString;
		int stringsInBody = pStringsToCheck - &stringsToCheck[0];
		m_bodyPointSize= FindFontPointSize( paintDC, m_bodyFontName, stringsToCheck, stringsInBody, sectionSize );
	}

	// check that strings will fit vertically
	int singleStringOfBodyHeight = m_bodyPointSize.cx;

	int topOfText = m_bodyVerticalOffset; 
	RECT companyNameRect;
	if ( m_displayCompanyName && m_companyNameString) {
		companyNameRect.left = bodyLeftMargin;
		companyNameRect.top = topOfText;
		companyNameRect.right = bodyRightMargin;
		companyNameRect.bottom = topOfText+singleStringOfBodyHeight;
		topOfText += singleStringOfBodyHeight;
	}

	RECT versionRect;
	if ( m_displayVersion && m_versionString ) {
		versionRect.left = bodyLeftMargin;
		versionRect.top = topOfText;
		versionRect.right = bodyRightMargin;
		versionRect.bottom = topOfText+singleStringOfBodyHeight;
		topOfText += singleStringOfBodyHeight;
	}

	RECT copyrightRect;
	if ( m_displayCopyright && m_copyrightString ) {
		copyrightRect.left = bodyLeftMargin;
		copyrightRect.top = topOfText;
		copyrightRect.right = bodyRightMargin;
		copyrightRect.bottom = topOfText+singleStringOfBodyHeight;
		topOfText += singleStringOfBodyHeight;
	}

	RECT commentsRect;
	if ( m_displayComments && m_commentsString ) {
		commentsRect.left = bodyLeftMargin;
		commentsRect.top = topOfText;
		commentsRect.right = bodyRightMargin;
		commentsRect.bottom = topOfText+singleStringOfBodyHeight;
		topOfText += singleStringOfBodyHeight;
	}


	// display body (Company Name, Version, Copyright and Comments)
	HFONT bodyFont = CreatePointFont( m_bodyPointSize.cy, m_bodyFontName, paintDC );
	HFONT originalFont = (HFONT)SelectObject( paintDC, bodyFont );
	SetTextColor( paintDC, (m_bodyTextColor == -1) ? m_productNameTextColor : m_bodyTextColor );
	SetBkMode(paintDC, TRANSPARENT);
	if ( m_displayCompanyName && m_companyNameString )
		DrawText( paintDC, m_companyNameString, strlen(m_companyNameString), &companyNameRect, DT_VCENTER|DT_CENTER|DT_SINGLELINE );
	if ( m_displayVersion && m_versionString)
		DrawText( paintDC, m_versionString, strlen(m_versionString), &versionRect, DT_VCENTER|DT_CENTER|DT_SINGLELINE );
	if ( m_displayCopyright && m_copyrightString)
		DrawText( paintDC, m_copyrightString, strlen(m_copyrightString), &copyrightRect, DT_VCENTER|DT_CENTER|DT_SINGLELINE );
	if ( m_displayComments && m_commentsString )
		DrawText( paintDC, m_commentsString, strlen(m_commentsString), &commentsRect, DT_VCENTER|DT_CENTER|DT_SINGLELINE );

	SelectObject( paintDC, originalFont);
	DeleteObject( bodyFont );
}

void CSplashScreen::DisplayStatusLine( HDC paintDC, int windowWidth, int windowHeight )
{
	SIZE sectionSize;
	int statusLeftMargin = m_statusLeftMargin;
	int statusRightMargin = windowWidth - m_statusRightMargin;
	int widthOfStatus = statusRightMargin - statusLeftMargin;
	sectionSize.cx = widthOfStatus;
	sectionSize.cy = m_statusVerticalHeight;

	int topOfText = m_statusVerticalOffset; 
	int bottomOfText = topOfText + m_statusVerticalHeight; 
	RECT statusRect;
	statusRect.left = 0;
	statusRect.top = topOfText;
	statusRect.right = windowWidth;
	statusRect.bottom = topOfText + m_statusVerticalHeight;

	if ( (m_statusMessagePointSize.cx == -1) && (m_statusMessagePointSize.cy == -1) ) {
		m_statusMessagePointSize = FindFontPointSize( paintDC, m_statusMessageFontName, &m_statusMessage, 1, sectionSize );
	}

	HFONT statusFont = CreatePointFont( m_statusMessagePointSize.cy, m_statusMessageFontName, paintDC );
	HFONT originalFont = (HFONT)SelectObject( paintDC, statusFont );

	SetTextColor( paintDC, (m_bodyTextColor == -1) ? m_productNameTextColor : m_statusMessageTextColor );
	SetBkMode( paintDC, TRANSPARENT );
	DrawText( paintDC, m_statusMessage, strlen(m_statusMessage), &statusRect, DT_VCENTER|DT_CENTER|DT_SINGLELINE );
	
	SelectObject( paintDC, originalFont);
	DeleteObject( statusFont );
}
void CSplashScreen::OnPaint( HWND hWnd )
{
	PAINTSTRUCT ps;
	HDC paintDC = BeginPaint(hWnd, &ps);


	HDC imageDC = ::CreateCompatibleDC( paintDC );

	BITMAPINFO bitmapInfo;
	memset ( &bitmapInfo, 0, sizeof(BITMAPINFOHEADER) );
	bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	int scanLines = GetDIBits(imageDC,		// handle to DC
							  m_bitmap,			// handle to bitmap
							  0,				// first scan line to set
							  0,				// number of scan lines to copy
							  NULL,				// array for bitmap bits
							  &bitmapInfo,		// bitmap data buffer
							  DIB_RGB_COLORS );	// RGB or palette index

	// Paint the bitmap image.
	HBITMAP pOldBitmap = (HBITMAP)SelectObject( imageDC, m_bitmap );
	int width = bitmapInfo.bmiHeader.biWidth;
	int height = bitmapInfo.bmiHeader.biHeight;
	BitBlt( paintDC, 0, 0, width, height, imageDC, 0, 0, SRCCOPY );
	SelectObject( imageDC, pOldBitmap );

	// calculate height of strings
	int heightOfDialogFace = height;
	int widthOfDialogFace = width;

	DisplayProductName( paintDC, width, height );
	DisplayBody( paintDC, width, height );

	if ( m_statusMessage ) {
		DisplayStatusLine( paintDC, width, height );
	}

	EndPaint(hWnd, &ps);
}

void CSplashScreen::GetVersionStrings()
{	
	DWORD dwHandle;			// ignored 
	char *buf;				// pointer to buffer to receive file-version info.

	// get name of executable
	char moduleName[_MAX_PATH];
	::GetModuleFileName ( NULL, moduleName, sizeof(moduleName) );

	// Get the size of the version information.
	DWORD verSize = GetFileVersionInfoSize(
		moduleName,	// pointer to filename string
		&dwHandle		// pointer to variable to receive zero
	);

	if (verSize != 0)
	{
		buf = new char[verSize + 1];

		BOOL res = GetFileVersionInfo(
				moduleName,	// pointer to filename string
				NULL,			// ignored 
				verSize,		// size of buffer
				buf 			// pointer to buffer to receive file-version info.
		);
		ASSERT(res);

		UINT ver = (UINT)verSize;

		LPVOID lplpBuffer;
		BOOL doThis = VerQueryValue (buf, TEXT("\\StringFileInfo\\041104B0\\ProductName"), &lplpBuffer, &ver);
		if ( doThis ) {
			m_productNameString = new TCHAR[ver+1];
			strcpy(m_productNameString, (char *)lplpBuffer);
		}

		doThis = VerQueryValue (buf, TEXT("\\StringFileInfo\\041104B0\\CompanyName"), &lplpBuffer, &ver);
		if ( doThis ) {
			m_companyNameString = new TCHAR[ver+1];
			strcpy(m_companyNameString, (char *)lplpBuffer);
		}

		doThis = VerQueryValue (buf, TEXT("\\StringFileInfo\\041104B0\\LegalCopyright"), &lplpBuffer, &ver);
		if ( doThis ) {
			m_copyrightString = new TCHAR[ver+1];
			strcpy(m_copyrightString, (char *)lplpBuffer);
		}

		doThis = VerQueryValue (buf, TEXT("\\StringFileInfo\\041104B0\\Comments"), &lplpBuffer, &ver);
		if ( doThis ) {
			m_commentsString = new TCHAR[ver+1];
			strcpy(m_commentsString, (char *)lplpBuffer);
		}

		doThis = VerQueryValue (buf, TEXT("\\StringFileInfo\\041104B0\\ProductVersion"), &lplpBuffer, &ver);
		if ( doThis ) {
			/*int versionNumbers[4];
			int numberOfValues = sscanf ( (char *)lplpBuffer, "%d,%d,%d,%d", &versionNumbers[0],&versionNumbers[1], &versionNumbers[2], &versionNumbers[3] );
			char numberString[12*4+1];
			if ( versionNumbers[3] != 0 ) {
				sprintf ( numberString, "%d.%d.%d.%d", versionNumbers[3],versionNumbers[2], versionNumbers[1], versionNumbers[0] );
			} else if ( versionNumbers[2] != 0 ) {
				sprintf ( numberString, "%d.%d.%d", versionNumbers[2], versionNumbers[1], versionNumbers[0] );
			} else if ( versionNumbers[1] != 0 ) {
				sprintf ( numberString, "%d.%d",  versionNumbers[1], versionNumbers[0] );
			} else {
				sprintf ( numberString, "%d", versionNumbers[0] );
			}
			int numberLength = strlen ( numberString );
			m_versionNumberString = new TCHAR[numberLength+1];
			strcpy ( m_versionNumberString, numberString );*/
			m_versionNumberString = new TCHAR[ver];
			strcpy ( m_versionNumberString, (char *)lplpBuffer);

			LPCTSTR versionPrefix = "Version ";
			int versionNumberStringLength = strlen( versionPrefix ) + strlen ( m_versionNumberString );
			m_versionString = new char [versionNumberStringLength+1];

			strcpy ( m_versionString, "Version " );
			strcat ( m_versionString, m_versionNumberString );
		}
		delete buf;
	}
}
