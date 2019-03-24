#ifndef Puzzle_HPP
#define Puzzle_HPP

#include <string>
#include <vector>
using namespace std;

class Puzzle
{
    public:
        Puzzle();
        Puzzle(unsigned short tipo, std::string enun, 
            unsigned short opciones, unsigned short solucion);
        ~Puzzle();

        unsigned short GetTipo();
        std::string GetEnunciado();
        unsigned short GetOpciones();
        unsigned short GetSolucion();
        bool CorregirSolucion(unsigned short solucion);
        void AnyadirImgRespuesta(std::string img);
        std::string GetImagen(unsigned short pos);
    protected:

    private:
        unsigned short tipo; // 1 = ACERTIJO, 2 = HANNOI
        std::string enunciado;
        unsigned short opciones; //2 o 4
        unsigned short solucion;
        vector<std::string> imgRespuestas;
};
#endif