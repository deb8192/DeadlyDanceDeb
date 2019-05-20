#include "Menu.hpp"
#include "../Juego.hpp"

Menu::Menu()
{
    _motor = MotorGrafico::GetInstance();
    _motora = MotorAudioSystem::getInstance();
    r = 0;
    g = 20;
    b = 20;
    rm = true;
    gm = true;
    bm = true;
}

Menu::~Menu()
{
    // Punteros a clases singleton
    _motora = nullptr;
    _motor = nullptr;
}

void Menu::Iniciar()
{

    //Motor de audio inicializar
    _motora->setListenerPosition(0.0f, 0.0f, 0.0f);

    //Motor grafico, inicializar
    _motor->FondoEscena(0.0f,0.0f,0.0f,0.0f);
    _motor->ActivarFuenteDefault();

    // Llama al texto y los botones
    Reanudar();

    //reinicia croma cambiante
    r = 0;
    g = 20;
    b = 20;
    rm = true;
    gm = true;
    bm = true;
}

// Actualiza lo que se ve por pantalla
void Menu::Render()
{
    calcularColor();
    float multi = 1.0f/400.0f;
    _motor->FondoEscena(0.0f,(float)r*multi,(float)g*multi,(float)b*multi);
    _motor->RenderEscena();               // Vuelve a pintar
}

void Menu::Update()
{
    _motora->update(false);
}

void Menu::ManejarEventos()
{
    if (_motor->OcurreEvento(GUI_ID_EMPEZAR_BUTTON))//cambiamos de estado porque han pulsado boton jugar
    {
        borrarEscenaResetearEvento(GUI_ID_EMPEZAR_BUTTON);// reseteamos el evento
        _motor->ResetKey(LMOUSE_PRESSED_DOWN);
        jugar();
    }

    if (_motor->OcurreEvento(GUI_ID_CONFIGURACION_BUTTON))
    {
        borrarEscenaResetearEvento(GUI_ID_CONFIGURACION_BUTTON);
        configuracion();
    }

    if (_motor->OcurreEvento(GUI_ID_CREDITOS_BUTTON))
    {
        borrarEscenaResetearEvento(GUI_ID_CREDITOS_BUTTON);
        creditos();
    }

    if (_motor->OcurreEvento(GUI_ID_CONTINUARPARTIDA_BUTTON))
    {
        borrarEscenaResetearEvento(GUI_ID_CONTINUARPARTIDA_BUTTON);
        _motor->ResetKey(LMOUSE_PRESSED_DOWN);
        continuarPartida();
    }

    if (_motor->OcurreEvento(GUI_ID_SALIR_BUTTON))
    {
        borrarEscenaResetearEvento(GUI_ID_SALIR_BUTTON);
        salir();
    }
}

void Menu::pintarBotones()
{
    GestorInterfaces * _ges = GestorInterfaces::GetInstance();
    _ges->ActualizarParametros();
    GestorInterfaces::menu * m = _ges->GetMenu();
    //std::cout << m->xLogoM << " " << m->yLogoM <<"\n";
    _motor->CrearImagen("assets/images/logo1.png",m->xLogoM,m->yLogoM,_ges->GetEscaladoY());
    _motor->CrearImagen("assets/images/logo2.png",m->xLogo2M,m->yLogo2M,_ges->GetEscaladoY());
    _motor->CrearImagen("assets/images/logo3.png",m->xLogo3M,m->yLogo3M,_ges->GetEscaladoY());
    _motor->CrearBoton(m->xEmpezarM,m->yEmpezarM,500,230, GUI_ID_EMPEZAR_BUTTON, L"Iniciar Partida", L"Iniciar Partida");//te da la opcion de empezar una nueva partida
    _motor->CrearBoton(m->xContinuarM,m->yContinuarM,500,270, GUI_ID_CONTINUARPARTIDA_BUTTON, L"Continuar Partida", L"Continuar Partida");//te da la opcion de cargar una partida
    _motor->CrearBoton(m->xConfiM,m->yConfiM,500,310, GUI_ID_CONFIGURACION_BUTTON, L"Configuracion", L"Configuracion");
    _motor->CrearBoton(m->xCreM,m->yCreM,500,350, GUI_ID_CREDITOS_BUTTON, L"Creditos", L"Creditos");
    _motor->CrearBoton(m->xSalirM,m->ySalirM,500,390, GUI_ID_SALIR_BUTTON, L"Salir al Escritorio", L"Salir");
}

void Menu::borrarEscenaResetearEvento(short id)
{
    // Limpiamos el gui y la escena
    _motor->BorrarScena();
    _motor->BorrarGui();
    _motor->ResetEvento(id);
}

void Menu::jugar()
{

    _motora->getEvent("Menu")->stop(); //Detener musica Menu
    Juego::GetInstance()->estado.CambioEstadoIniciarPartida();
    //_motor->AsignarCargando(_motor->CrearImagen("assets/images/cargando.png",540,330,1.0f));
}

void Menu::configuracion()
{
    Juego::GetInstance()->estado.CambioEstadoConfig();
}

void Menu::creditos()
{
    Juego::GetInstance()->estado.CambioEstadoCreditos();
}

void Menu::salir()
{
    _motor->CerrarJuego();
}

void Menu::Pausar()
{
}

void Menu::Reanudar()
{
    _motora->getEvent("Menu")->start(); //Reproducir musica Menu
    //_motor->CrearTexto("Deadly Dance", 0, 0, 80, 20); // Parametros: texto, x1, y1, x2, y2
    pintarBotones();
}

void Menu::calcularColor()
{
    unsigned short estavez = 1;
    //std::cout << " color " << estavez << std::endl;

    if(estavez == 1)
    {
        if(rm)
        {
            r = r+4;
        }
        else
        {
            r = r-1;
        }

        if(r == 220)
        {
            rm = false;
        }

        if(r == 0)
        {
            rm = true;
        }

        //std::cout << " col " << r << std::endl;
    }

    /*if(estavez == 2)
    {
        if(bm)
        {
            b = b+1;
        }
        else
        {
            b = b-1;
        }

        if(b == 180)
        {
            bm = false;
        }

        if(b == 0)
        {
            bm = true;
        }
    }*/

    /*if(estavez == 3)
    {
        if(gm)
        {
            g = g+1;
        }
        else
        {
            g = g-1;
        }

        if(g == 20)
        {
            gm = false;
        }

        if(g == 0)
        {
            gm = true;
        }
    }*/
}

void Menu::continuar()
{

}

void Menu::continuarPartida()
{
    Juego::GetInstance()->estado.CambioEstadoContinuarPartida();
}
