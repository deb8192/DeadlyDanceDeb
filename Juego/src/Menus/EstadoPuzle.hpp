#ifndef ESTADO_PUZLE_HPP
#define ESTADO_PUZLE_HPP

#include "../Estado.hpp"
#include "../Puzzles/Puzzle.hpp"

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
        void corregirSolucion(unsigned short opcion);

        Puzzle* _puzzle;
        unsigned short width, height;
        unsigned short tipo, opciones, solucion;
        enum opcPuzzles { P_ACERTIJO = 1, P_HANOI = 2 };
};
#endif /* ESTADO_PUZLE_HPP */