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
        Arma(int ataque);
        ~Arma();
        
        //drawable metodos
        void setPosiciones(int nx,int ny,int nz);
        void setID(int);
        int getID();
        //Arma(int ataque);//defines tu la informacion del jugador
        /*float getX();
        float getY();
        float getZ();
        float getRX();
        float getRY();
        float getRZ(); */

    private:
        //float ax, az,deg;    
        int potenciaAtaque;      
        //MotorGrafico * motor;
      //  core::vector3df dir; 
};

#endif /* Arma_HPP */