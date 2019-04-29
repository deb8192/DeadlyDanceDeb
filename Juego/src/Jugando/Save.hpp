#ifndef Save_HPP
#define Save_HPP

#include <ctime> //libreria para obtener el tiempo actual para el guardado
#include <iostream>
#include <fstream>
#include <cstring>

class Save
{
    public:
        Save();//crea la instancia para la partida de guardado //pone la partida por defecto (vacia)
        bool RecuperarPartida(const char *);//recupera la partida,si existe el archivo
        void GuardarPartida(const char *);//guarda la partida en la ruta que le indiques
        unsigned int GetTipo(); //obtiene el tipo si es rockero (0) o bailadora (1)
        void SetTipo(unsigned int); //cambia el tipo de personaje
        unsigned int GetDinero();//devuelve el dinero que tiene la partida
        void SetDinero(unsigned int);//cambia el dinero que tiene la partida
        unsigned int GetNivel();//obtiene el nivel por el que debe empezar la partida
        void SetNivel(unsigned int);//cambia el nivel por el que debe empezar la partida (normalmente GetNivel+1)
        const char * GetNombre();//obtiene el nombre por el que se inicio la partida
        void SetNombre(const char *);//cambia el nombre por el que se inicio la partida
        const char * GetFecha();//obtiene la fecha de guardado

    private:

        struct Partida
        {
            unsigned int tipo;//si es un rockero o una bailadora
            unsigned int dinero;//dinero que tiene 
            unsigned int nivel;//nivel por el que empieza el jugador
            char nombre[30];//nombre que le ha dado el jugador
            char fechaActual[10];//fecha del guardado
        };

    Partida save;

};

#endif