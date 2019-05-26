#include "Bailaora.hpp"

Bailaora::Bailaora(Sala* sala,unsigned short tipoJug,int nX,int nY,int nZ,int ancho,int largo,int alto,int accion,int maxVida)
: Jugador(sala,tipoJug,nX,nY,nZ,ancho,largo,alto,accion,maxVida)
{
    // TO DO: cambiar por las suyas
    #ifdef WEMOTOR
        _modelo = "assets/models/bailarina/bailarina_000001.obj";
        escalado = 0.55f;
        fps = 268;
        _textura = "assets/texture/bailarina.png";
        _animacion = "assets/animaciones/bailarina.xml";
        
        modelosArmas[0]= "assets/models/Armas/Bailarina/Guitarra1/Guitarra1_000001.obj";
        fpsArmas[0] = 24;
        texturasArmas[0] = "assets/texture/guitarra-1.png";
        animacionesArmas[0] = "assets/animaciones/BGuitarra1.xml";

        modelosArmas[1]= "assets/models/Armas/Bailarina/Guitarra2/Guitarra2_000001.obj";
        fpsArmas[1] = 24;
        texturasArmas[1] = "assets/texture/guitarra-2.png";
        animacionesArmas[1] = "assets/animaciones/BGuitarra1.xml";

        modelosArmas[2]= "assets/models/Armas/Bailarina/Guitarra3/Guitarra3_000001.obj";
        fpsArmas[2] = 24;
        texturasArmas[2] = "assets/texture/guitarra-3.png";
        animacionesArmas[2] = "assets/animaciones/BGuitarra1.xml";

        modelosArmas[3]= "assets/models/Armas/Bailarina/Flauta1/Flauta1_000001.obj";
        fpsArmas[3] = 15;
        texturasArmas[3] = "assets/texture/flauta-1.png";
        animacionesArmas[3] = "assets/animaciones/BFlauta1.xml";

        modelosArmas[4]= "assets/models/Armas/Bailarina/Flauta2/Flauta2_000001.obj";
        fpsArmas[4] = 15;
        texturasArmas[4] = "assets/texture/flauta-2.png";
        animacionesArmas[4] = "assets/animaciones/BFlauta1.xml";

        modelosArmas[5]= "assets/models/Armas/Bailarina/Flauta3/Flauta3_000001.obj";
        fpsArmas[5] = 15;
        texturasArmas[5] = "assets/texture/flauta-3.png";
        animacionesArmas[5] = "assets/animaciones/BFlauta1.xml";

        modelosArmas[6]= "assets/models/Armas/Bailarina/Arpa1/Arpa1_000001.obj";
        fpsArmas[6] = 22;
        texturasArmas[6] = "assets/texture/arpa-1.png";
        animacionesArmas[6] = "assets/animaciones/BArpa1.xml";

        modelosArmas[7]= "assets/models/Armas/Bailarina/Arpa2/Arpa2_000001.obj";
        fpsArmas[7] = 22;
        texturasArmas[7] = "assets/texture/arpa-2.png";
        animacionesArmas[7] = "assets/animaciones/BArpa1.xml";

        modelosArmas[8]= "assets/models/Armas/Bailarina/Arpa3/Arpa3_000001.obj";
        fpsArmas[8] = 22;
        texturasArmas[8] = "assets/texture/arpa-3.png";
        animacionesArmas[8] = "assets/animaciones/BArpa1.xml";
        

        _rutaArmaEspecial = "assets/models/Armas/Especiales/castanyuela.obj";
        _rutaTexturaArmaEspecial = "assets/texture/castanyuela.png";

    #else
        _modelo = "assets/models/bailarina/bailarina_000001.obj";
    #endif
}

Bailaora::~Bailaora()
{
    _modelo = nullptr;
}

//Si el ataque especial es el de la Bailaora, es circular a distancia
void Bailaora::armaAtacarEspecialUpd()
{
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

    /*if(atgy >= 360.0)
    {
        atgy -= 360.0;
    }
    else if(atgy < 0.0)
    {
        atgy += 360;
    }*/

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

void Bailaora::RenderAtaqueEsp(float updateTime, float drawTime)
{
    _armaEspecial->moverseEntidad(1 / updateTime);
    _armaEspecial->RotarEntidad(1 / updateTime);
    _armaEspecial->UpdateTimeMove(drawTime);

    _motor->mostrarArmaEspecial(
        _armaEspecial->getX(), _armaEspecial->getY(), _armaEspecial->getZ(),
        _armaEspecial->getRX(), _armaEspecial->getRY(), _armaEspecial->getRZ());

    _motor->dibujarObjetoTemporal(
        _armaEspecial->getFisX()*2, _armaEspecial->getY(),_armaEspecial->getFisZ()*2,
        _armaEspecial->getRX(), _armaEspecial->getRY(), _armaEspecial->getRZ(),
        8, 1, 8, 3);
}

void Bailaora::resetContador()
{
    
}
