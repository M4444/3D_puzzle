#pragma once
#include "Kvadar.h"

class Kocka : public Kvadar
{
public:
	Kocka(Boja b, float x, float y, float z, float a) : Kvadar(b, x, y, z, a, a, a) {}

	/*void ctraj()
	{
		glPushMatrix();
		{
			glTranslatef(x, y, z);
			glScalef(a, a, a);
			glRotatef(Rx, 1, 0, 0);
			glRotatef(Ry, 0, 1, 0);
			glRotatef(Rz, 0, 0, 1);

			glBegin(GL_QUADS);
			{
				// Front
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
	}*/
};