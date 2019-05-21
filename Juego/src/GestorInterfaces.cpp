#include "GestorInterfaces.hpp"

//para clases singleton deben tener un indicador de que se ha creado el unico objeto
GestorInterfaces * GestorInterfaces::_unica_instancia = 0;
//fin indicador singleton

GestorInterfaces::GestorInterfaces()
{
        _menu = new menu;
}

void GestorInterfaces::UpdateDimensionesVentana(int * dimensiones)
{
        Width = dimensiones[0];//se actualiza ancho
        Height = dimensiones[1];//se actualiza alto
        //delete [] dimensiones;//se borra datos pasados
}

void GestorInterfaces::UpdateDimensionesVentana(unsigned int w, unsigned h)
{
        Width = w;//se actualiza ancho
        Height = h;//se actualiza alto
}

void GestorInterfaces::ActualizarParametros()
{
        
        escaladoWidth = 1.0f;
        escaladoHeight = 1.0f;
        
        //std::cout << Width << " " << Height << "\n";

        _menu->xLogoM = Width*(_menu->xLogo);
        _menu->yLogoM = Height*(_menu->yLogo); 
        
        _menu->xLogo2M = Width*(_menu->xLogo2);
        _menu->yLogo2M = Height*(_menu->yLogo2);

        _menu->xLogo3M = Width*(_menu->xLogo3);
        _menu->yLogo3M = Height*(_menu->yLogo3); 

        _menu->xEmpezarM = Width*(_menu->xEmpezar);
        _menu->yEmpezarM = Height*(_menu->yEmpezar);

        _menu->xContinuarM = Width*(_menu->xContinuar);
        _menu->yContinuarM = Height*(_menu->yContinuar);

        _menu->xConfiM = Width*(_menu->xConfi);
        _menu->yConfiM = Height*(_menu->yConfi);

        _menu->xCreM = Width*(_menu->xCre);
        _menu->yCreM = Height*(_menu->yCre);

        _menu->xSalirM = Width*(_menu->xSalir);
        _menu->ySalirM = Height*(_menu->ySalir);
}

GestorInterfaces::menu * GestorInterfaces::GetMenu()
{
        return _menu;
}

float GestorInterfaces::GetEscaladoX()
{
        return escaladoWidth;
}

float GestorInterfaces::GetEscaladoY()
{
        return escaladoHeight;
}
