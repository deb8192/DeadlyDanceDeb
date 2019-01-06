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
        void setPosiciones(float nx,float ny,float nz);
        void setID(int);
        int getID();
        //Metodos Muere jugador y enemigo
        bool estasMuerto();
        void MuereJugador(float tiempo);//muere jugador (el tiempo controla los cambio de color del jugador)
        //npc metodos
        int Atacar();//efectua un ataque normal, llama al motor para ejecutar la animacion.
        //void AtacarEspecial();//efectua el ataque especial segun el tipo, esto llama a motor grafico para realizar la animacion, cuando se termina se pone a cero la barra
        int AtacarEspecial();//efectua el ataque especial segun el tipo, esto llama a motor grafico para realizar la animacion, cuando se termina se pone a cero la barra
        void AtacarUpdate(int danyo);
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
        void setNombre(const char * nombre);
        void setSuerte(int suer);
        void setDanyoCritico(int danyoC);
        void setProAtaCritico(int probabilidad);
        void setTimeAtEsp(float time);
        void setLastTimeAtEsp(float time);

        int getVida();
        int getTipo();
        int getBarraAtEs();
        int getAtaque();
        Arma* getArma();
        Arma* getArmaEspecial();
        const char* getNombre();
        int getSuerte();
        int getDanyoCritico();
        int getProAtaCritico();
        int* getBuffos();
        float getTimeAtEsp();
        float getLastTimeAtEsp();
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
        //Variables para el metodo morir
        float acumMuJug = 0; //variable para el tiempo de muerte del jugador
        bool pulsadoMuerte = false;
        bool pulsadoMuerteEnemigos=false;
        float acumMuEne = 0;
        //PRUEBAS ATAQUE ESPECIAL
        Arma *armaEquipada;
        Arma *armaEspecial;
        const char * rutaArmaEspecial = "assets/models/Arma.obj";
        const char * nombreJugador = "Heavy";
        //!PRUEBAS ATAQUE ESPECIAL
       //  core::vector3df dir;
        float danyo_arma = 10.0f;
        float atx, atespx, aty, atespy, atz, atespz, atgx, atgy, atgz, incrAtDisCirc;
        float atposX, atespposX, atposY, atespposY, atposZ, atespposZ;
        int tipo_arma = 2;
        vector <unsigned int> atacados_normal;
};

#endif /* Jugador_HPP */
