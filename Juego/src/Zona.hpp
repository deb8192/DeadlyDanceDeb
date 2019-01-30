#ifndef Zona_HPP
#define Zona_HPP
#include <iostream>
#include <cstring>
#include "INdrawable.hpp"

using namespace std;

class Zona
{

    public:
        //Constructor y destructor
        Zona(int anc, int lar, int alt, const char *tip);
        ~Zona();

        //set atributos
        void setPosiciones(float newx,float newy,float newz);

        //ID de la zona
        void setID(int newid);
        int getID();

        //get de atributos
        float getX();
        float getY();
        float getZ();
        float getAncho();
        float getAlto();
        float getLargo();
        bool  getProposito();
        const char* getTipo();

    private:
        const char *tipo;
        float ancho, largo, alto;
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
        int id = -1;
        bool proposito = false; //Esto se pone true si la zona ha cumplido su proposito (como zona de cofres con un cofre)
};

#endif
