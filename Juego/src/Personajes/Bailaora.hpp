#ifndef Bailaora_HPP
#define Bailaora_HPP

#include "Jugador.hpp"

class Bailaora : public Jugador
{
    public:
        Bailaora(int nX,int nY,int nZ, int ancho, int largo, int alto, int accion);
        ~Bailaora();

        void RenderAtaqueEsp(float updateTime, float drawTime);
};
#endif /* Bailaora_HPP */