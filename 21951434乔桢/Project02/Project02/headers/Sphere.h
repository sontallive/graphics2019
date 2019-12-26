#ifndef SPHERE_H
#define SPHERE_H

#ifndef PI
#define PI 3.1415926
#endif
#ifndef PI2
#define PI2 6.2831853
#endif

#include <glad/glad.h>
#include <cmath>

class Sphere {
public:
	GLuint* vboId;
	GLuint vert, texcoord;
	GLfloat* verts;//���涥���뷨������ָ��
	GLfloat* texcoords;//�������������ָ��
	GLfloat vertNum;
	/*Sphere(int m, int n) {
		vertNum = m*n * 4;//��������
		verts = new GLfloat[vertNum * 5];//ÿ��������xyz��������,���*3
		float stepAngZ = PI / m;//����Ƕ�ÿ�����ӵ�ֵ
		float stepAngXY = PI2 / n;//����Ƕ�ÿ�����ӵ�ֵ
		float angZ = 0.0;//��ʼ������Ƕ�
		float angXY = 0.0;//��ʼ�ĺ���Ƕ�

		int index = 0;
		for (int i = 0; i<m; i++) {
			for (int j = 0; j<n; j++) {
				//����һ������
				float x1 = sin(angZ)*cos(angXY);
				float y1 = sin(angZ)*sin(angXY);
				float z1 = cos(angZ);
				verts[index] = x1; index++;
				verts[index] = y1; index++;
				verts[index] = z1; index++;
				float v1 = angZ / PI;
				float u1 = angXY / PI2;
				verts[index] = u1; index++;
				verts[index] = v1; index++;

				float x2 = sin(angZ + stepAngZ)*cos(angXY);
				float y2 = sin(angZ + stepAngZ)*sin(angXY);
				float z2 = cos(angZ + stepAngZ);
				verts[index] = x2; index++;
				verts[index] = y2; index++;
				verts[index] = z2; index++;
				float v2 = (angZ + stepAngZ) / PI;
				float u2 = angXY / PI2;
				verts[index] = u2; index++;
				verts[index] = v2; index++;


				float x3 = sin(angZ + stepAngZ)*cos(angXY + stepAngXY);
				float y3 = sin(angZ + stepAngZ)*sin(angXY + stepAngXY);
				float z3 = cos(angZ + stepAngZ);
				verts[index] = x3; index++;
				verts[index] = y3; index++;
				verts[index] = z3; index++;
				float v3 = (angZ + stepAngZ) / PI;
				float u3 = (angXY + stepAngXY) / PI2;
				verts[index] = u3; index++;
				verts[index] = v3; index++;

				float x4 = sin(angZ)*cos(angXY + stepAngXY);
				float y4 = sin(angZ)*sin(angXY + stepAngXY);
				float z4 = cos(angZ);
				verts[index] = x4; index++;
				verts[index] = y4; index++;
				verts[index] = z4; index++;
				float v4 = angZ / PI;
				float u4 = (angXY + stepAngXY) / PI2;
				verts[index] = u4; index++;
				verts[index] = v4; index++;

				angXY += stepAngXY;
			}
			angXY = 0.0;//ÿ�κ��򵽴�2PI�Ƕ������Ƕȹ�0
			angZ += stepAngZ;
		}*/
	Sphere(int m, int n) {
		vertNum = m*n * 4*1.5;//��������
		verts = new GLfloat[vertNum * 5];//ÿ��������xyz��������,���*3
		float stepAngZ = PI / m;//����Ƕ�ÿ�����ӵ�ֵ
		float stepAngXY = PI2 / n;//����Ƕ�ÿ�����ӵ�ֵ
		float angZ = 0.0;//��ʼ������Ƕ�
		float angXY = 0.0;//��ʼ�ĺ���Ƕ�

		int index = 0;
		for (int i = 0; i<m; i++) {
			for (int j = 0; j<n; j++) {
				//����һ������
				float x1 = sin(angZ)*cos(angXY);
				float y1 = sin(angZ)*sin(angXY);
				float z1 = cos(angZ);
				verts[index] = x1; index++;
				verts[index] = y1; index++;
				verts[index] = z1; index++;
				float v1 = angZ / PI;
				float u1 = angXY / PI2;
				verts[index] = u1; index++;
				verts[index] = v1; index++;

				float x2 = sin(angZ + stepAngZ)*cos(angXY);
				float y2 = sin(angZ + stepAngZ)*sin(angXY);
				float z2 = cos(angZ + stepAngZ);
				verts[index] = x2; index++;
				verts[index] = y2; index++;
				verts[index] = z2; index++;
				float v2 = (angZ + stepAngZ) / PI;
				float u2 = angXY / PI2;
				verts[index] = u2; index++;
				verts[index] = v2; index++;


				float x3 = sin(angZ + stepAngZ)*cos(angXY + stepAngXY);
				float y3 = sin(angZ + stepAngZ)*sin(angXY + stepAngXY);
				float z3 = cos(angZ + stepAngZ);
				verts[index] = x3; index++;
				verts[index] = y3; index++;
				verts[index] = z3; index++;
				float v3 = (angZ + stepAngZ) / PI;
				float u3 = (angXY + stepAngXY) / PI2;
				verts[index] = u3; index++;
				verts[index] = v3; index++;

			    verts[index] = x1; index++;
				verts[index] = y1; index++;
				verts[index] = z1; index++;
				verts[index] = u1; index++;
				verts[index] = v1; index++;

				verts[index] = x3; index++;
				verts[index] = y3; index++;
				verts[index] = z3; index++;
				verts[index] = u3; index++;
				verts[index] = v3; index++;
				
				float x4 = sin(angZ)*cos(angXY + stepAngXY);
				float y4 = sin(angZ)*sin(angXY + stepAngXY);
				float z4 = cos(angZ);
				verts[index] = x4; index++;
				verts[index] = y4; index++;
				verts[index] = z4; index++;
				float v4 = angZ / PI;
				float u4 = (angXY + stepAngXY) / PI2;
				verts[index] = u4; index++;
				verts[index] = v4; index++;

				angXY += stepAngXY;
			}
			angXY = 0.0;//ÿ�κ��򵽴�2PI�Ƕ������Ƕȹ�0
			angZ += stepAngZ;
		}
	}//m������ϸ�̶ֳ�,n�Ǻ���ϸ�̶ֳ�
	~Sphere() {}
};

#endif