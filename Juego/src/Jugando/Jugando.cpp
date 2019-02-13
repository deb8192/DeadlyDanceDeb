#include "Jugando.hpp"
#include "../Juego.hpp"
#include "Nivel.hpp"

// para clases singleton deben tener un indicador de que se ha creado el unico objeto
Jugando* Jugando::_unicaInstancia = 0;
// fin indicador singleton

Jugando::~Jugando()
{
    cout << "Borrando Jugando" << endl;
    delete _motor;
    //delete _unicaInstancia;
}

void Jugando::Iniciar()
{
    cout << "\e[42m Entrando en Estado - Jugando \e[0m" << endl;
    _motor = MotorGrafico::GetInstance();
    reiniciando = false;
    _motor->CrearCamara();
    _motor->FondoEscena(255,0,0,0);
}

void Jugando::Render()
{
    _motor->FondoEscena(255,0,0,0); // Borra

    Nivel* _nivel = Nivel::getInstance();
    _nivel->Draw();

    _motor->RenderEscena();               // Vuelve a pintar
}

void Jugando::Update()
{
    _motor->clearDebug();

    //Actualiza el motor de audio
    MotorAudioSystem* _motora = MotorAudioSystem::getInstance();
    _motora->update(false);

    SenseEventos* _sense = SenseEventos::getInstance();
    _sense->update();//se actualizan sentidos

    Nivel* _nivel = Nivel::getInstance();
    if (_nivel->GetJugador()->EstaMuerto()) // Comprobar si ha muerto el jugador, vida <= 0
    {
        _nivel->GetJugador()->MuereJugador(); // Animacion de muerte
        Juego::GetInstance()->estado.CambioEstadoMuerte();
    }
    _nivel->update();//se actualiza posiciones y interpolado
}

void Jugando::UpdateIA()
{
    Nivel* _nivel = Nivel::getInstance();

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

    Nivel* _nivel = Nivel::getInstance();

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