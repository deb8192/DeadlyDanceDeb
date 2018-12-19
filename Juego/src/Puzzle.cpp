#include "Puzzle.hpp"

Puzzle::Puzzle()
{
    tipo = 1;
    enunciado = "";
    opciones = 0;
    solucion = 0;
}

Puzzle::Puzzle(short tipo, std::string e, short opciones, short solucion)
{
    this->tipo = tipo;
    this->enunciado = e;
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

short Puzzle::GetTipo()
{
    return tipo;
}

std::string Puzzle::GetEnunciado()
{
    return enunciado;
}

short Puzzle::GetOpciones()
{
    return opciones;
}

short Puzzle::GetSolucion()
{
    return solucion;
}

bool Puzzle::CorregirSolucion(short solucion)
{
    if (this->solucion != solucion)
    {
        return false;
    }
    return true;
}

void Puzzle::AnyadirImgRespuesta(std::string img)
{
    imgRespuestas.push_back(img);
}

std::string Puzzle::GetImagen(short pos)
{
    return imgRespuestas.at(pos);
}