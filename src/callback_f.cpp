#include "callback_f.h"

#include <windows.h>
/********/
//#include "GL/glut.h"
//#include "GL/GL.H"
/********/

#include "custom.h"
#include "geometry.h"

// funkcija koja vrsi prikaz na ekranu
void draw(void)
{
	// obrisi bafer za boje i bafer za dubine
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// postavi matricu transformacije MODELA na jedinicnu
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	postaviPosmatraca();

	//-----------------------------------------
	// Specifican kod za crtanje dolazi ovde

	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(-10, -5, -10);
	glColor3f(0, 1, 0);
	glVertex3f(10, -5, -10);
	glColor3f(0, 0, 1);
	glVertex3f(10, -5, 10);
	glColor3f(0.4, 0.4, 0.4);
	glVertex3f(-10, -5, 10);
	glEnd();

	crtajKocku(-2, 2, -4, 2);
	crtajKocku(2, -3, -8, 3);
	crtajKocku(2, 2, -3, 1);


	//-----------------------------------------

	//ispisiMeni();

	//-----------------------------------------

	// Praznjenje bafera, da bi se forsiralo crtanje svih do sada
	// prosledjenih objekata
	glFlush();
	// Zamena prednjeg i zadnjeg bafera  
	glutSwapBuffers();
}

extern int sirina_prozora, visina_prozora;

// Funkcija koja se poziva svaki put kada prozor promeni velicinu
void reshape(int width, int height)
{
	// Postavljanje viewport-a
	glViewport(0, 0, (GLint)width, (GLint)height);
	sirina_prozora = width;
	visina_prozora = height;
	postaviProjekciju();
}

// funkcija koja se poziva kada se pritisne 
void key_down(unsigned char key, int x, int y)
{
	switch(key)
	{
		// escape
	case 27:
		exit(0);
		break;

		// space
	case 32:
		break;

	case '1':
	case '2':
	case '3':
	case '4':
		//pozicija_posmatraca = key - '1';
		//glutPostRedisplay();
		break;
	}
}

// funkcija koja se poziva kada se pritisne specijalan taster na tastaturi
void special_key_down(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_UP:
		//tekuci_ugao_rotacije++;
		//glutPostRedisplay();
		break;

	case GLUT_KEY_DOWN:
		//tekuci_ugao_rotacije--;
		//glutPostRedisplay();
		break;

	case GLUT_KEY_LEFT:
	case GLUT_KEY_RIGHT:
		//tekuca_projekcija = 1 - tekuca_projekcija;
		//postaviProjekciju();
		//glutPostRedisplay();
		break;
	}
}

// funkcija koja se poziva kada se desava promena nad
// dugmicima misa
void mouse_action(int button, int state, int x, int y)
{
	switch(button)
	{
	case GLUT_LEFT_BUTTON:
		switch(state)
		{
		case GLUT_DOWN:
			break;

		case GLUT_UP:
			break;
		}
		break;

	case GLUT_RIGHT_BUTTON:
		switch(state)
		{
		case GLUT_DOWN:
			break;

		case GLUT_UP:
			break;
		}
		break;
	}
}

// funkcija koja se poziva kada se krece kurzor misa
// parametri imaju vrednost koordinata misa
void mouse_motion(int x, int y)
{
}