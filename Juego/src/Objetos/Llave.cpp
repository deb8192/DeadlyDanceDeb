#include "Llave.hpp"

Llave::Llave()
{

}

Llave::Llave(int codigo)
{
    codigoPuerta = codigo;
}

Llave::~Llave()
{
    codigoPuerta = 0;
}

int Llave::GetCodigoPuerta()
{
    return codigoPuerta;
}