#include "Zona.hpp"

//Constructor
Zona::Zona(int anc, int lar, int alt, const char *tip)
{
  std::string name_tipo(tip);
  char * cadena_tipo = new char[sizeof(name_tipo)];
  strcpy(cadena_tipo, name_tipo.c_str());

  tipo = cadena_tipo;

  //Si es una zona de cofres el tamanyo de esta estara predefinida
  if(strcmp(cadena_tipo,"zChest") == 0){
    ancho = 4.0;
    largo = 4.0;
    alto = 4.0;
  }else{
    ancho = anc;
    largo = lar;
    alto = alt;
  }

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

void Zona::setProposito(bool p)
{
  proposito = p;
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

//Si la zona ha alcanzado su proposito actualmente
bool Zona::getProposito()
{
  return proposito;
}

const char* Zona::getTipo()
{
    return tipo;
}
