#include "Jugando.hpp"
#include "../Juego.hpp"

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

    Nivel* nivel = Nivel::getInstance();
    nivel->Draw();

    _motor->RenderEscena();               // Vuelve a pintar
}

void Jugando::Update()
{
    _motor->clearDebug();
    Nivel* nivel = Nivel::getInstance();
    SenseEventos* sense = SenseEventos::getInstance();
    sense->update();//se actualizan sentidos
    nivel->update();//se actualiza posiciones y interpolado

    //Actualiza el motor de audio
    MotorAudioSystem* motora = MotorAudioSystem::getInstance();
    motora->update(false);
}

void Jugando::UpdateIA()
{
    Nivel* nivel = Nivel::getInstance();
    nivel->updateIA();
}

void Jugando::ManejarEventos() {
    // ESC o P para abrir menu de pausa
    if ( _motor->EstaPulsado(KEY_ESC) || 
        _motor->EstaPulsado(KEY_P)) {
        
        _motor->ResetKey(KEY_ESC);
        _motor->ResetKey(KEY_P);
        menuPausa();
    }

    if ( _motor->EstaPulsado(KEY_K)) {
        
        _motor->ResetKey(KEY_K);
        menuMuerto();
    }

    Nivel* nivel = Nivel::getInstance();
    nivel->InteractuarNivel();
}

void Jugando::menuPausa()
{
    Juego::GetInstance()->estado.CambioEstadoPausa();
}

void Jugando::menuMuerto()
{
    // TO DO: Borrar cosas
    Juego::GetInstance()->estado.CambioEstadoMuerte();
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