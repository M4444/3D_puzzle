#include "Polje.h"

/********/
#include "GL/glut.h"
#include "GL/GL.H"
/********/

void Polje::ctraj()
{
	glPushMatrix();
	{
		glTranslatef(x, y-1, z);
		glScalef(a, a, a);
		glRotatef(Rx, 1, 0, 0);
		glRotatef(Ry, 0, 1, 0);
		glRotatef(Rz, 0, 0, 1);

		glBegin(GL_QUADS);
		{
			//Down
			switch (boja)
			{
				default: case 0:
					glColor3f(0.5, 0.3, 0);
				break;
				case 1:
					glColor3f(0.8f, 0.0f, 0.0f);
				break;
				case 2:
					glColor3f(0.8f, 0.8f, 0.0f);
				break;
				case 3:
					glColor3f(0.4f, 0.0f, 0.8f);
				break;
				case 4:
					glColor3f(0.0f, 0.0f, 0.8f);
				break;
			}
			glVertex3f(0.5f, 0.0f, 0.5f);
			glVertex3f(-0.5f, 0.0f, 0.5f);
			glVertex3f(-0.5f, 0.0f, -0.5f);
			glVertex3f(0.5f, 0.0f, -0.5f);
		}glEnd();

	}glPopMatrix();
}

bool Polje::proveri(float tx, float tz)
{
	if(tx <= x + 0.5*a && tx >= x - 0.5*a && tz <= z + 0.5*a && tz >= z - 0.5*a)
	{
		return true;
	}
	else
	{
		return false;
	}
}