#include "Configuracion.hpp"
#include "../Juego.hpp"

Configuracion::Configuracion()
{
    _motor = MotorGrafico::GetInstance();
    configuracion.CargarConfiguracion("config.global");
    volAmbiente = configuracion.GetVolAmbiente();
    volEfectos = configuracion.GetVolEfectos();
    volVoces = configuracion.GetVolVoces();
    heightScreen = configuracion.GetHeight();
    widthScreen = configuracion.GetWidth();
    muteAll = configuracion.GetMuteAll();
    vsync = configuracion.GetVsync();
    suavizadoMsax1 = configuracion.GetSuavizadoMsaX1();
    resolucion[0] = 0;
}

Configuracion::~Configuracion()
{
    _motor = nullptr;
}

void Configuracion::Iniciar()
{
    //para 800 x 600 las barras son de 366 unidades
    _motor->CrearTexto("Configuracion", 340, 20, 300, 20); // Parametros: texto, x1, y1, x2, y2
    //_motor->CrearImagen("assets/images/pr2.png",150,100,10.0f);
    _motor->CrearTexto("Resolucion:", 30, 70, 100, 20); // Parametros: texto, x1, y1, x2, y2
    
    if(heightScreen == 800)
    {
        idsElementos[6] = _motor->CrearTexto("800x600 60Fps", 385, 80, 100, 20); // Parametros: texto, x1, y1, x2, y2
    }
    else if(heightScreen == 1280)
    {
        idsElementos[6] = _motor->CrearTexto("1280x720 60Fps", 385, 80, 100, 20);
    }
    else if (heightScreen == 1920) 
    {
        idsElementos[6] = _motor->CrearTexto("1920x1080 60Fps", 385, 80, 100, 20);
    }
    else
    {
        idsElementos[6] = _motor->CrearTexto("ErrorResolution", 385, 80, 100, 20);
    }
    
    _motor->CrearBoton2(348,65,2.0f,170,40,300,990,L"Slot 1",L"assets/images/camposeleccionn.png",false,"assets/images/camposeleccionp.png","assets/images/camposeleccione.png");
    _motor->CrearTexto("Sonido Ambiente:", 30, 135, 100, 20); // Parametros: texto, x1, y1, x2, y2
    _motor->CrearImagen("assets/images/barradeslizante.png",350,120,2.0f);
    idsElementos[0] = _motor->CrearBoton2(362+(((float)366/(float)100)*(float)volAmbiente),125,2.0f,170,40,300,991,L"Slot 1",L"assets/images/deslizadorn.png",false,"assets/images/deslizadorp.png","assets/images/deslizadore.png");
    _motor->CrearTexto("Volumen de Efectos:", 30, 200, 100, 20); // Parametros: texto, x1, y1, x2, y2
    _motor->CrearImagen("assets/images/barradeslizante.png",350,180,2.0f);
    idsElementos[1] = _motor->CrearBoton2(362+(((float)366/(float)100)*(float)volEfectos),185,2.0f,170,40,300,992,L"Slot 1",L"assets/images/deslizadorn.png",false,"assets/images/deslizadorp.png","assets/images/deslizadore.png");
    _motor->CrearTexto("Volumen de las Voces:", 30, 260, 100, 20); // Parametros: texto, x1, y1, x2, y2
    _motor->CrearImagen("assets/images/barradeslizante.png",350,240,2.0f);
    idsElementos[2] = _motor->CrearBoton2(362+(((float)366/(float)100)*(float)volVoces),245,2.0f,170,40,300,993,L"Slot 1",L"assets/images/deslizadorn.png",false,"assets/images/deslizadorp.png","assets/images/deslizadore.png");
    _motor->CrearTexto("Mute All: ", 30, 320, 100, 20);
    if(muteAll)
    {
        idsElementos[3] = _motor->CrearBoton2(348,305,2.0f,170,40,300,994,L"Slot 1",L"assets/images/marcadorp.png",false,"assets/images/marcadorn.png","assets/images/marcadore.png");
    }
    else
    {
        idsElementos[3] = _motor->CrearBoton2(348,305,2.0f,170,40,300,994,L"Slot 1",L"assets/images/marcadorn.png",false,"assets/images/marcadorp.png","assets/images/marcadore.png");
    }
    _motor->CrearTexto("Activar Vsync: ", 30, 380, 100, 20);
    if(vsync)
    {
        idsElementos[4] = _motor->CrearBoton2(348,365,2.0f,170,40,300,995,L"Slot 1",L"assets/images/marcadorp.png",false,"assets/images/marcadorn.png","assets/images/marcadore.png");
    }
    else
    {
        idsElementos[4] = _motor->CrearBoton2(348,365,2.0f,170,40,300,995,L"Slot 1",L"assets/images/marcadorn.png",false,"assets/images/marcadorp.png","assets/images/marcadore.png");
    }
    _motor->CrearTexto("Suavizado MSAX1: ", 30, 440, 100, 20);
    if(suavizadoMsax1)
    {
        idsElementos[5] = _motor->CrearBoton2(348,425,2.0f,170,40,300,996,L"Slot 1",L"assets/images/marcadorp.png",false,"assets/images/marcadorn.png","assets/images/marcadore.png");
    }
    else
    {
        idsElementos[5] = _motor->CrearBoton2(348,425,2.0f,170,40,300,996,L"Slot 1",L"assets/images/marcadorn.png",false,"assets/images/marcadorp.png","assets/images/marcadore.png");
    }
    _motor->CrearBoton(300,520,0,0,997,L" Guardar Cambios",L"");

    _motor->ResetKey(LMOUSE_PRESSED_DOWN);
    
}

// Actualiza lo que se ve por pantalla
void Configuracion::Render()
{
    _motor->FondoEscena(0,0,0,0); // Borra
    _motor->RenderEscena();               // Vuelve a pintar
}

void Configuracion::Update()
{
    
}

void Configuracion::ManejarEventos()
{
    if(_motor->OcurreEvento(991))
    {
        if((float)_motor->GetPosicionRaton()[0] >= 362.0f && (float)_motor->GetPosicionRaton()[0] <= 728.0f)
        {
            volAmbiente = ((float)_motor->GetPosicionRaton()[0]-362.0f)*(100.0f/366.0f);
            _motor->CambiarPosicionImagen(991,(float)_motor->GetPosicionRaton()[0],125);
        }
    }

    if(_motor->OcurreEvento(992))
    {
        if((float)_motor->GetPosicionRaton()[0] >= 362.0f && (float)_motor->GetPosicionRaton()[0] <= 728.0f)
        {
            volEfectos = ((float)_motor->GetPosicionRaton()[0]-362.0f)*(100.0f/366.0f);
            _motor->CambiarPosicionImagen(992,(float)_motor->GetPosicionRaton()[0],185);
        }
    }

    if(_motor->OcurreEvento(993))
    {
        if((float)_motor->GetPosicionRaton()[0] >= 362.0f && (float)_motor->GetPosicionRaton()[0] <= 728.0f)
        {
            volVoces = ((float)_motor->GetPosicionRaton()[0]-362.0f)*(100.0f/366.0f);
            _motor->CambiarPosicionImagen(993,(float)_motor->GetPosicionRaton()[0],245);
        }
    }

    if(_motor->OcurreEvento(994))
    {
        if(muteAll)
        {
            muteAll = false;
            _motor->BorrarElementoPorIdReal(idsElementos[3]);
            idsElementos[3] = _motor->CrearBoton2(348,305,2.0f,170,40,300,994,L"Slot 1",L"assets/images/marcadorn.png",false,"assets/images/marcadorp.png","assets/images/marcadore.png");
        }
        else
        {
            muteAll = true;
            _motor->BorrarElementoPorIdReal(idsElementos[3]);
            idsElementos[3] = _motor->CrearBoton2(348,305,2.0f,170,40,300,994,L"Slot 1",L"assets/images/marcadorp.png",false,"assets/images/marcadorn.png","assets/images/marcadore.png");
        }
        _motor->ResetKey(LMOUSE_PRESSED_DOWN);
    }

    if(_motor->OcurreEvento(995))
    {
        if(vsync)
        {
            vsync = false;
            _motor->BorrarElementoPorIdReal(idsElementos[4]);
            idsElementos[4] = _motor->CrearBoton2(348,365,2.0f,170,40,300,995,L"Slot 1",L"assets/images/marcadorn.png",false,"assets/images/marcadorp.png","assets/images/marcadore.png");

        }
        else
        {
            vsync = true;
            _motor->BorrarElementoPorIdReal(idsElementos[4]);
            idsElementos[4] = _motor->CrearBoton2(348,365,2.0f,170,40,300,995,L"Slot 1",L"assets/images/marcadorp.png",false,"assets/images/marcadorn.png","assets/images/marcadore.png");

        }
        _motor->ResetKey(LMOUSE_PRESSED_DOWN);
    }

    if(_motor->OcurreEvento(996))
    {
        if(suavizadoMsax1)
        {
            suavizadoMsax1 = false;
            _motor->BorrarElementoPorIdReal(idsElementos[5]);
            idsElementos[5] = _motor->CrearBoton2(348,425,2.0f,170,40,300,996,L"Slot 1",L"assets/images/marcadorn.png",false,"assets/images/marcadorp.png","assets/images/marcadore.png");
        }
        else
        {
            suavizadoMsax1 = true;
            _motor->BorrarElementoPorIdReal(idsElementos[5]);
            idsElementos[5] = _motor->CrearBoton2(348,425,2.0f,170,40,300,996,L"Slot 1",L"assets/images/marcadorp.png",false,"assets/images/marcadorn.png","assets/images/marcadore.png");
        }
        _motor->ResetKey(LMOUSE_PRESSED_DOWN);
    }

    if(_motor->OcurreEvento(990))
    {
        if(resolucion[0] == 0)
        {
            resolucion[0] = _motor->CrearTexto("800x600 60Fps", 385, 120, 100, 20); 
            resolucion[1] = _motor->CrearBoton2(348,105,2.0f,170,40,300,884,L"Slot 1",L"assets/images/camposelecciono.png",false,"assets/images/camposeleccionp.png","assets/images/camposeleccione.png");
            resolucion[2] = _motor->CrearTexto("1280x720 60Fps", 385, 160, 100, 20); 
            resolucion[3] = _motor->CrearBoton2(348,145,2.0f,170,40,300,885,L"Slot 1",L"assets/images/camposelecciono.png",false,"assets/images/camposeleccionp.png","assets/images/camposeleccione.png");     
            resolucion[4] = _motor->CrearTexto("1920x1080 60Fps", 385, 200, 100, 20); 
            resolucion[5] = _motor->CrearBoton2(348,185,2.0f,170,40,300,886,L"Slot 1",L"assets/images/camposelecciono.png",false,"assets/images/camposeleccionp.png","assets/images/camposeleccione.png");   
        }
        else
        {
            borrarResoluciones();
        }

        _motor->ResetKey(LMOUSE_PRESSED_DOWN);
        
    }

    if(resolucion[0] != 0)
    {
        if(_motor->OcurreEvento(884))
        {
            heightScreen = 800;
            widthScreen = 600;
            _motor->CambiarTexto(idsElementos[6],"800x600 60Fps");
            borrarResoluciones();
        }
        if(_motor->OcurreEvento(885))
        {
            heightScreen = 1280;
            widthScreen = 720;  
            _motor->CambiarTexto(idsElementos[6],"1280x720 60Fps");
            borrarResoluciones();

        }
        if(_motor->OcurreEvento(886))
        {
            heightScreen = 1920;
            widthScreen = 1080; 
            _motor->CambiarTexto(idsElementos[6],"1920x1080 60Fps");
            borrarResoluciones();
        }
    }

    if(_motor->OcurreEvento(997))
    {
        configuracion.SetConfiguracion(volAmbiente,volEfectos,volVoces,heightScreen,widthScreen,muteAll,vsync,suavizadoMsax1);
        configuracion.GuardarConfiguracion("config.global");
    }

    if (_motor->EstaPulsado(KEY_ESC)) 
    {
        _motor->ResetKey(KEY_ESC);
        atras();
    }
}

// Vuelve al menu principal
void Configuracion::atras()
{
    _motor->BorrarScena();
    _motor->BorrarGui();
    Juego::GetInstance()->estado.SaltarAlMenu();
}

void Configuracion::borrarResoluciones()
{
    if(resolucion[0] != 0)
    {
        _motor->BorrarElementoPorIdReal(resolucion[0]);
        _motor->BorrarElementoPorIdReal(resolucion[1]);
        _motor->BorrarElementoPorIdReal(resolucion[2]);
        _motor->BorrarElementoPorIdReal(resolucion[3]);
        _motor->BorrarElementoPorIdReal(resolucion[4]);
        _motor->BorrarElementoPorIdReal(resolucion[5]);
        resolucion[0] = 0;
    }
}