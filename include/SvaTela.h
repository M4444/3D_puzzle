#pragma once
#include <list>
#include "Telo.h"
#include "Polje.h"

//using namespace std;
//class Telo;

class SvaTela
{
public:
	static int curFreeIndex;

	static int precision;
	static int v_precision;

	std::list<Polje*> Polja;

	std::list<Telo *> Tela;
	Telo* trenutnoTelo;

	int zapamcenaTela;
	bool promene;
public:
	SvaTela(int prec, int vertical_prec);

	void incPrecision(int prec, int vertical_prec);

	static int getPrec();
	static int getVerticalPrec();

	void dozvoliPromene();
	void zabraniPromene();

	void napraviPolje(float x = 0, float y = 0, float z = 0, float a = 1);
	void napraviPoljeSaImenom(char c, int b, float x = 0, float y = 0, float z = 0, float a = 1);

	void napraviKocku(Boja b, float x = 0, float y = 0, float z = 0, float a = 1);
	void napraviKvadar(Boja b, float x = 0, float y = 0, float z = 0, float ax = 1, float ay = 1, float az = 1);
	void napraviValjak(Boja b, float x = 0, float y = 0, float z = 0, float r = 1, float h = 1);
	void napraviLoptu(Boja b, float x = 0, float y = 0, float z = 0, float R = 1);
	void napraviKupu(Boja b, float x = 0, float y = 0, float z = 0, float r = 1, float h = 1);
	void napraviPiramidu(Boja b, float x = 0, float y = 0, float z = 0, float r = 1, float h = 2, int sides = 4);

	void rotirajTelo(float Rx, float Ry, float Rz);

	bool naTelu(int x, int y, int visina_prozora);
	bool naSelektovanomTelu(int x, int y, int visina_prozora);
	//bool selektovanoTelo();
	void selektujTelo(int x, int y, int visina_prozora);
	void pomeriTrenutnoTelo(float x, float y);
	void rotirajTrenutnoTelo(float dx, float dy, float dz);

	void zapamtiTrenutnaTela(char p = '\0');
	bool proveriPolja();

	void crtajSve();
	void resetujSve();
	void izbrisiSve();
};