#include "Pausa.hpp"
#include "../Juego.hpp"

#include "../Jugando/Jugando.hpp"

// para clases singleton deben tener un indicador de que se ha creado el unico objeto
//Pausa* Pausa::_unicaInstancia = 0;
// fin indicador singleton

Pausa::~Pausa()
{
    cout << "Borrando pausa" <<endl;
    delete _motor;
    //delete _unicaInstancia;
}

void Pausa::Iniciar()
{
    cout << "\e[42m Pausa \e[0m" << endl;
    _motor = MotorGrafico::GetInstance();
    _motor->FondoEscena(255,5,115,125);
    _motor->ActivarFuenteDefault();
    _motor->CrearTexto("Pausa - ESC o P = Atras", 0, 0, 400, 20);
    pintarBotones();
}

// Actualiza lo que se ve por pantalla
void Pausa::Render()
{
    _motor->FondoEscena(255,5,115,125);     // Borra
    _motor->RenderEscena();                 // Vuelve a pintar
}

void Pausa::Update()
{
    
}

void Pausa::ManejarEventos()
{
    if (_motor->OcurreEvento(GUI_ID_SALIR_BUTTON))
    {
        borrarEscenaResetearEvento(GUI_ID_SALIR_BUTTON);
        salir();
    }

    if (_motor->OcurreEvento(GUI_ID_MENU_BUTTON))
    {
        borrarEscenaResetearEvento(GUI_ID_MENU_BUTTON);
        menuPrincipal();
    }
    
    if (_motor->OcurreEvento(GUI_ID_REINICIAR_BUTTON))
    {
        borrarEscenaResetearEvento(GUI_ID_REINICIAR_BUTTON);
        reiniciarPartida();
    }

    // ESC o P para cerrar menu de pausa
    if (_motor->OcurreEvento(GUI_ID_ATRAS_BUTTON) ||
        _motor->EstaPulsado(KEY_ESC) || 
        _motor->EstaPulsado(KEY_P)) {
        
        borrarEscenaResetearEvento(GUI_ID_ATRAS_BUTTON);
        _motor->ResetKey(KEY_ESC);
        _motor->ResetKey(KEY_P);
        atras();
    }
}

void Pausa::pintarBotones()
{
    _motor->CrearBoton(300,200,500,230, GUI_ID_ATRAS_BUTTON, L"Atras", L"Volver al juego");
    _motor->CrearBoton(300,240,500,270, GUI_ID_REINICIAR_BUTTON, L"Reiniciar partida", L"Reiniciar");
    _motor->CrearBoton(300,280,500,310, GUI_ID_MENU_BUTTON, L"Menu principal", L"M. principal");
    _motor->CrearBoton(300,320,500,350, GUI_ID_SALIR_BUTTON, L"Salir del juego", L"Cierra el juego");
}

void Pausa::borrarEscenaResetearEvento(short id)
{
    // Limpiamos el gui y la escena
    _motor->BorrarScena();
    _motor->BorrarGui();
    _motor->ResetEvento(id);
}

// Vuelve al menu principal
void Pausa::menuPrincipal()
{
    // Elimina el estadode pausa y juego antes de anyadir el menu
    Juego::GetInstance()->estado.VaciarPila();
    Juego::GetInstance()->estado.EstadoMenu();
}

// Elimina el estado pausa e indica al juego que se tiene que reiniciar
void Pausa::reiniciarPartida()
{
    Juego::GetInstance()->estado.QuitarPausa();
    Jugando::GetInstance()->Reiniciar();
}

void Pausa::atras()
{
    // TO DO: puede ser que haya que reanudar algo como el tiempo
    Juego::GetInstance()->estado.QuitarPausa();
}

void Pausa::salir()
{
    Juego::GetInstance()->estado.VaciarPila();
    _motor->CerrarJuego();
}

void Pausa::Vaciar()
{
    cout << "Vaciando pausa" <<endl;
};