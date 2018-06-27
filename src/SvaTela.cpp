#include "SvaTela.h"
#include "Kocka.h"
#include "Kvadar.h"
#include "Valjak.h"
#include "Lopta.h"
#include "Kupa.h"
#include "Piramida.h"

int SvaTela::curFreeIndex = 2;

int SvaTela::precision;
int SvaTela::v_precision;

SvaTela::SvaTela(int prec, int vertical_prec)
{
	//curFreeIndex = 1;

	precision = prec;
	if(precision <= 3) precision = 3;
	v_precision = vertical_prec;
	if(v_precision < 2) v_precision = 2;

	trenutnoTelo = NULL;
	zapamcenaTela = 0;
	promene = true;
}

void SvaTela::incPrecision(int prec, int vertical_prec)
{
	precision += prec;
	if(precision <= 3) precision = 3;

	v_precision += vertical_prec;
	if(v_precision < 2) v_precision = 2;

	glutPostRedisplay();
}

int SvaTela::getPrec()
{
	return precision;
}
int SvaTela::getVerticalPrec()
{
	return v_precision;
}

void SvaTela::dozvoliPromene()
{
	promene = true;
}
void SvaTela::zabraniPromene()
{
	promene = false;
}

void SvaTela::napraviPolje(float x, float y, float z, float a)
{
	Polje *p = new Polje(x, y, z, a);
	Polja.push_back(p);
}

void SvaTela::napraviPoljeSaImenom(char c, int b, float x, float y, float z, float a)
{
	Polje *p = new Polje(x, y, z, a);
	p->setChar(c);
	p->setColor(b);
	Polja.push_back(p);
}

void SvaTela::napraviKocku(Boja b, float x, float y, float z, float a)
{
	Kocka *k = new Kocka(b, x, y, z, a);
	k->setStencilIndex(curFreeIndex);
	Tela.push_back(k);

	curFreeIndex++;
}

void SvaTela::napraviKvadar(Boja b, float x, float y, float z, float ax, float ay, float az)
{
	Kvadar *k = new Kvadar(b, x, y, z, ax, ay, az);
	k->setStencilIndex(curFreeIndex);
	Tela.push_back(k);

	curFreeIndex++;
}

void SvaTela::napraviValjak(Boja b, float x, float y, float z, float r, float h)
{
	Valjak *v = new Valjak(b, x, y, z, r, h);
	v->setStencilIndex(curFreeIndex);
	Tela.push_back(v);

	curFreeIndex++;
}

void SvaTela::napraviLoptu(Boja b, float x, float y, float z, float R)
{
	Lopta *l = new Lopta(b, x, y, z, R);
	l->setStencilIndex(curFreeIndex);
	Tela.push_back(l);

	curFreeIndex++;
}

void SvaTela::napraviKupu(Boja b, float x, float y, float z, float r, float h)
{
	Kupa *k = new Kupa(b, x, y, z, r, h);
	k->setStencilIndex(curFreeIndex);
	Tela.push_back(k);

	curFreeIndex++;
}

void SvaTela::napraviPiramidu(Boja b, float x, float y, float z, float r, float h, int sides)
{
	Piramida *p = new Piramida(b, x, y, z, r, h, sides);
	p->setStencilIndex(curFreeIndex);
	Tela.push_back(p);

	curFreeIndex++;
}

void SvaTela::rotirajTelo(float Rx, float Ry, float Rz)
{
	if(!promene) return;
	Tela.front()->setStartRotation(Rx, Ry, Rz);
}

bool SvaTela::naTelu(int x, int y, int visina_prozora)
{
	GLuint index;

	glReadPixels(x, visina_prozora - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

	for(std::list<Telo*>::iterator it = Tela.begin(); it != Tela.end(); it++)
	{
		Telo *telo = *it;

		if(telo->getStencilIndex() == index)
		{
			return true;
		}
	}
	return false;
}

bool SvaTela::naSelektovanomTelu(int x, int y, int visina_prozora)
{
	GLuint index;

	glReadPixels(x, visina_prozora - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

	if(trenutnoTelo->getStencilIndex() == index) return true;
	else return false;
}

/*bool SvaTela::selektovanoTelo()
{
	return (trenutnoTelo != NULL);
}*/

void SvaTela::selektujTelo(int x, int y, int visina_prozora)
{
	if(!promene) return;

	GLuint index;
	bool selektovano = false;

	glReadPixels(x, visina_prozora - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

	for(std::list<Telo*>::iterator it = Tela.begin(); it != Tela.end(); it++)
	{
		Telo *telo = *it;

		if(telo->getStencilIndex() == index)
		{
			telo->promeniOkvir(true);
			trenutnoTelo = telo;
			selektovano = true;
		}
		else
		{
			telo->promeniOkvir(false);
		}
	}
	if(!selektovano) trenutnoTelo = NULL;
}

void SvaTela::pomeriTrenutnoTelo(float x, float y)
{
	if(!promene) return;

	if(trenutnoTelo != NULL)
	{
		trenutnoTelo->pomeriURavni(x, y);
	}
	glutPostRedisplay();
}

void SvaTela::rotirajTrenutnoTelo(float dx, float dy, float dz)
{
	if (!promene) return;

	if (trenutnoTelo != NULL)
	{
		trenutnoTelo->rotiraj(dx, dy, dz);
	}
	glutPostRedisplay();
}

void SvaTela::zapamtiTrenutnaTela(char p)
{
	for(std::list<Polje*>::iterator it = Polja.begin(); it != Polja.end(); it++)
	{
		Polje *polje = *it;
		if(polje->gerChar() == p) polje->zapamti(zapamcenaTela, Tela.size());
	}
	zapamcenaTela = Tela.size();
}

bool SvaTela::proveriPolja()
{
	for(std::list<Polje*>::iterator it = Polja.begin(); it != Polja.end(); it++)
	{
		Polje *polje = *it;
		std::list<Telo*>::iterator it2 = Tela.begin();
		for(int i = 0; i < polje->prvoTelo(); i++)	// provera prethodnih tela
		{
			Telo *telo = *it2;
			if((polje->proveri(telo->getX(), telo->getZ()))) return false;
			it2++;
		}
		for(int i = 0; i < (polje->posledenjeTelo() - polje->prvoTelo()); i++)	// provera zapamcenih tela
		{
			Telo *telo = *it2;
			if(!(polje->proveri(telo->getX(), telo->getZ()))) return false;
			it2++;
		}
		for(; it2 != Tela.end(); it2++)	// provera sledecih tela
		{
			Telo *telo = *it2;
			if((polje->proveri(telo->getX(), telo->getZ()))) return false;
		}
	}
	return true;
}


void SvaTela::crtajSve()
{
	for(std::list<Polje*>::iterator it = Polja.begin(); it != Polja.end(); it++)
	{
		Polje *polje = *it;
		polje->ctraj();
	}

	for(std::list<Telo*>::iterator it = Tela.begin(); it != Tela.end(); it++)
	{
		Telo *telo = *it;
		glStencilFunc(GL_ALWAYS, telo->getStencilIndex(), -1);
		telo->ctraj();
		if(telo->dozvoljenOkvir())
		{
			//glStencilFunc(GL_NEVER, telo->getStencilIndex(), -1);
			telo->crtajOkvir();
		}
	}
}

void SvaTela::resetujSve()
{
	if(!promene) return;

	for(std::list<Telo*>::iterator it = Tela.begin(); it != Tela.end(); it++)
	{
		Telo *telo = *it;
		glStencilFunc(GL_ALWAYS, telo->getStencilIndex(), -1);
		telo->reset();
	}
	glutPostRedisplay();
}

void SvaTela::izbrisiSve()
{
	if(!promene) return;

	int n = Polja.size();
	for(int i = 0; i < n; i++)
	{
		Polja.pop_front();
	}

	n = Tela.size();
	for(int i = 0; i < n; i++)
	{
		Tela.pop_front();
	}
	curFreeIndex = 2;
	zapamcenaTela = 0;
	glutPostRedisplay();
}