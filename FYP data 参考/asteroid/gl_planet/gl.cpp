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

	//保存当前位置
	glPushMatrix();
	//大球自转
	//glRotatef((GLfloat)day,0.0,1.0,0.0);
	//画地球,半径，经线，纬线
	glutWireSphere(1.0,20,16);
	//去除当前变换矩阵，恢复原来的矩阵
	glPopMatrix();
	//保存原来的矩阵
	glPushMatrix();
	//以下变换是作用于小球上的
	//先旋转，相当于绕着地球旋转一定角度
	//局部坐标系固定在球体上，旋转一定角度，坐标系也跟着旋转
	glRotatef((GLfloat)year,0.0,1.0,0.0);

	//沿着x轴正方向移动一定距离，相当于环绕半径
	glTranslatef(2.0,0,0);

	glRotatef((GLfloat)day,0.0,1.0,0.0);
	//画一个小球
	glutWireSphere(0.2,10,8);
	glPopMatrix();
	glFlush();
}
void reshape(int w,int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//设置透视,fovy,aspect,near,far
	gluPerspective(60.0,(GLfloat)w/(GLfloat)h,1.0,20.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//设置观察点,
	gluLookAt(0,0,5,0,0,0,0,1,0);
	
}

void keyboard(unsigned char key,int x,int y)
{
	switch(key)
	{
	case 'd':
		day=(day+10)%360;
		//标记当前窗口需要重绘
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