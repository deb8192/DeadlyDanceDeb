#include "pollo.hpp"

pollo::pollo()
{
    std::cout << "Con 1" << std::endl;
}

pollo::~pollo()
{

}

void pollo::Atacar()
{
    std::cout << "Ataque normal pollo" << std::endl;
}