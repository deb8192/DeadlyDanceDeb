#include "TravornioBoss.hpp"
#include "../Personajes/Jugador.hpp"
#include "cmath"

TravornioBoss::TravornioBoss(float nX, float nY, float nZ, int maxVida)
: Enemigo(nX,nY,nZ,maxVida)
{
    funciona = true;
    atacado = false;
    ataqueEspecial = false;
    seAcerca = false;
    _ordenes = new short [constantes.DOS];
    maxRotacion = constantes.PI_CUARTOS;
    rotation = constantes.CERO;
    direccion = 0;
    maxDistanciaJugador = 30;
    minDistanciaJugador = 15;

    estadoMuerte = 8;
    _modelo = "assets/models/Travornio/travornio_000001.obj";
    _textura = "";
    fps = 150;
    _animacion = "assets/animaciones/Unicornio.xml";
    escalado = 0.50f;//es muy grande, por eso se escala
}

TravornioBoss::~TravornioBoss()
{
    funciona = false;
    atacado = false;
    ataqueEspecial = false;
    seAcerca = false;
    delete[] _ordenes;
    _ordenes = nullptr;
    maxRotacion = 0;
    rotation = 0;
    direccion = 0;
    maxDistanciaJugador = 0;
    minDistanciaJugador = 0;
    _modelo = nullptr;
    _textura = nullptr;
}

/***************** RunIA *****************
 * Funcion que llama a recorrer el arbol
 * de TravornioBoss comportamiento en Enemigo
 *
 * Entradas:
 *
 * Salidas:
*/
void TravornioBoss::RunIA()
{
    Constantes constantes;
    if(this->getTimeMoverse() <= 0 && this->getTimeAt() <= 0 && this->getTimeDefenderse() <= 0 && this->getTimeAtEsp() <= 0)
    {
        if(this->getDefenderse())
        {
            this->setDefenderse(false);
        }
        if(atacado)
        {
            atacado = false;
        }
        if(hecho)
        {
            hecho = false;
        }
        if(seAcerca)
        {
            seAcerca = false;
        }
        if(ataqueEspecial)
        {
            ataqueEspecial = false;
            _motor->cambiarAnimacion(5,0,7);
        }
        _ordenes = this->Enemigo::RunIA(funciona);
    }
}

/***************** UpdateTravornioBoss *****************
 * Funcion que llama a la funcion actual donde se
 * ha quedado la lectura del arbol del TravornioBoss
 *
 * Entradas:
 *      i: sennala al enemigo del array
 * Salidas:
*/

void TravornioBoss::UpdateTravornioBoss(short *i, int* _jug, bool ayuda)
{
    Constantes constantes;
    Jugador* _jugador = (Jugador*)_jug;
    funciona = true;
    int porcentaje_50 = this->getVidaIni() * constantes.MAX_VIDA_BOSS_PELIGRO / constantes.CIEN;
    if(this->getVida() <= porcentaje_50 && modo != MODO_PELIGRO)
    {
        SetModo(MODO_PELIGRO);
        this->ForzarCambioNodo(&constantes.SIETE);
    }
    
    if(_ordenes != nullptr)
    {
        switch (_ordenes[0])
        {
            case EN_COMPROBAR: //Comprueba distintas condiciones del enemigo como su vida
                {
                    switch (_ordenes[1])
                    {
                        case EN_MAX_VIDA_33:
                            {
                                porcentaje_50 = this->getVidaIni() * constantes.MAX_VIDA_BOSS_PELIGRO / constantes.CIEN;
                                if(this->getVida() <= porcentaje_50)
                                {
                                    funciona = true;
                                }
                                else {funciona = false;}
                            }
                            break;
                        case EN_NORMAL:
                            if(this->GetModo() == MODO_DEFAULT)
                            {
                                funciona = true;
                            }
                            else {funciona = false;}
                            break;
                        case EN_PELIGRO:
                            if(this->GetModo() == MODO_PELIGRO)
                            {
                                funciona = true;
                            }
                            else {funciona = false;}
                            break;
                        case EN_ATAQUE_ESPECIAL:
                            if(this->getBarraAtEs() == constantes.CIEN)
                            {
                                funciona = true;
                            }
                            else {funciona = false;}
                            break;
                        default:
                            funciona = false;
                            break;
                    }
                }
                break;
            case EN_CAMBIAR:    //Cambia el modo del boss
                switch (_ordenes[1])
                {
                    case EN_PELIGRO:
                            this->SetModo(MODO_PELIGRO);
                        break;
                
                    default:
                            this->SetModo(MODO_DEFAULT);
                        break;
                }
            case EN_ATAQUE_ESPECIAL:    //El boss realiza uno de sus ataques especiales
                switch (_ordenes[1])
                {
                    case EN_AT_ESP_2:
                    {
                        bool nuevaDireccion = false;
                        if(this->getTimeAtEsp() <= 0 && !ataqueEspecial)
                        {
                            _motor->cambiarAnimacion(5,*i,5);
                            this->setTimeAtEsp(constantes.TIEMPO_ATESP_TRAVORNIO);
                            ataqueEspecial = true;
                            nuevaDireccion = true;
                        }
                        this->ataqueRebote(nuevaDireccion, _jug);   //TO DO: tener en cuenta las colisiones con la pared
                        float resto = (float) ((int) (this->getTimeAt() * constantes.CIEN) % (int) (constantes.UN_CUARTO * constantes.CIEN)) / constantes.CIEN;
                        if(resto <= constantes.DIEZ_PORCIENTO)
                        {
                            int danyo = this->AtacarEspecial();

                            if(danyo > 0)
                            {
                                _jugador->ModificarVida(-danyo);
                            }
                            this->setTimeAtEsp(this->getTimeAtEsp() - resto);
                        }
                        //funciona = true;
                        /* ataque especial 1 */
                    }
                        break;
                
                    default:
                        SetRespawnBoss(true);
                        this->setBarraAtEs(constantes.CERO);
                        _motor->cambiarAnimacion(5,*i,3);
                        /* Llamar animacion pedir ayuda */
                        break;
                }
                break;
            case EN_ATACAR: //El boss ataca
                {
                    bool nuevaDireccion = false;
                    if(this->getTimeAt() <= 0 && !atacado)
                    {
                        _motor->cambiarAnimacion(5,0,4);
                        this->setTimeAt(constantes.DOS);
                        atacado = true;
                        nuevaDireccion = true;
                    }
                    this->embestir(nuevaDireccion, _jug);
                    float resto = (float) ((int) (this->getTimeAt() * constantes.CIEN) % (int) (constantes.UN_CUARTO * constantes.CIEN)) / constantes.CIEN;
                    if(resto <= constantes.DIEZ_PORCIENTO)
                    {
                        int danyo = this->Atacar(*i);

                        if(danyo > 0)
                        {
                            _jugador->ModificarVida(-danyo);
                        }
                        this->setTimeAt(this->getTimeAt() - resto);
                    }
                    funciona = true;
                }
                break;
            case EN_MOVERSE: //El boss se mueve tanteando al jugador
                {
                    int nuevaDireccion = 0;
                    if(!hecho)
                    {
                        //Moverse estableciendo una direccion de movimiento 
                        nuevaDireccion = rand() % 8 + 1;       
                        direccion = this->Moverse(nuevaDireccion, direccion, _jug, minDistanciaJugador, maxDistanciaJugador, &seAcerca);
                        nuevaDireccion = 0;
                        this->setTimeMoverse(1.5f);
                        hecho = true;
                    }
                    else
                    { 
                        //Se desplaza y cambia la direccion cada medio segundo de tiempo
                        if(this->getTimeMoverse() > 0)
                        {
                            float resto = (float) ((int) (this->getTimeMoverse() * constantes.CIEN) % (int) (constantes.UN_MEDIO * constantes.CIEN)) / constantes.CIEN;
                            if(resto <= constantes.DIEZ_PORCIENTO)
                            {
                                nuevaDireccion = rand() % 8 + 1;    
                                this->setTimeMoverse(this->getTimeMoverse() - resto);
                            }
                        }
                        direccion = this->Moverse(nuevaDireccion, direccion, _jug, minDistanciaJugador, maxDistanciaJugador, &seAcerca);
                        nuevaDireccion = 0;
                    }
                    funciona = true;
                }
                break;
            case EN_DEFENDERSE: //El boss se defiende
                {
                    VectorEspacial posJugador;
                    posJugador.vX = _jugador->getX();
                    posJugador.vY = _jugador->getY();
                    posJugador.vZ = _jugador->getZ();
                    if(this->getTimeDefenderse() <= 0)
                    {
                        this->setTimeDefenderse(constantes.TIEMPO_DEFENSA);
                        this->setDefenderse(true);
                        _motor->cambiarAnimacion(5,*i,2);
                    }
                    this->alinearse(&posJugador, false);
                    funciona = true;
                }
            default:
                break;
        }
    }
}

void TravornioBoss::SetNuevasOrdenes(short newOrden)
{
    _ordenes[0] = newOrden;
}
