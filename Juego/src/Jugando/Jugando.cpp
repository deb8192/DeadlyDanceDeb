#include "Jugando.hpp"
#include "../Juego.hpp"

//singleton
Jugando* Jugando::_unica_instancia = 0;
//fin indicador singleton

Jugando::Jugando()
{
    reiniciando = false;
    _motor = MotorGrafico::GetInstance();
    _nivel = Nivel::getInstance();
    _motora = MotorAudioSystem::getInstance();
    _sense = SenseEventos::getInstance();

    //Esto luego se cambia para que se pueda cargar el nivel que se escoja o el de la partida.
    _nivel->CargarNivel(5);
}

Jugando::~Jugando()
{
    cout << "Borrando Jugando" << endl;
    reiniciando = false;

    // Punteros a clases singleton
    _sense = nullptr;
    _motora = nullptr;
    _nivel = nullptr;
    _motor = nullptr;

    // Liberar memoria
    delete _unica_instancia;
}

void Jugando::Iniciar()
{
    cout << "\e[42m Entrando en Estado - Jugando \e[0m" << endl;
    reiniciando = false;
    _motor->CrearCamara();
    _motor->FondoEscena(255,0,0,0);
}

void Jugando::Render()
{
    _motor->FondoEscena(255,0,0,0); // Borra

    _nivel->Draw();

    _motor->RenderEscena();               // Vuelve a pintar
}

void Jugando::Update()
{
    _motor->clearDebug();

    //Actualiza el motor de audio
    _motora->update(false);

    _sense->update();//se actualizan sentidos

    if (_nivel->GetJugador()->EstaMuerto()) // Comprobar si ha muerto el jugador, vida <= 0
    {
        _nivel->GetJugador()->MuereJugador(); // Animacion de muerte
        Juego::GetInstance()->estado.CambioEstadoMuerte();
    }
    _nivel->update();//se actualiza posiciones y interpolado
}

void Jugando::UpdateIA()
{
    /* *********** Teclas para probar cosas *************** */
    if (_motor->EstaPulsado(KEY_J))
    {
        _motor->ResetKey(KEY_J);
        _nivel->GetJugador()->QuitarVida(20);
    }
    /* **************************************************** */
    _nivel->updateIA();
}

void Jugando::ManejarEventos() {
    // ESC o P para abrir menu de pausa
    if (_motor->EstaPulsado(KEY_ESC) || 
        _motor->EstaPulsado(KEY_P)) {
        
        _motor->ResetKey(KEY_ESC);
        _motor->ResetKey(KEY_P);
        Juego::GetInstance()->estado.CambioEstadoPausa();
    }

    /* *********** Teclas para probar cosas *************** */

    if (_motor->EstaPulsado(KEY_K))
    {
        _motor->ResetKey(KEY_K);
        _nivel->GetJugador()->setVida(0);
    }

    //para modo debug
    if(_motor->EstaPulsado(KEY_G_DEBUG))
    {
        _motor->activarDebugGrafico();
        _motor->ResetKey(KEY_G_DEBUG);
    }

    //para pathfinding activado
    if(_motor->EstaPulsado(KEY_C))
    {
        _motor->activarPathfinding();
        _motor->ResetKey(KEY_C);
    }
    /* **************************************************** */
    
    _nivel->InteractuarNivel();
}

void Jugando::Pausar()
{ 
    cout << "Pausando el juego" << endl;
}

void Jugando::Reanudar()
{ 
    if (reiniciando) {
        cout << "REINICIAR JUEGO" << endl;
        reiniciando = false;
    } else {
        cout << "Reanudando el juego" << endl;
    }
}

// Elimina los datos en memoria
void Jugando::Vaciar()
{
    cout << "Vaciando el juego" << endl;
}

void Jugando::Reiniciar()
{
    reiniciando = true;
}