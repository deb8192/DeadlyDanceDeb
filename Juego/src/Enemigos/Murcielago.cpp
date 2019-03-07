#include "Murcielago.hpp"
#include "../ConstantesComunes.hpp"
#include "../Personajes/Jugador.hpp"
#include "cmath"

Murcielago::Murcielago(float nX, float nY, float nZ, int maxVida)
: Enemigo(nX,nY,nZ,maxVida)
{
    Constantes constantes;
    funciona = true;
    atacado = enZonaOscura = false;
    _ordenes = new short [constantes.DOS];
    maxRotacion = constantes.PI_CUARTOS; 
    rotation = constantes.CERO;
    zonaElegida = nullptr;

    _modelo = "assets/models/Murcielago.obj";
}

Murcielago::~Murcielago()
{
    delete[] _ordenes;
    _ordenes = nullptr;
    _modelo = nullptr;
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

void Murcielago::UpdateMurcielago(short *i, int* _jug, std::vector<Zona*> &_getZonas)
{
     Jugador* _jugador = (Jugador*)_jug;
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
                    funciona = this->perseguir(_jug);
                }
                break;
        
            case EN_ATACAR: //El Murcielago ataca
                {
                    if(!atacado)
                    {
                        int danyo;
                        danyo = this->Atacar(*i);
                        if(danyo > 0)
                        {
                            _jugador->ModificarVida(-danyo);
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
                    //this->PedirAyuda();
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
                        //TO DO: revisar por constr. copia
                        vector<Zona*> zonas = _getZonas;
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
            case EN_RECUPERA:  //El murcielago recupera vida en una zona oscura
                if(enZonaOscura)
                {
                    //uint8 vida = rand() % 5 + 1;
                    unsigned short vida = rand() % 5 + 1;
                    this->ModificarVida(vida);
                    funciona = true;
                }
                else funciona = false;
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
