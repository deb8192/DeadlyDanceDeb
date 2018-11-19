#include "pugixml.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>

#ifndef CargadorNiveles_HPP
#define CargadorNiveles_HPP

class CargadorNiveles
{
    public:
        CargadorNiveles();
        void CargarNivelXml(int); //esta funcion carga el nivel desde xml
        void GuardarNivelXml(int); //esta funcion guarda el nivel en xml
        void GuardarNivelBin(int); //esta funcion guarda el nivel en formato bin con el numero que le pases
        void CargarNivelBin(int); //esta funcion carga el nivel desde un archivo binario  

    private:
        
        int * lista;
};

#endif