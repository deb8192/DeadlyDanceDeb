#include "Juego.hpp"

//para clases singleton deben tener un indicador de que se ha creado el unico objeto
Juego* Juego::unica_instancia = 0;
//fin indicador singleton

Juego::Juego()
{
    motor = MotorGrafico::getInstance();//se recoge instancia de motor
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

void Juego::Update()
{
    estado->Actualizar();//con esto se llama al update adecuado
    //cout << "\e[24m Aqui \e[0m" << endl;
    if(motor->ocurreEvento(101))//cambiamos de estado porque han pulsado boton jugar
    {
        //limpiamos el gui y la scena
        motor->borrarScena();
        motor->borrarGui();
        Jugar();
    }
    if(motor->ocurreEvento(102))//salimos del juego
    {
        motor->closeGame();   
    }
}

//se llama cuando se presiona un boton de salir del juego.
void Juego::Salir()
{   
    
}

//cuando se presiona boton de jugar
void Juego::Jugar()
{
    cout<<"Cambia a juego"<<endl;
    estado = &jugando;//se cambia a estado jugando
    nivel = new Nivel();
}