#ifndef Heavy_HPP
#define Heavy_HPP

#include "Jugador.hpp"

class Heavy : public Jugador
{
    public:
        Heavy(int nX,int nY,int nZ,int ancho,int largo,int alto,int accion);
        ~Heavy();

        void RenderAtaqueEsp(float updateTime, float drawTime);

};
#endif /* Heavy_HPP */