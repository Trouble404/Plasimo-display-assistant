#include <windows.h> // 根据系统需要
#include <GL/gl.h>
#include <GL/glaux.h>
#include <gl/glut.h>
#include <TCHAR.H>
#include <MATH.H>
#include <stdio.h>

#define pi 3.1415926
static float c=pi/180.0f; //弧度和角度转换参数
static int du=90,oldmy=-1,oldmx=-1; //du是视点绕y轴的角度,opengl里默认y轴是上方向
static float r=220.0f,h=0.0f; //r是视点绕y轴的半径,h是视点高度即在y轴上的坐标


void Mouse(int button, int state, int x, int y) //处理鼠标点击
{
    if(state==GLUT_DOWN) //第一次鼠标按下时,记录鼠标在窗口中的初始坐标
        oldmx=x,oldmy=y;
}
void onMouseMove(int x,int y) //处理鼠标拖动
{
    //printf("%d\n",du);
    du+=x-oldmx; //鼠标在窗口x轴方向上的增量加到视点绕y轴的角度上，这样就左右转了
    h +=30.f*(y-oldmy); //鼠标在窗口y轴方向上的改变加到视点的y坐标上，就上下转了
    if(h>250.0f) h=250.0f; //视点y坐标作一些限制，不会使视点太奇怪
    else if(h<-250.0f) h=-250.0f;
    oldmx=x,oldmy=y; //把此时的鼠标坐标作为旧值，为下一次计算增量做准备
}
void axis()
{
//设置坐标轴颜色
	glColor3f(1.0f, 0.0f, 0.0f);
//x轴
	glBegin(GL_LINES);
	glVertex3f(0,0.0,0.0);
	glVertex3f(200,0.0,0.0);

//Arrow
	glVertex3f(192.0f,6.0f,0.0f);
	glVertex3f(200.0f,0.0f,0.0f);
	glVertex3f(192.0f,-6.0f,0.0f);
	glVertex3f(200.0f,0.0f,0.0f);
	glVertex3f(192.0f,0.0f,6.0f);
	glVertex3f(200.0f,0.0f,0.0f);
	glVertex3f(192.0f,0.0f,-6.0f);
	glVertex3f(200.0f,0.0f,0.0f);
	glEnd();
               

//y轴
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0,0,0.0);
	glVertex3f(0,200,0.0);

	glVertex3f(-0.3f*20,9.6f*20,0.0f);
	glVertex3f(0.0f,10.0f*20,0.0f);
	glVertex3f(0.3f*20,9.6f*20,0.0f);
	glVertex3f(0.0f,10.0f*20,0.0f);

	glVertex3f(0.0f,9.6f*20,-0.3f*20);
	glVertex3f(0.0f,10.0f*20,0.0f);
	glVertex3f(0.0f,9.6F*20,0.3f*20);
	glVertex3f(0.0f,10.0f*20,0.0f);
	glEnd();


//z轴
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0,0.0,0);
	glVertex3f(0,0,200);
	
	//Arrow
	glVertex3f(0.3f*20,0.0f,9.60f*20);
	glVertex3f(0.0f,0.0f,10.0f*20);
	glVertex3f(-0.3f*20,0.0f,9.60f*20);
	glVertex3f(0.0f,0.0f,10.0f*20);
	
	glVertex3f(0.0f,0.3f*20,9.60f*20);
	glVertex3f(0.0f,0.0f,10.0f*20);
	glVertex3f(0.0f,-0.3f*20,9.60f*20);
	glVertex3f(0.0f,0.0f,10.0f*20);
	glEnd();

}
void DrawText()
{
	//glPushMatrix();
	
	//glColor3f(1.0f,1.0f,1.0f);	
	
	wglUseFontBitmaps(wglGetCurrentDC(),0,255,100);
	
	glListBase(100);
	glRasterPos3f(220.0f,0.0f,0.0f);
	glCallLists(2,GL_UNSIGNED_BYTE,_T("+x")); 
	
	glRasterPos3f(0.0f,220.0f,0.0f);
	glCallLists(2,GL_UNSIGNED_BYTE,_T("+y")); 
	
	glRasterPos3f(0.0f,0.0f,220.0f);
	glCallLists(2,GL_UNSIGNED_BYTE,_T("+z")); 
	
	glRasterPos3f(0.0f,0.0f,0.0f);
	glCallLists(6,GL_UNSIGNED_BYTE,_T("Center")); 
	
	//glPopMatrix();
}
/*
void DrawFont()  //画坐标轴指示
{
glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  //指定在内存中每一像素行的开始位置的排列方式为按单字节排列
glColor3f(0.0f, 0.0f, 0.0f);
 
glRasterPos2f(500.0f, -500.0f);
glBitmap(8, 8, 0.0f, 0.0f, 0.0f, 0.0f, rastersX);  //x
 
glRasterPos2f(250.0f, -250.0f);
glBitmap(8, 8, 0.0f, 0.0f, 0.0f, 0.0f, rastersY);  //y

glRasterPos2f(250.0f, -250.0f);
glBitmap(8, 8, 0.0f, 0.0f, 0.0f, 0.0f, rastersZ);  //z

glFlush();
}
*/
void reshape(int w,int h)
{
    glViewport( 0, 0, w, h );//投影变换函数
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(75.0f, (float)w/h, 1.0f, 1000.0f);
    glMatrixMode( GL_MODELVIEW );
}
void myDisplay(void)
{
	glEnable (GL_LINE_SMOOTH);
	glEnable (GL_BLEND);
	//glEnable(GL_DEPTH_TEST);
	//设置缓冲颜色
	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	//设置视点
	//gluLookAt(220, 220, 220, 0, 0, 0, 0, 1, 0);
	gluLookAt(r*cos(c*du), h, r*sin(c*du), 0, 0, 0, 0, 1, 0);
	//添加坐标轴
	axis();
	DrawText();
	glutWireTeapot(60);
	glFlush();
    glutSwapBuffers();//用于双缓冲
}
void DrawTower()
{

}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH ); 
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("三维坐标");
    glutReshapeFunc( reshape );
    glutDisplayFunc(myDisplay); 
    glutIdleFunc(myDisplay);  //设置不断调用显示函数
    glutMouseFunc(Mouse);
    glutMotionFunc(onMouseMove);
    glutMainLoop(); 
    return 0; 
}