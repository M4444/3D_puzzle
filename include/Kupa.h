#pragma once
#include "Telo.h"
#include "SvaTela.h"

class Kupa : public Telo
{
private:
	float r;
	float h;

public:
	Kupa(Boja b, float x, float y, float z, float r, float h) : Telo(b, x, y, z, r)
	{
		this->r = r;
		this->h = h;
	}

	float getScaleX()
	{
		return 2*r;
	}
	float getScaleY()
	{
		return h;
	}
	float getScaleZ()
	{
		return 2*r;
	}

	void ctraj()
	{
		int p = SvaTela::getPrec();
		glPushMatrix();
		{
			glTranslatef(x, y, z);
			glScalef(r, h, r);
			glRotatef(Rx, 1, 0, 0);
			glRotatef(Ry, 0, 1, 0);
			glRotatef(Rz, 0, 0, 1);

			// Down
			//glColor3f(0, 1, 1);
			glColor3fv(colors3fv[b][2]);
			// Center
			glVertex3f(0, -0.5, 0);
			glBegin(GL_TRIANGLE_FAN);
			{
				int theta;
				for(theta = 0; theta < 360; theta += 360 / p)
				{
					glVertex3f(cos(DEG_TO_RAD(theta)), -0.5, sin(DEG_TO_RAD(theta)));
				}
			}glEnd();

			// Up
			//glColor3f(0.6, 1, 0.6);
			glColor3fv(colors3fv[b][0]);
			glBegin(GL_TRIANGLE_FAN);
			{
				glVertex3f(0, 0.5, 0);
				int theta;
				for(theta = 0; theta <= 360; theta += 360 / p)
				{
					glVertex3f(cos(DEG_TO_RAD(theta)), -0.5, sin(DEG_TO_RAD(theta)));
				}
				if(theta != 360) glVertex3f(cos(DEG_TO_RAD(360)), -0.5, sin(DEG_TO_RAD(360)));
			}glEnd();

		}glPopMatrix();
	}
};