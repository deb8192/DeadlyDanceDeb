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
}

Configuracion::~Configuracion()
{
    _motor = nullptr;
}

void Configuracion::Iniciar()
{
    //para 800 x 600 las barras son de 366 unidades
    _motor->CrearTexto("Configuracion - ESC para salir", 0, 0, 300, 20); // Parametros: texto, x1, y1, x2, y2
    //_motor->CrearImagen("assets/images/pr2.png",150,100,10.0f);
    _motor->CrearTexto("Sonido Ambiente:", 30, 115, 100, 20); // Parametros: texto, x1, y1, x2, y2
    _motor->CrearImagen("assets/images/barradeslizante.png",350,100,2.0f);
    idsElementos[0] = _motor->CrearBoton2(362+(((float)366/(float)100)*(float)volAmbiente),105,2.0f,170,40,300,991,L"Slot 1",L"assets/images/deslizadorn.png",false,"assets/images/deslizadorp.png","assets/images/deslizadore.png");
    _motor->CrearTexto("Volumen de Efectos:", 30, 180, 100, 20); // Parametros: texto, x1, y1, x2, y2
    _motor->CrearImagen("assets/images/barradeslizante.png",350,160,2.0f);
    idsElementos[1] = _motor->CrearBoton2(362+(((float)366/(float)100)*(float)volEfectos),165,2.0f,170,40,300,992,L"Slot 1",L"assets/images/deslizadorn.png",false,"assets/images/deslizadorp.png","assets/images/deslizadore.png");
    _motor->CrearTexto("Volumen de las Voces:", 30, 240, 100, 20); // Parametros: texto, x1, y1, x2, y2
    _motor->CrearImagen("assets/images/barradeslizante.png",350,220,2.0f);
    idsElementos[2] = _motor->CrearBoton2(362+(((float)366/(float)100)*(float)volVoces),225,2.0f,170,40,300,993,L"Slot 1",L"assets/images/deslizadorn.png",false,"assets/images/deslizadorp.png","assets/images/deslizadore.png");
    _motor->CrearTexto("Mute All: ", 30, 300, 100, 20);
    if(muteAll)
    {
        idsElementos[3] = _motor->CrearBoton2(348,285,2.0f,170,40,300,994,L"Slot 1",L"assets/images/marcadorp.png",false,"assets/images/marcadorn.png","assets/images/marcadore.png");
    }
    else
    {
        idsElementos[3] = _motor->CrearBoton2(348,285,2.0f,170,40,300,994,L"Slot 1",L"assets/images/marcadorn.png",false,"assets/images/marcadorp.png","assets/images/marcadore.png");
    }
    _motor->CrearTexto("Activar Vsync: ", 30, 360, 100, 20);
    if(vsync)
    {
        idsElementos[4] = _motor->CrearBoton2(348,345,2.0f,170,40,300,995,L"Slot 1",L"assets/images/marcadorp.png",false,"assets/images/marcadorn.png","assets/images/marcadore.png");
    }
    else
    {
        idsElementos[4] = _motor->CrearBoton2(348,345,2.0f,170,40,300,995,L"Slot 1",L"assets/images/marcadorn.png",false,"assets/images/marcadorp.png","assets/images/marcadore.png");
    }
    _motor->CrearTexto("Suavizado MSAX1: ", 30, 420, 100, 20);
    if(suavizadoMsax1)
    {
        idsElementos[5] = _motor->CrearBoton2(348,405,2.0f,170,40,300,996,L"Slot 1",L"assets/images/marcadorp.png",false,"assets/images/marcadorn.png","assets/images/marcadore.png");
    }
    else
    {
        idsElementos[5] = _motor->CrearBoton2(348,405,2.0f,170,40,300,996,L"Slot 1",L"assets/images/marcadorn.png",false,"assets/images/marcadorp.png","assets/images/marcadore.png");
    }
    _motor->CrearBoton(300,500,0,0,997,L" Guardar Cambios",L"");
    
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

    }

    if(_motor->OcurreEvento(992))
    {

    }

    if(_motor->OcurreEvento(993))
    {

    }

    if(_motor->OcurreEvento(994))
    {

    }

    if(_motor->OcurreEvento(995))
    {

    }

    if(_motor->OcurreEvento(996))
    {

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