#include "Juego.hpp"

//para clases singleton deben tener un indicador de que se ha creado el unico objeto
Juego* Juego::_unica_instancia = 0;
//fin indicador singleton

Juego::Juego()
{
    _motor = MotorGrafico::getInstance();//se recoge instancia de motor

    //Motor de audio inicializar
    _motora = MotorAudioSystem::getInstance();
    _motora->setListenerPosition(0.0f, 0.0f, 0.0f);
    _motora->getEvent("Menu")->start(); //Reproducir musica Menu

    nivel = Nivel::getInstance();//se recoge la instancia de nivel
    estado = &cinematica;//se empieza en el estado menu

    // Cargamos los puzzles 1 vez
    cargadorXML.CargarPuzzlesXml();
}

bool Juego::Running()
{
    return _motor->sigueFuncionando();
}

void Juego::LimpiarVentana()
{
    _motor->limpiarDevice();
}

void Juego::InicializarVentana()
{
    if(estado->QueEstado() == 3)
    {
        _motor->crearVentana(2);//crea ventana
        _motor->CrearCamara();//creamos la camara
        //le ponemos la marca de tiempo, cuando pasen 16 segundos lo pasamos
        Times* _tiempo = Times::GetInstance();
        marcaTiempo=_tiempo->GetTiempo(1);
    }
    else
    {
        _motor->borrarGui();//para borrar cinematicas
	    _motor->crearTextoDePrueba();//crea un texto
        _motor->activarFuenteDefault();//activa la fuente por defecto que trae irrlicht
        _motor->PintarBotonesMenu();//pinta los botones del menu -> esto mover a menu
    }
}

void Juego::setNivelThen()
{
    //nivel->setThen();
}

void Juego::Draw()
{
    if(estado->QueEstado() == 3)
    {
        Times* _tiempo = Times::GetInstance();

        if(_tiempo->CalcularTiempoPasado(marcaTiempo) >= tiempoTotal || _motor->finalCinematica() || _motor->estaPulsado(KEY_ESPACIO))
        {
            estado = &menu;
            InicializarVentana();
            _motor->resetKey(KEY_ESPACIO);
        }

        estado->Pintar();
    }
    else
    {
        estado->Pintar();
    }
}

void Juego::Update()
{
    /*if(estado->QueEstado() == 3)
    {
        Times* _tiempo = Times::GetInstance();

        if(_tiempo->CalcularTiempoPasado(marcaTiempo) >= tiempoTotal || _motor->finalCinematica())
        {
            estado = &menu;
            InicializarVentana();
        }

        estado->Actualizar();
    }
    else
    {*/
        estado->Actualizar();
        //con esto se llama al update adecuado
        //cout << "\e[24m Aqui \e[0m" << endl;
        if(_motor->ocurreEvento(GUI_ID_EMPEZAR_BUTTON))//cambiamos de estado porque han pulsado boton jugar
        {
            //limpiamos el gui y la scena
            _motor->borrarScena();
            _motor->borrarGui();
            nivel->CargarNivel(2);//esto luego se cambia para que se pueda cargar el nivel que se escoja o el de la partida.
            _motor->resetEvento(GUI_ID_EMPEZAR_BUTTON);//reseteamos el evento
            Jugar();
        }

        if(_motor->ocurreEvento(GUI_ID_MENU_BUTTON) /*&& nivel->EstaLimpio()*/)
        {
            _motora->getEvent("Nivel1")->stop(); //Detener musica Menu
            _motora->getEvent("Menu")->start(); //Reproducir musica juego
            _motor->resetEvento(GUI_ID_MENU_BUTTON);
            cambiarEstadoMenu();
        }

        if(_motor->ocurreEvento(GUI_ID_REINICIAR_BUTTON))
        {
            _motora->getEvent("Nivel1")->stop();
            _motor->resetEvento(GUI_ID_REINICIAR_BUTTON);
            _motor->borrarScena();
            _motor->borrarGui();
            nivel->CargarNivel(2);
            _motor->CrearCamara();
        }

        if(_motor->ocurreEvento(GUI_ID_SALIR_BUTTON))//salimos del juego
        {
            _motor->closeGame();
        }

        estado->Eventos();

        //para modo debug
        if(_motor->estaPulsado(KEY_G_DEBUG))
        {
            _motor->activarDebugGrafico();
            _motor->resetKey(KEY_G_DEBUG);
        }

        //para pathfinding activado
        if(_motor->estaPulsado(KEY_C))
        {
            _motor->activarPathfinding();
            _motor->resetKey(KEY_C);
        }

        // Cargar XML arboles
        if(_motor->ocurreEvento(GUI_ID_ARBOLES_BUTTON))
        {
            _motor->resetEvento(GUI_ID_ARBOLES_BUTTON);
            CargarArbolesXML();
        }

        // Puzzles
        if(_motor->ocurreEvento(GUI_ID_PUZZLES_BUTTON))
        {
            _motor->resetEvento(GUI_ID_PUZZLES_BUTTON);
            _motor->borrarScena();
            _motor->borrarGui();
            CargarPuzzlesXML();
        }

        // Ocurre despues de pulsar Atras en Puzzles
        if(_motor->ocurreEvento(GUI_ID_ATRAS_BUTTON))
        {
            _motor->resetEvento(GUI_ID_ATRAS_BUTTON);
            estado = &menu;
        }
    //}
}

//se llama cuando se presiona un boton de salir del juego.
void Juego::Salir()
{

}

//cuando se presiona boton de jugar
void Juego::Jugar()
{
    _motora->getEvent("Menu")->stop(); //Detener musica Menu

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
    _motor->CrearCamara();
    _motor->PosicionCamaraEnPuzzles();

    // Cargamos el puzzle: 3=HANOI / 0 al 2=OPCIONES
    haciendo_puzzles.AsignarPuzzle(cargadorXML.GetPuzzles().at(3));
    haciendo_puzzles.Iniciar();
}

void Juego::UpdateIA()
{
    estado->ActualizarIA();
}

void Juego::cambiarEstadoMenu()
{
    _motor->borrarScena();
    _motor->borrarGui();
    _motor->crearTextoDePrueba();//crea un texto
    _motor->activarFuenteDefault();//activa la fuente por defecto que trae irrlicht
    _motor->PintarBotonesMenu();
    estado = &menu;
}
