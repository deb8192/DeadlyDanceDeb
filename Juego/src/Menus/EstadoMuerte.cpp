#include "EstadoMuerte.hpp"
#include "../Juego.hpp"

EstadoMuerte::EstadoMuerte()
{
    _motor = MotorGrafico::GetInstance();
}

EstadoMuerte::~EstadoMuerte()
{
}

void EstadoMuerte::Iniciar()
{
    cout << "\e[42m EstadoMuerte \e[0m" << endl;
    _motor->FondoEscena(255,0,0,0);
    _motor->ActivarFuenteDefault();
    _motor->CrearTexto("Muerto - ESC = M. principal", 0, 0, 400, 20);
    pintarBotones();
}

// Actualiza lo que se ve por pantalla
void EstadoMuerte::Render()
{
    _motor->FondoEscena(255,0,0,0);     // Borra
    _motor->RenderEscena();             // Vuelve a pintar
}

void EstadoMuerte::Update()
{
    
}

void EstadoMuerte::ManejarEventos()
{
    if (_motor->OcurreEvento(GUI_ID_SALIR_BUTTON))
    {
        borrarEscenaResetearEvento(GUI_ID_SALIR_BUTTON);
        salir();
    }

    if (_motor->OcurreEvento(GUI_ID_REINICIAR_BUTTON))
    {
        borrarGUIResetearEvento(GUI_ID_REINICIAR_BUTTON);
        reiniciarPartida();
    }

    if (_motor->OcurreEvento(GUI_ID_MENU_BUTTON) || 
        _motor->EstaPulsado(KEY_ESC))
    {
        borrarEscenaResetearEvento(GUI_ID_MENU_BUTTON);
        _motor->ResetKey(KEY_ESC);
        menuPrincipal();
    }
}

void EstadoMuerte::pintarBotones()
{
    _motor->CrearBoton(300,200,500,230, GUI_ID_REINICIAR_BUTTON, L"Reiniciar partida", L"Reiniciar");
    _motor->CrearBoton(300,240,500,270, GUI_ID_MENU_BUTTON, L"Menu principal", L"M. principal");
    _motor->CrearBoton(300,280,500,310, GUI_ID_SALIR_BUTTON, L"salir del juego", L"Cierra el juego");
}

// Para Salir y Menu principal, borra GUI y Escena
void EstadoMuerte::borrarEscenaResetearEvento(short id)
{
    _motor->ResetEvento(id);
    // Limpiamos el gui y la escena
    _motor->BorrarScena();
    _motor->BorrarGui();
    
}

// Para Atras y Reiniciar partida, borra solo GUI
void EstadoMuerte::borrarGUIResetearEvento(short id)
{
     _motor->ResetEvento(id);
    // Limpiamos el gui
    _motor->BorrarGui();
}

void EstadoMuerte::menuPrincipal()
{
    // Elimina todos los estados y anyade el de menu
    Juego::GetInstance()->estado.CambioDeJuegoAMenu();
}

void EstadoMuerte::reiniciarPartida()
{
    Juego::GetInstance()->estado.ReiniciarPartida();
}

void EstadoMuerte::salir()
{
    _motor->CerrarJuego();
}

void EstadoMuerte::Vaciar()
{
    cout << "Vaciando muerte" <<endl;
}