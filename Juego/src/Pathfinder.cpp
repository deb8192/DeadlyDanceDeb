#include "Pathfinder.hpp"

int Pathfinder::comprobarListas(Sala* nodo, vector <struct NodeRecord> lista)
{
    unsigned int i = 0;
    bool esta = false;
    if(!lista.empty())
    {
        while(!esta && i < lista.size())
        {
            if(nodo == lista.at(i).nodo)
            {
                return i;
            }
            i++;
        }
    }
    return 0;
}

int Pathfinder::calcularCostes(struct NodeRecord nodo, Sala* destino)
{
    //Se obtiene la posicion de cada sala en el espacio
    int * datosOrigen = nodo.nodo->getSizes();
    int * datosDestino = destino->getSizes();

    //Se saca la distancia entre las salas (vector)
    double costeX = datosDestino[2] - datosOrigen[2];
    double costeY = datosDestino[3] - datosOrigen[3];
    double costeZ = datosDestino[4] - datosOrigen[4];

    //Se obtiene la distancia en un valor (modulo del vector)
    double coste = pow(costeX, 2) + pow(costeY, 2) + pow(costeZ, 2);
    coste = sqrt(coste);

    int costeFinal = nodo.costSoFar + (int) coste;
    return costeFinal;
}

void Pathfinder::getSmallest()
{
    unsigned int i = 0;
    actualNodo.estimatedTotalCost = INT_MAX;
    while(i < listaAbierta.size() && actualNodo.estimatedTotalCost > 0)   
    {
        if(listaAbierta.at(i).estimatedTotalCost < actualNodo.estimatedTotalCost)
        {
            actualNodo = listaAbierta.at(i);
        }
        i++;
    }
}

bool Pathfinder::coincide(Sala *nodo, Sala *end)
{
    if(nodo->getPosicionEnGrafica() == end->getPosicionEnGrafica())
    {
        return true;
    }
    return false;
}
std::vector <struct Pathfinder::NodeRecord> Pathfinder::encontrarCamino(Nivel instanciaNivel, Sala *start, Sala *end, float totalCostSoFar)
{
    startNodo.nodo = start;
    startNodo.conexion = NULL;
    startNodo.costSoFar = 0;
    startNodo.estimatedTotalCost = calcularCostes(startNodo, end);

    vector <Sala*> conexiones;

    listaAbierta.push_back(startNodo);

    bool termina;
    
    unsigned int i = 0;

    while(listaAbierta.size() > 0)
    {
        Pathfinder::getSmallest();     //Se obtiene el nodo con menor coste estimado
        termina = coincide(actualNodo.nodo, end);             //SE comprueba si es el último (la primera vez solo comprueba la sala start).

        //Si las salas coinciden, se ha llegado al final y se acaba la ejecucion.
        if(termina)                                 
        {
            //Falta hacer el camino inverso
            while(coincide(actualNodo.nodo, start) == false)
            {
                camino.insert(camino.begin(), actualNodo);
                actualNodo = *actualNodo.conexion;
            }
            return camino;
        }
        //En caso contrario comprobamos las demas salas conectadas a la sala actual
        else
        {
            conexiones = actualNodo.nodo->getSalidas();
            for(i = 0; i < conexiones.size(); i++)
            {
                Sala * sala = conexiones.at(i);
                int costeLlegada = calcularCostes(actualNodo, sala);
                int estaCerrado = 0, estaAbierto = 0;

                //Se comprueba si la sala actual esta en la lista cerrada
                estaCerrado = comprobarListas(sala, listaCerrada);

                //Se comprueba si la sala actual esta en la lista cerrada
                estaAbierto = comprobarListas(sala, listaAbierta);

                if(estaCerrado > 0)
                {
                    endNodo = listaCerrada.at(estaCerrado);
                        
                    //Si en el actual recorrido hemos encontrado un coste menor,
                    //sacamos el nodo de la lista cerrada
                    if(endNodo.costSoFar > costeLlegada)
                    {
                        listaCerrada.erase(listaCerrada.begin() + estaCerrado);
                        endNodo.estimatedTotalCost -= endNodo.costSoFar;
                    }
                }

                else if(estaAbierto > 0)
                {
                    endNodo = listaAbierta.at(estaAbierto);

                    //Si en el actual recorrido hemos encontrado un coste menor,
                    //sacamos el nodo de la lista cerrada
                    if(endNodo.costSoFar > costeLlegada)
                    {
                        endNodo.estimatedTotalCost -= endNodo.costSoFar;
                    }
                }

                else
                {
                    endNodo.nodo = sala;
                    endNodo.estimatedTotalCost = calcularCostes(endNodo, end);
                }

                //Se han hecho todas las comprobaciones y se deben
                //terminar de rellenar todos los datos del nodo
                endNodo.costSoFar = costeLlegada;
                endNodo.conexion = &actualNodo;
                endNodo.estimatedTotalCost += costeLlegada;

                estaAbierto = comprobarListas(actualNodo.nodo, listaAbierta);
                if(estaAbierto != 0)
                {
                    listaAbierta.erase(listaAbierta.begin() + estaAbierto);
                }
                listaCerrada.push_back(actualNodo);
            }
        }
    }
    return camino;
}