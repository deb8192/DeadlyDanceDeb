#pragma once

#include "Estado.hpp"
#include <stack>  // Para la pila de estados

class GestorEstados
{
public:
    GestorEstados() { }
    ~GestorEstados() {
        _estado = nullptr;
        while (_estados.size() > 0) {
            delete(_estados.top());
            _estados.top() = nullptr;
            _estados.pop();
        }
    }
    
    void CambioEstadoCinematica();
    void QuitarPausa();
    void ReiniciarPartida();
    void CambioDeJuegoAMenu();
    void CambioEstadoMenu();
    void CambioEstadoJugar();
    void CambioEstadoPuzle();
    void CambioEstadoConfig();
    void CambioEstadoCreditos();
    void CambioEstadoPausa();
    void CambioEstadoMuerte();

    void ProcesarPilaEstados();
    Estado* &GetEstadoActivo();
    void SaltarAlMenu();
    void VaciarPila();

private:
    stack<Estado*> _estados;
    Estado* _estado;

    bool reemplazando;
    bool anyadiendo;
    bool eliminando;

    void anyadir(Estado* _nuevoEstado, bool reemplazar);
    void eliminar();
};