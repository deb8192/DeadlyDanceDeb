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

        Puzzle* _puzzle;
};
#endif /* ESTADO_PUZLE_HPP */