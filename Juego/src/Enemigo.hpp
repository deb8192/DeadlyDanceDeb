#ifndef Enemigo_HPP
#define Enemigo_HPP

#include "INnpc.hpp"
#include "INdrawable.hpp"
#include "INsentidos.hpp"
#include "Sala.hpp"
#include <vector>

class Enemigo : public INnpc , public INdrawable, public INsentidos //multiple herencia a esto se le llama derivacion multiple
{

    public:
        Enemigo();

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

        int getVida();
        int getTipo();
        int getBarraAtEs();
        int getAtaque();
        int getSuerte();
        int getDanyoCritico();
        int getProAtaCritico();
        int* getBuffos();
        //propios
        Sala* getSala();

    protected:
        Sala * estoy;//sala en la que esta el enemigo
};

#endif
