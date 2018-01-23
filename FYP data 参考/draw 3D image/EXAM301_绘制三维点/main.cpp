

#include <math.h> 
#include "../OpenGL/glut.h"
#include <iostream>
using namespace std;


GLdouble  r = -45.0;


void Initialization();
void Drawing();
void glutOnDisplay();
void glutOnReshape(int w, int h);
void glutOnKeyboard(unsigned char key, int x, int y);
void PrintVersion();

int main(int argc, char *argv[])
{

	string projName = argv[0];
	int i = projName.rfind("\\");
	projName = projName.substr(i+1, projName.length()-(i+1)-4);//起始截取索引，截取几个字符

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(400, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow(projName.c_str());

	glutDisplayFunc(glutOnDisplay);
	glutReshapeFunc(glutOnReshape);
	glutKeyboardFunc(glutOnKeyboard);
	PrintVersion();
	glutMainLoop();

	
	
	system("pause");
	return 0;
}

void Initialization()
{
	glClearColor(1.0f, 1.0f, 0.0f, 0.0f);		//将背景色设为绿色
}



void Drawing()
{
	GLfloat x, y, z = -50.0f, inc = 0, angle;
	glPushMatrix();								//将当前矩阵压入矩阵堆栈
	glRotated(r, 1.0, 0.0, 0.0);			//将当前坐标系 绕 X 轴旋转 -45°
	glRotated(15, 0, 1, 0);						//将当前坐标系 绕 Y 轴旋转 -15°
	glColor3d(1, 0, 0);
	glBegin(GL_POINTS);
		for(angle=0.0f;  angle<=2.0f*3.14159f * 3.0;   angle+=0.1f)
		{
			x = inc * sin(angle);				//计算点的 X 坐标
			y = inc * cos(angle);				//计算点的 Y 坐标
			if(angle == 0.0f)
			{
				//起点用绿色
				glColor3f(0, 1, 0);
				glPointSize(10);
				glVertex3f(x, y, z);
				glPointSize(1);
				glColor3d(1, 0, 0);
			
			}else
			{
				glVertex3d(x, y, z);				//绘制点
			}
			z += 0.5;							//Z 坐标增量
			inc += 0.3f;
		}
	glEnd();
	glPopMatrix();

}


void Drawing302()
{
	GLfloat x, y, z=-50.0f, inc=0, angle, ptSize[2], szStep, curSize;
	glPushMatrix();								//将当前矩阵压入矩阵堆栈
	glRotated(r, 1.0, 0.0, 0.0);				//将当前坐标系 绕 X 轴旋转 -45°
	glRotated(15, 0, 1, 0);						//将当前坐标系 绕 Y 轴旋转 -15°

	glGetFloatv(GL_POINT_SIZE_RANGE, ptSize);
	glGetFloatv(GL_POINT_SIZE_GRANULARITY, &szStep);
	curSize = ptSize[0];

	glColor3d(1, 0, 0);
	for(angle=0.0f;  angle<=2.0f*3.14159f * 3.0;   angle+=0.1f)
	{
		x = inc * sin(angle);				//计算点的 X 坐标
		y = inc * cos(angle);				//计算点的 Y 坐标
		glPointSize(curSize);
		glBegin(GL_POINTS);
			glVertex3d(x, y, z);			//绘制点
		glEnd();

		z += 0.5;							//Z 坐标增量
		inc += 0.3f;
		curSize += szStep;
	}
	glPointSize(ptSize[0]);
	glPopMatrix();
}


void glutOnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//Drawing();
	Drawing302();
	glutSwapBuffers();
}

void glutOnReshape(int w, int h)
{
	GLfloat aspect = (GLfloat)w / (GLfloat)h;		//计算窗口的纵横比
	GLfloat nRange = 100.0f;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(w <= h)
	{
		glOrtho(-nRange, nRange, -nRange/aspect, nRange/aspect, -nRange, nRange);
	}
	else
	{
		glOrtho(-nRange, nRange, -nRange*aspect, nRange*aspect, -nRange, nRange);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void glutOnKeyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'w':
	case 'W':
		r+=1.0;
		cout<<r<<endl;
		break;

	case 's':
	case 'S':
		r -= 1.0;
		cout<<r<<endl;
		break;
	case 27:
		exit(0);
		break;
	}
	glutPostRedisplay();
}


void PrintVersion()
{
	const GLubyte* name = glGetString(GL_VENDOR);			//返回负责当前OpenGL实现厂商的名字
	const GLubyte* biaoshifu = glGetString(GL_RENDERER);	//返回一个渲染器标识符，通常是个硬件平台
	const GLubyte* OpenGLVersion =glGetString(GL_VERSION);	//返回当前OpenGL实现的版本号
	const GLubyte* gluVersion= gluGetString(GLU_VERSION);	//返回当前GLU工具库版本
	printf("OpenGL实现厂商的名字：%s\n", name);
	printf("渲染器标识符：%s\n", biaoshifu);
	printf("OpenGL实现的版本号：%s\n",OpenGLVersion );
	printf("GLU工具库版本：%s\n", gluVersion);
	printf("如对本源码有意见与建议望请分享.  Q172272869\n");
}



