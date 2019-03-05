#include "MuerteBoss.hpp"
#include "../ConstantesComunes.hpp"
#include "../Personajes/Jugador.hpp"
#include "cmath"

MuerteBoss::MuerteBoss(float nX, float nY, float nZ, int maxVida)
: Enemigo(nX,nY,nZ,maxVida)
{
    Constantes constantes;
    funciona = true;
    atacado = false;
    _ordenes = new short [constantes.DOS];
    maxRotacion = constantes.PI_CUARTOS; 
    rotation = constantes.CERO;

    _textura = "assets/texture/HeavyTex.png";
    _modelo = "assets/models/rockero.b3d";
}

MuerteBoss::~MuerteBoss()
{
    delete[] _ordenes;
    _ordenes = nullptr;

    _textura = nullptr;
    _modelo = nullptr;
}

/***************** RunIA *****************
 * Funcion que llama a recorrer el arbol
 * de del MuerteBoss comportamiento en Enemigo
 * 
 * Entradas:
 * 
 * Salidas:
*/
void MuerteBoss::RunIA()
{
    
}

/***************** UpdateMuerteBoss *****************
 * Funcion que llama a la funcion actual donde se
 * ha quedado la lectura del arbol del MuerteBoss
 * 
 * Entradas:
 *      i: (sennala al MuerteBoss del array, NO NECESARIO APARENTEMENTE)
 * Salidas:
*/ 

void MuerteBoss::UpdateMuerteBoss(short *i, int* _jug)
{
    
}

void MuerteBoss::SetNuevasOrdenes(short newOrden)
{
    _ordenes[0] = newOrden;
}