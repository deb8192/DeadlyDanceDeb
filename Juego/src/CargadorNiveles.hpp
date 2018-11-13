#include "pugixml.hpp"
#include <stdio.h>

#ifndef CargadorNiveles_HPP
#define CargadorNiveles_HPP

class CargadorNiveles
{
    public:
        CargadorNiveles();
        void CargarNivel(int); //esta funcion carga el nivel desde xml
        void GuardarNivelBin(int); //esta funcion guarda el nivel en formato bin con el nombre que le pases
        void CargarNivelBin(int); //esta funcion carga el nivel desde un archivo binario  

    private:
        
        int * lista;
};

#endif