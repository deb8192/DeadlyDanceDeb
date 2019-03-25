#include "Guardian.hpp"
#include "../ConstantesComunes.hpp"
#include "../Personajes/Jugador.hpp"
#include "cmath"

Guardian::Guardian(float nX, float nY, float nZ, int maxVida, int disfraz)
: Enemigo(nX,nY,nZ,maxVida)
{
    Constantes constantes;
    funciona = true;
    atacado = hecho = escondido = false;
    _ordenes = new short [constantes.DOS];
    maxRotacion = constantes.PI_CUARTOS / constantes.TRES; 
    rotation = constantes.CERO;
    zonaElegida = nullptr;

    switch(disfraz)
    {
        case 3 :
            _modelo = "assets/models/guardian_m/GuardianMuerteConTextura.obj";
            break;
            //Cambiar por unicornio
        case 4 :
            _modelo = "assets/models/guardian_m/GuardianMuerteConTextura.obj";
    }
}

Guardian::~Guardian()
{
    delete[] _ordenes;
    _ordenes = nullptr;
    _modelo = nullptr;
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
    Constantes constantes;
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

void Guardian::UpdateGuardian(short *i, int* _jug, std::vector<Zona*> &_getZonas)
{
     Jugador* _jugador = (Jugador*)_jug;
    Constantes constantes;

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
                    cout<<"ESTA ESCONDIDO EL SEÑOR GUARDIAN"<<endl;
                    VectorEspacial posJugador;
                    posJugador.vX = _jugador->getX();
                    posJugador.vY = _jugador->getY();
                    posJugador.vZ = _jugador->getZ();
                    this->alinearse(&posJugador, false);
                    if(this->ver(constantes.UNO, constantes.NUEVE * constantes.DIEZ))
                    {
                        funciona = false;
                    }
                    else 
                    {
                        funciona = true;
                    }
                }
                break;

            case EN_ATRAVESAR:
                switch(_ordenes[1])
                {
                    case EN_ULTIMA_PUERTA:
                        if(!puertasAtravesadas.empty())
                        {
                            funciona = this->buscar(&puertasAtravesadas.top());
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
            case EN_COMPROBAR:
            {
                switch (_ordenes[1])
                {
                    case EN_PELIGRO:
                        
                        if(modo == MODO_HUIDA)
                        {
                            funciona = true;
                        }
                        break;
                    case EN_ATAQUE:
                        
                        if(modo == MODO_ATAQUE)
                        {
                            cout<<"EL SEÑOR GUARDIAN ESTA EN MODO ATAQUE"<<endl;
                            funciona = true;
                        }
                        break;
                    case EN_OCULTACION:
                        
                        if(modo == MODO_OCULTACION)
                        {
                            funciona = true;
                        }
                        break;
                }
            }
            case EN_PERSIGUE: //El Guardian se persigue al jugador
                {
                    funciona = this->perseguir(_jug);
                }
                break;
        
            case EN_ATACAR: //El Guardian ataca
                {
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
                }
                break;      
            case EN_DEFENDERSE: //El Guardian se defiende
                {
                    /*if(!atacado)
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
                    }*/
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
                    this->ver(constantes.DOS, constantes.NUEVE * constantes.DIEZ);
                    if(!hecho)
                    {
                        //Merodea estableciendo un nuevo angulo de rotacion
                        this->setRotation(this->randomBinomial() * maxRotacion);
                        this->Merodear();
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
                        this->Merodear();
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
                        case EN_ESCONDITE:
                        {
                            if(!escondido)
                            {
                                VectorEspacial coordenadasZonaDestino;
                                //Se obtienen las coordenadas de la zona de destino en caso de no tener zona
                                if(zonaElegida == nullptr)
                                {
                                    //TO DO: revisar por constr. copia
                                    vector<Zona*> zonas = _getZonas;
                                    zonas.reserve(zonas.size());
                                    zonaElegida = this->getZonaMasCercana(zonas);
                                }
                                coordenadasZonaDestino.vX = zonaElegida->getX();
                                coordenadasZonaDestino.vY = zonaElegida->getY();
                                coordenadasZonaDestino.vZ = zonaElegida->getZ();
                                funciona = this->buscar(&coordenadasZonaDestino);
                                if(funciona)
                                {
                                    zonaElegida->annadirElemento();
                                    escondido = true;
                                    modo = MODO_OCULTACION;
                                    this->ForzarCambioNodo(&constantes.DIECIOCHO);
                                }
                            }
                            this->ver(constantes.DOS, constantes.NUEVE * constantes.DIEZ);
                        }
                        break; 
                    }
                
                
                break;
            
            
            default:
                if(this->ver(constantes.UNO, constantes.NUEVE * constantes.DIEZ))
                { 
                    if(distanciaEnemigoJugador.modulo < distanciaEnemigoObstaculo.modulo)
                    {
                        modo = MODO_BUSCAR_ESCONDITE;
                        this->setTimeMerodear(constantes.CERO);
                        funciona = true;
                    }
                }
                else
                {
                    funciona = false;
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
