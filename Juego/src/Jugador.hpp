#ifndef Jugador_HPP
#define Jugador_HPP
#include <iostream>
#include <math.h>
#include <algorithm>
#include "INnpc.hpp"
#include "INdrawable.hpp"

using namespace std;

//aqui definimos la clase del jugador con herencia de la interfaz INnpc
class Jugador : public INnpc , public INdrawable //multiple herencia a esto se le llama derivacion multiple
{
    public:
        Jugador();//esto le deja a la entidad el constructor por defecto
        Jugador(int,int,int,int,int,int);//defines tu la informacion del jugador
        void movimiento(float dt,bool a, bool s, bool d, bool w);

        //drawable metodos
        void setPosiciones(int nx,int ny,int nz);
        void setID(int);
        int getID();
        //npc metodos
        void Atacar(int);//efectua un ataque normal, llama al motor para ejecutar la animacion.
        void AtacarEspecial();//efectua el ataque especial segun el tipo, esto llama a motor grafico para realizar la animacion, cuando se termina se pone a cero la barra
        void QuitarVida(int);//quita vida a la entidad
        void RecuperarVida(int);//le suma vida a la entidad
        void AumentarBarraAtEs(int);//aumenta el valor de la barra de ataque critico
        void Interactuar(int, int);//llama a la mecanica de interactuar

        void setVida(int vid);
        void setTipo(int tip);
        void setBarraAtEs(int bar);
        void setAtaque(int ataq);
        void setSuerte(int suer);
        void setProAtaCritico(int probabilidad);

        int getVida();
        int getTipo();
        int getBarraAtEs();
        int getAtaque();
        int getSuerte();
        int getProAtaCritico();
        int* getBuffos();

        float getX();
        float getY();
        float getZ();
        float getRX();
        float getRY();
        float getRZ();

    private:
        float ax = 1.0f,
              az = 20.0f,
              deg;
      //  core::vector3df dir;
};

#endif /* Jugador_HPP */
