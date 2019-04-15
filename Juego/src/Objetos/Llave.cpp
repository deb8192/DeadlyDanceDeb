#include "Llave.hpp"

Llave::Llave()
{

}

Llave::Llave(int codigo)
{
    codigoPuerta = codigo;
}

int Llave::GetCodigoPuerta()
{
    return codigoPuerta;
}