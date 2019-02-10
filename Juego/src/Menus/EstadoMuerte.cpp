#include "EstadoMuerte.hpp"
#include "../Juego.hpp"

// para clases singleton deben tener un indicador de que se ha creado el unico objeto
//EstadoMuerte* EstadoMuerte::_unicaInstancia = 0;
// fin indicador singleton

EstadoMuerte::~EstadoMuerte()
{
    delete _motor;
    //delete _unicaInstancia;
}

void EstadoMuerte::Iniciar()
{
    cout << "\e[42m EstadoMuerte \e[0m" << endl;
    _motor = MotorGrafico::GetInstance();
    _motor->FondoEscena(255,5,115,125);
    _motor->ActivarFuenteDefault();
    _motor->CrearTexto("Muerto - ESC = M. principal", 0, 0, 400, 20);
    pintarBotones();
}

// Actualiza lo que se ve por pantalla
void EstadoMuerte::Render()
{
    _motor->FondoEscena(255,5,115,125); // Borra
    _motor->RenderEscena();               // Vuelve a pintar
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

    if (_motor->OcurreEvento(GUI_ID_MENU_BUTTON) || 
        _motor->EstaPulsado(KEY_ESC))
    {
        borrarEscenaResetearEvento(GUI_ID_MENU_BUTTON);
        _motor->ResetKey(KEY_ESC);
        menuPrincipal();
    }
    
    if (_motor->OcurreEvento(GUI_ID_REINICIAR_BUTTON))
    {
        borrarEscenaResetearEvento(GUI_ID_REINICIAR_BUTTON);
        reiniciarPartida();
    }
}

void EstadoMuerte::pintarBotones()
{
    _motor->CrearBoton(300,200,500,230, GUI_ID_REINICIAR_BUTTON, L"Reiniciar partida", L"Reiniciar");
    _motor->CrearBoton(300,240,500,270, GUI_ID_MENU_BUTTON, L"Menu principal", L"M. principal");
    _motor->CrearBoton(300,280,500,310, GUI_ID_SALIR_BUTTON, L"salir del juego", L"Cierra el juego");
}

void EstadoMuerte::borrarEscenaResetearEvento(short id)
{
    // Limpiamos el gui y la escena
    _motor->BorrarScena();
    _motor->BorrarGui();
    _motor->ResetEvento(id);
}

// Vuelve al menu principal
void EstadoMuerte::menuPrincipal()
{
    Juego::GetInstance()->estado.CambioEstadoMenu();
}

void EstadoMuerte::reiniciarPartida()
{
    // TO DO: llamar a reiniciar
    Juego::GetInstance()->estado.CambioEstadoJugar();
}

void EstadoMuerte::salir()
{
    // TO DO: vaciar memoria antes
    Vaciar();
    _motor->CerrarJuego();
}

void EstadoMuerte::Vaciar()
{
    cout << "Vaciando muerte" <<endl;
}