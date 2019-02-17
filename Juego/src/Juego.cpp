#include "Juego.hpp"

// para clases singleton deben tener un indicador de que se ha creado el unico objeto
Juego* Juego::_unicaInstancia = 0;
// fin indicador singleton

Juego::Juego()
{
    _motor = MotorGrafico::GetInstance();// se recoge instancia de_motor
    _tiempo = Times::GetInstance();
}

Juego::~Juego()
{
    // Punteros a clases singleton
    _tiempo = nullptr;
    _motor = nullptr;

    // Liberar memoria
    delete _unicaInstancia;
}

void Juego::inicializarVentana()
{
    cout << "\e[42m Iniciando Juego \e[0m" << endl;
    _motor->CrearVentana(2);//crea ventana de 800x600

    //estado.CambioEstadoMenu();// temporal para pruebas, 
    estado.CambioEstadoCinematica();
}

void Juego::Iniciar()
{
    inicializarVentana();

    // se debe dar valor a las variables de interpolacion antes del bucle
	//juego->setNivelThen();
	_tiempo->SetFrames(60,15,4);//definimos a cuanto queremos que vaya el programa

    // te devuelve true si esta en funcionamiento la ventana del juego, te devuelve false si se ha cerrado la ventana
    while (_motor->VentanaAbierta())// comprobamos que esta activo el dispositivo
	{
        // Comprueba si hay que anyadir o eliminar un estado
        estado.ProcesarPilaEstados();

        if(_tiempo->EjecutoDraw())// Actualiza 60 veces por segundo
		{
            // Comprueba los eventos de teclado o botones
            estado.GetEstadoActivo()->ManejarEventos();

			if(_tiempo->EjecutoUpdate())// Actualiza 15 veces por segundo
			{
				if(_tiempo->EjecutoIA())// Actualiza 4 veces por segundo
				{
					estado.GetEstadoActivo()->UpdateIA();//si lo esta actualizamos la IA
				}
				estado.GetEstadoActivo()->Update();//si lo esta actualizamos la escena
			}
			estado.GetEstadoActivo()->Render();//si lo esta dibujamos la escena
		}
	}

	limpiarVentana(); //si no lo esta borramos de memoria el dispositivo
}

void Juego::limpiarVentana()
{
   _motor->LimpiarDevice();
}