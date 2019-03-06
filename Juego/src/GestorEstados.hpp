#pragma once

#include "Estado.hpp"
#include <stack>  // Para la pila de estados

class GestorEstados
{
public:
    GestorEstados();
    ~GestorEstados();
    
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
    void CambioEstadoGanar();

    void ProcesarPilaEstados();
    Estado* &GetEstadoActivo();
    void SaltarAlMenu();

private:
    stack<Estado*> _estados;
    Estado* _estado;

    bool reemplazando;
    bool anyadiendo;
    bool eliminando;

    void anyadir(Estado* _nuevoEstado, bool reemplazar);
    void eliminar();
};