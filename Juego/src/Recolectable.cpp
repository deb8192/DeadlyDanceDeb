#include "Recolectable.hpp"


Recolectable::Recolectable()
{

}

Recolectable::~Recolectable()
{

}

Recolectable::Recolectable(int ataque, const char *nombre, int anc, int lar, int alt, const char *objeto, const char *textura)
{
    std::string name_objeto(objeto);
    cadena_objeto = new char[sizeof(name_objeto)];
    strcpy(cadena_objeto, name_objeto.c_str());
     
    std::string name_textura(textura);
    cadena_textura = new char[sizeof(name_textura)];
    strcpy(cadena_textura, name_textura.c_str());

    std::string name_nombre(nombre);
    cadena_nombre = new char[sizeof(name_nombre)];
    strcpy(cadena_nombre, name_nombre.c_str());

    potenciaAtaque = ataque;
    nombreObjeto = cadena_nombre;
    ancho = anc;
    largo = lar;
    alto = alt;
    ruta_objeto = cadena_objeto; // deberia recoger *objeto pero se corrompe en la segunda iteracion del bucle
    ruta_textura = cadena_textura;
}
void Recolectable::setPosiciones(float nx,float ny,float nz)
{
    x = nx;
    y = ny;
    z = nz;
}
int Recolectable::getAtaque()
{
    return potenciaAtaque;
}

const char* Recolectable::getNombre()
{
    return nombreObjeto;
}

const char* Recolectable::getObjeto()
{
    return ruta_objeto;
}

float Recolectable::getX()
{
    return x;
}
float Recolectable::getY()
{
    return y;
}
float Recolectable::getZ()
{
    return z;
}
float Recolectable::getRX()
{
    return rx;
}
float Recolectable::getRY()
{
    return ry;
}
float Recolectable::getRZ()
{
    return rz;
}
void Recolectable::setID(int nid)
{
    id = nid;
}

int Recolectable::getID()
{
    return id;
}


const char* Recolectable::getTextura()
{
    return ruta_textura;
}
float Recolectable::getAncho()
{
    return ancho;
}
float Recolectable::getLargo()
{
    return largo;
}
float Recolectable::getAlto()
{
    return alto;
}
