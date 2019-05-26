#ifndef ESTADO_PUZLE_HPP
#define ESTADO_PUZLE_HPP

#include "../Estado.hpp"
#include "../Puzzles/Puzzle.hpp"
#include "../Puzzles/PilaFichas.hpp"
#include <stack> // para la pila de fichas


class EstadoPuzle: public Estado {
    public:
        EstadoPuzle(int* puzzle);
        ~EstadoPuzle();
        
        void Iniciar();
        void Render();
        void Update();
        void ManejarEventos();
        
    private:
        void atras();
        void comprobarEventosOpciones();
        void comprobarEventosHanoi();
        void corregirSolucion(int opcion);
        void comprobarGanar();
        void crearFichasPila();
        bool comprobarPilaVacia(int pila);
        bool comprobarTopPila(int fichaY);
        bool comprobarTamanyo();
        int  recolocarFicha();
        void sacarFicha();
        int  meterFicha();
        void reiniciarPilas();
        void deseleccionarNodo();
        int  getZonaVentana();

        Puzzle* _puzzle;
        unsigned int width, height, width_aux, height_aux;
        int tipo, opciones, solucion;
        enum opcPuzzles { P_ACERTIJO = 1, P_HANOI = 2 };

        // Pilas de fichas
        stack <PilaFichas*> pilaIzq;
        stack <PilaFichas*> pilaCentro;
        stack <PilaFichas*> pilaDer;
        PilaFichas* ficha;

        enum posZ { IZQ=-9, CENTRO=0, DER=9, NO_SELECT=-1 };
        int pasos, pilaInicial, pilaFinal;
        bool pulsado;
        int x_linea1, x_linea2;
        int fichaMover;
        float iniXFichas;
};
#endif /* ESTADO_PUZLE_HPP */