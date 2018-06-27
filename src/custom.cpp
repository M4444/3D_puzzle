#include "custom.h"

#include <windows.h>
/********/
//#include "GL/glut.h"
//#include "GL/GL.H"
/********/

void postaviPosmatraca()
{
	switch(0)
	{
	case 0:
		glTranslatef(0, 0, -10);
		glRotatef(45, 1, 0, 0);
		glRotatef(45, 0, 1, 0);
		break;

	case 1:
		glTranslatef(0, 0, -10);
		glRotatef(45, 1, 0, 0);
		glRotatef(-45, 0, 1, 0);
		break;

	case 2:
		glTranslatef(0, 0, -10);
		glRotatef(45, 1, 0, 0);
		glRotatef(-135, 0, 1, 0);
		break;

	case 3:
		glTranslatef(0, 0, -10);
		glRotatef(45, 1, 0, 0);
		glRotatef(135, 0, 1, 0);
		break;
	}
}

void postaviProjekciju()
{
	// Biranje matrice PROJEKCIJE kao aktivne matrice za buducu manipulaciju
	glMatrixMode(GL_PROJECTION);

	// Postavljanje na jedinicnu matricu
	glLoadIdentity();

	switch(ORTOGRAFSKA)
	{
	case ORTOGRAFSKA:
		// ORTOGRAFSKA projekcija, gde je vidljiva zapremina kocka duzine stranice 10
		glOrtho(-15, 15, -15, 15, 1, 30);
		break;

	case SA_PERSPEKTIVOM:
		glFrustum(-1, 1, -1, 1, 1, 30);
		break;
	}

	glMatrixMode(GL_MODELVIEW);
}