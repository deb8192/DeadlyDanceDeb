#include "Menu.hpp"
#include "../Juego.hpp"

Menu::Menu()
{
    _motor = MotorGrafico::GetInstance();
    _motora = MotorAudioSystem::getInstance();
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
    _motor->FondoEscena(255,100,101,140);
    _motor->ActivarFuenteDefault();

    // Llama al texto y los botones
    Reanudar();
}

// Actualiza lo que se ve por pantalla
void Menu::Render()
{
    _motor->FondoEscena(255,100,101,140); // Borra
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

    if (_motor->OcurreEvento(GUI_ID_SALIR_BUTTON))
    {
        borrarEscenaResetearEvento(GUI_ID_SALIR_BUTTON);
        salir();
    }
}

void Menu::pintarBotones()
{
    _motor->CrearBoton(300,200,500,230, GUI_ID_EMPEZAR_BUTTON, L"Iniciar Juego", L"Empieza a jugar");
    _motor->CrearBoton(300,240,500,270, GUI_ID_CONFIGURACION_BUTTON, L"Configuracion", L"Configuracion del juego");
    _motor->CrearBoton(300,280,500,310, GUI_ID_CREDITOS_BUTTON, L"Creditos", L"Creditos del juego");
    _motor->CrearBoton(300,320,500,350, GUI_ID_SALIR_BUTTON, L"Salir del juego", L"Sale del juego");
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
    Juego::GetInstance()->estado.CambioEstadoJugar();
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
    _motor->CrearTexto("Deadly Dance", 0, 0, 80, 20); // Parametros: texto, x1, y1, x2, y2
    pintarBotones();
}