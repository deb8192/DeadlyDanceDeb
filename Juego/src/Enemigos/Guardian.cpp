#include "Guardian.hpp"
#include "../ConstantesComunes.hpp"
#include "../Personajes/Jugador.hpp"
#include "cmath"

Guardian::Guardian(float nX, float nY, float nZ, int maxVida, int disfraz)
: Enemigo(nX,nY,nZ,maxVida)
{
    funciona = true;
    seAcerca = false;
    atacado = hecho = escondido = false;
    _ordenes = new short [constantes.DOS];
    maxRotacion = constantes.PI_CUARTOS / constantes.TRES;
    rotation = constantes.CERO;
    zonaElegida = nullptr;
    zonaSeleccionada = false;
    maxDistanciaJugador = 30;
    minDistanciaJugador = 15;
    direccion = 0;

    switch(disfraz)
    {
        case 3 :
            _modelo = "assets/models/guardian_m/GuardianMuerteConTextura.obj";
            _textura = "assets/models/guardian_m/trocitos_G_M_prueba.jpg";
            break;
            //Cambiar por unicornio
        case 4 :
            _modelo = "assets/models/guardian_m/GuardianMuerteConTextura.obj";
            _textura = "assets/models/guardian_m/trocitos_G_M_prueba.jpg";
            break;
    }
}

Guardian::~Guardian()
{
    delete[] _ordenes;
    _ordenes = nullptr;
    _modelo = nullptr;
    _textura = nullptr;
    maxDistanciaJugador = 0;
    minDistanciaJugador = 0;
    direccion = 0;
}

/***************** RunIA *****************
 * Funcion que llama a recorrer el arbol
 * de del Guardian comportamiento en Enemigo
 *
 * Entradas:
 *
 * Salidas:
*/
void Guardian::RunIA()
{
    if(modo == MODO_HUIDA)
    {
        else if(_ordenes[0] != EN_PERSIGUE && _ordenes[0] != EN_ATACAR && _ordenes[0] != EN_DEFENDERSE  && _ordenes[0] != EN_MOVERSE)
        {
            this->ForzarCambioNodo(&constantes.DIEZ);
        }
    }
    else if(modo == MODO_ATAQUE)
    {
        else if(_ordenes[0] != EN_PERSIGUE && _ordenes[0] != EN_ATACAR && _ordenes[0] != EN_DEFENDERSE)
        {
            this->ForzarCambioNodo(&constantes.VEINTE);
        }
    }
    if(this->getTimeMerodear() <= 0)
    {
        if(atacado)
        {
            atacado = false;
        }
        if(hecho)
        {
            hecho = false;
        }
        if(modo == MODO_BUSCAR_ESCONDITE)
        {
            this->SetNuevasOrdenes(EN_BUSCA);
            this->SetNuevosObjetivos(EN_ESCONDITE);
        }
        else
        {
            _ordenes = this->Enemigo::RunIA(funciona);
            forzadoCambio = false;
        }
    }
}

/***************** UpdateGuardian *****************
 * Funcion que llama a la funcion actual donde se
 * ha quedado la lectura del arbol del Guardian
 *
 * Entradas:
 *      i: (sennala al Guardian del array, NO NECESARIO APARENTEMENTE)
 * Salidas:
*/

void Guardian::UpdateGuardian(short *i, int* _jug, std::vector<ZonaEscondite*> &_getZonasEscondite)
{
    Jugador* _jugador = (Jugador*)_jug;
    funciona = true;

    if(_ordenes != nullptr)
    {
        switch (_ordenes[0])
        {
            case EN_VER: //El Pollo ve al jugador
                {
                    switch(_ordenes[1])
                    {
                        case EN_JUGADOR:
                            if(this->ver(constantes.UNO, constantes.NUEVE * constantes.DIEZ))
                            {
                                this->ver(constantes.DOS, constantes.NUEVE * constantes.DIEZ);
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
                }
                break;
            case EN_NO_VER:
                {
                    VectorEspacial posJugador;
                    posJugador.vX = _jugador->getX();
                    posJugador.vY = _jugador->getY();
                    posJugador.vZ = _jugador->getZ();
                    this->alinearse(&posJugador, false);
                    if(this->ver(constantes.UNO, constantes.NUEVE * constantes.DIEZ))
                    {
                        funciona = false;
                        this->setTimeOcultarse(1.5f);
                    }
                    else
                    {
                        if(this->getTimeOcultarse() <= 0)
                        {
                            funciona = true;
                        }
                        else
                        {
                            funciona = false;
                        }

                    }
                }
                break;
            case EN_NO_OIR:
                {
                    VectorEspacial posJugador;
                    posJugador.vX = _jugador->getX();
                    posJugador.vY = _jugador->getY();
                    posJugador.vZ = _jugador->getZ();
                    this->alinearse(&posJugador, false);
                    if(this->oir(constantes.UNO))
                    {
                        funciona = false;
                        this->setTimeOcultarse(1.5f);
                    }
                    else
                    {
                        if(this->getTimeOcultarse() <= 0)
                        {
                            funciona = true;
                        }
                        else
                        {
                            funciona = false;
                        }

                    }
                }
                break;
            case EN_ATRAVESAR:
                switch(_ordenes[1])
                {
                    case EN_ULTIMA_PUERTA:
                        if(!puertasAtravesadas.empty())
                        {
                            funciona = false;
                        }
                        break;
                    case EN_PUERTA:
                        /*if(!puertasAtravesadas.empty())
                        {
                            funciona = this->buscar(&puertasAtravesadas.top());
                        }*/
                        break;
                }
                break;
            case EN_CAMBIAR:
            {
                switch(_ordenes[1])
                {
                    case EN_PELIGRO:

                        modo = MODO_HUIDA;
                        if(zonaElegida !=nullptr)
                        {
                            zonaElegida->setProposito(false);
                            zonaElegida = nullptr;
                        }
                        if(escondido)
                        {
                            escondido = false;
                        }
                        funciona = true;

                        break;
                    case EN_ATAQUE:

                        modo = MODO_ATAQUE;
                        if(zonaElegida !=nullptr)
                        {
                            zonaElegida->setProposito(false);
                            zonaElegida = nullptr;
                        }
                        if(escondido)
                        {
                            escondido = false;
                        }
                        funciona = true;

                        break;
                    case EN_OCULTACION:

                        modo = MODO_OCULTACION;
                        if(zonaElegida !=nullptr)
                        {
                            zonaElegida->setProposito(false);
                            zonaElegida = nullptr;
                        }
                        if(escondido)
                        {
                            escondido = false;
                        }
                        funciona = true;

                        break;
                    case EN_NORMAL:

                        modo = MODO_DEFAULT;
                        if(zonaElegida !=nullptr)
                        {
                            zonaElegida->setProposito(false);
                            zonaElegida = nullptr;
                        }
                        if(escondido)
                        {
                            escondido = false;
                        }
                        funciona = true;

                        break;
                }
            }
            break;
            case EN_COMPROBAR:
            {
                switch (_ordenes[1])
                {
                    case EN_PELIGRO:

                        if(modo == MODO_HUIDA)
                        {
                            funciona = true;
                        }
                        else
                        {
                            funciona = false;
                        }
                        break;
                    case EN_ATAQUE:

                        if(modo == MODO_ATAQUE)
                        {
                            //cout<<"EL SEÑOR GUARDIAN ESTA EN MODO ATAQUE"<<endl;
                            funciona = true;
                        }
                        else
                        {
                            funciona = false;
                        }
                        break;
                    case EN_OCULTACION:

                        if(modo == MODO_OCULTACION)
                        {
                            funciona = true;
                        }
                        else
                        {
                            funciona = false;
                        }
                        break;
                }
            }
            break;
            case EN_PERSIGUE: //El Guardian se persigue al jugador
                {
                    funciona = this->perseguir(_jug, i);
                }
                break;

            case EN_ATACAR: //El Guardian ataca
                {
                    //cout<<"ataca guardian"<<endl;
                    if(!atacado)
                    {
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
                    else
                    {
                        funciona = false;
                    }
                }
                break;
            case EN_MOVERSE: //El guardian se mueve tanteando al jugador
                {
                    int nuevaDireccion = 0;
                    if(!hecho)
                    {
                        //Moverse estableciendo una direccion de movimiento 
                        nuevaDireccion = rand() % 8 + 1;       
                        direccion = this->Moverse(nuevaDireccion, direccion, _jug, minDistanciaJugador, maxDistanciaJugador, &seAcerca);
                        nuevaDireccion = 0;
                        this->setTimeMoverse(1.0f);
                        hecho = true;
                    }
                    else
                    { 
                        //Se desplaza y cambia la direccion cada medio segundo de tiempo
                        if(this->getTimeMoverse() > 0)
                        {
                            float resto = (float) ((int) (this->getTimeMoverse() * constantes.CIEN) % (int) (constantes.UN_CUARTO * constantes.CIEN)) / constantes.CIEN;
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
                    }
                    this->alinearse(&posJugador, false);
                    funciona = true;
                }
                break;
            case EN_OIR: //El Guardian oye algo
                    if(this->oir(constantes.UNO))
                    {
                        funciona = true;
                    }
                    else
                    {
                        funciona = false;
                    }
                break;

            case EN_MERODEA: //El Guardian merodea
            {
                if(modo == MODO_DEFAULT)
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
                        if(this->ver(constantes.UNO, constantes.NUEVE * constantes.DIEZ))
                        {
                            if(distanciaEnemigoJugador.modulo < distanciaEnemigoObstaculo.modulo)
                            {
                                modo = MODO_BUSCAR_ESCONDITE;
                                this->setTimeMerodear(constantes.CERO);
                                funciona = true;
                            }
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
                        if(this->ver(constantes.UNO, constantes.NUEVE * constantes.DIEZ))
                        {
                            if(distanciaEnemigoJugador.modulo < distanciaEnemigoObstaculo.modulo)
                            {
                                modo = MODO_BUSCAR_ESCONDITE;
                                this->setTimeMerodear(constantes.CERO);
                                funciona = true;
                            }
                        }
                    }
                }
            }
            break;
            case EN_BUSCA:  //El Guardian busca un escondite o un objeto
                switch(_ordenes[1])
                {
                        //TO DO detectar si las zonas están en otra sala y usar pathfinding
                        case EN_ESCONDITE:
                        {
                            if(modo != MODO_BUSCAR_ESCONDITE)
                                modo = MODO_BUSCAR_ESCONDITE;
                            if(!escondido)
                            {
                                VectorEspacial coordenadasZonaDestino;
                                //Se obtienen las coordenadas de la zona de destino en caso de no tener zona
                                if(zonaElegida == nullptr)
                                {
                                    //TO DO: revisar por constr. copia
                                    
                                    zonaElegida = this->getZonaEsconditeMasCercana(_getZonasEscondite, zonaElegida);

                                }

                                coordenadasZonaDestino.vX = zonaElegida->getX();
                                coordenadasZonaDestino.vY = zonaElegida->getY();
                                coordenadasZonaDestino.vZ = zonaElegida->getZ();
                                funciona = this->buscar(&coordenadasZonaDestino);
                                if(funciona)
                                {
                                    zonaElegida->setProposito(true);
                                    escondido = true;
                                    this->setTimeOcultarse(1.5f);
                                    modo = MODO_OCULTACION;
                                    this->ForzarCambioNodo(&constantes.TREINTA);
                                }
                            }
                            //this->ver(constantes.DOS, constantes.NUEVE * constantes.DIEZ);
                        }
                        break;
                    }


                break;


            default:
                if(modo == MODO_DEFAULT)
                {
                    this->ver(constantes.DOS, constantes.CINCO * constantes.SEIS);
                    if(!hecho)
                    {
                        //Merodea estableciendo un nuevo angulo de rotacion
                        this->setRotation(this->randomBinomial() * maxRotacion);
                        this->Merodear(i);
                        this->setTimeMerodear(1.5f);
                        hecho = true;
                        //Comprueba si ve al jugador para atacarle en caso necesario
                        if(this->ver(constantes.UNO, constantes.NUEVE * constantes.DIEZ))
                        {
                            if(distanciaEnemigoJugador.modulo < distanciaEnemigoObstaculo.modulo)
                            {
                                modo = MODO_BUSCAR_ESCONDITE;
                                this->setTimeMerodear(constantes.CERO);
                                funciona = true;
                            }
                        }
                    }
                    else
                    {
                        //Merodea poniendo en positivo o negativo el angulo actual de rotacion
                        int rota = rand() % 3 - 1;
                        if (rota != 0)
                        {
                            rotation *= rota;
                        }
                        this->Merodear(i);
                        //Comprueba si ve al jugador para atacarle en caso necesario
                        if(this->ver(constantes.UNO, constantes.NUEVE * constantes.DIEZ))
                        {
                            if(distanciaEnemigoJugador.modulo < distanciaEnemigoObstaculo.modulo)
                            {
                                modo = MODO_BUSCAR_ESCONDITE;
                                this->setTimeMerodear(constantes.CERO);
                                funciona = true;
                            }
                        }
                    }
                }

                break;
        }
    }
}

void Guardian::SetNuevasOrdenes(short newOrden)
{
    forzadoCambio = true;
    _ordenes[0] = newOrden;
}

void Guardian::SetNuevosObjetivos(short newTarjet)
{
    forzadoCambio = true;
    _ordenes[1] = newTarjet;
}
