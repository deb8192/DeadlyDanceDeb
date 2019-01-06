#ifndef Enemigo_HPP
#define Enemigo_HPP

#include "INnpc.hpp"
#include "INdrawable.hpp"
#include "INsentidos.hpp"
#include "Arma.hpp"
#include "Sala.hpp"
#include <vector>

class Enemigo : public INnpc , public INdrawable, public INsentidos //multiple herencia a esto se le llama derivacion multiple
{

    public:
        Enemigo();
        ~Enemigo();

        void definirSala(Sala * sala);

        //sentidos metodos
        void generarSonido(int intensidad, double duracion);

        void queEscuchas();//recupera la informacion de los sonidos que escucha

        void queVes();//recupera informacion de los objetos,enemigos,jugador que ve.
        //drawables metodos
        void setPosiciones(float nx,float ny,float nz);
        void setID(int);
        int getID();
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

        //getters y setters
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
        int getVida();
        int getTipo();
        int getBarraAtEs();
        int getAtaque();
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
        float getRX();
        float getRY();
        float getRZ();

    protected:
        Sala * estoy;//sala en la que esta el enemigo
        float atx, atespx, aty, atespy, atz, atespz, atgx, atgy, atgz, incrAtDisCirc, atespposX, atespposY, atespposZ;
        float atacktime = 0.0f;
        Arma *armaEspecial;
        const char * rutaArmaEspecial = "assets/models/objeto.obj";
};

#endif
