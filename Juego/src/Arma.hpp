#ifndef Arma_HPP
#define Arma_HPP
#include <iostream>
#include "INobjetos.hpp"
#include "INdrawable.hpp"
//#include "MotorGrafico.hpp"

using namespace std;

//aqui definimos la clase del jugador con herencia de la interfaz INnpc
class Arma : public INobjetos , public INdrawable //multiple herencia a esto se le llama derivacion multiple
{
    public:
        Arma();         //esto le deja a la entidad el constructor por defecto
        Arma(int ataque, const char *nombre, int anc, int lar, int alt, const char *objeto, const char *textura);
        ~Arma();
        
        //drawable metodos
        void setPosiciones(float nx,float ny,float nz);
        void setPosicionesArmaEsp(float nx,float ny,float nz, float ry);

        //setters
        void setNombre(const char*);
        void setAtaque(int);
        //void getPosiciones();

        //getters
        const char* getNombre();
        int getAtaque();
        void setID(int);
        int getID();

        float getX();
        float getY();
        float getZ();
        float getRX();
        float getRY();
        float getRZ();
        const char* getObjeto();
        const char* getTextura();
        float getAncho();
        float getLargo();
        float getAlto();

    private:
        int potenciaAtaque;
        const char* nombreArma;  
        //MotorGrafico * motor;
      //  core::vector3df dir; 
};

#endif /* Arma_HPP */