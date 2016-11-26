#include <Windows.h>
#include <GL\glut.h>
#include<math.h>
#include<stdio.h>
using namespace std;
const double PI = 3.141592653589793238462;

GLfloat x = 0.0f;										//图像平移分量
GLfloat z = 0.0f;
GLfloat y = 0.0f;
GLfloat tx = 1.0f;										//视图大小，控制缩放
GLfloat ty = 1.0f;
GLfloat tz = 1.0f;
GLfloat oldmy, oldmx;									//鼠标按下的位置（x,y)
GLfloat deltax, deltay;									//释放后，x和y移动分量

GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };	//光照参数
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f };

void Cube()												//正方体
{
	glBegin(GL_QUADS);									// Draw A Quad
		glColor3f(0.0f, 1.0f, 0.0f);					// Set The Color To Green
		glVertex3f(1.0f, 1.0f, -1.0f);					// Top Right Of The Quad (Top)
		glVertex3f(-1.0f, 1.0f, -1.0f);					// Top Left Of The Quad (Top)
		glVertex3f(-1.0f, 1.0f, 1.0f);					// Bottom Left Of The Quad (Top)
		glVertex3f(1.0f, 1.0f, 1.0f);					// Bottom Right Of The Quad (Top)
		glColor3f(1.0f, 0.5f, 0.0f);					// Set The Color To Orange
		glVertex3f(1.0f, -1.0f, 1.0f);					// Top Right Of The Quad (Bottom)
		glVertex3f(-1.0f, -1.0f, 1.0f);					// Top Left Of The Quad (Bottom)
		glVertex3f(-1.0f, -1.0f, -1.0f);				// Bottom Left Of The Quad (Bottom)
		glVertex3f(1.0f, -1.0f, -1.0f);					// Bottom Right Of The Quad (Bottom)
		glColor3f(1.0f, 0.0f, 0.0f);					// Set The Color To Red
		glVertex3f(1.0f, 1.0f, 1.0f);					// Top Right Of The Quad (Front)
		glVertex3f(-1.0f, 1.0f, 1.0f);					// Top Left Of The Quad (Front)
		glVertex3f(-1.0f, -1.0f, 1.0f);					// Bottom Left Of The Quad (Front)
		glVertex3f(1.0f, -1.0f, 1.0f);					// Bottom Right Of The Quad (Front)
		glColor3f(1.0f, 1.0f, 0.0f);					// Set The Color To Yellow
		glVertex3f(1.0f, -1.0f, -1.0f);					// Top Right Of The Quad (Back)
		glVertex3f(-1.0f, -1.0f, -1.0f);				// Top Left Of The Quad (Back)
		glVertex3f(-1.0f, 1.0f, -1.0f);					// Bottom Left Of The Quad (Back)
		glVertex3f(1.0f, 1.0f, -1.0f);					// Bottom Right Of The Quad (Back)
		glColor3f(0.0f, 0.0f, 1.0f);					// Set The Color To Blue
		glVertex3f(-1.0f, 1.0f, 1.0f);					// Top Right Of The Quad (Left)
		glVertex3f(-1.0f, 1.0f, -1.0f);					// Top Left Of The Quad (Left)
		glVertex3f(-1.0f, -1.0f, -1.0f);				// Bottom Left Of The Quad (Left)
		glVertex3f(-1.0f, -1.0f, 1.0f);					// Bottom Right Of The Quad (Left)
		glColor3f(1.0f, 0.0f, 1.0f);					// Set The Color To Violet
		glVertex3f(1.0f, 1.0f, -1.0f);					// Top Right Of The Quad (Right)
		glVertex3f(1.0f, 1.0f, 1.0f);					// Top Left Of The Quad (Right)
		glVertex3f(1.0f, -1.0f, 1.0f);					// Bottom Left Of The Quad (Right)
		glVertex3f(1.0f, -1.0f, -1.0f);					// Bottom Right Of The Quad (Right)
	glEnd();
}
void Cone()												//圆锥体
{
	glBegin(GL_TRIANGLES);								// Start Drawing A Triangle
		glColor3f(1.0f,0.0f,0.0f);						// Red
		glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Front)
		glColor3f(0.0f,1.0f,0.0f);						// Green
		glVertex3f(-1.0f,-1.0f, 1.0f);					// Left Of Triangle (Front)
		glColor3f(0.0f,0.0f,1.0f);						// Blue
		glVertex3f( 1.0f,-1.0f, 1.0f);					// Right Of Triangle (Front)
		glColor3f(1.0f,0.0f,0.0f);						// Red
		glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Right)
		glColor3f(0.0f,0.0f,1.0f);						// Blue
		glVertex3f( 1.0f,-1.0f, 1.0f);					// Left Of Triangle (Right)
		glColor3f(0.0f,1.0f,0.0f);						// Green
		glVertex3f( 1.0f,-1.0f, -1.0f);					// Right Of Triangle (Right)
		glColor3f(1.0f,0.0f,0.0f);						// Red
		glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Back)
		glColor3f(0.0f,1.0f,0.0f);						// Green
		glVertex3f( 1.0f,-1.0f, -1.0f);					// Left Of Triangle (Back)
		glColor3f(0.0f,0.0f,1.0f);						// Blue
		glVertex3f(-1.0f,-1.0f, -1.0f);					// Right Of Triangle (Back)
		glColor3f(1.0f,0.0f,0.0f);						// Red
		glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Left)
		glColor3f(0.0f,0.0f,1.0f);						// Blue
		glVertex3f(-1.0f,-1.0f,-1.0f);					// Left Of Triangle (Left)
		glColor3f(0.0f,1.0f,0.0f);						// Green
		glVertex3f(-1.0f,-1.0f, 1.0f);					// Right Of Triangle (Left)
	glEnd();											// Done Drawing The Pyramid
}
void Circle()											// 圆形
{
	glBegin(GL_TRIANGLE_FAN);//扇形连续填充三角形串
	glVertex3f(0.0f, 0.0f, 0.0f);
	int i = 0;
	for (i = 0; i <= 390; i += 15)
	{
		float p = i * 3.14 / 180;
		glVertex3f(sin(p), cos(p), 0.0f);
	}
	glEnd();
}
void Cylinder()											// 圆柱体
{
	glBegin(GL_QUAD_STRIP);//连续填充四边形串
	int i = 0;
	glColor3f(0.0f, 0.0f, 1.0f);						// Blue
	for (i = 0; i <= 390; i += 15)
	{
		float p = i * 3.14 / 180;
		glVertex3f(sin(p), cos(p), 2.0f);
		glVertex3f(sin(p), cos(p), 0.0f);
	}
	glEnd();
	glColor3f(0.0f, 1.0f, 0.0f);						// Green
	Circle();
	glTranslatef(0, 0, 2.0);
	Circle();
}

void Sphere()											// 球体
{
	GLfloat xx = 0, yy = 0, zz = 0, radius = 1;			//球心坐标为（xx，yy，zz），球的半径为radius。
	GLfloat M = 50, N = 50;								//M，N分别表示球体的横纵向被分成多少份  
	float step_z = PI / M;
	float step_xy = 2 * PI / N;
	float x[4], y[4], z[4];

	float angle_z = 0.0;
	float angle_xy = 0.0;
	int i = 0, j = 0;
	glColor3f(0.0f, 1.0f, 0.0f);						// Green
	glBegin(GL_QUADS);
	for (i = 0; i<M; i++)
	{
		angle_z = i * step_z;

		for (j = 0; j<N; j++)
		{
			angle_xy = j * step_xy;

			x[0] = radius * sin(angle_z) * cos(angle_xy);
			y[0] = radius * sin(angle_z) * sin(angle_xy);
			z[0] = radius * cos(angle_z);

			x[1] = radius * sin(angle_z + step_z) * cos(angle_xy);
			y[1] = radius * sin(angle_z + step_z) * sin(angle_xy);
			z[1] = radius * cos(angle_z + step_z);

			x[2] = radius*sin(angle_z + step_z)*cos(angle_xy + step_xy);
			y[2] = radius*sin(angle_z + step_z)*sin(angle_xy + step_xy);
			z[2] = radius*cos(angle_z + step_z);

			x[3] = radius * sin(angle_z) * cos(angle_xy + step_xy);
			y[3] = radius * sin(angle_z) * sin(angle_xy + step_xy);
			z[3] = radius * cos(angle_z);

			for (int k = 0; k<4; k++)
			{
				glVertex3f(xx + x[k], yy + y[k], zz + z[k]);
			}
		}
	}
	glEnd();
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();										//push Matrix
	glRotatef(deltax, 0.0, 1.0, 0.0);					//x轴旋转
	glRotatef(deltay, 1.0, 0.0, 0.0);					//y轴旋转
	glTranslatef(x, y, z);
	glScalef(tx, ty, tz);
								

	Cone();											//这里调用显示model函数

	glPopMatrix();
	glutSwapBuffers();
}

void Mouse(int button, int state, int x, int y) //处理鼠标点击  
{
	if (state == GLUT_DOWN) //第一次鼠标按下时,记录鼠标在窗口中的初始坐标  
		oldmx = x, oldmy = y;
}

void onMouseMove(int x, int y) //处理鼠标拖动  
{
	deltax += 360 * (x - oldmx) / 600;
	deltay += 360 * (y - oldmy) / 600;
	oldmx = x;
	oldmy = y;
}


void SpecialKeys(int key, int rx, int ry)
{
	if (key == GLUT_KEY_UP)
		y += 0.1f;

	if (key == GLUT_KEY_DOWN)
		y -= 0.1f;

	if (key == GLUT_KEY_LEFT)
		x -= 0.1f;

	if (key == GLUT_KEY_RIGHT)
		x += 0.1f;
	glutPostRedisplay();

}

void keyboard(unsigned char key, int m_x, int m_y)
{
	switch (key) {
	case '+':												//键盘中'+'就是'='
	case '=':
		tx = tx * 1.1;
		ty = ty * 1.1;
		tz = tz * 1.1;
		glutPostRedisplay();
		break;
	case '-':
		tx = tx / 1.1;
		ty = ty / 1.1;
		tz = tz / 1.1;
		glutPostRedisplay();
		break;
	}
}
void init()
{
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);	// Position The Light
	glEnable(GL_LIGHT1);								// Enable Light One	

}
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(300, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("OpenGL");
	init();
	printf("方向键控制平移，+ - 控制缩放，鼠标控制旋转");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(display);  //设置不断调用显示函数  
	glutMouseFunc(Mouse);
	glutMotionFunc(onMouseMove);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialKeys);
	glutMainLoop();
	return 0;
}
