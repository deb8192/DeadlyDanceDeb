#ifndef Zona_HPP
#define Zona_HPP
#include <iostream>
#include <cstring>
#include "../Motores/MotorGrafico.hpp"
#include "Sala.hpp"

using namespace std;

class Zona
{

    public:
        // Estructura con el alias "Posiciones"
        using PosicionesZonas = struct {
            float x = 0.0f;
            float y = 0.0f;
            float z = 0.0f;
        };
        //Constructor y destructor
        Zona(int anc, int lar, int alt, const char* tip);
        ~Zona();

        //set atributos
        void setPosiciones(float newx,float newy,float newz);
        void setProposito(bool p);

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
        short getTipo();
        void Render();
        Sala* GetSala();
        void SetSala(Sala* sala);


        enum tiposZona 
        {  
            Z_CHEST = 0,
            Z_DARK,
            Z_HIDE,
            Z_RESPAWN
        };

    private:
        Sala* _estoy;
        MotorGrafico* _motor;

        short tipo;       //Indica el tipo de zona que es para contabilizar cofres, murcielagos o lo que fuera necesario
        PosicionesZonas posicionActual;        //Strunct que contiene la posicion de la zona
        float ancho, largo, alto;   //Dimensione de las zonaa
        int id;                     //ID de la zona
        bool proposito = false; //Esto se pone true si la zona ha cumplido su proposito (como zona de cofres con un cofre)
};

#endif
