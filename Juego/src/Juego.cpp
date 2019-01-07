#include "Juego.hpp"

//para clases singleton deben tener un indicador de que se ha creado el unico objeto
Juego* Juego::unica_instancia = 0;
//fin indicador singleton

Juego::Juego()
{
    motor = MotorGrafico::getInstance();//se recoge instancia de motor

    //Motor de audio inicializar
    motora = MotorAudioSystem::getInstance();
    motora->setListenerPosition(0.0f, 0.0f, 0.0f);
    motora->getEvent("Level01")->start(); //Reproducir musica Menu

    nivel = Nivel::getInstance();//se recoge la instancia de nivel
    estado = &menu;//se empieza en el estado menu

    // Cargamos los puzzles 1 vez
    cargadorXML.CargarPuzzlesXml();
}

bool Juego::Running()
{
    return motor->sigueFuncionando();
}

void Juego::LimpiarVentana()
{
    motor->limpiarDevice();
}

void Juego::InicializarVentana()
{
    motor->crearVentana(2);//crea ventana
    motor->CrearCamara();//creamos la camara
	motor->crearTextoDePrueba();//crea un texto
    motor->activarFuenteDefault();//activa la fuente por defecto que trae irrlicht
    motor->PintarBotonesMenu();//pinta los botones del menu -> esto mover a menu
}

void Juego::setNivelThen()
{
    nivel->setThen();
}

void Juego::Update()
{
    estado->Actualizar();//con esto se llama al update adecuado
    //cout << "\e[24m Aqui \e[0m" << endl;
    if(motor->ocurreEvento(GUI_ID_EMPEZAR_BUTTON))//cambiamos de estado porque han pulsado boton jugar
    {
        //limpiamos el gui y la scena
        motor->borrarScena();
        motor->borrarGui();
        nivel->CargarNivel(3);//esto luego se cambia para que se pueda cargar el nivel que se escoja o el de la partida.
        motor->resetEvento(GUI_ID_EMPEZAR_BUTTON);//reseteamos el evento
        Jugar();
    }
    if(motor->ocurreEvento(GUI_ID_SALIR_BUTTON))//salimos del juego
    {
        motor->closeGame();
    }
    //para modo debug
    if(motor->estaPulsado(KEY_G_DEBUG))
    {
        motor->activarDebugGrafico();
        motor->resetKey(KEY_G_DEBUG);
    }

    // Cargar XML arboles
    if(motor->ocurreEvento(GUI_ID_ARBOLES_BUTTON))
    {
        motor->resetEvento(GUI_ID_ARBOLES_BUTTON);
        CargarArbolesXML();   
    }

    // Puzzles
    if(motor->ocurreEvento(GUI_ID_PUZZLES_BUTTON))
    {
        motor->resetEvento(GUI_ID_PUZZLES_BUTTON);
        motor->borrarScena();
        motor->borrarGui();
        CargarPuzzlesXML();
    }
    
    // Ocurre despues de pulsar Atras en Puzzles
    if(motor->ocurreEvento(GUI_ID_BACK_MENU_BUTTON))
    {
        motor->resetEvento(GUI_ID_BACK_MENU_BUTTON);
        estado = &menu;
    }
}

//se llama cuando se presiona un boton de salir del juego.
void Juego::Salir()
{

}

//cuando se presiona boton de jugar
void Juego::Jugar()
{
    motora->getEvent("Level01")->stop(); //Detener musica Menu
    motora->setListenerPosition(0.0f, 0.0f, 0.0f);
    motora->getEvent("Level03")->start(); //Reproducir musica juego

    estado = &jugando;//se cambia a estado jugando
    
    estado->Ini();
}

void Juego::CargarArbolesXML()
{
    //cargadorXML.CargarBehaviorTreeXml("PolloBT");
}

void Juego::CargarPuzzlesXML()
{
    estado = &haciendo_puzzles;//se cambia a estado puzzles

    // Creamos la camara y la posicionamos
    motor->CrearCamara();
    motor->PosicionCamaraEnPuzzles();

    // Cargamos el puzzle: 3=HANOI / 0 al 2=OPCIONES
    haciendo_puzzles.AsignarPuzzle(cargadorXML.GetPuzzles().at(3));
    haciendo_puzzles.Iniciar();
}

void Juego::UpdateIA()
{
    estado->ActualizarIA();
}