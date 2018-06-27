#include "geometry.h"

#include <windows.h>
/********/
//#include "GL/glut.h"
//#include "GL/GL.H"
/********/

void crtajKocku(float x, float y, float z, float a)
{
	glPushMatrix();
	{
		glTranslatef(x, y, z);
		glScalef(a, a, a);
		
		GLfloat v[8][3] = {
							{ -0.5f, -0.5f,  0.5f },
							{  0.5f, -0.5f,  0.5f },
							{  0.5f,  0.5f,  0.5f },
							{ -0.5f,  0.5f,  0.5f },
							{  0.5f, -0.5f, -0.5f },
							{ -0.5f, -0.5f, -0.5f },
							{ -0.5f,  0.5f, -0.5f },
							{  0.5f,  0.5f, -0.5f }
						  };


		glBegin(GL_QUADS);
		{/*
			// Font
			glColor3f(1, 0, 0);
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glVertex3f( 0.5f, -0.5f, 0.5f);
			glVertex3f( 0.5f,  0.5f, 0.5f);
			glVertex3f(-0.5f,  0.5f, 0.5f);

			// Back
			glColor3f(1, 0.5, 0);
			glVertex3f( 0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f,  0.5f, -0.5f);
			glVertex3f( 0.5f,  0.5f, -0.5f);
			*/

			glColor3f(1, 0, 0);
			glVertex3fv(cube3fv[0]);
			glVertex3fv(cube3fv[1]);
			glVertex3fv(cube3fv[2]);
			glVertex3fv(cube3fv[3]);

			// Back
			glColor3f(1, 0.5, 0);
			glVertex3fv(cube3fv[4]);
			glVertex3fv(cube3fv[5]);
			glVertex3fv(cube3fv[6]);
			glVertex3fv(cube3fv[7]);

			// Right
			glColor3f(0, 1, 0);
			glVertex3fv(cube3fv[1]);
			glVertex3fv(cube3fv[4]);
			glVertex3fv(cube3fv[7]);
			glVertex3fv(cube3fv[2]);

			// Left
			glColor3f(0, 0, 1);
			glVertex3fv(cube3fv[5]);
			glVertex3fv(cube3fv[0]);
			glVertex3fv(cube3fv[3]);
			glVertex3fv(cube3fv[6]);

			// Up
			glColor3f(1, 1, 0);
			glVertex3fv(cube3fv[3]);
			glVertex3fv(cube3fv[2]);
			glVertex3fv(cube3fv[7]);
			glVertex3fv(cube3fv[6]);

			//Down
			glColor3f(1, 1, 1);
			glVertex3fv(cube3fv[1]);
			glVertex3fv(cube3fv[0]);
			glVertex3fv(cube3fv[5]);
			glVertex3fv(cube3fv[4]);

		}glEnd();

	}glPopMatrix();
}