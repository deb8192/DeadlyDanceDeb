#ifndef Jugador_HPP
#define Jugador_HPP
#include <iostream>
#include <math.h>
#include <algorithm>
#include "INnpc.hpp"
#include "INdrawable.hpp"
#include "Arma.hpp"
#include "MotorFisicas.hpp"
#include "MotorGrafico.hpp"
#include <ctime>

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
        int Atacar();//efectua un ataque normal, llama al motor para ejecutar la animacion.
        //void AtacarEspecial();//efectua el ataque especial segun el tipo, esto llama a motor grafico para realizar la animacion, cuando se termina se pone a cero la barra
        int AtacarEspecial();//efectua el ataque especial segun el tipo, esto llama a motor grafico para realizar la animacion, cuando se termina se pone a cero la barra
        void AtacarUpdate();
        void AtacarEspecialUpdate(int *danyo);
        void QuitarVida(int);//quita vida a la entidad
        void RecuperarVida(int);//le suma vida a la entidad
        void AumentarBarraAtEs(int);//aumenta el valor de la barra de ataque critico
        void Interactuar(int, int);//llama a la mecanica de interactuar

        void setVida(int vid);
        void setTipo(int tip);
        void setBarraAtEs(int bar);
        void setAtaque(int ataq);
        void setArma(Arma *arma);
        void setArmaEspecial(int ataque);
        void setSuerte(int suer);
        void setDanyoCritico(int danyoC);
        void setProAtaCritico(int probabilidad);
        void setTimeAtEsp(float time);

        int getVida();
        int getTipo();
        int getBarraAtEs();
        int getAtaque();
        Arma* getArma();
        Arma* getArmaEspecial();
        int getSuerte();
        int getDanyoCritico();
        int getProAtaCritico();
        int* getBuffos();
        float getTimeAtEsp();
        const char *getRutaArmaEsp();

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
        //PRUEBAS ATAQUE ESPECIAL
        float timeAtEsp = 0.0;
        Arma *armaEquipada;
        Arma *armaEspecial;
        const char * rutaArmaEspecial = "assets/models/Arma.obj";
        const char * nombreJugador = "Heavy";
        //!PRUEBAS ATAQUE ESPECIAL
       //  core::vector3df dir;
        float danyo_arma = 10.0f;
        float atx, atespx, aty, atespy, atz, atespz, atgx, atgy, atgz;
        float atposX, atespposX, atposY, atespposY, atposZ, atespposZ;
        int tipo_arma = 2;
};

#endif /* Jugador_HPP */
