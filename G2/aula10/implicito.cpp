

#include <GLUT/glut.h>
#include <cmath>
#include "implicito.h"
#include <iostream>
using namespace std;

void implicito::display_superficie()
{
    int i,j,k;
    float x,y,z;
    float dx,dy,dz;
    float z0,z1,z2,z3;
    float v[8][3];
    dx = (xmax-xmin)/pontos;
    dy = (ymax-ymin)/pontos;
    dz = (zmax-zmin)/pontos;
    glColor3f(1.0,1.0,1.0);
    x = xmin;
    for(i=0;i < pontos; i++)
    {
        y = ymin;
        for(j=0 ; j < pontos; j++)
        {
            z = zmin;
            for(k=0; k< pontos; k++)
            {
                v[0][0] = x ; v[1][0] = x+dx; v[2][0] = x ;
                v[3][0] = x+dx;
                v[0][1] = y ; v[1][1] = y ; v[2][1] = y+dy;
                v[3][1] = y+dy;
                v[0][2] = z ; v[1][2] = z ; v[2][2] = z ;
                v[3][2] = z ;
                v[4][0] = x ; v[5][0] = x+dx; v[6][0] = x ;
                v[7][0] = x+dx;
                v[4][1] = y ; v[5][1] = y ; v[6][1] = y+dy;
                v[7][1] = y+dy;
                v[4][2] = z+dz; v[5][2] = z+dz; v[6][2] = z+dz;
                v[7][2] = z+dz;
                tetraedro(v[0],v[1],v[3],v[7]);
                tetraedro(v[0],v[1],v[5],v[7]);
                tetraedro(v[0],v[2],v[3],v[7]);
                tetraedro(v[0],v[2],v[6],v[7]);
                tetraedro(v[0],v[4],v[5],v[7]);
                tetraedro(v[0],v[4],v[6],v[7]);
                z += dz;
            }
            y += dy;
        }
        x += dx;
    }
}

void implicito::tetraedro(float *v0,float *v1, float *v2,float *v3)
{
    #define TETRA 0
    
    int i;
    int n = 0;
    float t,p[4][3];
    float w0,w1,w2,w3;
    w0 = f(v0[0],v0[1],v0[2]);
    w1 = f(v1[0],v1[1],v1[2]);
    w2 = f(v2[0],v2[1],v2[2]);
    w3 = f(v3[0],v3[1],v3[2]);
    if (w0 * w1 < 0) {
        t = -w0/(w1-w0);
        for(i=0;i<3;i++)
            p[n][i] = v0[i] + t * (v1[i] - v0[i]);
        n++;
    }
    if (w1 * w3 < 0) {
        t = -w1/(w3-w1);
        for(i=0;i<3;i++)
            p[n][i] = v1[i] + t * (v3[i] - v1[i]);
        n++;
    }
    if (w0 * w3 < 0) {
        t = -w0/(w3-w0);
        for(i=0;i<3;i++)
            p[n][i] = v0[i] + t * (v3[i] - v0[i]);
        n++;
    }
    if (w2 * w3 < 0) {
        t = -w2/(w3-w2);
        for(i=0;i<3;i++)
            p[n][i] = v2[i] + t * (v3[i] - v2[i]);
        n++;
    }
    if (w0 * w2 < 0) {
        t = -w0/(w2-w0);
        for(i=0;i<3;i++)
            p[n][i] = v0[i] + t * (v2[i] - v0[i]);
        n++;
    }
    if (w1 * w2 < 0) {
        t = -w1/(w2-w1);
        for(i=0;i<3;i++)
            p[n][i] = v1[i] + t * (v2[i] - v1[i]);
        n++;
    }
    if (n == 3) { // Triangulo
#if TETRA
        glColor3f(0,0,1);
        glBegin(GL_LINE_LOOP);
        glVertex3fv(v0);
        glVertex3fv(v1);
        glVertex3fv(v2);
        glEnd();
        glBegin(GL_LINES);
        glVertex3fv(v0);
        glVertex3fv(v3);
        glVertex3fv(v1);
        glVertex3fv(v3);
        glVertex3fv(v2);
        glVertex3fv(v3);
        glEnd();
#endif
        glColor3f(1,0,0);
        glBegin(GL_TRIANGLES);
        glVertex3f(p[0][0],p[0][1],p[0][2]);
        glVertex3f(p[1][0],p[1][1],p[1][2]);
        glVertex3f(p[2][0],p[2][1],p[2][2]);
        glEnd();
        glLineWidth(3);
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
        glBegin(GL_LINE_LOOP);
        glColor3f(0,0,0);
        glVertex3f(p[0][0],p[0][1],p[0][2]);
        glVertex3f(p[1][0],p[1][1],p[1][2]);
        glVertex3f(p[2][0],p[2][1],p[2][2]);
        glEnd();
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        glEnable(GL_LIGHT2);
        glLineWidth(1);
    }
    if (n == 4) { // QUADS
#if TETRA
        glColor3f(0,0,1);
        glBegin(GL_LINE_LOOP);
        glVertex3fv(v0);
        glVertex3fv(v1);
        glVertex3fv(v2);
        glEnd();
        glBegin(GL_LINES);
        glVertex3fv(v0);
        glVertex3fv(v3);
        glVertex3fv(v1);
        glVertex3fv(v3);
        glVertex3fv(v2);
        glVertex3fv(v3);
        glEnd();
#endif
        glColor3f(0,0,0);
        glLineWidth(3);
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
        glBegin(GL_LINE_LOOP);
        glVertex3f(p[0][0],p[0][1],p[0][2]);
        glVertex3f(p[1][0],p[1][1],p[1][2]);
        glVertex3f(p[2][0],p[2][1],p[2][2]);
        glVertex3f(p[3][0],p[3][1],p[3][2]);
        glEnd();
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        glEnable(GL_LIGHT2);
        glLineWidth(1);
        glColor3f(1,0,0);
        glBegin(GL_QUADS);
        glVertex3f(p[0][0],p[0][1],p[0][2]);
        glVertex3f(p[1][0],p[1][1],p[1][2]);
        glVertex3f(p[2][0],p[2][1],p[2][2]);
        glVertex3f(p[3][0],p[3][1],p[3][2]);
        glEnd();
    }
 /*   glLineWidth(3.0);
    glBegin(GL_LINES);
    float r[3];
    if (n < 5) {
        for(int i = 0;i<n;i++) {
            (*this).n(p[i][0],p[i][1],p[i][2],r);
            glVertex3f(p[i][0],p[i][1],p[i][2]);
            glVertex3f(p[i][0]+r[0],p[i][1]+r[1],p[i][2]+r[2]);
        }
    }
    glEnd();
    glLineWidth(1.0);*/
	
}

void implicito::n(float x,float y,float z,float *r)
{
	  r[0] = 2*x;
	  r[1] = 2*y;
	  r[2] = 2*z;
	//  cout << r[0] << "  " << r[1] << "  " << r[2] << endl;
	//  float norma = sqrt(r[0] * r[0] + r[1] * r[1] + r[2]*r[2]);
		
	//  r[0] /= norma;		
	//  r[1] /= norma;
	//  r[2] /= norma;
}

