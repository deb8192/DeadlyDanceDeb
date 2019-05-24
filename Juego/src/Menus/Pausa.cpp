#include "Pausa.hpp"
#include "../Juego.hpp"

Pausa::Pausa()
{
    _motor = MotorGrafico::GetInstance();
    _motora = MotorAudioSystem::getInstance();
}

Pausa::~Pausa()
{
    _motor = nullptr;
    _motora = nullptr;
}

void Pausa::Iniciar()
{
    _motor->FondoEscena(255,0,0,0);
    _motor->ActivarFuenteDefault();
    pintarBotones();
}

// Actualiza lo que se ve por pantalla
void Pausa::Render()
{
    _motor->FondoEscena(255,0,0,0);         // Borra
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
        _motor->ResetKey(LMOUSE_PRESSED_DOWN);
        salir();
    }

    if (_motor->OcurreEvento(GUI_ID_REINICIAR_BUTTON))
    {
        borrarGUIResetearEvento(GUI_ID_REINICIAR_BUTTON);
        _motor->ResetKey(LMOUSE_PRESSED_DOWN);
        reiniciarPartida();
    }

    // ESC o P para cerrar menu de pausa
    if (_motor->OcurreEvento(GUI_ID_ATRAS_BUTTON) ||
        _motor->EstaPulsado(KEY_ESC) ||
        _motor->EstaPulsado(KEY_P)) {

        borrarGUIResetearEvento(GUI_ID_ATRAS_BUTTON);
        _motor->ResetKey(KEY_ESC);
        _motor->ResetKey(KEY_P);
        _motor->ResetKey(LMOUSE_PRESSED_DOWN);
        atras();
    }

    if (_motor->OcurreEvento(GUI_ID_MENU_BUTTON))
    {
        borrarEscenaResetearEvento(GUI_ID_MENU_BUTTON);
        _motor->ResetKey(LMOUSE_PRESSED_DOWN);
        menuPrincipal();
    }
}

void Pausa::pintarBotones()
{
    GestorInterfaces * _ges = GestorInterfaces::GetInstance();
    _ges->ActualizarParametros();
    GestorInterfaces::menu * m = _ges->GetMenu();
    titulo = _motor->CrearImagen("assets/images/TituloPausa.png",m->xLogoM,m->yLogoM,_ges->GetEscaladoY());
    _motor->CrearBoton(300,200,500,230, GUI_ID_ATRAS_BUTTON, L"Continuar", L"Volver al juego");
    _motor->CrearBoton(300,240,500,270, GUI_ID_REINICIAR_BUTTON, L"Reiniciar partida", L"Reiniciar");
    _motor->CrearBoton(300,280,500,310, GUI_ID_MENU_BUTTON, L"Menu principal", L"M. principal");
    _motor->CrearBoton(300,320,500,350, GUI_ID_SALIR_BUTTON, L"Salir del juego", L"Cierra el juego");
}

// Para Salir y Menu principal, borra GUI y Escena
void Pausa::borrarEscenaResetearEvento(short id)
{
    // Limpiamos el gui y la escena
    _motor->BorrarElementoPorIdReal(titulo);
    _motor->BorrarScena();
    _motor->BorrarGui();
    _motor->ResetEvento(id);
}

// Para Atras y Reiniciar partida, borra solo los botones del GUI
void Pausa::borrarGUIResetearEvento(short id)
{
    _motor->BorrarElementoPorIdReal(titulo);
    _motor->BorrarElemento(GUI_ID_ATRAS_BUTTON);
    _motor->BorrarElemento(GUI_ID_REINICIAR_BUTTON);
    _motor->BorrarElemento(GUI_ID_MENU_BUTTON);
    _motor->BorrarElemento(GUI_ID_SALIR_BUTTON);
    _motor->ResetEvento(id);
}

// Vuelve al menu principal
void Pausa::menuPrincipal()
{
    _motora->getEvent("AmbienteLava")->stop(); //Detener ambiente
    _motora->getEvent("AmbienteGritos")->stop(); //Detener musica ambiente
    _motora->getEvent("Nivel1")->stop(); //Detener musica Juego
    _motora->getEvent("Nivel2")->stop(); //Detener musica Juego
    _motor->LimpiarElementosJuego();
    // Elimina todos los estados y anyade el de menu
    Juego::GetInstance()->estado.CambioDeJuegoAMenu();
}

// Elimina el estado pausa e indica al juego que se tiene que reiniciar
void Pausa::reiniciarPartida()
{
    Juego::GetInstance()->estado.ReiniciarPartida();
}

void Pausa::atras()
{
    Juego::GetInstance()->estado.QuitarPausa();
}

void Pausa::salir()
{
    _motor->CerrarJuego();
}
