#include "Telo.h"

void Telo::crtajOkvir()
{
	glPushMatrix();
	{
		glTranslatef(x, y, z);
		glScalef(getScaleX()*1.1, getScaleY()*1.1, getScaleZ()*1.1);
		glRotatef(Rx, 1, 0, 0);
		glRotatef(Ry, 0, 1, 0);
		glRotatef(Rz, 0, 0, 1);

		glLineWidth(2);
		glBegin(GL_LINES);
		{
			// FDL
			glColor3f(0, 1, 0);
			glVertex3fv(cube3fv[0]);
			glVertex3f(cube3fv[0][0] + 0.25, cube3fv[0][1], cube3fv[0][2]);
			glVertex3fv(cube3fv[0]);
			glVertex3f(cube3fv[0][0], cube3fv[0][1] + 0.25, cube3fv[0][2]);
			glVertex3fv(cube3fv[0]);
			glVertex3f(cube3fv[0][0], cube3fv[0][1], cube3fv[0][2] - 0.25);

			// FDR
			glColor3f(0, 1, 0);
			glVertex3fv(cube3fv[1]);
			glVertex3f(cube3fv[1][0] - 0.25, cube3fv[1][1], cube3fv[1][2]);
			glVertex3fv(cube3fv[1]);
			glVertex3f(cube3fv[1][0], cube3fv[1][1] + 0.25, cube3fv[1][2]);
			glVertex3fv(cube3fv[1]);
			glVertex3f(cube3fv[1][0], cube3fv[1][1], cube3fv[1][2] - 0.25);

			// FUR
			glColor3f(0, 1, 0);
			glVertex3fv(cube3fv[2]);
			glVertex3f(cube3fv[2][0] - 0.25, cube3fv[2][1], cube3fv[2][2]);
			glVertex3fv(cube3fv[2]);
			glVertex3f(cube3fv[2][0], cube3fv[2][1] - 0.25, cube3fv[2][2]);
			glVertex3fv(cube3fv[2]);
			glVertex3f(cube3fv[2][0], cube3fv[2][1], cube3fv[2][2] - 0.25);

			// FUL
			glColor3f(0, 1, 0);
			glVertex3fv(cube3fv[3]);
			glVertex3f(cube3fv[3][0] + 0.25, cube3fv[3][1], cube3fv[3][2]);
			glVertex3fv(cube3fv[3]);
			glVertex3f(cube3fv[3][0], cube3fv[3][1] - 0.25, cube3fv[3][2]);
			glVertex3fv(cube3fv[3]);
			glVertex3f(cube3fv[3][0], cube3fv[3][1], cube3fv[3][2] - 0.25);

			// BDR
			glColor3f(0, 1, 0);
			glVertex3fv(cube3fv[4]);
			glVertex3f(cube3fv[4][0] - 0.25, cube3fv[4][1], cube3fv[4][2]);
			glVertex3fv(cube3fv[4]);
			glVertex3f(cube3fv[4][0], cube3fv[4][1] + 0.25, cube3fv[4][2]);
			glVertex3fv(cube3fv[4]);
			glVertex3f(cube3fv[4][0], cube3fv[4][1], cube3fv[4][2] + 0.25);

			// BDL
			glColor3f(0, 1, 0);
			glVertex3fv(cube3fv[5]);
			glVertex3f(cube3fv[5][0] + 0.25, cube3fv[5][1], cube3fv[5][2]);
			glVertex3fv(cube3fv[5]);
			glVertex3f(cube3fv[5][0], cube3fv[5][1] + 0.25, cube3fv[5][2]);
			glVertex3fv(cube3fv[5]);
			glVertex3f(cube3fv[5][0], cube3fv[5][1], cube3fv[5][2] + 0.25);

			// BUL
			glColor3f(0, 1, 0);
			glVertex3fv(cube3fv[6]);
			glVertex3f(cube3fv[6][0] + 0.25, cube3fv[6][1], cube3fv[6][2]);
			glVertex3fv(cube3fv[6]);
			glVertex3f(cube3fv[6][0], cube3fv[6][1] - 0.25, cube3fv[6][2]);
			glVertex3fv(cube3fv[6]);
			glVertex3f(cube3fv[6][0], cube3fv[6][1], cube3fv[6][2] + 0.25);

			// BUR
			glColor3f(0, 1, 0);
			glVertex3fv(cube3fv[7]);
			glVertex3f(cube3fv[7][0] - 0.25, cube3fv[7][1], cube3fv[7][2]);
			glVertex3fv(cube3fv[7]);
			glVertex3f(cube3fv[7][0], cube3fv[7][1] - 0.25, cube3fv[7][2]);
			glVertex3fv(cube3fv[7]);
			glVertex3f(cube3fv[7][0], cube3fv[7][1], cube3fv[7][2] + 0.25);
		}glEnd();

	}glPopMatrix();
}