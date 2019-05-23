#include "Heavy.hpp"

Heavy::Heavy(Sala* sala,unsigned short tipoJug,int nX,int nY,int nZ,int ancho,int largo,int alto,int accion, int maxVida)
: Jugador(sala,tipoJug,nX,nY,nZ,ancho,largo,alto,accion,maxVida)
{
    #ifdef WEMOTOR
        _modelo = "assets/models/rockero/rockero_rigging_000001.obj";
        escalado = 1.75f;
        fps = 128;
        _textura = "assets/texture/HeavyTex.png";
        _animacion = "assets/animaciones/rockero.xml";
    #else
        _modelo = "assets/models/rockero.b3d";
    #endif
}

Heavy::~Heavy()
{
    _modelo = nullptr;
}

//Si el ataque especial es el del Heavy, es cuerpo a cuerpo
void Heavy::armaAtacarEspecialUpd()
{
    int distancia = 5;
    //Calculo de la posicion del arma delante  int getAnimacion();del jugador
    if(contadortime > 0.0f && contadortime <= 0.1f)
    {
        atespx = distancia * sin(constantes.PI * this->getRY() / constantes.PI_RADIAN) + this->getX();
        atespz = distancia * cos(constantes.PI * this->getRY() / constantes.PI_RADIAN) + this->getZ();
        _armaEspecial->setNewRotacion(getRX(), this->getRY(), getRZ());
    }
    _armaEspecial->initPosicionesFisicas(atespx/2, this->getY()/2, atespz/2);
    _armaEspecial->setNewPosiciones(atespx, this->getY() + new_pos_y, atespz);
}

/*************** AtacarEspecialUpdate *****************
 *  Funcion que actualiza la posicion y
 *  la colision del ataque especial
 *      Entradas: int danyo y vector<Enemigo*> _getEnemigos
 *      Salidas:
 */
void Heavy::AtacarEspecialUpdate(int* danyo, std::vector<Enemigo*> &_getEnemigos)
{
    armaAtacarEspecialUpd();
    atacarEspUpdComun(danyo, _getEnemigos);
}

void Heavy::RenderAtaqueEsp(float updateTime, float drawTime)
{
    if(contadortime < 1.5f)
    {
        contadortime += drawTime;
        if(contadortime > 1.5f)contadortime = 1.5f;
        if(new_pos_y > 0)new_pos_y--;
    }

    _armaEspecial->moverseEntidad(1 / updateTime);
    _armaEspecial->RotarEntidad(1 / updateTime);
    _armaEspecial->UpdateTimeMove(drawTime);

    _motor->mostrarArmaEspecial(
        _armaEspecial->getX(), _armaEspecial->getY() + new_pos_y, _armaEspecial->getZ(),
        _armaEspecial->getRX(), _armaEspecial->getRY(), _armaEspecial->getRZ());

    _motor->dibujarObjetoTemporal(
        _armaEspecial->getFisX()*2, _armaEspecial->getY(),_armaEspecial->getFisZ()*2,
        _armaEspecial->getRX(), _armaEspecial->getRY(), _armaEspecial->getRZ(),
        8, 1, 8, 2);
}

void Heavy::resetContador()
{
    contadortime = 0.0f;
    new_pos_y = 15.0f;
}
