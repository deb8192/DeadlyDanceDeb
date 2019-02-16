#pragma once

#include "Estado.hpp"
#include <stack>  // Para la pila de estados

class GestorEstados
{
public:
    GestorEstados() { }
    ~GestorEstados() {
        while (_estados.size() > 0) {
            _estado = _estados.top();
            //delete _estado;
            _estado = 0;
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