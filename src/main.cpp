#include <windows.h>

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "SvaTela.h"

//using namespace std;

/********/
#include "GL/glut.h"
#include "GL/GL.H"
/********/

#include <time.h>	// time()
#include <stdlib.h>	// srand()

#define     ORTOGRAFSKA       0
#define     SA_PERSPEKTIVOM   1

//const double PI = 3.141592653589793;
//#define PI  3.14159265358979323

//#define DEG_TO_RAD(x) ((x) * PI / 180)
//#define RAD_TO_DEG(x) ((x) * 180 / PI)

//#include "callback_f.h"

int sirina_prozora = 0, visina_prozora = 0;

//int precision = 40;		// 36
//int v_precision = 50;	// 4
int ugao_rotacije = 45, uhvaceni_ugao_rotacije; 
int ugao_uzvisenosti = 45, uhvaceni_ugao_uzvisenosti;
int mis_x = -1, mis_y = -1;
int mis_pom_x, mis_pom_y;
bool mis_kamera = false;
bool mis_pomeranje = false;

bool odabir = true;
bool igra_u_toku = false;
bool obavljen_zadatak = false;
int faza = 0;
int vreme = 0;

int trenutni_objekat = -1;
int br_ispisa_menija = 0;

bool dozvoliOkvir[10] = { false };

SvaTela svaTela = SvaTela(40, 50);

// funkcija koja inicijalizuje stanje OpenGL-a
void init_all(void)
{
	// pozadinska boja se postavlja na crnu
	glClearColor(0.8, 0.8, 0.8, 0.0);
	// koristi se model nijansiranog sencenja
	glShadeModel(GL_SMOOTH);

	// poligoni se crtaju popunjeno bilo da se posmatraju s lica ili s nalicja
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// ukljucuje se rezim provere dubine pre crtanja
	glEnable(GL_DEPTH_TEST);
	// osposobljavanje stensil operacija
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	srand(time(NULL));
}

void glutTimer(int value)
{
	if(value != 0)
	{
		vreme--;
		if(vreme <= 0)
		{
			igra_u_toku = false;
			svaTela.zabraniPromene();
			obavljen_zadatak = svaTela.proveriPolja();
		}
		glutPostRedisplay();
		glutTimerFunc(1000, glutTimer, igra_u_toku);
	}
	//glutTimerFunc(1000, glutTimer, igra_u_toku);
}

/***************************************************************************************************************************/
void pisiTekst(const char *tekst, float x, float y, void *glut_bitmap_font = GLUT_BITMAP_HELVETICA_12)
{
	glRasterPos2f(x, y);
	while(*tekst)
		glutBitmapCharacter(glut_bitmap_font, *tekst++);
}

void ispisiMeni()
{
	char tekst[1024];
	int hight = 1;

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();


	glColor3f(0, 0, 0);
	glTranslated(-1, -1, 0);
	glScaled(2.0 / sirina_prozora, 2.0 / visina_prozora, 1);

	switch(faza)
	{
		case 0:
			sprintf_s(tekst, "3D SLAGALICA");
			pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
			sprintf_s(tekst, "Odaberite igru:");
			pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
			sprintf_s(tekst, "a. grupisanje tela prema boji, velicini ili obliku");
			pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
			sprintf_s(tekst, "b. sastavljanje sto vise kule slaganjem tela odredjene grupe");
			pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
			sprintf_s(tekst, "c. postavljanje zadatog tela u odnosu na neko drugo telo");
			pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
			sprintf_s(tekst, "d. redjanje tela u policu sa pregradcima na cijim ledjima su slike tela");
			pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
		break;
		case 1:
			sprintf_s(tekst, "IGRA GRUPISANJA TELA");
			pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
			sprintf_s(tekst, "Postavite odgovarajuca tela na oznaceno polje:");
			pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
			sprintf_s(tekst, "- plava tela");
			pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
			sprintf_s(tekst, "- zute lopte");
			pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
			sprintf_s(tekst, "- crvene male kvadre");
			pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
			if(igra_u_toku)
			{
				sprintf_s(tekst, "Po zavrsetku pritisnite 'G'");
				pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
				sprintf_s(tekst, "Preostalo vreme: %d sec", vreme);
				pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
			}
			else
			{
				if(obavljen_zadatak)
				{
					sprintf_s(tekst, "Zadatak je uradjen.");
					hight++;
					pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
					sprintf_s(tekst, "Nazad ('N')");
					pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
				}
				else
				{
					sprintf_s(tekst, "Zadatak nije uradjen.");
					hight++;
					pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
					sprintf_s(tekst, "Pokusati ponovo? Da('D') Ne('N')");
					pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
				}
			}
		break;
		case 3:
			sprintf_s(tekst, "IGRA POSTAVLJANJA TELA");
			pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
			sprintf_s(tekst, "Postavite veliku crvenu piramidu desno i iznad male zute kupe:");
			pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
			sprintf_s(tekst, "- crvena: ispred levo");
			pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
			sprintf_s(tekst, "- zuta: ispred desno");
			pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
			sprintf_s(tekst, "- plava: iznad desno");
			pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
			sprintf_s(tekst, "- ljubicasta: iznad levo");
			pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
			if (igra_u_toku)
			{
				sprintf_s(tekst, "Po zavrsetku pritisnite 'G'");
				pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
				sprintf_s(tekst, "Preostalo vreme: %d sec", vreme);
				pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
			}
			else
			{
				if (obavljen_zadatak)
				{
					sprintf_s(tekst, "Zadatak je uradjen.");
					hight++;
					pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
					sprintf_s(tekst, "Nazad ('N')");
					pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
				}
				else
				{
					sprintf_s(tekst, "Zadatak nije uradjen.");
					hight++;
					pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
					sprintf_s(tekst, "Pokusati ponovo? Da('D') Ne('N')");
					pisiTekst(tekst, 10, visina_prozora - 20 * hight++);
				}
			}
		break;
	}

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void postaviPosmatraca()
{
	glTranslatef(0, 0, -10);
	glRotatef(ugao_uzvisenosti, 1, 0, 0);
	glRotatef(ugao_rotacije, 0, 1, 0);
	/*switch(0)
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
	}*/
}

void postaviProjekciju()
{
	double ratio = sirina_prozora / visina_prozora;
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

void F0()
{
	svaTela.napraviKocku(CRVENA, 5, 0, -5, 2);
	svaTela.napraviKocku(ZELENA, 2, 0, 2, 2);
	svaTela.rotirajTelo(0, 90, 0);
	svaTela.napraviKocku(PLAVA, -2, 0, -2, 2);
	svaTela.rotirajTelo(0, -180, 0);
	svaTela.napraviLoptu(ZUTA, 0, 0, 0, 2);
	svaTela.napraviValjak(TIRKIZNA, 2, 0, -2, 1, 2);
	svaTela.napraviKupu(PINK, -2, 0, 2, 1, 2);
	svaTela.napraviKvadar(NARANDZASTA, 5, 0, 0, 2, 2, 6);
	svaTela.napraviKvadar(LJUBICASTA, 0, 0, -5, 6, 2, 2);
	svaTela.rotirajTelo(0, 180, 0);
	svaTela.napraviPiramidu(CRVENA, 2, 2, 2);
	svaTela.napraviPiramidu(NARANDZASTA, -2, 2, -2);
}

void F1S0()
{
	svaTela.napraviPolje(6, 0, -6, 7);
	svaTela.napraviKocku(PLAVA, 0, -0.5, 0, 1);
	svaTela.napraviKupu(PLAVA, 0, 0, 5, 1, 2);
	svaTela.napraviValjak(PLAVA, 6, -0.5, 0, 0.5, 1);
	svaTela.napraviKvadar(PLAVA, -5, -0.25, 5, 1, 1.5, 1);
	svaTela.napraviLoptu(ZUTA, -2, 0, -2, 2);
	svaTela.napraviLoptu(ZUTA, 7, -0.5, 7, 1);
	svaTela.napraviKvadar(CRVENA, -3, -0.25, -7, 1, 1.5, 1);
	svaTela.napraviKvadar(CRVENA, -2, -0.5, 3, 1.5, 1, 1);
	svaTela.zapamtiTrenutnaTela();
	svaTela.napraviKocku(CRVENA, 6, 0, 4, 2);
	svaTela.napraviPiramidu(LJUBICASTA, -5, -0.5, -3, 0.5, 1);

}

void F3S0()
{
	svaTela.napraviPoljeSaImenom('1', 1, 6, 0, -6, 7);
	svaTela.napraviPoljeSaImenom('9', 4, -6, 0, 6, 7);
	svaTela.napraviPoljeSaImenom('7', 2, -6, 0, -6, 7);
	svaTela.napraviPoljeSaImenom('3', 3, 6, 0, 6, 7);
	svaTela.napraviPiramidu(CRVENA, 2, 0, 2);
	svaTela.zapamtiTrenutnaTela('9');
	svaTela.napraviKupu(ZUTA, 0, -0.5, 0, 0.5, 1);

}

// funkcija koja vrsi prikaz na ekranu
void draw(void)
{
	glClearStencil(0);
	// obrisi bafer za boje i bafer za dubine
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// postavi matricu transformacije MODELA na jedinicnu
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	postaviPosmatraca();

	//-----------------------------------------
	// Specifican kod za crtanje dolazi ovde
	int curSt = 1;
	//crtajPodlogu(10, -3);
	glStencilFunc(GL_ALWAYS, curSt++, -1);
	glBegin(GL_QUADS);
	{
		glColor3f(0, 0.6, 0);
		glVertex3f(-10, -1.15, -10);
		glColor3f(0, 0.8, 0);
		glVertex3f(10, -1.15, -10);
		glColor3f(0, 0.8, 0);
		glVertex3f(10, -1.15, 10);
		glColor3f(0, 0.6, 0);
		glVertex3f(-10, -1.15, 10);
	}glEnd();

	svaTela.crtajSve();
	/*curSt++;
	curSt++;
	curSt++;
	curSt++;
	curSt++;
	curSt++;*/

	//-----------------------------------------

	ispisiMeni();
	
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
	int w = height * 1;           // w is width adjusted for aspect ratio
	int left = (width - w) / 2;
	glViewport(left, 0, (GLint)w, (GLint)height);
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

	case 'r':
		svaTela.resetujSve();
		break;

	case '8':
		svaTela.incPrecision(0, 1);
		break;
	case '2':
		svaTela.incPrecision(0, -1);
		break;
	case '0':
		//pozicija_posmatraca = key - '1';
		//glutPostRedisplay();
		break;
	case '+':
		svaTela.incPrecision(1, 0);
		break;
	case '-':
		svaTela.incPrecision(-1, 0);
		break;
	case '7':
		if (!odabir) svaTela.rotirajTrenutnoTelo(3, 0, 0);
		break;
	case '9':
		if (!odabir) svaTela.rotirajTrenutnoTelo(-3, 0, 0);
		break;
	case '4':
		if (!odabir) svaTela.rotirajTrenutnoTelo(0, 3, 0);
		break;
	case '6':
		if (!odabir) svaTela.rotirajTrenutnoTelo(0, -3, 0);
		break;
	case '1':
		if (!odabir) svaTela.rotirajTrenutnoTelo(0, 0, 3);
		break;
	case '3':
		if (!odabir) svaTela.rotirajTrenutnoTelo(0, 0, -3);
		break;
	case 'w':
		if(!odabir) if(!mis_pomeranje) svaTela.pomeriTrenutnoTelo(0, 1);
		break;
	case 's':
		if(!odabir) if(!mis_pomeranje) svaTela.pomeriTrenutnoTelo(0, -1);
		break;
	case 'a':
		if(odabir)
		{
			faza = 1;
			odabir = false;
			igra_u_toku = true;
			vreme = 30;
			glutTimerFunc(1000, glutTimer, igra_u_toku);
			svaTela.izbrisiSve();
			F1S0();
		}
		else if(!mis_pomeranje) svaTela.pomeriTrenutnoTelo(1, 0);
		break;
	case 'c':
		if (odabir)
		{
			faza = 3;
			odabir = false;
			igra_u_toku = true;
			vreme = 30;
			ugao_rotacije = 180;
			glutTimerFunc(1000, glutTimer, igra_u_toku);
			svaTela.izbrisiSve();
			F3S0();
		}
		break;
	case 'd':
		if(!igra_u_toku && faza != 0)
		{
			igra_u_toku = true;
			svaTela.dozvoliPromene();
			svaTela.resetujSve();
			vreme = 30;
			glutTimerFunc(1000, glutTimer, igra_u_toku);
		}
		else if(!odabir) if(!mis_pomeranje) svaTela.pomeriTrenutnoTelo(-1, 0);
		break;
	case 'g':
		if(igra_u_toku)
		{
			igra_u_toku = false;
			svaTela.zabraniPromene();
			obavljen_zadatak = svaTela.proveriPolja();
			glutPostRedisplay();
		}
		break;
	case 'n':
		if(!igra_u_toku && faza != 0)
		{
			faza = 0;
			odabir = true;
			svaTela.dozvoliPromene();
			svaTela.izbrisiSve();
			F0();
		}
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
		ugao_uzvisenosti++;
		glutPostRedisplay();
		break;

	case GLUT_KEY_DOWN:
		//tekuci_ugao_rotacije--;
		ugao_uzvisenosti--;
		glutPostRedisplay();
		break;

	case GLUT_KEY_LEFT:
		ugao_rotacije++;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		ugao_rotacije--;
		//tekuca_projekcija = 1 - tekuca_projekcija;
		//postaviProjekciju();
		glutPostRedisplay();
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
			if(!mis_kamera)
			{
				mis_x = x;
				mis_y = y;
				//dozvoliOkvirSelektovanom();
				svaTela.selektujTelo(x, y, visina_prozora);
				glutPostRedisplay();
			}
			if(svaTela.naTelu(x, y, visina_prozora))
			{
				mis_pomeranje = true;
				mis_pom_x = x;
				mis_pom_y = y;
				glutSetCursor(GLUT_CURSOR_INFO);
			}
			break;

		case GLUT_UP:
			mis_pomeranje = false;
			glutSetCursor(GLUT_CURSOR_INHERIT);
			//mis_pomeranje_pravog = false;
			/*if(!mis_kamera)
			{
				mis_x = x;
				mis_y = y;
				dozvoliOkvirSelektovanom();
				svaTela.selektujTelo(x, y, visina_prozora);
				glutPostRedisplay();
			}*/
			break;
		}
		break;

	case GLUT_RIGHT_BUTTON:
		switch(state)
		{
		case GLUT_DOWN:
			//mis_kamera = !mis_kamera;
			if(!mis_pomeranje)
			{
				int a = 9;
				mis_kamera = true;
				mis_x = x;
				mis_y = y;
				uhvaceni_ugao_rotacije = ugao_rotacije;
				uhvaceni_ugao_uzvisenosti = ugao_uzvisenosti;
			}
			break;

		case GLUT_UP:
			mis_kamera = false;
			break;
		}
		break;

	case GLUT_MIDDLE_BUTTON:
		if(!mis_kamera && !mis_pomeranje)
		{
			mis_kamera = false;
			ugao_rotacije = 45;
			ugao_uzvisenosti = 45;
			glutPostRedisplay();
		}
		break;
	}
}

// funkcija koja se poziva kada se krece kurzor misa
// parametri imaju vrednost koordinata misa
void mouse_motion(int x, int y)
{
	if(mis_kamera)
	{
		ugao_rotacije = uhvaceni_ugao_rotacije - (mis_x - x)/2;
		ugao_uzvisenosti = uhvaceni_ugao_uzvisenosti - (mis_y - y) / 2;
		glutPostRedisplay();
	}
	if(mis_pomeranje)
	{
		//if(!svaTela.naSelektovanomTelu(x, y, visina_prozora))
		//{
		//	dozvoliOkvirSelektovanom();
		//	svaTela.selektujTelo(x, y, visina_prozora);
		//}
		//mis_pomeranje_pravog = true;
		
		float xp = (mis_pom_x - x) / 30.0;
		float yp = (mis_pom_y - y) / 30.0;
		float f = (ugao_uzvisenosti == 0) ? 0 : 1 / sin(DEG_TO_RAD(ugao_uzvisenosti));
		//if(ugao_uzvisenosti == 0) f = 0;
		//else f = 1 / sin(DEG_TO_RAD(ugao_uzvisenosti));
		svaTela.pomeriTrenutnoTelo(-cos(DEG_TO_RAD(ugao_rotacije))*xp + sin(DEG_TO_RAD(ugao_rotacije))*f*yp,
									-sin(DEG_TO_RAD(ugao_rotacije))*xp - cos(DEG_TO_RAD(ugao_rotacije))*f*yp);
	}
	mis_pom_x = x;
	mis_pom_y = y;
	//mis_x = x;
	//mis_y = y;
	//glutPostRedisplay();
}
/***************************************************************************************************************************/

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(900, 900);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(argv[0]);

	init_all();
	F0();

	// postavljanje "callback" funkcija
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key_down);
	glutSpecialFunc(special_key_down);
	glutMouseFunc(mouse_action);
	glutMotionFunc(mouse_motion);
	glutPassiveMotionFunc(mouse_motion);

	// postavljanje izgleda kurzora misa
	glutSetCursor(GLUT_CURSOR_INHERIT);
	// postavljanje prozora preko celog ekrana
	//glutFullScreen();
	//glutTimerFunc(1000, glutTimer, igra_u_toku);

	glutMainLoop();

	return 0;
}

