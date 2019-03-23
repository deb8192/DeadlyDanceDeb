#include "GestorEstados.hpp"
#include "Menus/Cinematica.hpp"
#include "Menus/Menu.hpp"
#include "Menus/EstadoPuzle.hpp"
#include "Menus/Configuracion.hpp"
#include "Menus/Creditos.hpp"
#include "Menus/Pausa.hpp"
#include "Menus/EstadoMuerte.hpp"
#include "Menus/EstadoGanar.hpp"
#include "Jugando/Jugando.hpp"

GestorEstados::GestorEstados()
{

}

GestorEstados::~GestorEstados() {
    _estado = nullptr;
    while (_estados.size() > 0) {
        delete(_estados.top());
        _estados.top() = nullptr;
        _estados.pop();
    }
}

// Primer estado que se anyade en la pila al abrir el juego
void GestorEstados::CambioEstadoCinematica()
{
    anyadir(new Cinematica(), true);
}

// Carga el Menu principal, se llama desde Cinematica
void GestorEstados::CambioEstadoMenu()
{
    //eliminar(); // Elimina el estado superior (Cinematica) antes de anyadir el menu
    anyadir(new Menu(), false);
}

// Deja el Menu y carga el juego
void GestorEstados::CambioEstadoJugar()
{
    anyadir(new Jugando(), false);
}

// Elimina la Pausa y deja paso al estado jugando
void GestorEstados::QuitarPausa()
{
    eliminar();
}

// Se llama desde Pausa y EstadoMuerte
void GestorEstados::ReiniciarPartida()
{
    _estados.pop();
    _estados.top()->Reiniciar();
    _estados.top()->Reanudar();
}

// Se llama desde Pausa y EstadoMuerte
void GestorEstados::CambioDeJuegoAMenu()
{
    _estados.pop(); // Pausa o Muerte
    _estados.pop(); // Jugando
    _estados.top()->Reanudar(); //Menu
}

void GestorEstados::CambioEstadoPuzle()
{
    anyadir(new EstadoPuzle(), false);
}

void GestorEstados::CambioEstadoConfig()
{
    anyadir(new Configuracion(), false);
}

void GestorEstados::CambioEstadoCreditos()
{
    anyadir(new Creditos(), false);
}

void GestorEstados::CambioEstadoPausa()
{
    anyadir(new Pausa(), false);
}

void GestorEstados::CambioEstadoMuerte()
{
    anyadir(new EstadoMuerte(), false);
}

void GestorEstados::CambioEstadoGanar()
{
    anyadir(new EstadoGanar(), false);
}

void GestorEstados::anyadir(Estado* _nuevoEstado, bool reemplazar)
{
    anyadiendo = true;
    reemplazando = reemplazar;
    _estado = move(_nuevoEstado);
    _nuevoEstado = 0;
}

void GestorEstados::eliminar()
{
    eliminando = true;
}

void GestorEstados::ProcesarPilaEstados()
{
    if ( eliminando && !_estados.empty())
    {
        delete(_estados.top());
        _estados.top() = nullptr;
        _estados.pop();
        
        if (!_estados.empty())
        {
            _estados.top()->Reanudar();
        }
        eliminando = false;
    }
    
    if (anyadiendo)
    {
        if (!_estados.empty())
        {
            if (reemplazando)
            {
                _estados.pop();
            }
            else
            {
                _estados.top()->Pausar();
            }
        }
        
        _estados.push(move(_estado));
        _estado=0;
        _estados.top()->Iniciar();
        anyadiendo = false;
    }
}

Estado* &GestorEstados::GetEstadoActivo()
{
    return _estados.top();
}

// Se llama desde los estados Puzle/Config/Creditos
void GestorEstados::SaltarAlMenu()
{
    short int tam = _estados.size();
    for (short int est=0; est<tam-1; est++)
    {
        delete(_estados.top());
        _estados.top() = nullptr;
        _estados.pop();
    }
    _estados.top()->Reanudar();
}