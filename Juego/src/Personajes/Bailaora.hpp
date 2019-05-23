#ifndef Bailaora_HPP
#define Bailaora_HPP

#include "Jugador.hpp"

class Bailaora : public Jugador
{
    public:
        Bailaora(Sala* sala,unsigned short tipoJug,int nX,int nY,int nZ, int ancho, int largo, int alto, int accion, int maxVida);
        ~Bailaora();

        void AtacarEspecialUpdate(int* danyo, vector<Enemigo*> &_getEnemigos);
        void AtacarEspecialUpdate(int* danyo, Enemigo* &_boss);
        void RenderAtaqueEsp(float updateTime, float drawTime);
        void resetContador();

        private:
            void armaAtacarEspecialUpd();
};
#endif /* Bailaora_HPP */
