#ifndef Puzzle_HPP
#define Puzzle_HPP

#include <string>
#include <vector>
using namespace std;

class Puzzle
{
    public:
        Puzzle();
        Puzzle(short tipo, std::string enunciado, short opciones, short solucion);
        ~Puzzle();

        short GetTipo();
        std::string GetEnunciado();
        short GetOpciones();
        short GetSolucion();
        bool CorregirSolucion(short solucion);
        void AnyadirImgRespuesta(std::string img);
        std::string GetImagen(short pos);
    protected:

    private:
        short tipo; //opcion, casillas o arrastrar
        std::string enunciado;
        short opciones; //2, 3 o 4
        short solucion;
        vector<std::string> imgRespuestas;
};
#endif