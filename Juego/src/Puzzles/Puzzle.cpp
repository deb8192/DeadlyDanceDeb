#include "Puzzle.hpp"

Puzzle::Puzzle()
{
    tipo = 1;
    enunciado = "";
    opciones = 0;
    solucion = 0;
}

Puzzle::Puzzle(unsigned short tipo, std::string enun, 
    unsigned short opciones, unsigned short solucion)
{
    this->tipo = tipo;
    this->enunciado = enun;
    this->opciones = opciones;
    this->solucion = solucion;
}

Puzzle::~Puzzle()
{
    this->tipo = 0;
    this->enunciado = "";
    this->opciones = 0;
    this->solucion = 0;
}

unsigned short Puzzle::GetTipo()
{
    return tipo;
}

std::string Puzzle::GetEnunciado()
{
    return enunciado;
}

unsigned short Puzzle::GetOpciones()
{
    return opciones;
}

unsigned short Puzzle::GetSolucion()
{
    return solucion;
}

void Puzzle::AnyadirImgRespuesta(std::string img)
{
    imgRespuestas.push_back(move(img));
}

std::string Puzzle::GetImagen(unsigned short pos)
{
    return imgRespuestas.at(pos);
}