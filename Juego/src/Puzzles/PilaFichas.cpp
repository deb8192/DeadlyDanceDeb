#include "PilaFichas.hpp"

PilaFichas::PilaFichas()
{
	tamanyo = 0;
	posY = 0;
}

PilaFichas::PilaFichas(short tam, short y)
{
	tamanyo = tam;
	posY = y;
}

PilaFichas::~PilaFichas()
{
	tamanyo = 0;
	posY = 0;
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