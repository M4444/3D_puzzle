#pragma once;

/********/
#include "GL/glut.h"
#include "GL/GL.H"
/********/

#define PI  3.14159265358979323
#define DEG_TO_RAD(x) ((x) * PI / 180)
#define RAD_TO_DEG(x) ((x) * 180 / PI)

enum Boja
{
	CRVENA = 0,
	ZELENA = 1,
	PLAVA = 2,
	ZUTA = 3,
	TIRKIZNA = 4,
	PINK = 5,
	NARANDZASTA = 6,
	LJUBICASTA = 7
};

static GLfloat colors3fv[8][4][3] = {
	{	/* crvene */
		{ 1.0f, 0.0f, 0.0f },
		{ 0.9f, 0.0f, 0.0f },
		{ 0.8f, 0.0f, 0.0f },
		{ 1.0f, 0.4f, 0.4f }
	},
	{	/* zelene */
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.9f, 0.0f },
		{ 0.0f, 0.8f, 0.0f },
		{ 0.4f, 1.0f, 0.4f },
	},
	{	/* plave */
		{ 0.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 0.9f },
		{ 0.0f, 0.0f, 0.8f },
		{ 0.4f, 0.4f, 1.0f }
	},
	{	/* zute */
		{ 1.0f, 1.0f, 0.0f },
		{ 0.9f, 0.9f, 0.0f },
		{ 0.8f, 0.8f, 0.0f },
		{ 1.0f, 1.0f, 0.4f }
	},
	{	/* tirkizne */
		{ 0.0f, 1.0f, 1.0f },
		{ 0.0f, 0.9f, 0.9f },
		{ 0.0f, 0.8f, 0.8f },
		{ 0.4f, 1.0f, 1.0f }
	},
	{	/* pink */
		{ 1.0f, 0.0f, 1.0f },
		{ 0.9f, 0.0f, 0.9f },
		{ 0.8f, 0.0f, 0.8f },
		{ 1.0f, 0.4f, 1.0f }
	},
	{	/* narandzaste */
		{ 1.0f, 0.5f, 0.0f },
		{ 0.9f, 0.45f, 0.0f },
		{ 0.8f, 0.4f, 0.0f },
		{ 1.0f, 0.9f, 0.4f }
	},
	{	/* ljubicaste */
		{ 0.5f, 0.0f, 1.0f },
		{ 0.45f, 0.0f, 0.9f },
		{ 0.4f, 0.0f, 0.8f },
		{ 0.9f, 0.4f, 1.0f }
	}
};

const static GLfloat cube3fv[8][3] = {
	{ -0.5f, -0.5f, 0.5f },
	{ 0.5f, -0.5f, 0.5f },
	{ 0.5f, 0.5f, 0.5f },
	{ -0.5f, 0.5f, 0.5f },
	{ 0.5f, -0.5f, -0.5f },
	{ -0.5f, -0.5f, -0.5f },
	{ -0.5f, 0.5f, -0.5f },
	{ 0.5f, 0.5f, -0.5f }
};

class Telo
{
protected:
	Boja b;
	float x, y, z;
	float sx, sy, sz;
	float a;
	float Rx, Ry, Rz;
	float sRx, sRy, sRz;
	bool okvir;
	int stencilIndex;
public:
	Telo(Boja b, float x = 0, float y = 0, float z = 0, float a = 1)
	{
		this->b = b;
		this->x = sx = x;
		this->y = sy = y;
		this->z = sz = z;
		this->a = a;
		Rx = sRx = 0;
		Ry = sRy = 0;
		Rz = sRz = 0;
		okvir = false;

		stencilIndex = -1;
	}

	void reset()
	{
		this->x = sx;
		this->y = sy;
		this->z = sz;

		Rx = sRx;
		Ry = sRy;
		Rz = sRz;
	}

	void setStartRotation(float rx, float ry, float rz)
	{
		Rx = sRx = rx;
		Ry = sRy = ry;
		Rz = sRz = rz;
	}

	void rotiraj(float rx, float ry, float rz)
	{
		Rx += rx;
		Ry += ry;
		Rz += rz;
	}

	void pomeriURavni(float tx, float ty)
	{
		x += tx;
		z += ty;
	}

	void promeniOkvir(bool o)
	{
		okvir = o;
	}
	bool dozvoljenOkvir()
	{
		return okvir;
	}

	void setStencilIndex(int i)
	{
		stencilIndex = i;
	}
	int getStencilIndex()
	{
		return stencilIndex;
	}

	float getX()
	{
		return x;
	}
	float getY()
	{
		return y;
	}
	float getZ()
	{
		return z;
	}

	virtual float getScaleX()
	{
		return a;
	}
	virtual float getScaleY()
	{
		return a;
	}
	virtual float getScaleZ()
	{
		return a;
	}

	virtual void ctraj() = 0;
	virtual void crtajOkvir();
};