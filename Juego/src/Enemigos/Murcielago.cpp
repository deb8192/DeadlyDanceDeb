#include "Murcielago.hpp"
#include "../ConstantesComunes.hpp"
#include "../Jugando/Nivel.hpp"
#include "../Jugando/Zona.hpp"
#include "cmath"

Murcielago::Murcielago() : Enemigo()
{
    Constantes constantes;
    funciona = true;
    atacado = enZonaOscura = false;
    _ordenes = new short [constantes.DOS];
    maxRotacion = constantes.PI_CUARTOS; 
    rotation = constantes.CERO;
    zonaElegida = nullptr;
}

Murcielago::~Murcielago()
{
    Constantes constantes;
    funciona = false;
    atacado = false;
    for(short i = 0; i < constantes.DOS; i++)
    {
        _ordenes[i] = 0;
    }
    delete _ordenes;
    maxRotacion = 0;
    rotation = 0.0f;
}

/***************** RunIA *****************
 * Funcion que llama a recorrer el arbol
 * de del Murcielago comportamiento en Enemigo
 * 
 * Entradas:
 * 
 * Salidas:
*/
void Murcielago::RunIA()
{
    Constantes constantes;
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

/***************** UpdateMurcielago *****************
 * Funcion que llama a la funcion actual donde se
 * ha quedado la lectura del arbol del Murcielago
 * 
 * Entradas:
 *      i: (sennala al Murcielago del array, NO NECESARIO APARENTEMENTE)
 * Salidas:
*/ 

void Murcielago::UpdateMurcielago(short *i)
{
    Constantes constantes;

    funciona = true;
    if(modo == constantes.UNO && _ordenes != nullptr)
    {
        if(enZonaOscura)
        {
            enZonaOscura = false;
        }
        switch (_ordenes[0])
        {
            case EN_PERSIGUE: //El Murcielago se mueve
                {
                    funciona = this->perseguir();
                }
                break;
        
            case EN_ATACAR: //El Murcielago ataca
                {
                    if(!atacado)
                    {
                        Nivel* _nivel;
                        int danyo;
                        danyo = this->Atacar(*i);
                        _nivel = Nivel::getInstance();
                        if(danyo > 0)
                        {
                            _nivel->GetJugador()->QuitarVida(danyo);
                            cout<<"Ataca por la IA" <<endl;
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

    else if(_ordenes != nullptr)
    {
        switch (_ordenes[0])
        {          
            case EN_OIR: //El Murcielago oye al jugador
                {
                    if(this->oir(constantes.UNO))
                    {
                        funciona = true;
                    }
                    else 
                    {
                        funciona = false;
                    }
                }
                break;
            case EN_PIDE_AYUDA: //El Murcielago pide ayuda
                {
                    modo = MODO_ATAQUE;
                    this->setTimeMerodear(constantes.CERO);
                    cout<<"Pide ayuda a los aliados"<<endl;
                    this->pedirAyuda();
                    funciona = true;
                }
                break;
            case EN_BUSCA:  //El murcielago busca una zona oscura
                if(!enZonaOscura)
                {
                    VectorEspacial coordenadasZonaDestino;
                    //Se obtienen las coordenadas de la zona de destino en caso de no tener zona
                    if(zonaElegida == nullptr)
                    {
                        Nivel* _nivel;
                        _nivel = Nivel::getInstance();
                        vector<Zona*> zonas = _nivel->GetZonas();
                        zonas.reserve(zonas.size());
                        zonaElegida = this->getZonaMasCercana(zonas, constantes.CERO);
                    }
                    coordenadasZonaDestino.vX = zonaElegida->getX();
                    coordenadasZonaDestino.vY = zonaElegida->getY();
                    coordenadasZonaDestino.vZ = zonaElegida->getZ();
                    funciona = this->buscar(&coordenadasZonaDestino);
                    if(funciona)
                    {
                        zonaElegida->annadirElemento();
                        enZonaOscura = true;
                    }
                }
                break;
            
            default:
                cout<<"No hace nada"<<endl;
                break;
        }
    }
}

void Murcielago::SetNuevasOrdenes(short newOrden)
{
    _ordenes[0] = newOrden;
}
