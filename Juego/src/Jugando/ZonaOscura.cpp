#include "ZonaOscura.hpp"

ZonaOscura::ZonaOscura(int anc, int lar, int alt, const char *tip)
    :Zona(anc, lar, alt, tip)
{
    hayMurcielagos = false;
    totalElementos = 0;
    elementosActuales = 0;
}
ZonaOscura::~ZonaOscura()
{
    hayMurcielagos = false;
    totalElementos = 0;
    elementosActuales = 0;
}

void ZonaOscura::annadirElemento()
{
    elementosActuales++;
    if(elementosActuales == totalElementos)
    {
        this->setProposito(true);
    }
}

void ZonaOscura::quitarElemento()
{
    if(elementosActuales == totalElementos)
    {
        this->setProposito(false);
    }
    elementosActuales--;
}

void ZonaOscura::SetHayMurcielagos(bool hayMurcielago)
{
    hayMurcielagos = hayMurcielago;
}

void ZonaOscura::SetTotalElementos(unsigned short elementos)
{
  totalElementos = elementos;
}

bool ZonaOscura::GetHayMurcielagos()
{
    return hayMurcielagos;
}

unsigned short ZonaOscura::GetTotalElementos()
{
  return totalElementos;
}

unsigned short ZonaOscura::GetElementosActuales()
{
  return elementosActuales;
}
