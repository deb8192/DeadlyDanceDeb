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
    if(motor->ocurreEvento(101))//cambiamos de estado porque han pulsado boton jugar
    {
        //limpiamos el gui y la scena
        motor->borrarScena();
        motor->borrarGui();
        nivel->CargarNivel(1);//esto luego se cambia para que se pueda cargar el nivel que se escoja o el de la partida.
        motor->resetEvento(101);//reseteamos el evento
        Jugar();
    }
    if(motor->ocurreEvento(102))//salimos del juego
    {
        motor->closeGame();
    }
    //para modo debug
    if(motor->estaPulsado(7))
    {
        motor->activarDebugGrafico();
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
    motora->getEvent("Level02")->start(); //Reproducir musica juego

    estado = &jugando;//se cambia a estado jugando
    estado->Ini();
}
