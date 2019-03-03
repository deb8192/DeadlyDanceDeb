#include "../ConstantesComunes.hpp"
#include "Zona.hpp"

//Constructor
Zona::Zona(int anc, int lar, int alt, const char *tip)
{
  Constantes constantes;
  ancho = anc;
  largo = lar;
  alt = alt;
  std::string name_tipo(tip);
  char* cadena_tipo = new char[sizeof(name_tipo)];
  strcpy(cadena_tipo, name_tipo.c_str());

  //Si es una zona de cofres el tamanyo de esta estara predefinida
  if(strcmp(cadena_tipo, constantes.ZCHEST) == 0)
  {
    tipo = Z_CHEST;
  }
  else if(strcmp(cadena_tipo, constantes.ZDARK) == 0)
  {
    tipo = Z_DARK;
  }

  tip = nullptr;

  posicionActual.x = 0.0f;
  posicionActual.y = 0.0f;
  posicionActual.z = 0.0f;
  totalElementos = 0;
  elementosActuales = 0;
  id = -1;

}

//Destructor
Zona::~Zona()
{
    posicionActual.x = 0.0f;
    posicionActual.y = 0.0f;
    posicionActual.z = 0.0f;
    id = 0;
    tipo = 0;
    ancho = 0.0f;
    largo = 0.0f;
    alto = 0.0f;
    id = 0.0f;
    proposito = false;
}

void Zona::annadirElemento()
{
  elementosActuales++;
}

void Zona::setPosiciones(float newx,float newy,float newz)
{
    posicionActual.x = newx;
    posicionActual.y = newy;
    posicionActual.z = newz;
}

void Zona::setID(int newid)
{
  id = newid;
}

void Zona::setProposito(bool p)
{
  proposito = p;
}


void Zona::setTotalElementos(unsigned short elementos)
{
  totalElementos = elementos;
}

int Zona::getID()
{
 return id;
}

float Zona::getX()
{
  return posicionActual.x;
}

float Zona::getY()
{
  return posicionActual.y;
}

float Zona::getZ()
{
  return posicionActual.z;
}

float Zona::getAncho()
{
  return ancho;
}

float Zona::getAlto()
{
  return alto;
}

float Zona::getLargo()
{
  return largo;
}

//Si la zona ha alcanzado su proposito actualmente
bool Zona::getProposito()
{
  return proposito;
}

unsigned short Zona::getTotalElementos()
{
  return totalElementos;
}

unsigned short Zona::getElementosActuales()
{
  return elementosActuales;
}

short Zona::getTipo()
{
    return tipo;
}
