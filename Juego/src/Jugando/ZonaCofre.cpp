#include "ZonaCofre.hpp"

ZonaCofre::ZonaCofre(int anc, int lar, int alt, const char *tip)
    :Zona(anc, lar, alt, tip)
{
    cofreAranna = false;
    totalElementos = 0;
    elementosActuales = 0;
}
ZonaCofre::~ZonaCofre()
{
    cofreAranna = false;
    totalElementos = 0;
    elementosActuales = 0;
}

void ZonaCofre::annadirElemento()
{
    elementosActuales++;
    if(elementosActuales == totalElementos)
    {
        this->setProposito(true);
    }
}

void ZonaCofre::quitarElemento()
{
    if(elementosActuales == totalElementos)
    {
        this->setProposito(false);
    }
    elementosActuales--;
}

void ZonaCofre::SetCofreAranna(bool esAranna)
{
    cofreAranna = esAranna;
}

void ZonaCofre::SetTotalElementos(unsigned short elementos)
{
  totalElementos = elementos;
}

bool ZonaCofre::GetCofreAranna()
{
    return cofreAranna;
}

unsigned short ZonaCofre::GetTotalElementos()
{
  return totalElementos;
}

unsigned short ZonaCofre::GetElementosActuales()
{
  return elementosActuales;
}
