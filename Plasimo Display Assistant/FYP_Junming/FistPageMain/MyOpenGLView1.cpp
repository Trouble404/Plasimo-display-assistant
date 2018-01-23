#define _CRT_SECURE_NO_WARNINGS 1
#include "StdAfx.h"
#include "MyOpenGLView1.h"
#include <math.h>
#include <sstream>
#include <vector>

#define TIMERID 8
// float scaleview;
#define maxnum 150
std::vector<HangVert> colorpoints[maxnum];
std::vector<std::string> timestring[maxnum] ;
std::vector<int> timesheight[maxnum];
double min[maxnum] = { 10000000000000000000 };
double max[maxnum] = { -1000000000000000000 };
float x, y = 0;
GLuint mTexts;
void LoadASCII()//for displaying characs in openGL
{
	mTexts = glGenLists(96);
	HFONT hFont = CreateFontA(24, 0, 0, 0, 300, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_QUALITY, "Arial");

	SelectObject(GetDC(GetActiveWindow()), hFont);
	wglUseFontBitmaps(GetDC(GetActiveWindow()), 32, 96, mTexts);
}
char *LoadFileContent(const char *path)
{
	FILE *pFile = fopen(path, "rb");
	if (pFile)
	{
		fseek(pFile, 0, SEEK_END);
		int nLen = ftell(pFile);
		char *buffer = new char[nLen + 1];
		if (nLen != 0)
		{
			rewind(pFile);
			fread(buffer, nLen, 1, pFile);
			buffer[nLen] = '\0';
		}
		else
		{
			//printf("load file %s fail\n", path);
		}
		fclose(pFile);
		return buffer;
	}
	else
	{
		//printf("open file %s fail\n", path);
	}
	fclose(pFile);
	return  nullptr;
}
void CMyOpenGLView1::Readtxt(const char* filePath)
{
	int num = -1;
	for (int  i = 0; i < maxnum; i++)
	{
		colorpoints[i].clear();
		min[i] = 10000000000000000000;//The min value of text file
		max[i] = -1000000000000000000;//The max value of text file

		timestring[i].clear();//storage of time
		colorpoints[i].clear();//storage of data in text
		timesheight[i].clear();//the space in each time
	}
	
	//char*fileContent = LoadFileContent(filePath);
	 FILE *fp;
	 fp = fopen(filePath, "r");
	//std::stringstream ssObjFile(fileContent);
	char szOneLine[1000];
	std::string temp;
	int heigth = 0;
	//while (!ssObjFile.eof())
	while (!feof(fp))
	{
		temp.clear();
	
		memset(szOneLine, 0, 1000);//Read one row
		fgets(szOneLine, 1000, fp);
		
		//ssObjFile.getline(szOneLine, 256);
		if (strlen(szOneLine) > 0)
		{
			HangVert vi;
			std::stringstream ssOneLine(szOneLine);

			if (szOneLine[0] != '#')//if not "#" it's the data
			{
				for (int i = 0; i < 60; i++)//obtain the data in each row
				{
					ssOneLine >> vi.colorpoint[i];
					if (vi.colorpoint[i] != 0 && vi.colorpoint[i] != 1)
					{
						if (vi.colorpoint[i] > max[num])
							max[num] = vi.colorpoint[i];
						if(vi.colorpoint[i] < min[num])
							min[num] = vi.colorpoint[i];
					}
				}
				colorpoints[num].push_back(vi);
			}
			else if(szOneLine[0] == '#'&&szOneLine[2] == 't')//if is "#" it mean it is the start of a series data of time
			{
				num++;
				//give a different color to different two time images
				for (int i = 0; i < 60; i++)
					vi.colorpoint[i] = 1010;
				colorpoints[num].push_back(vi);
				for (int i = 0; i < 60; i++)
					vi.colorpoint[i] = 1010;
				colorpoints[num].push_back(vi);
				
				//save the charater of time
				ssOneLine >> temp;
				ssOneLine >> temp;
				ssOneLine >> temp;
				ssOneLine >> temp;
				timestring[num].push_back(temp);
				timesheight[num].push_back(heigth);
				
			}
			else 
			{
				int a = 0;

			}

			heigth++;
		}

	}
	fclose(fp);
	SetTimer(TIMERID, 10, 0);
}
void setcolor(double num)
{
	//Based on different value of data, drawing different colors

	int a = 1;
	 if(num<=2)
	{
		
		glColor3f(1*a, 0, 1*a);
	}
	else if (num < 3 && num >= 2)
	{
	
		glColor3f(0, 0, 1 * a);
		
	}
	else if (num < 4 && num >= 3)
	{
		
		glColor3f(0, 1*a, 1 * a);

	}
	else if (num < 5 && num >= 4)
	{
	
		glColor3f(0, 1 * a, 0 );

	}
	else if (num < 6 && num >= 5)
	{
	
		glColor3f(1*a, 1 * a, 0);

	}
	else if (num < 7 && num >= 6)
	{
	
		glColor3f(1 * a, 0.64 * a, 0);
	}
	else if (num>= 7)
	{
	
		glColor3f(1 * a, 0, 0);
	}

}
CMyOpenGLView1::CMyOpenGLView1(void)
{

		lbuttondown=FALSE;
		drawrobottype=0;

}


CMyOpenGLView1::~CMyOpenGLView1(void)
{
}


BEGIN_MESSAGE_MAP(CMyOpenGLView1, CWnd)
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

	ON_WM_KEYUP()
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyOpenGLView message handlers

int CMyOpenGLView1::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

void CMyOpenGLView1::OnPaint() //opengl drawing
{
	CPaintDC dc(this); // device context for painting
	wglMakeCurrent(hdc, hglrc);
	::glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// TODO: Add your message handler code here
	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clear buffer


	int height = 0;

	glPushMatrix();
	glTranslated(30, -0 + y, -250);
	glScaled(1, 1, 1);



	for (int j = 0; j < maxnum; j++)
	{
		if (colorpoints[j].size() > 1)
		{
			int mm_height = 0;
			//glPushMatrix(); draw time
			for (int i = 0; i < timestring[j].size(); i++)//timestring.size()
			{

			
				glColor3f(1, 1, 1);
				glRasterPos3f(-100, -timesheight[j][i] * 4 + 10 * i + y, -250);
				glListBase(mTexts - 32);
				glCallLists(strlen(timestring[j][i].c_str()), GL_BYTE, timestring[j][i].c_str());

				mm_height = timesheight[j][i] * 4 ;
			}

				
			{
				float mid = (max[j] - min[j]) / 7.0;
				float x1 = min[j] + mid;
				float x2 = min[j] + 2 * mid;
				float x3 = min[j] + 3 * mid;
				float x4 = min[j] + 4 * mid;
				float x5 = min[j] + 5 * mid;
				float x6 = min[j] + 6 * mid;
				float x7 = min[j] + 7 * mid;

				CString s1;
				s1.Format("Purple  :  %.2e -- %.2e", min, x1);
				CString s2;
				s2.Format("Blue    : %.2e -- %.2e", x1, x2);
				CString s3;
				s3.Format("cyan    : %.2e -- %.2e", x2, x3);
				CString s4;
				s4.Format("Green   : %.2e -- %.2e", x3, x4);
				CString s5;
				s5.Format("Yellow  : %.2e -- %.2e", x4, x5);
				CString s6;
				s6.Format("Orange  : %.2e -- %.2e", x5, x6);
				CString s7;
				s7.Format("Red    :： %.2e -- %.2e", x6, x7);

				float  midx = -200, midy = -mm_height +y ;

				glColor3f(1, 0, 1);
				glRasterPos3f(midx, -15+ midy, -250);
				glListBase(mTexts - 32);
				glCallLists(strlen(((std::string)s1.GetBuffer()).c_str()), GL_BYTE, ((std::string)s1.GetBuffer()).c_str());

				glColor3f(0, 0, 1);
				glRasterPos3f(midx, -30 + midy, -250);
				glListBase(mTexts - 32);
				glCallLists(strlen(((std::string)s2.GetBuffer()).c_str()), GL_BYTE, ((std::string)s2.GetBuffer()).c_str());

				glColor3f(0, 1, 1);
				glRasterPos3f(midx, -45 + midy, -250);
				glListBase(mTexts - 32);
				glCallLists(strlen(((std::string)s3.GetBuffer()).c_str()), GL_BYTE, ((std::string)s3.GetBuffer()).c_str());

				glColor3f(0, 1, 0);
				glRasterPos3f(midx, -60 + midy, -250);
				glListBase(mTexts - 32);
				glCallLists(strlen(((std::string)s4.GetBuffer()).c_str()), GL_BYTE, ((std::string)s4.GetBuffer()).c_str());

				glColor3f(1, 1, 0);
				glRasterPos3f(midx, -75 + midy, -250);
				glListBase(mTexts - 32);
				glCallLists(strlen(((std::string)s5.GetBuffer()).c_str()), GL_BYTE, ((std::string)s5.GetBuffer()).c_str());

				glColor3f(1, 0.64, 0);
				glRasterPos3f(midx, -90 + midy, -250);
				glListBase(mTexts - 32);
				glCallLists(strlen(((std::string)s6.GetBuffer()).c_str()), GL_BYTE, ((std::string)s6.GetBuffer()).c_str());

				glColor3f(1, 0, 0);
				glRasterPos3f(midx, -105 + midy, -250);
				glListBase(mTexts - 32);
				glCallLists(strlen(((std::string)s7.GetBuffer()).c_str()), GL_BYTE, ((std::string)s7.GetBuffer()).c_str());

			}
			


			double mid = 7 / (max[j] - min[j]);
			double addnum = 1 - min[j]*mid;
			glPushMatrix();
			glTranslatef(-30, 0, 0);
			glScaled(4, 4, 1);
			glEnable(GL_POINT_SMOOTH);
			glPointSize(6);
			glBegin(GL_POINTS);

			//Draw the image of data
			for (int i = 0; i < colorpoints[j].size(); i++)
			{


				for (int k = 0; k < 60; k++)
				{


					glColor3f(0.1, 0.2, 0.3);
					if (colorpoints[j][i].colorpoint[k] == 1010)
						glColor3f(0.3, 0.2, 0.1);
					else if (colorpoints[j][i].colorpoint[k] != 0 && colorpoints[j][i].colorpoint[k] != 1)
						setcolor(colorpoints[j][i].colorpoint[k] * mid + addnum); //transf the range to number 1~7
					glVertex2f(0.5*k, -0.5*i- height);

				}
				

			}
			height += 0.5*colorpoints[j].size();
			glEnd();
			glPopMatrix();
		}
	}
	
	glPopMatrix();
	::glFinish();		// end of drawing
	SwapBuffers( hdc);
	wglMakeCurrent(hdc,NULL);
	Sleep(1);
	// Do not call CWnd::OnPaint() for painting messages
}

void CMyOpenGLView1::drawrobot(int type)
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

void CMyOpenGLView1::DrawTu1()
{
	  // glTranslated(-1.0,1.0 ,0.0 );
	   
	
}
void CMyOpenGLView1::DrawTu2()
{
}

BOOL CMyOpenGLView1::SetupPixelFormat(HDC hdc)
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

void CMyOpenGLView1::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	GLdouble aspect_ratio;

	if( 0 >= cx || 0 >= cy )
		return;
	gl_width = cx;
	gl_heigth = cy;
	SetupViewPort( cx, cy );//setting size
	
	// compute the aspect ratio
	aspect_ratio = (GLdouble)cx / (GLdouble)cy;//The ratio of length and width
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(-cx / 2, cx / 2, -cy / 2, cy / 2);
	gluPerspective(45.0f, (GLfloat)cx / (GLfloat)cy, 0.1f, 10000.0f);// Calculate The Aspect Ratio Of The Window
	
	
	::glMatrixMode(GL_MODELVIEW);
	

	::glLoadIdentity();//reset
	


}

BOOL CMyOpenGLView1::SetupViewPort(int cx, int cy)
{
	LoadASCII();
	glViewport(0, 0, cx, cy);//Redraw the dialog  based on the change
	
	return TRUE;
}

BOOL CMyOpenGLView1::SetupViewingFrustum(GLdouble aspect_ratio)
{
	gluPerspective( 40.0f, aspect_ratio, 0.1f, 20.0f );
	return TRUE;
}

BOOL CMyOpenGLView1::SetupViewingTransform()//openGL setting
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

BOOL CMyOpenGLView1::SetupLighting()//OpenGL setting
{

	//setting lighting
	GLfloat model_ambient[] = { 2.0f, 2.0f, 2.0f, 1.0f };
	GLfloat light_position0[]= { 1.0f, 0.0f, 5.0f, 0.0f };
	GLfloat light_color0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	
	
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, model_ambient );
	

	glLightfv( GL_LIGHT0, GL_POSITION, light_position0 );
	

	glLightfv( GL_LIGHT0, GL_DIFFUSE, light_color0 );
	

	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	
	return TRUE;
}

void CMyOpenGLView1::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	this->SetFocus();
	CWnd::OnLButtonDown(nFlags, point);
}

void CMyOpenGLView1::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	
	CWnd::OnLButtonUp(nFlags, point);
}

void CMyOpenGLView1::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default


	CWnd::OnMouseMove(nFlags, point);
}
void CMyOpenGLView1::getdc()
{
	::GetDC(m_hWnd);
}

void CMyOpenGLView1::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnLButtonDblClk(nFlags, point);
}

void CMyOpenGLView1::OnPaint2(int type)
{
	::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );//clear buffer
	
		::glPushMatrix();// put to the top matrix
		
		::glPopMatrix();//pop the top matrix

	::glFinish();	//end of draw
	
	SwapBuffers( hdc);
	
	
}

BOOL CMyOpenGLView1::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default

	y -= 0.5*zDelta; // move speed of mouse wheel

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

void CMyOpenGLView1::OnDestroy()
{
	 
	CWnd::OnDestroy();
	// TODO: 在此处添加消息处理程序代码
	
}
void CMyOpenGLView1::OnTimer(UINT_PTR nIDEvent)
{
	OnPaint();

}

void CMyOpenGLView1::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	y -= 5; //move speed of keyboard
	CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CMyOpenGLView1::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);
}


void CMyOpenGLView1::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	y += 5;//move speed of keyboard
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
