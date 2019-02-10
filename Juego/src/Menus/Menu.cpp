#include "Menu.hpp"
#include "../Juego.hpp"

// para clases singleton deben tener un indicador de que se ha creado el unico objeto
//Menu* Menu::_unicaInstancia = 0;
// fin indicador singleton

Menu::Menu()
{
}

Menu::~Menu()
{
    cout << "Borrando menu" <<endl;
    delete _motor;
    //delete _unicaInstancia;
}

void Menu::Iniciar()
{
    cout << "\e[42m Menu \e[0m" << endl;

    //Motor de audio inicializar
    _motora = MotorAudioSystem::getInstance();
    _motora->setListenerPosition(0.0f, 0.0f, 0.0f);
    _motora->getEvent("Menu")->start(); //Reproducir musica Menu

    //Motor grafico, inicializar
    _motor = MotorGrafico::GetInstance();
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

    if (_motor->OcurreEvento(GUI_ID_PUZZLES_BUTTON))
    {
        borrarEscenaResetearEvento(GUI_ID_PUZZLES_BUTTON);
        cargarPuzzlesXML();
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
    _motor->CrearBoton(300,240,500,270, GUI_ID_PUZZLES_BUTTON, L"Puzzles", L"Minijuego");
    _motor->CrearBoton(300,280,500,310, GUI_ID_CONFIGURACION_BUTTON, L"Configuracion", L"Configuracion del juego");
    _motor->CrearBoton(300,320,500,350, GUI_ID_CREDITOS_BUTTON, L"Creditos", L"Creditos del juego");
    _motor->CrearBoton(300,360,500,390, GUI_ID_SALIR_BUTTON, L"Salir del juego", L"Sale del juego");
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
    cout << "\e[42m jugar \e[0m" << endl;

    _motora->getEvent("Menu")->stop(); //Detener musica Menu
    
    nivel = Nivel::getInstance();//se recoge la instancia de nivel
    nivel->CargarNivel(5);//esto luego se cambia para que se pueda cargar el nivel que se escoja o el de la partida.

    Juego::GetInstance()->estado.CambioEstadoJugar();
}

void Menu::cargarPuzzlesXML()
{
    // Cargamos los puzzles 1 vez
    cargadorXML.CargarPuzzlesXml();
    Juego::GetInstance()->estado.CambioEstadoPuzle();
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
    // TO DO: vaciar memoria antes
    Juego::GetInstance()->estado.VaciarPila();
    _motor->CerrarJuego();
}

// Elimina la memoria
void Menu::Vaciar()
{
    // TO DO: vaciar memoria
    cout << "Vaciando menu" <<endl;
}

void Menu::Pausar()
{
    cout << "Pausando menu" <<endl;
}

void Menu::Reanudar()
{
    cout << "Reanudando menu" <<endl;
    _motor->CrearTexto("Deadly Dance", 0, 0, 80, 20); // Parametros: texto, x1, y1, x2, y2
    pintarBotones();
}