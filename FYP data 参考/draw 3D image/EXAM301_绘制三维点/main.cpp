

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
	projName = projName.substr(i+1, projName.length()-(i+1)-4);//��ʼ��ȡ��������ȡ�����ַ�

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
	glClearColor(1.0f, 1.0f, 0.0f, 0.0f);		//������ɫ��Ϊ��ɫ
}



void Drawing()
{
	GLfloat x, y, z = -50.0f, inc = 0, angle;
	glPushMatrix();								//����ǰ����ѹ������ջ
	glRotated(r, 1.0, 0.0, 0.0);			//����ǰ����ϵ �� X ����ת -45��
	glRotated(15, 0, 1, 0);						//����ǰ����ϵ �� Y ����ת -15��
	glColor3d(1, 0, 0);
	glBegin(GL_POINTS);
		for(angle=0.0f;  angle<=2.0f*3.14159f * 3.0;   angle+=0.1f)
		{
			x = inc * sin(angle);				//������ X ����
			y = inc * cos(angle);				//������ Y ����
			if(angle == 0.0f)
			{
				//�������ɫ
				glColor3f(0, 1, 0);
				glPointSize(10);
				glVertex3f(x, y, z);
				glPointSize(1);
				glColor3d(1, 0, 0);
			
			}else
			{
				glVertex3d(x, y, z);				//���Ƶ�
			}
			z += 0.5;							//Z ��������
			inc += 0.3f;
		}
	glEnd();
	glPopMatrix();

}


void Drawing302()
{
	GLfloat x, y, z=-50.0f, inc=0, angle, ptSize[2], szStep, curSize;
	glPushMatrix();								//����ǰ����ѹ������ջ
	glRotated(r, 1.0, 0.0, 0.0);				//����ǰ����ϵ �� X ����ת -45��
	glRotated(15, 0, 1, 0);						//����ǰ����ϵ �� Y ����ת -15��

	glGetFloatv(GL_POINT_SIZE_RANGE, ptSize);
	glGetFloatv(GL_POINT_SIZE_GRANULARITY, &szStep);
	curSize = ptSize[0];

	glColor3d(1, 0, 0);
	for(angle=0.0f;  angle<=2.0f*3.14159f * 3.0;   angle+=0.1f)
	{
		x = inc * sin(angle);				//������ X ����
		y = inc * cos(angle);				//������ Y ����
		glPointSize(curSize);
		glBegin(GL_POINTS);
			glVertex3d(x, y, z);			//���Ƶ�
		glEnd();

		z += 0.5;							//Z ��������
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
	GLfloat aspect = (GLfloat)w / (GLfloat)h;		//���㴰�ڵ��ݺ��
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
	const GLubyte* name = glGetString(GL_VENDOR);			//���ظ���ǰOpenGLʵ�ֳ��̵�����
	const GLubyte* biaoshifu = glGetString(GL_RENDERER);	//����һ����Ⱦ����ʶ����ͨ���Ǹ�Ӳ��ƽ̨
	const GLubyte* OpenGLVersion =glGetString(GL_VERSION);	//���ص�ǰOpenGLʵ�ֵİ汾��
	const GLubyte* gluVersion= gluGetString(GLU_VERSION);	//���ص�ǰGLU���߿�汾
	printf("OpenGLʵ�ֳ��̵����֣�%s\n", name);
	printf("��Ⱦ����ʶ����%s\n", biaoshifu);
	printf("OpenGLʵ�ֵİ汾�ţ�%s\n",OpenGLVersion );
	printf("GLU���߿�汾��%s\n", gluVersion);
	printf("��Ա�Դ��������뽨���������.  Q172272869\n");
}



