#include "Heavy.hpp"
#include "../ConstantesComunes.hpp"

Heavy::Heavy(int nX,int nY,int nZ,int ancho,int largo,int alto,int accion, int maxVida)
: Jugador(nX,nY,nZ,ancho,largo,alto,accion,maxVida)
{
    _modelo = "assets/models/rockero.b3d";
}

Heavy::~Heavy()
{
    _modelo = nullptr;
}

//Si el ataque especial es el del Heavy, es cuerpo a cuerpo
void Heavy::armaAtacarEspecialUpd()
{
    Constantes constantes;
    int distancia = 5;
    //Calculo de la posicion del arma delante  int getAnimacion();del jugador
    atespx = distancia * sin(constantes.PI * this->getRY() / constantes.PI_RADIAN) + this->getX();
    atespz = distancia * cos(constantes.PI * this->getRY() / constantes.PI_RADIAN) + this->getZ();
    _armaEspecial->initPosicionesFisicas(atespx/2, this->getY()/2, atespz/2);
    _armaEspecial->setNewPosiciones(atespx, this->getY(), atespz);
    _armaEspecial->setNewRotacion(getRX(), this->getRY(), getRZ());
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

/*************** AtacarEspecialUpdate *****************
 *  Funcion que actualiza la posicion y
 *  la colision del ataque especial
 *      Entradas: int danyo y Enemigo* _boss
 *      Salidas:
 */
void Heavy::AtacarEspecialUpdate(int* danyo, Enemigo* &_boss)
{
    armaAtacarEspecialUpd();
    atacarEspUpdBossComun(danyo, _boss);
}

void Heavy::RenderAtaqueEsp(float updateTime, float drawTime)
{
    getArmaEspecial()->moverseEntidad(1 / updateTime);
    getArmaEspecial()->RotarEntidad(1 / updateTime);
    getArmaEspecial()->UpdateTimeMove(drawTime);

    _motor->mostrarArmaEspecial(
        GetDatosAtEsp()[0],
        getY(),
        GetDatosAtEsp()[2],
        getRX(),
        getRY(),
        getRZ());

    _motor->dibujarObjetoTemporal(
        getArmaEspecial()->getFisX()*2,
        getY(),
        getArmaEspecial()->getFisZ()*2,
        getRX(),
        getRY(),
        getRZ(),
        8,
        1,
        8,
        2);
}