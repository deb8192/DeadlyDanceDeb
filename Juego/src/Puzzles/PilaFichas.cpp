#include "PilaFichas.hpp"

PilaFichas::PilaFichas()
{
	tamanyo = 0;
	posX = 0;
	posY = 0;
	imagenFicha = 0;
	incremento = 0;
}

PilaFichas::PilaFichas(short tam, short x, short y)
{
	tamanyo = tam;
	posY = y;
	imagenFicha = 0;

	switch (tamanyo)
	{
		case 1:
			incremento = 75;
		break;
		case 2:
			incremento = 50;
		break;
		case 3:
			incremento = 25;
		break;
		default:
			incremento = 0;
		break;
	}
	posX = x+incremento;
}

PilaFichas::~PilaFichas()
{
	tamanyo = 0;
	posX = 0;
	posY = 0;
	imagenFicha = 0;
	incremento = 0;
}

int PilaFichas::GetIMG()
{
	return imagenFicha;
}

short PilaFichas::GetTamayo()
{
	return tamanyo;
}

short PilaFichas::GetPosX()
{
	return posX;
}

short PilaFichas::GetPosY()
{
	return posY;
}

int PilaFichas::GetInc()
{
	return incremento;
}

void PilaFichas::SetPosX(short x)
{
	posX = x;
}

void PilaFichas::SetPosY(short y)
{
	posY = y;
}

void PilaFichas::SetIMG(int img)
{
	imagenFicha = img;
}