#include<GL/glut.h>

static int year=0,day=0;

void init()
{
	glClearColor(0.0,0.0,0.0,1.0);
	glShadeModel(GL_FLAT);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);

	//���浱ǰλ��
	glPushMatrix();
	//������ת
	//glRotatef((GLfloat)day,0.0,1.0,0.0);
	//������,�뾶�����ߣ�γ��
	glutWireSphere(1.0,20,16);
	//ȥ����ǰ�任���󣬻ָ�ԭ���ľ���
	glPopMatrix();
	//����ԭ���ľ���
	glPushMatrix();
	//���±任��������С���ϵ�
	//����ת���൱�����ŵ�����תһ���Ƕ�
	//�ֲ�����ϵ�̶��������ϣ���תһ���Ƕȣ�����ϵҲ������ת
	glRotatef((GLfloat)year,0.0,1.0,0.0);

	//����x���������ƶ�һ�����룬�൱�ڻ��ư뾶
	glTranslatef(2.0,0,0);

	glRotatef((GLfloat)day,0.0,1.0,0.0);
	//��һ��С��
	glutWireSphere(0.2,10,8);
	glPopMatrix();
	glFlush();
}
void reshape(int w,int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//����͸��,fovy,aspect,near,far
	gluPerspective(60.0,(GLfloat)w/(GLfloat)h,1.0,20.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//���ù۲��,
	gluLookAt(0,0,5,0,0,0,0,1,0);
	
}

void keyboard(unsigned char key,int x,int y)
{
	switch(key)
	{
	case 'd':
		day=(day+10)%360;
		//��ǵ�ǰ������Ҫ�ػ�
		glutPostRedisplay();
		break;
	case 'D':
		day=(day-10)%360;
		glutPostRedisplay();
		break;
	case 'y':
		year=(year+5)%360;
		glutPostRedisplay();
		break;
	case 'Y':
		year=(year-5)%360;
		glutPostRedisplay();
		break;

	}
}

int main(int argv,char ** argc)
{
	glutInit(&argv,argc);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("planet");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}