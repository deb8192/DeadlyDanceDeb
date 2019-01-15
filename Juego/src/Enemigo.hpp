#ifndef Enemigo_HPP
#define Enemigo_HPP
#include "INnpc.hpp"
#include "INdrawable.hpp"
#include "INsentidos.hpp"
#include "Arma.hpp"
#include "Sala.hpp"
#include <vector>
#include "Arbol2.hpp"

class Enemigo : public INnpc , public INdrawable, public INsentidos //multiple herencia a esto se le llama derivacion multiple
{

    public:
        Enemigo();
        ~Enemigo();

        void definirSala(Sala * sala);

        //sentidos metodos
        void generarSonido(int intensidad,double duracion,int tipo);//la intensidad es el alcance y la duracion es cuanto dura el sonido, el tipo 1 son sonidos del jugador, 2 es pedir ayuda de los enemigos

        void queEscuchas();//recupera la informacion de los sonidos que escucha

        void queVes();//recupera informacion de los objetos,enemigos,jugador que ve.
        //drawables metodos

        //npc metodos
        int Atacar();//efectua un ataque normal, llama al motor para ejecutar la animacion.
        //void AtacarEspecial();//efectua el ataque especial segun el tipo, esto llama a motor grafico para realizar la animacion, cuando se termina se pone a cero la barra
        int AtacarEspecial();//efectua el ataque especial segun el tipo, esto llama a motor grafico para realizar la animacion, cuando se termina se pone a cero la barra
        void QuitarVida(int);//quita vida a la entidad
        bool estasMuerto();//llama desde Nivel
        bool finalAnimMuerte();// si la animacion de muerte acaba, entonces en nivel lo mataremos del todo
        void MuereEnemigo(int enemi);//Animacion de muertes
        void RecuperarVida(int);//le suma vida a la entidad
        void AumentarBarraAtEs(int);//aumenta el valor de la barra de ataque critico
        void Interactuar(int, int);//llama a la mecanica de interactuar
        void moverseEscenario(float, float);//Realiza el desplazamiento mediante la interpolacion
        void UpdateTimeMove(float time);//actualiza el tiempo del movimiento de la interpolacion

        //getters y setters

        void setID(int);
        void setPosiciones(float nx,float ny,float nz);
        void setNewPosiciones(float nx,float ny,float nz);
        void setLastPosiciones(float nx,float ny,float nz);
        void setPosicionesFisicas(float nx,float ny,float nz);
        void initPosicionesFisicas(float nx,float ny,float nz);
        void setVida(int vid);
        void setTipo(int tip);
        void setBarraAtEs(int bar);
        void setAtaque(int ataq);
        void setArmaEspecial(int ataque);
        void setSuerte(int suer);
        void setDanyoCritico(int danyoC);
        void setProAtaCritico(int probabilidad);
        void setSala(Sala* sala);
        void setAtackTime(float t);
        void setTimeAtEsp(float time);
        void setLastTimeAtEsp(float time);
        void setRotation(float rot);
        void setPosAtaques(int p);

        int getID();
        int getVida();
        int getTipo();
        int getBarraAtEs();
        int getAtaque();
        int getPosAtaques();
        int getSuerte();
        int getDanyoCritico();
        int getProAtaCritico();
        int* getBuffos();
        Sala* getSala();
        float getAtackTime();
        float getTimeAtEsp();
        float getLastTimeAtEsp();
        float getX();
        float getY();
        float getZ();
        float getNewX();
        float getNewY();
        float getNewZ();
        float getLastX();
        float getLastY();
        float getLastZ();
        float getFisX();
        float getFisY();
        float getFisZ();
        float getRX();
        float getRY();
        float getRZ();

        //comportamientos bases
            bool ver(int tipo);//1 si ve al jugador
            bool oir(int tipo);//1 si se oye jugador, 2 si se oye enemigo(pedir ayuda)
            bool buscar();//por defecto devuelve true
            bool perseguir();//por defecto devuelve true
            bool Acciones(int);//esto es para recorrer el arbol
            bool pedirAyuda();//pide ayuda
            bool ContestarAyuda();//esto es de prueba no hace dayo tampoco
            bool Merodear(int tipo);//para dar vueltas por una zona, segun el enemigo tendra diferentes merodeos
        //fin comportamientos bases

        //activar ia
        void setArbol(Arbol2 *);//asigna un arbol de ia al enemigo
        Arbol2 * getArbol();//devuelve el puntero al arbol de ia que tiene, CUIDADO si no tiene arbol devuelve nullptr
        void runIA();//corre la ia del enemigo
        //fin ia

    protected:
        Sala * estoy;//sala en la que esta el enemigo
        float atx, atespx, aty, atespy, atz, atespz, atgx, atgy, atgz, incrAtDisCirc, atespposX, atespposY, atespposZ;
        float atacktime = 0.0f, moveTime = 0.0f;
        Arma *armaEspecial;
        const char * rutaArmaEspecial = "assets/models/objeto.obj";
        Arbol2 * arbol;//este arbol es la ia para hacerlo funcionar debes llamar a runIA() desde nivel, cuidado porque si es nullptr puede dar errores.
        int pos_ataques; //para controlar el array de ataques en colisiones
};

#endif
