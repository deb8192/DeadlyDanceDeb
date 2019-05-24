#include "PilaFichas.hpp"

PilaFichas::PilaFichas()
{
	tamanyo = 0;
	posY = 0;
	imagenFicha = 0;
}

PilaFichas::PilaFichas(short tam, short y)
{
	tamanyo = tam;
	posY = y;
	imagenFicha = 0;
}

PilaFichas::~PilaFichas()
{
	tamanyo = 0;
	posY = 0;
	imagenFicha = 0;
}

int PilaFichas::GetIMG()
{
	return imagenFicha;
}

short PilaFichas::GetTamayo()
{
	return tamanyo;
}

short PilaFichas::GetPosY()
{
	return posY;
}

void PilaFichas::SetPosY(short y)
{
	posY = y;
}

void PilaFichas::SetIMG(int img)
{
	imagenFicha = img;
}