#ifndef Jugador_HPP
#define Jugador_HPP
#include <iostream>
#include "INnpc.hpp"
#include "INdrawable.hpp"

using namespace std;

//aqui definimos la clase del jugador con herencia de la interfaz INnpc
class Jugador : public INnpc , public INdrawable //multiple herencia a esto se le llama derivacion multiple
{
    public:
        Jugador();//esto le deja a la entidad el constructor por defecto
        Jugador(int,int,int,int,int,int,std::string malla);//defines tu la informacion del jugador
        void AtacarEspecial();//define el ataque especial para el jugador
    private:
};

#endif /* Jugador_HPP */