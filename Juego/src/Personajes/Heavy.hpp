#ifndef Heavy_HPP
#define Heavy_HPP

#include "Jugador.hpp"

class Heavy : public Jugador
{
    public:
        Heavy(unsigned short tipoJug,int nX,int nY,int nZ,int ancho,int largo,int alto,int accion, int maxVida);
        ~Heavy();

        
        void AtacarEspecialUpdate(int* danyo, vector<Enemigo*> &_getEnemigos);
        void AtacarEspecialUpdate(int* danyo, Enemigo* &_boss);
        void RenderAtaqueEsp(float updateTime, float drawTime);

    private:
        void armaAtacarEspecialUpd();
};
#endif /* Heavy_HPP */