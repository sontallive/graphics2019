#ifndef CAMERA_H
#define CAMERA_H
#include "base.h"
struct glCamera
{
  vec3  pos;
  float viewMatrix[16];
  vec3  forward;
  vec3  right;
  vec3  up;

public :

  glCamera( vec3 at)
  {
    pos=at;
  }

  void getViewMatrix()
  {
    glMatrixMode(GL_MODELVIEW);
    glGetFloatv(GL_MODELVIEW_MATRIX,viewMatrix);
  }

  void update()
  {
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glTranslatef(-pos.x,-pos.y,-pos.z);

   getViewMatrix();

   right=vec3(viewMatrix[0],viewMatrix[4],viewMatrix[8]);
   up=vec3(viewMatrix[1],viewMatrix[5],viewMatrix[9]);
   forward=vec3(viewMatrix[2],viewMatrix[6],viewMatrix[10]);
  } 
};
#endif
#ifndef GLSKYBOX
#define GLSKYBOX
#include "base.h"
#include "gltexture.h"

void glDrawSkyBox(glTexture *tex,float x,float y,float z,float width,float height,float len)
{
  tex->MakeCurrent();

  //��ȡ���ĵ�
  x=x-width/2;
  y=y-height/2;
  z=z-len/2;

  //back face
  glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,1.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x+width, y, z);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x+width, y+height, z);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x, y+height, z);

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x, y, z);
  glEnd();
  //front face
  glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,-1.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x, y, z+len);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x, y+height, z+len);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x+width, y+height, z+len);

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x+width, y, z+len);
  glEnd();
  //bottom face
  glBegin(GL_QUADS);
    glNormal3f(0.0,1.0,0.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x, y, z);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x, y, z+len);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x+width, y, z+len);

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x+width, y, z);
  glEnd();
  //top face
  glBegin(GL_QUADS);
    glNormal3f(0.0,-1.0,0.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x+width, y+height, z);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x+width, y+height, z+len);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x, y+height, z+len);

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x, y+height, z);
  glEnd();
  //left face
  glBegin(GL_QUADS);
    glNormal3f(1.0,0.0,0.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x, y+height, z);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x, y+height, z+len);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x, y, z+len);

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x, y, z);
  glEnd();

  //right face
  glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,-1.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x+width, y, z);

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x+width, y, z+len);

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x+width, y+height, z+len);

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x+width, y+height, z);
  glEnd();
}
#endif
class planet
{
public:
  float aroundRotatedSpeed;
  float selfRotatedSpeed;
  float radius;
  vec3 pos;

  glTexture *texture;
public:

  planet(const char* texname,float as,float ss,float radius,vec3 pos)
  {
    texture=new glTexture(texname,true);
    this->aroundRotatedSpeed =as;
    this->selfRotatedSpeed =ss;
    this->radius =radius;
    this->pos =pos;

  }

  planet()
  {
      if (!texture)
      {
          delete texture;
          texture = NULL;
      }
  }

};
bool lighting = true;
fileSystem filesys;//record/replayϵͳʹ��
int frontViewOnOff;//���ر�����ǰ��ͼ������ͼת��
glTexture *boxtex;//��պ�������ͼ����������պ���Ҫ�����޷�������������ھ���һ��������պ��������ϣ���һ��
glTexture *parttex;
glExplosion * glexp = new glExplosion(1, vec3(0, 0, 0), 1.0f, 0);
bool isexp = true;
int numexp;
float px, py, pz;
glTrail* trail;

planet * earth; //����
planet * moon;  //����

glCamera camera(vec3(0.0f, 0.0f, 10.0f)); //�������ʼλ��,w/s�����������ǰ���ƶ���a/d��������������ƶ��������������϶������������pitch/yaw��ת

int angle = 0; //���ı������������ǵ��ƶ���ת�����ٶ�����angleΪ�����������ı�angle��ת�ٶȻ�Ӱ���������ǵ��˶��ٶȣ��������ٶȺ;��룬�������Ƕ��ǰ���angle��Ա��������˶�

void SetLight(bool b)
{
    float amb[4] = { 1.0, 0.8, 0.8, 1 };
    float dif[4] = { 1.0, 1.0, 1.0, 1 };
    float pos[4] = { 0, 10, 0, 1 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, dif);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);

    if (b)
    {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }
    else
    {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
    }

    glShadeModel(GL_SMOOTH);
}

void init()
{
    boxtex = new glTexture("�ǿ�ͼ.png", true);

    sun = new planet("̫��.png", 0.0f, 1.0f, 1.0f, vec3(0.0f, 0.0f, 0.0f));
    earth = new planet("����.png", 1.0f, 2.0f, 0.5f, vec3(5.0f, 2.0f, 8.0f));
    moon = new planet("����.png", 0.5f, 0.5f, 0.2f, vec3(1.5f, 0.0f, 0.0f));

    parttex = new glTexture("particle.png");

    trail = new glTrail("spawnflash.png");
    trail->setPath(vec3(0, 0, 0));

    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    //��ʼ�������������
    drawInit();
}

void deinit()
{
    delete boxtex;
    delete sun;
    delete earth;
    delete moon;
    delete parttex;
    delete trail;
    delete glexp;
    drawDeInit();
}

void record()
{
    if (filesys.beginWrite("test.txt"))
    {
        filesys.writeInt(angle);
        filesys.closeFile();
    }
}

void rePlay()
{
    if (filesys.beginRead("test.txt"))
    {
        filesys.readInt(&angle);
        filesys.closeFile();
    }
}

static void DrawEarthAndMoon(planet *earth, planet *moon)
{
    glPushMatrix();//����ת+��ת��Χ��̫����
    earth->texture->MakeCurrent();

    glRotatef(angle*earth->aroundRotatedSpeed, 0.0f, 1.0f, 0.0f);
    glTranslatef(earth->pos.x, earth->pos.y, earth->pos.z);
    glRotatef(angle*earth->selfRotatedSpeed, 0.0f, 1.0f, 0.0f);
    drawSphere(earth->radius, 20, 20, true);

    glPushMatrix();//����ת+��ת��Χ�Ƶ���
    moon->texture->MakeCurrent();
    glRotatef(angle*moon->aroundRotatedSpeed, 0.0f, 1.0f, 0.0f);
    glTranslatef(moon->pos.x, moon->pos.y, moon->pos.z);
    glRotatef(angle*moon->selfRotatedSpeed, 0.0f, 1.0f, 0.0f);
    drawSphere(moon->radius, 20, 20, true);
    glPopMatrix();

    glPopMatrix();
}
static void DrawOtherPlanet(planet * p)
{
    glPushMatrix();
    p->texture->MakeCurrent();
    glRotatef(angle*p->aroundRotatedSpeed, 0.0f, 1.0f, 0.0f);
    glTranslatef(p->pos.x, p->pos.y, p->pos.z);
    glRotatef(angle*p->selfRotatedSpeed, 0.0f, 1.0f, 0.0f);
    drawSphere(p->radius, 20, 20, true);
    glPopMatrix();
}
void DrawSolarSystem(planet *sun)
{
    sun->texture->MakeCurrent();

    SetLight(lighting);
    glTranslatef(sun->pos.x, sun->pos.y, sun->pos.z);
    glRotatef(angle*sun->selfRotatedSpeed, 0.0f, 1.0f, 0.0f);
    drawSphere(sun->radius, 50, 50, true);
    DrawEarthAndMoon(earth, moon);//���»���
    DrawOtherPlanet(sx);
    DrawOtherPlanet(jx);
    DrawOtherPlanet(twx);
    DrawOtherPlanet(hwx);
    //����Ȧ����
    DrawOtherPlanet2(mx);
    DrawOtherPlanet2(tx);
    DrawTrail(jx);
}

int  main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA  GLUT_DOUBLE  GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    init();
    glutTimerFunc(25, myTimerFunc, 0);
    glutMainLoop();
    deinit();
    return 0;
}


