#pragma once;

class Polje
{
protected:
	float x, y, z;
	float a;
	float Rx, Ry, Rz;
	int zb, ze;
	char p;
	int boja;
public:
	Polje(float x = 0, float y = 0, float z = 0, float a = 1)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->a = a;
		Rx = 0;
		Ry = 0;
		Rz = 0;
		zb = 0;
		ze = 0;
		p = '\0';
		boja = 0;
	}

	void setChar(char c)
	{
		p = c;
	}
	char gerChar()
	{
		return p;
	}

	void setStartRotation(float rx, float ry, float rz)
	{
		Rx = rx;
		Ry = ry;
		Rz = rz;
	}

	void setColor(int b)
	{
		boja = b;
	}

	void zapamti(int a, int b)
	{
		zb = a;
		ze = b;
	}

	int prvoTelo()
	{
		return zb;
	}
	int posledenjeTelo()
	{
		return ze;
	}

	bool proveri(float x, float z);

	void ctraj();
};