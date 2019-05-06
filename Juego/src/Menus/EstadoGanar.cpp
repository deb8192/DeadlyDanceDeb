#include "EstadoGanar.hpp"
#include "../Juego.hpp"

EstadoGanar::EstadoGanar()
{
    _motor = MotorGrafico::GetInstance();
    _motora = MotorAudioSystem::getInstance();
}

EstadoGanar::~EstadoGanar()
{
    _motor = nullptr;
    _motora = nullptr;
}

void EstadoGanar::Iniciar()
{
    _motor->FondoEscena(255,0,0,0);
    _motor->ActivarFuenteDefault();
    pintarBotones();
}

// Actualiza lo que se ve por pantalla
void EstadoGanar::Render()
{
    _motor->FondoEscena(255,0,0,0);     // Borra
    _motor->RenderEscena();             // Vuelve a pintar
}

void EstadoGanar::Update()
{
    
}

void EstadoGanar::ManejarEventos()
{
    if (_motor->OcurreEvento(GUI_ID_SALIR_BUTTON))
    {
        borrarEscenaResetearEvento(GUI_ID_SALIR_BUTTON);
        _motor->ResetKey(LMOUSE_PRESSED_DOWN);
        salir();
    }

    if (_motor->OcurreEvento(GUI_ID_CONTINUAR))
    {
        _motor->ResetKey(LMOUSE_PRESSED_DOWN);
        borrarGUIResetearEvento(GUI_ID_CONTINUAR);
        siguienteNivel();
    }

    if (_motor->OcurreEvento(GUI_ID_MENU_BUTTON))
    {
        _motor->ResetKey(LMOUSE_PRESSED_DOWN);
        borrarEscenaResetearEvento(GUI_ID_MENU_BUTTON);
        menuPrincipal();
    }
}

void EstadoGanar::pintarBotones()
{
    _motor->CrearBoton(300,200,500,230, GUI_ID_CONTINUAR, L"Siguiente nivel", L"Continua al siguiente nivel");
    _motor->CrearBoton(300,240,500,270, GUI_ID_MENU_BUTTON, L"Menu principal", L"M. principal");
    _motor->CrearBoton(300,280,500,310, GUI_ID_SALIR_BUTTON, L"Salir del juego", L"Cierra el juego");
}

// Para Salir y Menu principal, borra GUI y Escena
void EstadoGanar::borrarEscenaResetearEvento(short id)
{
    _motor->ResetEvento(id);
    // Limpiamos el gui y la escena
    _motor->BorrarScena();
    _motor->BorrarGui();
}

// Para Atras y Reiniciar partida, borra solo los botones del GUI
void EstadoGanar::borrarGUIResetearEvento(short id)
{
    _motor->BorrarElemento(GUI_ID_CONTINUAR);
    _motor->BorrarElemento(GUI_ID_MENU_BUTTON);
    _motor->BorrarElemento(GUI_ID_SALIR_BUTTON);
    _motor->ResetEvento(id);
}

void EstadoGanar::menuPrincipal()
{
    _motora->getEvent("AmbienteGritos")->stop(); //Detener musica ambiente
    _motora->getEvent("Nivel1")->stop(); //Detener musica Juego
    _motora->getEvent("Nivel2")->stop(); //Detener musica Juego
    _motor->LimpiarElementosJuego();
    // Elimina todos los estados y anyade el de menu
    Juego::GetInstance()->estado.CambioDeGanarAMenu();
}

void EstadoGanar::siguienteNivel()
{
    // TO DO: hacer el cambio de nivel
    cout << "Cambio nivel sin hacer - Cierra el juego." <<endl;
}

void EstadoGanar::salir()
{
    _motor->CerrarJuego();
}