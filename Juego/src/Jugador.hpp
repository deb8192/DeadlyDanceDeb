#ifndef Jugador_HPP
#define Jugador_HPP
#include <iostream>
#include <math.h>
#include "INnpc.hpp"
#include "INdrawable.hpp"
#include "Arma.hpp"

using namespace std;

//aqui definimos la clase del jugador con herencia de la interfaz INnpc
class Jugador : public INnpc , public INdrawable //multiple herencia a esto se le llama derivacion multiple
{
    public:
        Jugador();//esto le deja a la entidad el constructor por defecto
        Jugador(int,int,int,int,int,int);//defines tu la informacion del jugador
        void AtacarEspecial(int, int);//define el ataque especial para el jugador
        float mcd(float ax, float az);
        void movimiento(float dt,bool a, bool s, bool d, bool w);
        float getX();
        float getY();
        float getZ();
        float getRX();
        float getRY();
        float getRZ(); 

    private:
        float ax, az,deg;   
        //Arma armaEquipada;       
      //  core::vector3df dir; 
};

#endif /* Jugador_HPP */