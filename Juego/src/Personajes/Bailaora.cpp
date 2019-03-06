#include "Bailaora.hpp"
#include "../ConstantesComunes.hpp"

Bailaora::Bailaora(int nX,int nY,int nZ,int ancho,int largo,int alto,int accion,int maxVida)
: Jugador(nX,nY,nZ,ancho,largo,alto,accion,maxVida)
{
    // TO DO: cambiar por las suyas
    _modelo = "assets/models/rockero.b3d";
}

Bailaora::~Bailaora()
{
    _modelo = nullptr;
}

//Si el ataque especial es el de la Bailaora, es circular a distancia
void Bailaora::armaAtacarEspecialUpd()
{
    Constantes constantes;
    //Formula de ataque circular aumentando la distancia
    incrAtDisCirc += 1.5;
    atespz = this->getZ();
    atespz += (incrAtDisCirc * cos(constantes.PI * atgy / constantes.PI_RADIAN));
    atespx = this->getX();
    atespx += (incrAtDisCirc * sin(constantes.PI * atgy / constantes.PI_RADIAN));
    atespposZ = atespz - this->getZ();
    atespposX = atespx - this->getX();
    _armaEspecial->setPosicionesFisicas(atespposZ, 0.0f, atespposZ);

    //Aumento de la rotacion hacia la izquierda.
    atgy += 30;

    if(atgy >= 360.0)
    {
        atgy -= 360.0;
    }
    else if(atgy < 0.0)
    {
        atgy += 360;
    }

    _armaEspecial->setNewPosiciones(atespx, this->getY(), atespz);
    _armaEspecial->setNewRotacion(getRX(), atgy, getRZ());
}

/*************** AtacarEspecialUpdate *****************
 *  Funcion que actualiza la posicion y
 *  la colision del ataque especial
 *      Entradas: int danyo y vector<Enemigo*> _getEnemigos
 *      Salidas:
 */
void Bailaora::AtacarEspecialUpdate(int* danyo, std::vector<Enemigo*> &_getEnemigos)
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
void Bailaora::AtacarEspecialUpdate(int* danyo, Enemigo* &_boss)
{
    armaAtacarEspecialUpd();
    atacarEspUpdBossComun(danyo, _boss);
}

void Bailaora::RenderAtaqueEsp(float updateTime, float drawTime)
{
    getArmaEspecial()->moverseEntidad(1 / updateTime);
    getArmaEspecial()->RotarEntidad(1 / updateTime);
    getArmaEspecial()->UpdateTimeMove(drawTime);

    _motor->mostrarArmaEspecial(
        GetDatosAtEsp()[0],
        GetDatosAtEsp()[1],
        GetDatosAtEsp()[2],
        GetDatosAtEsp()[3],
        GetDatosAtEsp()[4],
        GetDatosAtEsp()[5]);

    _motor->dibujarObjetoTemporal(
        getArmaEspecial()->getFisX()*2,
        getArmaEspecial()->getY(),
        getArmaEspecial()->getFisZ()*2,
        GetDatosAtEsp()[3],
        GetDatosAtEsp()[4],
        GetDatosAtEsp()[5],
        8,
        1,
        8,
        3);
}