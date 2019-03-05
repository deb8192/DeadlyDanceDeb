#ifndef Jugador_HPP
#define Jugador_HPP

#include <iostream>
#include <math.h>
#include <algorithm>
#include <ctime>
#include <cstring>
#include "../Enemigos/Enemigo.hpp"
#include "../Motores/INnpc.hpp"
#include "../Motores/INdrawable.hpp"
#include "../Motores/INsentidos.hpp"
#include "../Armas/Arma.hpp"
#include "../Objetos/Llave.hpp"
#include "../Motores/MotorGrafico.hpp"
#include "../Motores/MotorAudio.hpp"
#include "../Jugando/InterfazJugador.hpp"

using namespace std;

//aqui definimos la clase del jugador con herencia de la interfaz INnpc
class Jugador : public INnpc , public INdrawable, public INsentidos //multiple herencia a esto se le llama derivacion multiple
{
    public:
        Jugador();//esto le deja a la entidad el constructor por defecto
        ~Jugador();
        Jugador(int nX,int nY,int nZ,int ancho,int largo,int alto,int accion, int maxVida);//defines tu la informacion del jugador

        //Metodos de desplazamiento
        void movimiento(bool noMueve,bool a, bool s, bool d, bool w);
        void moverseEntidad(float);//Realiza el desplazamiento mediante la interpolacion
        void RotarEntidad(float);//Realiza la rotacion mediante la interpolacion
        void UpdateTimeMove(float time);//actualiza el tiempo del movimiento de la interpolacion

        //Metodos Muere jugador
        bool EstaMuerto();  // Comprueba si vida <= 0
        bool finalAnimMuerte();
        void MuereJugador();//muere jugador (el tiempo controla los cambio de color del jugador)

        //npc metodos
        int Atacar(int);//efectua un ataque normal, llama al motor para ejecutar la animacion.
        int AtacarEspecial();//efectua el ataque especial segun el tipo, esto llama a motor grafico para realizar la animacion, cuando se termina se pone a cero la barra
        void AtacarUpdate(int danyo, vector<Enemigo*> &_getEnemigos);
        void AtacarEspecialUpdate(int* danyo, vector<Enemigo*> &_getEnemigos);
        void Interactuar(int, int);//llama a la mecanica de interactuar

        //Metodos de INsentidos
        void generarSonido(int intensidad, double duracion, int tipo);
        void queEscuchas();
        void queVes();

        //Metodos jugador
        void AnnadirLlave(Llave* llave);
        void EliminarLlave(Llave* llave);

        //Animacion
        bool terminaAnimacion();

        //SETTERS & GETTERS
        //drawable metodos
        void setPosiciones(float nx,float ny,float nz);
        void setNewPosiciones(float nx,float ny,float nz);//modifica las posiciones finales de la interpolacion de la figura
        void setLastPosiciones(float nx,float ny,float nz);
        void setRotacion(float nrx, float nry, float nrz);
        void setNewRotacion(float nrx, float nry, float nrz);
        void setLastRotacion(float nrx, float nry, float nrz);
        void setPosicionesFisicas(float nx,float ny,float nz);
        void initPosicionesFisicas(float nx,float ny,float nz);
        void setID(int);

        //gets de npc
        void ModificarVida(int vid);
        void setVida(int vid);
        void setTipo(int tip);
        void ModificarBarraAtEs(int bar);
        void setBarraAtEs(int bar);
        void setAtaque(int ataq);
        void setArma(Arma* arma);
        void setArmaEspecial(int ataque);
        void setNombre(const char* nombre);
        void setSuerte(int suer);
        void setDanyoCritico(int danyoC);
        void setProAtaCritico(int probabilidad);
        void setTimeAt(float time);
        void setLastTimeAt(float time);
        void setTimeAtEsp(float time);
        void setLastTimeAtEsp(float time);

        //Animacion
        void setAnimacion(int);

        //gets de drawable
        float getX();
        float getY();
        float getZ();
        float getNewX();
        float getNewY();
        float getNewZ();
        float getLastX();
        float getLastY();
        float getLastZ();
        float getIniX();
        float getIniY();
        float getIniZ();
        float getFisX();
        float getFisY();
        float getFisZ();
        float getRX();
        float getRY();
        float getRZ();
        float* GetDatosAtEsp();
        int getID();

        //gets de npc
        int getVidaIni();
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
        float getTimeAt();
        float getLastTimeAt();
        const char* getRutaArmaEsp();

        int getDinero();
        void ModificarDinero(int monedas);
        void setDinero(int monedas);

        //Jugador
        int getAnimacion();
        vector <Llave*> GetLlaves();

        const char* GetTextura();
        const char* GetModelo();
        int GetAncho();
        int GetLargo();
        int GetAlto();

        virtual void RenderAtaqueEsp(float updateTime, float drawTime) = 0;

    protected:
        float ax = 1.0f,
              az = 20.0f,
              deg;
        Arma* _armaEquipada;
        Arma* _armaEspecial;
        vector <Llave*> llaves;
        //PRUEBAS ATAQUE ESPECIAL
        const char* _rutaArmaEspecial = "assets/models/Arma.obj";
        const char* _nombreJugador = "Heavy";
        //!PRUEBAS ATAQUE ESPECIAL
       //  core::vector3df dir;
        float danyo_arma = 10.0f;
        float atx, atespx, aty, atespy, atz, atespz, atgx, atgy, atgz, incrAtDisCirc;
        float atposX, atespposX, atposY, atespposY, atposZ, atespposZ;
        int tipo_arma = 2;
        vector <unsigned int> atacados_normal;
        int dinero = 0;

        const char* playerTextura;
        const char* playerModelo;
        int ancho; int largo; int alto;

        MotorGrafico* _motor;
        MotorAudioSystem* _motora;
        InterfazJugador* _interfaz;
};

#endif /* Jugador_HPP */