#include <GL/glew.h>
#include <freeglut.h>


//����任���Ʊ���
float fRotate = 0.0f;
float fScale = 1.0f;   
float fRevolve = 0.0f;
bool bPersp = false;
bool bAnim = false;//about��ת
bool bWire = false;
bool tAnim = false;
//���崰�ڴ�С
int wHeight = 0;
int wWidth = 0;

void Draw_Leg()
{
	glScalef(1, 1, 3);//����
	glutSolidCube(1.0);//����ʵ��������
}

void Draw_Scene()
{   //����� 
	glPushMatrix();
	glTranslatef(0, 0, 4 + 1);//�ƶ�
	glRotatef(90, 1, 0, 0); //��ת
	//��0,5,0��
	glutSolidTeapot(1);
	glPopMatrix();
	//������
	glPushMatrix();
	glTranslatef(0, 0, 3.5);
	glScalef(5, 4, 1);
	glutSolidCube(1.0);
	glPopMatrix();
	//��������
	glPushMatrix();
	glTranslatef(1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();

}

void updateView(int width, int height)//�л�ͶӰ��ʽ
{
	glViewport(0, 0, width, height);                        // Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
	glLoadIdentity();                                    // Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;

	if (bPersp){
		//todo when 'p' operation, hint: use FUNCTION gluPerspective
	}
	else
		glOrtho(-3, 3, -3, 3, -100, 100);

	glMatrixMode(GL_MODELVIEW);                            // Select The Modelview Matrix
}

void reshape(int width, int height)
{
	if (height == 0)                                        // Prevent A Divide By Zero By
	{
		height = 1;                                        // Making Height Equal One
	}

	wHeight = height;
	wWidth = width;

	updateView(wHeight, wWidth);
}

void idle()
{
	glutPostRedisplay();//�������»���
}
float size = 0.1f;
float eye[] = { 0, 0, 8 };
float center[] = { 0, 0, 0 };
float move[] = { 0, 0, 0 };
//�ü��̲ٿ�ͼ��
void key(unsigned char k, int x, int y)
{
	switch (k)
	{
	//����ƶ�
	case 'a': {
				  eye[0] = 3;
				  eye[1] = 0;
				  eye[2] = 8;
				  break;
	}
	case 'd': {
				  eye[0] = -3;
				  eye[1] = 0;
				  eye[2] = 8;
				  break;
	}
	case 'w': {
				  eye[0] = 0;
				  eye[1] = 3;
				  eye[2] = 8;
				  break;
	}
	case 's': {
				  eye[0] = 0;
				  eye[1] = -3;
				  eye[2] = 8;
				  break;
	}
	}
}


void redraw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();                                    // Reset The Current Modelview Matrix
	//�ӵ�ת��
	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);                // ������0��0��0�����ӵ����� (0,5,50)��Y������
	//�߿�ģʽ�����ģʽת��
	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	//����
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);//��������
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = { 5, 5, 5, 1 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);//��Դλ�ã���ɫ
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);//������
	glEnable(GL_LIGHT0);//������Դ

	//    glTranslatef(0.0f, 0.0f,-6.0f);            // Place the triangle at Center
	glRotatef(fRotate, 0, 1.0f, 0);            // Rotate around Y axis
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	Draw_Scene();    // Draw Scene

	glRotatef(fRevolve, 0, 1.0f, 0);            // Rotate around Y axis
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	glutSolidTeapot(1);

	glTranslatef(move[0], move[1], move[2]);
	glutSolidTeapot(1);

	if (bAnim) fRotate += 0.5f;
	if (tAnim) fRevolve += 0.3f;

	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480, 480);
	int windowHandle = glutCreateWindow("��ҵ1");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}

