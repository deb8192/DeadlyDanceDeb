#include "GestorInterfaces.hpp"

//para clases singleton deben tener un indicador de que se ha creado el unico objeto
GestorInterfaces * GestorInterfaces::_unica_instancia = 0;
//fin indicador singleton

GestorInterfaces::GestorInterfaces()
{
        _menu = new menu;
        _hud = new hud;
        _carga = new carga;
        _config = new config;
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


        //menu principal
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

        //configuracion

        _config->xTituloM = Width*(_config->xTitulo);
        _config->yTituloM = Height*(_config->yTitulo);

        //iniciar partida

        //continuar partida

        //creditos

        //hud
        _hud->xVidaM = Width*(_hud->xVida);
        _hud->yVidaM = Height*(_hud->yVida);

        _hud->xEnergiaM = Width*(_hud->xEnergia);
        _hud->yEnergiaM = Height*(_hud->yEnergia);

        _hud->xObjetoM = Width*(_hud->xObjeto);
        _hud->yObjetoM = Height*(_hud->yObjeto);

        _hud->xDineroM = Width*(_hud->xDinero);
        _hud->yDineroM = Height*(_hud->yDinero);

        _hud->xBarraVidaM = _hud->xVidaM+40;
        _hud->yBarraVidaM = _hud->yVidaM+8;

        _hud->xBarraEnergiaM = _hud->xEnergiaM+40;
        _hud->yBarraEnergiaM = _hud->yEnergiaM+8;

        _hud->xMarcaDineroM = _hud->xDineroM+26;
        _hud->yMarcaDineroM = _hud->yDineroM+14;

        _hud->xTipoObjetoM = _hud->xObjetoM+10;
        _hud->yTipoObjetoM = _hud->yObjetoM+8;

        _hud->xContadorLlavesM = _hud->xDineroM+100;
        _hud->yContadorLlavesM = _hud->yDineroM+100;

        _hud->xLlaveBossM = _hud->xEnergiaM-20;
        _hud->yLlaveBossM = _hud->yEnergiaM;

        //puzzles

        //carga

        _carga->xCargaM = Width*(_carga->xCarga);
        _carga->yCargaM = Height*(_carga->yCarga);


}

GestorInterfaces::menu * GestorInterfaces::GetMenu()
{
        return _menu;
}

GestorInterfaces::hud * GestorInterfaces::GetHud()
{
        return _hud;
}

float GestorInterfaces::GetEscaladoX()
{
        return escaladoWidth;
}

float GestorInterfaces::GetEscaladoY()
{
        return escaladoHeight;
}

GestorInterfaces::carga * GestorInterfaces::GetCarga()
{
        return _carga;
}

GestorInterfaces::config * GestorInterfaces::GetConfig()
{
        return _config;
}