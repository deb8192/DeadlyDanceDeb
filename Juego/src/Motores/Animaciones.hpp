// Contiene todos las animaciones (Animacion), de una entidad, se identifica por un id para actualizarlo en el motor
#ifndef ANIMACIONES
#define ANIMACIONES 

#include "Animacion.hpp"
#include "../pugixml.hpp"
#include <iostream>
#include <fstream> 

class Animaciones
{
    public:
        Animaciones();//constructor vacio
        Animaciones(const char *);//constructor se le pasa la ruta del archivo o binario
        ~Animaciones();//destruye sus estados y asi misma
        void GuardarAnimacionesBin();//guarda las animaciones que hay actualmente en binario, para una carga mas rapida.
        void ProcesarAnimacion(unsigned int frame_actual);//procesa la animacion, si tiene que saltar a otra, si tiene que cambiar de estado, etc..
        bool CambiarDeEstado(unsigned int);//cambia al estado que se le pase siempre que exista y no este la opcion de debeTerminar en ejecucion
        void AsignarID(unsigned int);//se le asigna el id del objeto que se cambia
        unsigned int GetID();//devuelve el id asignado
        bool ExisteEstado(unsigned int);//si el estado es posible se devuelve true si no false
        void CambiarEstado(unsigned int e, unsigned int start, unsigned int actual);//cambia el estado de la animacion
        bool SePuedeCambiarEstado(unsigned int frame_actual);//comprueba si es posible cambiar el estado
        bool GetEstaEnBucle();//devuelve si debe estar en bucle la animacion
        unsigned int * Update();//se devuelve un array de tres valores (0 inicial, 1 final, 2 velocidad), si no se devuelve es que esta en el estado
        bool SeCambiaEstado();//devuelve true si se debe actualizar el estado en el motor, si no se debe actualizar devuelve false
        
    private:
        Animacion * _ejecucion;//cuando se llame a procesarAnimacion se llamara a la animacion que haya en _ejecucion
        Animacion ** _animaciones;//contiene todos los estados de la entidad (moverse, coger objetos...)
        unsigned int id;//id al que pertenece en el motor 
        unsigned int numEstados;//numero de estados totales
        bool cambio;//sirve para saber si se ha cambiado el estado
        int buscarNumeroEstado(Animacion * e);//devuelve el numero al que pertenece ese estado


};

#endif