from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import time


global sun_rotate, earth_rorate, moon_rotate


def init():
    global sun_rotate, earth_rorate, moon_rotate
    sun_rotate, earth_rorate, moon_rotate = 0, 0, 0
    mat_spectual = [1.0, 1.0, 1.0, 1.0]
    light_position = [1.0, 1.0, 1.0, 0.0]
    mat_shiness = [25.0]
    Light_Model_Ambient = [0.2, 0.2, 0.2, 1.0]
    white_light = [1.0, 1.0, 1.0, 1.0]
    glClearColor(0.0, 0.0, 0.0, 0.0)
    glShadeModel(GL_SMOOTH)
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spectual)
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shiness)
    glLightfv(GL_LIGHT0, GL_POSITION, light_position)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light)
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light)
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient)
    glEnable(GL_COLOR_MATERIAL)
    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)
    glEnable(GL_DEPTH_TEST)


def reshape(width, height):
    glViewport(0, 0, width, height)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    if width <= height:
        glOrtho(-1.5, 1.5, -1.5 * height / width, 1.5 * height / width, -10.0, 10.0)
    else:
        glOrtho(-1.5 * width / height, 1.5 * width / height, -1.5, 1.5, -10.0, 10.0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    gluLookAt(5.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0)


def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glColor3f(1.0, 1.0, 1.0)
    glPushMatrix()
    # 旋转参数
    global sun_rotate, earth_rorate, moon_rotate
    sun_rotate = (sun_rotate + 2) % 360
    earth_rorate = (earth_rorate + 3) % 360
    moon_rotate = (moon_rotate + 5) % 360

    # 设置太阳
    glRotatef(sun_rotate, 0.0, 0.0, 1.0)
    glColor3f(1.0, 0.0, 0.0)
    glutSolidSphere(0.6, 30, 30)

    # 设置地球
    glPopMatrix()
    glPushMatrix()
    glRotatef(earth_rorate, 0.0, 0.0, 1.0)
    glTranslatef(0.0, -1.8, 0.0)
    glColor3f(0.0, 0.0, 1.0)
    glutSolidSphere(0.4, 30, 30)

    # 设置月球
    glRotatef(moon_rotate, 0.0, 0.0, 1.0)
    glTranslatef(0.0, 0.5, 0.0)
    glColor3f(0.0, 1.0, 0)
    glutSolidSphere(0.1, 30, 30)

    glutPostRedisplay()
    glPopMatrix()
    glFlush()
    glutSwapBuffers()
    time.sleep(0.05)


if __name__ == "__main__":
    glutInit()
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH)
    glutInitWindowSize(600, 400)
    glutCreateWindow(b"work2")
    init()
    glutDisplayFunc(display)
    glutIdleFunc(display)
    glutReshapeFunc(reshape)
    glutMainLoop()

