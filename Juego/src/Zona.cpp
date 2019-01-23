#include "Zona.hpp"

//Constructor
Zona::Zona(int anc, int lar, int alt, const char *tip)
{
  std::string name_tipo(tip);
  char * cadena_tipo = new char[sizeof(name_tipo)];
  strcpy(cadena_tipo, name_tipo.c_str());

  tipo = cadena_tipo;
  ancho = anc;
  largo = lar;
  alto = alt;
}

//Destructor
Zona::~Zona()
{

}

void Zona::setPosiciones(float newx,float newy,float newz)
{
    x = newx;
    y = newy;
    z = newz;
}

void Zona::setID(int newid)
{
  id = newid;
}

int Zona::getID()
{
 return id;
}

float Zona::getX()
{
  return x;
}

float Zona::getY()
{
  return y;
}

float Zona::getZ()
{
  return z;
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

const char* Zona::getTipo()
{
    return tipo;
}
