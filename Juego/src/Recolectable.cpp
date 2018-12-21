#include "Recolectable.hpp"


Recolectable::Recolectable()
{

}
Recolectable::Recolectable(int ataque, const char *nombre, int anc, int lar, int alt, const char *objeto, const char *textura)
{
    cout << "creando recolectable" << endl;
    
    potenciaAtaque = ataque;
    nombreObjeto = "nombre";
    ancho = anc;
    largo = lar;
    alto = alt;
    ruta_objeto = objeto; // deberia recoger *objeto pero se corrompe en la segunda iteracion del bucle
    ruta_textura = "textura";
}
void Recolectable::setPosiciones(int nx,int ny,int nz)
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