#pragma once
#include "Telo.h"

class Kvadar : public Telo
{
private:
	float aX, aY, aZ;

public:
	Kvadar(Boja b, float x, float y, float z, float ax, float ay, float az) : Telo(b, x, y, z)
	{
		aX = ax;
		aY = ay;
		aZ = az;
	}

	float getScaleX()
	{
		return aX;
	}
	float getScaleY()
	{
		return aY;
	}
	float getScaleZ()
	{
		return aZ;
	}

	void ctraj()
	{
		//int c = LJUBICASTA;
		glPushMatrix();
		{
			glTranslatef(x, y, z);
			glScalef(aX, aY, aZ);
			glRotatef(Rx, 1, 0, 0);
			glRotatef(Ry, 0, 1, 0);
			glRotatef(Rz, 0, 0, 1);

			glBegin(GL_QUADS);
			{
				// Front
				glColor3fv(colors3fv[b][2]);
				glVertex3fv(cube3fv[0]);
				glVertex3fv(cube3fv[1]);
				glVertex3fv(cube3fv[2]);
				glVertex3fv(cube3fv[3]);

				// Back
				glColor3fv(colors3fv[b][2]);
				glVertex3fv(cube3fv[4]);
				glVertex3fv(cube3fv[5]);
				glVertex3fv(cube3fv[6]);
				glVertex3fv(cube3fv[7]);

				// Right
				glColor3fv(colors3fv[b][1]);
				glVertex3fv(cube3fv[1]);
				glVertex3fv(cube3fv[4]);
				glVertex3fv(cube3fv[7]);
				glVertex3fv(cube3fv[2]);

				// Left
				glColor3fv(colors3fv[b][1]);
				glVertex3fv(cube3fv[5]);
				glVertex3fv(cube3fv[0]);
				glVertex3fv(cube3fv[3]);
				glVertex3fv(cube3fv[6]);

				// Up
				glColor3fv(colors3fv[b][0]);
				glVertex3fv(cube3fv[3]);
				glVertex3fv(cube3fv[2]);
				glVertex3fv(cube3fv[7]);
				glVertex3fv(cube3fv[6]);

				//Down
				glColor3fv(colors3fv[b][0]);
				glVertex3fv(cube3fv[1]);
				glVertex3fv(cube3fv[0]);
				glVertex3fv(cube3fv[5]);
				glVertex3fv(cube3fv[4]);

			}glEnd();

		}glPopMatrix();
	}
};