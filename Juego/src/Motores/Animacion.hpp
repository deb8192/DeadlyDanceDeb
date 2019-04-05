//contiene la logica de un unico estado de una animaciona
// Contiene todos las animaciones (Animacion), de una entidad, se identifica por un id para actualizarlo en el motor
#ifndef ANIMACION
#define ANIMACION 

#include <iostream>

class Animacion
{
    public:
        Animacion();//constructor vacio
        Animacion(unsigned int, unsigned int);//se le pasa fInicial y fFinal 
        ~Animacion();//destruye este estado
        void SetInicio(unsigned int);//define el frame inicial donde empieza
        void SetFinal(unsigned int);//define el frame final donde termina
        void SetRepite(bool);//define si se repite o no
        void SetSalta(bool);//define si salta cuando termina o se queda en el ultimo frame
        void SetTermina(bool);//define si debe terminar antes de saltar a otro estado o animacion
        void SetVelocidad(unsigned int);//define la velocidad con la que va la animacion
        void AsignarSiguiente(Animacion *);//asigna el siguiente estado, que se debe ejecutar cuando termine el estado
        bool GetTermina();//devuelve si hay que esperar a que termine
        bool GetRepite();//devuelve si se ejecuta en bucle 
        bool GetSalta();//devuelve si tiene siguiente animacion a la que saltar cuando termina
        unsigned int GetInicio();//devuelve el frame inicial
        unsigned int GetFinal();//devuelve el frame final
        unsigned int GetVelocidad();//devuelve la velocidad de la animacion
        Animacion * GetSiguiente();//devuelve la siguiente animacion en ejecucion

    private:
        unsigned int fInicio;//frame incial, donde empieza la animacion
        unsigned int fFinal;//frame final, donde termina la animacion
        bool seRepite;//se indica si la animacion se repite al terminar
        bool salto;//si al terminar salta a otra animacion se pone a cual animacion salta 
        bool debeTerminar;//por defecto es FALSE, pero si es true hasta que no termina no se puede cambiar de estado
        unsigned int velocidad;//por defecto es 1, es la velocidad con la cual se cambia de frame
        Animacion * _salta;//animacion a la que salta cuando termina
};

#endif