#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include "glaux.h"


#define imageWidth 64
#define imageHeight 64
static int width = 1200, height = 600;
static int pX = 100, pY = 100;
static GLubyte image[imageHeight][imageWidth][4];
static GLuint earth;
static GLuint sun;
#define MAX_CHAR    128
GLuint TextFont;
static int year = 0, day = 0, month = 0, angle = 0;

void mouse_click_func(int button, int state, int x, int y);
void XPrintString(char *s);
int LoadTexture()
{
	// �����Ͱ�����
	glGenTextures(1, &earth);
	glBindTexture(GL_TEXTURE_2D, earth);

	// ��������
	  //  AUX_RGBImageRec *TexImage1 = auxDIBImageLoad("et.bmp");
	//    if (NULL == TexImage1) return false;       // ���ʧ�ܣ�����false
	//    glTexImage2D(GL_TEXTURE_2D, 0, 3, TexImage2->sizeX, TexImage2->sizeY,
	//                 0, GL_RGB, GL_UNSIGNED_BYTE, TexImage2->data);


	// ��������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// �����Ͱ�����
	glGenTextures(1, &sun);
	glBindTexture(GL_TEXTURE_2D, sun);

	//    AUX_RGBImageRec *TexImage2 = auxDIBImageLoad("mt.bmp");
	//    if (NULL == TexImage2) return false;       // ���ʧ�ܣ�����false
	//    glTexImage2D(GL_TEXTURE_2D, 0, 3, TexImage2->sizeX, TexImage2->sizeY,
	//                 0, GL_RGB, GL_UNSIGNED_BYTE, TexImage2->data);

	// ��������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//�ͷ�ͼ����Դ
	//    if (TexImage1)
	//    {
	//        if (TexImage1->data)
	//        {
	//            free(TexImage1->data);
	//        }
	//        free(TexImage1);
	//    }

	//�ͷ�ͼ����Դ
	//    if (TexImage2)
	//    {
	//        if (TexImage2->data)
	//        {
	//            free(TexImage2->data);
	//        }
	//        free(TexImage2);
	//    }

	return true;
}


void makeImage(void) {
	int i, j, c;

	for (i = 0; i < imageHeight; i++) {
		for (j = 0; j < imageWidth; j++) {
			c = ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0)) * 255;
			image[i][j][0] = (GLubyte)c;
			image[i][j][1] = (GLubyte)c;
			image[i][j][2] = (GLubyte)c;
			image[i][j][3] = (GLubyte)225;
		}
	}
}

void init(void)
{
	// ���������ɫ�������ԭ����ɫ�Ļ�Ϸ�ʽ
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// �������ӳ��֧��
	glEnable(GL_TEXTURE_2D);

	if (!LoadTexture())
	{
		exit(0);
	}

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat position[] = { 0.0, 3.0, 2.0, 0.0 };
	GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat local_view[] = { 0.0 };

	glClearColor(0.0, 0.1, 0.1, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

	//����MAX_CHAR����������ʾ�б���
	TextFont = glGenLists(MAX_CHAR);

	//��ÿ���ַ��Ļ������װ����Ӧ����ʾ�б���
	wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, TextFont);

}

void display(void)
{
	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
	GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat no_shininess[] = { 0.0 };
	GLfloat low_shininess[] = { 5.0 };
	GLfloat high_shininess[] = { 100.0 };
	GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glBindTexture(GL_TEXTURE_2D, texName);
	// ����ӳ�俪�أ�Ϊ��Ӱ��ͼ��ͶӰ�����Ӿ�ƽ�棬��ʾopengl����������
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, sun);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glutSolidSphere(1.0, 40, 32);
	//glutWireSphere(1.0, 20, 16);   // draw sun

	glPushMatrix();

	glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
	glTranslatef(2.0, 0.0, 0.0);

	glPushMatrix();
	glRotatef((GLfloat)day, 0.0, 1.0, 0.0);

	glBindTexture(GL_TEXTURE_2D, earth);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(0.2, 20, 16);
	//glutWireSphere(0.2, 10, 8);    // draw earth
	glPopMatrix();

	glRotatef((GLfloat)month, 0.0, 1.0, 0.0);
	glTranslatef(0.5, 0.0, 0.0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glutSolidSphere(0.1, 20, 16);
	//glutWireSphere(0.1, 10, 8);     // draw moon

	glPopMatrix();

	glRotatef((GLfloat)angle, 0.0, 1.0, 0.0);
	glTranslatef(4.0, 0.0, 0.0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glutSolidSphere(0.4, 16, 12);
	//glutWireSphere(0.4, 16, 12);



	glColor3f(1.0, .5, 1.0);

	glRasterPos3f(0.5, 10, 0.0);
	XPrintString("hello!");

	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(pX, pY);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse_click_func);
	//glutMotionFunc(mouse_move_func);
	//glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
/* ��������ƶ�������϶���ת���м��϶�ƽ�ƣ��Ҽ��ص������ͼ
*/
void mouse_click_func(int button, int state, int x, int y)
{
	y = width - y;
	switch (button) {
	case GLUT_LEFT_BUTTON:
		
		break;
	}
}

void XPrintString(char *s)
{
	glPushAttrib(GL_LIST_BIT);

	//����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�
	
		glCallList(*s);

	glPopAttrib();
}

