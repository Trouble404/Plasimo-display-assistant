#pragma once

#pragma comment(lib,"GL//opengl32.lib")
#pragma comment(lib,"GL//glut32.lib")
#pragma comment(lib,"GL//glu32.lib")
#pragma comment( lib, "GL//glaux.lib")

#include "afxwin.h"
#include"GL/GL.H"
#include"GL/glut.h"
#include"GL/GLU.H"
#include"SVRead.h"
class CMyOpenGLView1 :
	public CWnd
{
public:
	CMyOpenGLView1(void);
	~CMyOpenGLView1(void);


public:
	void OnPaint2(int type);
	CPoint pointcurrent;
	BOOL lbuttondown;
	BOOL SetupLighting();
	BOOL SetupViewingTransform();
	BOOL SetupViewingFrustum(GLdouble aspect_ratio);
	BOOL SetupViewPort(int cx,int cy);
	BOOL SetupPixelFormat(HDC hdc);
	HGLRC hglrc;
	
	void drawrobot(int type);
	int drawrobottype;
	void Readtxt(const char* filePath);
	void DrawTu1();
	void DrawTu2();

	void getdc();

protected:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	HDC hdc;
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDestroy();
public:
	
	
	float  gl_width, gl_heigth;
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
struct HangVert
{
	float colorpoint[60];
};