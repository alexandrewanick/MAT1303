#include "glut.h"
#include "Funcao.hpp"
#include <cmath>
#include <iostream>
using namespace std;

Funcao f;

int xv;
int yv;

float t = 0;
float t1 = 0;

float theta = 135;
float phi   = 45.0;
float gamma = 90.0;
float dt = 0.0001;

void inicia_config()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
//	glRotatef(gamma,0,0,1);
//	glRotatef(phi  ,0,1,0);
//	glRotatef(theta,0,0,1);
	float x = cos(t1);
	float y = sin(t1);
	gluLookAt(x,y,1-t1,0,0,0,0,0,1);
	t1 += dt;
	if (fabs(t1) > 20)
		dt = -dt;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	glOrtho(-2,2,-2,2,-20,20);
	gluPerspective(45, 1.333, 0, 100);
}

void display()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINES);
	 glColor3f(1,0,0);
	 glVertex3f( 0,0,0);
	 glVertex3f( 1,0,0);

	 glColor3f(0,1,0);
	 glVertex3f(0,1,0);
	 glVertex3f(0,0,0); 
	 
	 glColor3f(0,0,1);
	 glVertex3f(0,0,1);
	 glVertex3f(0,0,0);
	glEnd();

	glColor3f(1,1,0);
	f.grafico();
	glutSwapBuffers();
}
void move()
{
	inicia_config();
    glutPostRedisplay();
}

void teclado(unsigned char key, int x, int y)
{
	cout << key << endl;
	if (key == 'a') {
		inicia_config();
		glutPostRedisplay();
	}

}

void botao_mouse(int b,int s,int x,int y)
{
	if (b == GLUT_RIGHT_BUTTON)
	{
		if (s == GLUT_DOWN) {
			xv = x;
			yv = y;
		}
		else
			if (s == GLUT_UP)
			    cout << "botao direito solto" << x << ", " << y << endl;
	}
}

void botao_movimento(int x,int y)
{
	theta += (x - xv);
	phi   += (yv - y);
	inicia_config();
	glutPostRedisplay();
	xv = x;
	yv = y;
}

void movimento(int x,int y)
{
	cout << x << " / " << y << endl;
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(400,400);
	glutCreateWindow("ponto");
	inicia_config();
	glutDisplayFunc(display);
	glutMouseFunc(botao_mouse);
	glutMotionFunc(botao_movimento);
	glutPassiveMotionFunc(movimento);
	glutKeyboardFunc(teclado);
	glutIdleFunc(move);
	glutMainLoop();
}
