#include "Nivel.hpp"

//para clases singleton deben tener un indicador de que se ha creado el unico objeto
Nivel* Nivel::unica_instancia = 0;
//fin indicador singleton


Nivel::Nivel()
{
    
}

bool Nivel::CargarNivel(int level)
{
    cargador.CargarNivelXml(level);
    return false;
}

