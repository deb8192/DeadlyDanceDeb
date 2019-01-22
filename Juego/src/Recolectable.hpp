#ifndef Recolectable_HPP
#define Recolectable_HPP
#include <iostream>
#include "INobjetos.hpp"
#include "INdrawable.hpp"
//#include "MotorGrafico.hpp"

using namespace std;

//aqui definimos la clase del jugador con herencia de la interfaz INnpc
class Recolectable : public INobjetos , public INdrawable //multiple herencia a esto se le llama derivacion multiple
{
    public:
        Recolectable();         //esto le deja a la entidad el constructor por defecto
        Recolectable(int ataque, const char *nombre, int anc, int lar, int alt, const char *objeto, const char *textura);
        //~Recolectable();
        
        //drawable metodos
        void setPosiciones(float nx,float ny,float nz);
        void setID(int);
        int getID();

        float getX();
        float getY();
        float getZ();
        float getRX();
        float getRY();
        float getRZ();

        int getAtaque();
        const char* getNombre();
        const char* getObjeto();
        const char* getTextura();
        float getAncho();
        float getLargo();
        float getAlto();


    private: 

        //creo que lo mejor esque el objeto que recojas tenga ya su valor de daño
        int potenciaAtaque;
        
};

#endif /* Recolectable_HPP */