
#include "StdAfx.h"
#include "MyOpenGLView.h"
#include <math.h>


#define TIMERID 8
 float scaleview;




CMyOpenGLView::CMyOpenGLView(void)
{
		//scaleview=0.015;
	    //scaleview=0.1;
		lbuttondown=FALSE;
		drawrobottype=0;
		m_dis1=false;
		m_dis2=false;
		biaohao_show = -1;
		data_row = 0;
		data_col = 0;

}


CMyOpenGLView::~CMyOpenGLView(void)
{
}


BEGIN_MESSAGE_MAP(CMyOpenGLView, CWnd)
	//{{AFX_MSG_MAP(CMyOpenGLView)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEWHEEL()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()

END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyOpenGLView message handlers

int CMyOpenGLView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	hdc=::GetDC(m_hWnd);
	SetupPixelFormat(hdc);
	CPaintDC dc(this);
	//hglrc= wglCreateContext(hdc);
	hglrc= wglCreateContext(hdc);
	wglMakeCurrent(hdc,hglrc);
	::glClearDepth(1.0f);
	::glEnable(GL_DEPTH_TEST);
	//::glClearColor(1.0f,0.0f,1.0f,1.0f);
	 
	//delete(hdc);
	return 0;
}

void CMyOpenGLView::OnPaint() //Darw curve
{
	CPaintDC dc(this); // device context for painting
	wglMakeCurrent(hdc,hglrc);
	::glClearColor(0.0f,0.0f,0.0f,1.0f);
	// TODO: Add your message handler code here
   	::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );//Clear Buffer
	
	glPushMatrix();//save the matrix
	glTranslatef(-gl_width / 2+1, -gl_heigth/2+1, 0);//location transf
	GLfloat curSizeLine = 1;
	glPointSize(curSizeLine);
	if (biaohao_show <= 1)//The first colume is time
		return ;
	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.0f, 0.0f);

	for (int i = 1; i < data_row; i++)
	{

		glVertex2f(atof(data[i][0]) / (maxx - minx)*gl_width, atof(data[i][biaohao_show]) / (maxy - miny)*gl_heigth);//draw all points

	}

	glEnd();
	glPopMatrix();
	::glFinish();		// End draw
	SwapBuffers( hdc);
	wglMakeCurrent(hdc,NULL);
	Sleep(1);
	// Do not call CWnd::OnPaint() for painting messages
}

void CMyOpenGLView::drawrobot(int type)
{
	
	if(type==1)
	{
		DrawTu1();

	   
		
	}
	else
	{
	
    
    glEnd();

	}

}

void CMyOpenGLView::DrawTu1()
{
	  // glTranslated(-1.0,1.0 ,0.0 );
	   
	
}
void CMyOpenGLView::DrawTu2()
{
}

BOOL CMyOpenGLView::SetupPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd=
	{
		sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | //The buffer can draw to a window or device surface
			PFD_SUPPORT_OPENGL |//The buffer supports OpenGL drawing.
			PFD_DOUBLEBUFFER,//The buffer is double-buffered. This flag and PFD_SUPPORT_GDI are mutually exclusive in the current generic implementation.
			PFD_TYPE_RGBA,//RGBA pixels. Each pixel has four components in this order: red, green, blue, and alpha.
			24,
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			16,
			0,
			0,
			PFD_MAIN_PLANE,
			0,
		0, 0, 0
	};
	int pixelformat;
	
	if( 0 == (pixelformat =
		::ChoosePixelFormat( hdc, &pfd))  )
	{
		
		return FALSE;
	}
	
	if( FALSE == ::SetPixelFormat( hdc,
		pixelformat, &pfd) )
	{
		
		return FALSE;
	}
	
	return TRUE;

}

void CMyOpenGLView::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	GLdouble aspect_ratio;

	if( 0 >= cx || 0 >= cy )
		return;
	gl_width = cx;
	gl_heigth = cy;
	SetupViewPort( cx, cy );//setting size of picture
	
	// compute the aspect ratio
	aspect_ratio = (GLdouble)cx / (GLdouble)cy;//the ratio of length and width
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-cx / 2, cx / 2, -cy / 2, cy / 2);
	
	
	::glMatrixMode(GL_MODELVIEW);
	

	::glLoadIdentity();//reset
	


}

BOOL CMyOpenGLView::SetupViewPort(int cx, int cy)
{
	glViewport(0, 0, cx, cy);//redraw based on the change of window
	
	return TRUE;
}

BOOL CMyOpenGLView::SetupViewingFrustum(GLdouble aspect_ratio)
{
	gluPerspective( 40.0f, aspect_ratio, 0.1f, 20.0f );
	return TRUE;
}

BOOL CMyOpenGLView::SetupViewingTransform()
{
	int i;
	
	GLfloat fovy = 30.0;
	GLfloat eye[3];
	GLfloat center[3] = { 0.0f, 0.0f, 1.0f };
	GLfloat eye_dir[3];
	GLfloat up[3];
	GLfloat norm, dist;
	
	eye[0] = 0.0;
	eye[1] = 5.0;
	eye[2] = 2.0;
	
	for(i=0; i<3; i++)
		eye_dir[i] = center[i] - eye[i];
	dist = (GLfloat)sqrt( eye_dir[0]*eye_dir[0] + eye_dir[1]*eye_dir[1] + eye_dir[2]*eye_dir[2] );
	for(i=0; i<3; i++)
		eye_dir[i] /= (GLfloat)dist;
	
	
	
	up[0] = -eye_dir[0] * eye_dir[2];
	up[1] = -eye_dir[1] * eye_dir[2];
	up[2] = eye_dir[0] * eye_dir[0] + eye_dir[1] * eye_dir[1];
	norm = up[1]*up[1] + up[1]*up[1] + up[2]*up[2];
	norm = (GLfloat)sqrt(norm);
	for(i=0; i<3; i++)
		up[i] /= norm;
	gluLookAt( eye[0], eye[1],    eye[2],
		center[0], center[1], center[2],
		up[0],    up[1],     up[2]);
	return TRUE;
}

BOOL CMyOpenGLView::SetupLighting()
{

	
	GLfloat model_ambient[] = { 2.0f, 2.0f, 2.0f, 1.0f };//default value
	GLfloat light_position0[]= { 1.0f, 0.0f, 5.0f, 0.0f };
	GLfloat light_color0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	
	
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, model_ambient );
	

	glLightfv( GL_LIGHT0, GL_POSITION, light_position0 );
	

	glLightfv( GL_LIGHT0, GL_DIFFUSE, light_color0 );
	

	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	
	return TRUE;
}

void CMyOpenGLView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	/*lbuttondown=TRUE;
	pointcurrent=point;
	SetFocus();*/
	CWnd::OnLButtonDown(nFlags, point);
}

void CMyOpenGLView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	/*lbuttondown=FALSE;*/
	
	CWnd::OnLButtonUp(nFlags, point);
}

void CMyOpenGLView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default


	CWnd::OnMouseMove(nFlags, point);
}
void CMyOpenGLView::getdc()
{
	::GetDC(m_hWnd);
}

void CMyOpenGLView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnLButtonDblClk(nFlags, point);
}

void CMyOpenGLView::OnPaint2(int type)
{
	::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );//clear buffer
	
		::glPushMatrix();

		
		::glPopMatrix();
		


	::glFinish();	
	
	SwapBuffers( hdc);
	
	
}

BOOL CMyOpenGLView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default


	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

void CMyOpenGLView::OnDestroy()
{
	 
	CWnd::OnDestroy();
	
}

void CMyOpenGLView::ReadFile(CString pathfile, char divided)//Read file and get data
{
	data_col = 0;
	data_row = 0;
	data = CSVRead::ReadCsvFile(pathfile, divided,&data_row,&data_col);

}
float*  CMyOpenGLView::ShowLine(int biaohao,float *kedu)
{   
	biaohao_show = biaohao;
	minx = -1; miny = -1; maxx = -1; maxy = -1;

	if (data == NULL)
		return kedu;

		for(int i = 1; i < data_row; i++)
		{
			if (minx == -1)
			minx = atof(data[i][0]);
			if (maxx == -1)
			maxx = atof(data[i][0]);
			if (miny == -1)
			miny = atof(data[i][biaohao]);
			if (maxy == -1)
			maxy = atof(data[i][biaohao]);

			CString a = data[i][0];
			CString b = data[i][biaohao];

			minx = atof(data[i][0]) < minx ? atof(data[i][0]) : minx;
			maxx = atof(data[i][0]) > maxx ? atof(data[i][0]) : maxx;

			miny = atof(data[i][biaohao]) < miny ? atof(data[i][biaohao]) : miny;
			maxy = atof(data[i][biaohao]) > maxy ? atof(data[i][biaohao]) : maxy;

		}

		kedu[0] = minx;
		kedu[1] = maxx;
		kedu[2] = miny;
		kedu[3] = maxy;

		SetTimer(TIMERID, 10, 0);
		return kedu;
}
void CMyOpenGLView::OnTimer(UINT_PTR nIDEvent)
{
	OnPaint();

}