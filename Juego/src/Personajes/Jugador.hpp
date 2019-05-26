#ifndef Jugador_HPP
#define Jugador_HPP

#include <iostream>
#include <math.h>
#include <algorithm>
#include <ctime>
#include <cstring>
#include "../Enemigos/Enemigo.hpp" // Tambien incluye MotorFisicas.hpp
#include "../Motores/INnpc.hpp"
#include "../Motores/INdrawable.hpp"
#include "../Motores/INsentidos.hpp"
#include "../Armas/Arma.hpp"
#include "../Objetos/Recolectable.hpp"
#include "../Objetos/Llave.hpp"
#include "../Motores/MotorGrafico.hpp"
#include "../Motores/MotorAudio.hpp"
#include "../Jugando/InterfazJugador.hpp"
#include "../ConstantesComunes.hpp"
#include "../Jugando/Sala.hpp"

using namespace std;

//aqui definimos la clase del jugador con herencia de la interfaz INnpc
class Jugador : public INnpc , public INdrawable, public INsentidos //multiple herencia a esto se le llama derivacion multiple
{
    public:
        Jugador();//esto le deja a la entidad el constructor por defecto
        ~Jugador();
        Jugador(Sala* sala, unsigned short tipoJug,int nX,int nY,int nZ,int ancho,int largo,int alto,
            int accion, int maxVida);//defines tu la informacion del jugador

        //Metodos de desplazamiento
        void movimiento(bool noMueve,bool a, bool s, bool d, bool w);
        bool moverseAlCentroDeLaSala(VectorEspacial* target); //Funcion a la que se llama al entrar a la sala del boss para desplazar al jugador al centro de la sala
        void moverseEntidad(float);//Realiza el desplazamiento mediante la interpolacion
        void RotarEntidad(float);//Realiza la rotacion mediante la interpolacion
        void UpdateTimeMove(float time);//actualiza el tiempo del movimiento de la interpolacion
        void Alinearse(VectorEspacial *target);

        //Metodos Muere jugador
        bool EstaMuerto();  // Comprueba si vida <= 0
        bool finalAnimMuerte();
        void MuereJugador();//muere jugador (el tiempo controla los cambio de color del jugador)

        //npc metodos
        int Atacar(int);//efectua un ataque normal, llama al motor para ejecutar la animacion.
        int AtacarEspecial();//efectua el ataque especial segun el tipo, esto llama a motor grafico para realizar la animacion, cuando se termina se pone a cero la barra
        void CrearCuerpoAtaque();
        void AtacarUpdate(int danyo, vector<Enemigo*> &_getEnemigos);
        void Interactuar(int, int);//llama a la mecanica de interactuar
        int GetTipoJug();
        
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
        void setPosicionesAtaque(float nx,float ny,float nz);
        void setNewPosiciones(float nx,float ny,float nz);//modifica las posiciones finales de la interpolacion de la figura
        void setLastPosiciones(float nx,float ny,float nz);
        void setRotacion(float nrx, float nry, float nrz);
        void setNewRotacion(float nrx, float nry, float nrz);
        void setLastRotacion(float nrx, float nry, float nrz);
        void setVectorOrientacion();
        void setPosicionesFisicas(float nx,float ny,float nz);
        void initPosicionesFisicas(float nx,float ny,float nz);
        void setID(int);

        //gets de npc
        void ModificarVida(int vid);
        void setVida(int vid);
        void setTipo(int tip);
        void ModificarBarraAtEs(int bar);
        void setBarraAtEs(int bar);
        void SetInvulnerabilidad(bool invulnerable);
        void setAtaque(int ataq);
        void setArma(Recolectable* _armaRec);
        void setArmaEspecial(int ataque);
        void setSuerte(int suer);
        void setDanyoCritico(int danyoC);
        void setProAtaCritico(int probabilidad);
        void setTimeAt(float time);
        void setLastTimeAt(float time);
        void setTimeAtEsp(float time);
        void setLastTimeAtEsp(float time);
        void setTimeInvulnerable(float time);
        void setLastTimeInvulnerable(float time);

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
        INnpc::VectorEspacial GetVectorOrientacion();
        float* GetDatosAtEsp();
        int getID();

        //gets de npc
        int getVidaIni();
        int getVida();
        int getTipo();
        int getBarraAtEs();
        bool GetInvulnerabilidad();
        int getAtaque();
        Arma* getArma();
        Arma* getArmaEspecial();
        int getSuerte();
        int getDanyoCritico();
        int getProAtaCritico();
        int* getBuffos();
        float getTimeAtEsp();
        float getLastTimeAtEsp();
        float getTimeAt();
        float getLastTimeAt();
        float getTimeInvulnerable();
        float getLastTimeInvulnerable();
        const char* getRutaArmaEsp();
        const char* getRutaTexturaArmaEsp();
        void girarCamara();
        int getDinero();
        void ModificarDinero(int monedas);
        void setDinero(int monedas);

        //Jugador
        int getAnimacion();
        vector <Llave*> GetLlaves();

        const char* GetModelo();
        const char* GetAnimacion();
        const char* GetTextura();
        unsigned int GetFps();
        float GetEscalado();
        
        int GetAncho();
        int GetLargo();
        int GetAlto();
        Sala* GetSala();
        void SetSala(Sala* sala);
        bool ColisionEntornoEne();

        virtual void AtacarEspecialUpdate(int* danyo, vector<Enemigo*> &_getEnemigos) = 0;
        virtual void RenderAtaqueEsp(float updateTime, float drawTime) = 0;
        virtual void resetContador() = 0;

        void Render(float updTime, float drawTime);

        //para las animaciones de las armas
        const char * GetModeloArma(unsigned int);//lee el numero de arma que le pases siempre que exista
        const char * GetAnimacionArma(unsigned int);//lee el archivo de animacion del arma siempre que exista
        const char * GetTexturaArma(unsigned int);//devuelve la ruta de la textura perteneciente al id que se le pasa
        unsigned int GetFpsArma(unsigned int);//te devuelve el numero de fps que tiene el arma
        float GetEscaladoArma(unsigned int);

    protected:
        void atacarEspUpdComun(int* danyo, std::vector<Enemigo*> &_getEnemigos);
        virtual void armaAtacarEspecialUpd() = 0;

        //estas variables son para el movimiento, giro de personaje y giro de la camara
        float ax = 1.0f,
              az = 20.0f,
              deg;
        int gcam = 0;
        float newy = 0;
        float newz = 0;

        Arma* _armaEquipada;
        Arma* _armaEspecial;
        vector <Llave*> llaves;
        
        //PRUEBAS ATAQUE ESPECIAL
        const char* _rutaArmaEspecial;
        const char* _rutaTexturaArmaEspecial;
        unsigned short tipoJug; // Se asigna antes de cargar el nivel
        //!PRUEBAS ATAQUE ESPECIAL

       //  core::vector3df dir;
        float danyo_arma = 10.0f;
        float atx, atespx, aty, atespy, atz, atespz, atgx, atgy, atgz, incrAtDisCirc;
        float atposX, atespposX, atposY, atespposY, atposZ, atespposZ;
        float tamanyoflecha = 1.0f;
        int tipo_arma = 2;
        vector <unsigned int> atacados_normal;
        int dinero;
        Sala* salaActual;

        int ancho; int largo; int alto;

        MotorGrafico* _motor;
        MotorAudioSystem* _motora;
        InterfazJugador* _interfaz;
        MotorFisicas* _fisicas;
        Constantes constantes;

        float escalado;//indica si se debe escalar la malla cuando se crea por defecto es 1.0f
        const char * _animacion;
        const char * _textura;
        unsigned int fps;

        //para las armas

        const char * modelosArmas[14];
        const char * animacionesArmas[14];
        const char * texturasArmas[14];
        unsigned int fpsArmas[14];
};

#endif /* Jugador_HPP */
