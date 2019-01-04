#ifndef Enemigo_HPP
#define Enemigo_HPP
#include "INnpc.hpp"
#include "INdrawable.hpp"
#include "INsentidos.hpp"
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
        void generarSonido(int intensidad, double duracion);

        void queEscuchas();//recupera la informacion de los sonidos que escucha

        void queVes();//recupera informacion de los objetos,enemigos,jugador que ve.
        //drawables metodos
        void setPosiciones(int nx,int ny,int nz);
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

        void setVida(int vid);
        void setTipo(int tip);
        void setBarraAtEs(int bar);
        void setAtaque(int ataq);
        void setSuerte(int suer);
        void setDanyoCritico(int danyoC);
        void setProAtaCritico(int probabilidad);
        void setAtackTime(float t);
        void setRotation(float rot);

        int getVida();
        int getTipo();
        int getBarraAtEs();
        int getAtaque();
        int getSuerte();
        int getDanyoCritico();
        int getProAtaCritico();
        int* getBuffos();
        float getAtackTime();
        //propios
        Sala* getSala();

        float getX();
        float getY();
        float getZ();
        float getRX();
        float getRY();
        float getRZ();

        //comportamientos bases
            bool ver();
            bool oir();
            bool buscar();//por defecto devuelve true
            bool perseguir();//por defecto devuelve true
            bool Acciones(int);
        //fin comportamientos bases
        
        //activar ia
        void setArbol(Arbol2 *);//asigna un arbol de ia al enemigo
        Arbol2 * getArbol();//devuelve el puntero al arbol de ia que tiene, CUIDADO si no tiene arbol devuelve nullptr
        void runIA();//corre la ia del enemigo
        //fin ia
        
    protected:
        Sala * estoy;//sala en la que esta el enemigo
        float atx, aty, atz, atgx, atgy, atgz;
        float atacktime = 0.0f;
        Arbol2 * arbol;//este arbol es la ia para hacerlo funcionar debes llamar a runIA() desde nivel, cuidado porque si es nullptr puede dar errores.
};

#endif
