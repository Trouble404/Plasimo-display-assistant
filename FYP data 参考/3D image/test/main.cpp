#include <windows.h> // ����ϵͳ��Ҫ
#include <GL/gl.h>
#include <GL/glaux.h>
#include <gl/glut.h>
#include <TCHAR.H>
#include <MATH.H>
#include <stdio.h>

#define pi 3.1415926
static float c=pi/180.0f; //���ȺͽǶ�ת������
static int du=90,oldmy=-1,oldmx=-1; //du���ӵ���y��ĽǶ�,opengl��Ĭ��y�����Ϸ���
static float r=220.0f,h=0.0f; //r���ӵ���y��İ뾶,h���ӵ�߶ȼ���y���ϵ�����


void Mouse(int button, int state, int x, int y) //���������
{
    if(state==GLUT_DOWN) //��һ����갴��ʱ,��¼����ڴ����еĳ�ʼ����
        oldmx=x,oldmy=y;
}
void onMouseMove(int x,int y) //��������϶�
{
    //printf("%d\n",du);
    du+=x-oldmx; //����ڴ���x�᷽���ϵ������ӵ��ӵ���y��ĽǶ��ϣ�����������ת��
    h +=30.f*(y-oldmy); //����ڴ���y�᷽���ϵĸı�ӵ��ӵ��y�����ϣ�������ת��
    if(h>250.0f) h=250.0f; //�ӵ�y������һЩ���ƣ�����ʹ�ӵ�̫���
    else if(h<-250.0f) h=-250.0f;
    oldmx=x,oldmy=y; //�Ѵ�ʱ�����������Ϊ��ֵ��Ϊ��һ�μ���������׼��
}
void axis()
{
//������������ɫ
	glColor3f(1.0f, 0.0f, 0.0f);
//x��
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
               

//y��
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


//z��
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
void DrawFont()  //��������ָʾ
{
glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  //ָ�����ڴ���ÿһ�����еĿ�ʼλ�õ����з�ʽΪ�����ֽ�����
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
    glViewport( 0, 0, w, h );//ͶӰ�任����
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
	//���û�����ɫ
	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	//�����ӵ�
	//gluLookAt(220, 220, 220, 0, 0, 0, 0, 1, 0);
	gluLookAt(r*cos(c*du), h, r*sin(c*du), 0, 0, 0, 0, 1, 0);
	//���������
	axis();
	DrawText();
	glutWireTeapot(60);
	glFlush();
    glutSwapBuffers();//����˫����
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
	glutCreateWindow("��ά����");
    glutReshapeFunc( reshape );
    glutDisplayFunc(myDisplay); 
    glutIdleFunc(myDisplay);  //���ò��ϵ�����ʾ����
    glutMouseFunc(Mouse);
    glutMotionFunc(onMouseMove);
    glutMainLoop(); 
    return 0; 
}