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
    void ReanudarDesdePuzzle(bool ganar);
    void CambioDeJuegoAMenu();
    void CambioDeGanarAMenu();
    void CambioEstadoMenu();
    void CambioEstadoJugar(unsigned int nivel,unsigned int tipoJugador,unsigned int dinero, unsigned int slot);
    void CambioEstadoPuzle(int* puzzle);
    void CambioEstadoConfig();
    void CambioEstadoCreditos();
    void CambioEstadoPausa();
    void CambioEstadoMuerte();
    void CambioEstadoGanar();
    void CambioEstadoIniciarPartida();
    void CambioEstadoContinuarPartida();

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