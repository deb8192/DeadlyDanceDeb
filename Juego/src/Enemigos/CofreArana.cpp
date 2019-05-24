#include "CofreArana.hpp"
#include "../Personajes/Jugador.hpp"
#include "cmath"

CofreArana::CofreArana(float nX, float nY, float nZ, int maxVida,
    float anchoN, float altoN, float largoN, Sala* salaC)
: Enemigo(nX,nY,nZ,maxVida)
{
    funciona = true;
    atacado = false;
    _ordenes = new short [constantes.DOS];
    maxRotacion = constantes.PI_CUARTOS;
    rotation = constantes.CERO;

    _modelo = "assets/models/CofreArana/cofrearana_000001.obj";
    _textura = "assets/texture/cofreArana.png";
    fps = 70;
    _animacion = "assets/animaciones/CofreArana.xml";
    estadoMuerte = 5;

    ancho = anchoN;
    largo = largoN;
    alto = altoN;

    idCofre = -1;
    sala = salaC;
    activada = false;
    primeraVezActivada = false;
}

CofreArana::~CofreArana()
{
    funciona = false;
    atacado = false;

    delete[] _ordenes;
    _ordenes = nullptr;

    maxRotacion = 0;
    rotation = 0;

    _modelo = nullptr;
    _textura = nullptr;

    ancho = 0;
    largo = 0;
    alto = 0;

    idCofre=0;
    activada = false;
    primeraVezActivada = false;
}

/***************** RunIA *****************
 * Funcion que llama a recorrer el arbol
 * de del CofreArana comportamiento en Enemigo
 *
 * Entradas:
 *
 * Salidas:
*/
void CofreArana::RunIA()
{
    if(this->getTimeMerodear() <= 0)
    {
        if(modo == constantes.UNO)
        {
            if(_ordenes[0] != EN_PERSIGUE && _ordenes[0] != EN_ATACAR)
            {
                this->ForzarCambioNodo(&constantes.CUATRO);
            }
        }
        if(atacado)
        {
            atacado = false;
        }
        if(hecho)
        {
            hecho = false;
        }
        _ordenes = this->Enemigo::RunIA(funciona);
    }
}

/***************** UpdateCofreArana *****************
 * Funcion que llama a la funcion actual donde se
 * ha quedado la lectura del arbol del CofreArana
 *
 * Entradas:
 *      i: (sennala al CofreArana del array, NO NECESARIO APARENTEMENTE)
 * Salidas:
*/

void CofreArana::UpdateCofreArana(short *i, int* _jug, bool ayuda)
{
    Jugador* _jugador = (Jugador*)_jug;
    funciona = true;
    if(modo == MODO_ATAQUE && _ordenes != nullptr)
    {
        switch (_ordenes[0])
        {
            case EN_PERSIGUE: //se mueve el cofrearana
                _motor->cambiarAnimacion(5,*i,1);
                funciona = this->perseguir(_jug, i);
                break;

            case EN_ATACAR: //se mueve el cofrearana
                {
                    if(!atacado)
                    {
                        _motor->cambiarAnimacion(5,*i,4);

                        int danyo;
                        danyo = this->Atacar(*i);

                        if(danyo > 0)
                        {
                            _jugador->ModificarVida(-danyo);
                            funciona = true;
                            atacado = true;
                        }
                        else
                        {
                            funciona = false;
                        }
                    }
                }
                break;
        }
    }


    else if(modo == MODO_AUXILIAR_ALIADO)
    {
        this->AuxiliarAliado();
    }

    else if(_ordenes != nullptr)
    {
        switch (_ordenes[0])
        {
            case EN_VER: //El Pollo ve al jugador
                {
                    if(this->ver(constantes.UNO, constantes.SEIS * constantes.CINCO))
                    {
                        this->ver(constantes.DOS, constantes.SEIS * constantes.CINCO);
                        if(distanciaEnemigoJugador.modulo < distanciaEnemigoObstaculo.modulo)
                        {
                            funciona = true;
                        }
                        else
                        {
                            funciona = false;
                        }
                    }
                    else
                    {
                        funciona = false;
                    }
                }
                break;

                case EN_PIDE_AYUDA: //El Pollo pide ayuda
                {
                    modo = MODO_ATAQUE;
                    this->setTimeMerodear(constantes.CERO);
                    //cout<<"Pide ayuda a los aliados"<<endl;
                    this->PedirAyuda(ayuda);
                    funciona = true;
                }
                break;

                case EN_OIR: //El Pollo oye un enemigo pedir ayuda
                {
                    if(this->oir(constantes.DOS))
                    {
                        funciona = true;
                    }
                    else
                    {
                        funciona = false;
                    }
                }
                break;

                case EN_ACUDE_AYUDA: //El Pollo oye un enemigo pedir ayuda
                {
                    this->ContestarAyuda();
                }
                break;

            case EN_MERODEA: //El Pollo merodea
                {
                    //this->ver(constantes.DOS, constantes.SEIS * constantes.CINCO);
                    if(!hecho)
                    {
                        //Merodea estableciendo un nuevo angulo de rotacion
                        if(!controlRotacion)
                        {
                            this->setRotation(this->randomBinomial() * maxRotacion);
                        }
                        this->Merodear(i);
                        this->setTimeMerodear(1.5f);
                        hecho = true;
                        //Comprueba si ve al jugador para atacarle en caso necesario
                        if(this->ver(constantes.UNO, constantes.SEIS * constantes.CINCO))
                        {
                            if(distanciaEnemigoJugador.modulo < distanciaEnemigoObstaculo.modulo)
                            {
                                modo = MODO_ATAQUE;
                                porcentajeVelocidad = constantes.UNO;
                                this->setTimeMerodear(constantes.CERO);
                                //cout<<"Pide ayuda a los aliados"<<endl;
                                this->PedirAyuda(ayuda);
                                funciona = true;
                            }
                        }
                        else if(this->oir(constantes.DOS))
                        {
                            this->ContestarAyuda();
                        }
                    }
                    else
                    {
                        //Merodea poniendo en positivo o negativo el angulo actual de rotacion
                        if(!controlRotacion)
                        {
                            int rota = rand() % 3 - 1;
                            if (rota != 0)
                            {
                                rotation *= rota;
                            }
                        }
                        this->Merodear(i);
                        //Comprueba si ve al jugador para atacarle en caso necesario
                        if(this->ver(constantes.UNO, constantes.SEIS * constantes.CINCO))
                        {
                            if(distanciaEnemigoJugador.modulo < distanciaEnemigoObstaculo.modulo)
                            {
                                modo = MODO_ATAQUE;
                                porcentajeVelocidad = constantes.UNO;
                                this->setTimeMerodear(constantes.CERO);
                                //cout<<"Pide ayuda a los aliados"<<endl;
                                this->PedirAyuda(ayuda);
                                funciona = true;
                            }
                        }
                        else if(this->oir(constantes.DOS))
                        {
                            this->ContestarAyuda();
                        }
                    }
                    funciona = true;
                }
                break;

            default:
                break;
        }
    }
}

void CofreArana::SetNuevasOrdenes(short newOrden)
{
    _ordenes[0] = newOrden;
}

float CofreArana::GetAncho()
{
    return ancho;
}

float CofreArana::GetAlto()
{
    return alto;
}

float CofreArana::GetLargo()
{
    return largo;
}

int CofreArana::GetIdCofre()
{
    return idCofre;
}

unsigned int CofreArana::GetPosMotorCofre()
{
    return posMotorCofre;
}

unsigned int CofreArana::GetPosObsCofre()
{
    return posObsCofre;
}

unsigned int CofreArana::GetPosArana()
{
    return posArana;
}

bool CofreArana::GetActivada()
{
    return activada;
}

bool CofreArana::GetPrimeraVezActivada()
{
    return primeraVezActivada;
}

void CofreArana::SetIdCofre(int idC)
{
    idCofre = idC;
}

void CofreArana::SetPosMotorCofre(unsigned int pos)
{
    posMotorCofre = pos;
}

void CofreArana::SetPosObsCofre(unsigned int pos)
{
    posObsCofre = pos;
}

void CofreArana::SetPosArana(unsigned int pos)
{
    posArana = pos;
}

void CofreArana::SetActivada(bool estado)
{
    activada = estado;
}

void CofreArana::SetPrimeraVezActivada(bool estado)
{
    primeraVezActivada = estado;
}