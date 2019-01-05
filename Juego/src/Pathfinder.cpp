#include "Pathfinder.hpp"
#include <string>
#include <cstring>
#include <iostream>
#include <cmath>

/********************* ComprobarListas ************************
 * Descripcion: Metodo que indica si una sala se encuentra en
 * cualquiera de las listas de nodos que se pasen
 * Entradas:
 *      *nodo: sala que se comrpueba
 *      lista: lista donde se comprueba si *nodo esta en ella o no  
 */
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
    return -1;
}
/********************* CalcularCostes ************************
 * Descripcion: Metodo que devuelve la distancia entre un
 * nodo origen y la sala de destino que se pasa
 * Entradas:
 *      nodo: nodo cuya sala es el origen de la distancia
 *      *destino: sala de destino de la distancia  
 */
int Pathfinder::calcularCostes(struct NodeRecord nodo, Sala* destino)
{
    //Se obtiene la posicion de cada sala en el espacio
    int * datosOrigen = nodo.nodo->getSizes();
    int * datosDestino = destino->getSizes();

    //Se saca la distancia entre las salas (vector)

    cout << "Datos " << datosDestino[2] << " " << datosOrigen[2] <<endl;
    cout << "Datos " << datosDestino[3] << " " << datosOrigen[3] <<endl;
    cout << "Datos " << datosDestino[4] << " " << datosOrigen[4] <<endl;
    cout << "Coste " << nodo.costSoFar <<endl;
    double costeX = abs(datosDestino[2] - datosOrigen[2]);
    double costeY = abs(datosDestino[3] - datosOrigen[3]);
    double costeZ = abs(datosDestino[4] - datosOrigen[4]);

    //Se obtiene la distancia en un valor (modulo del vector)
    double coste = pow(costeX, 2) + pow(costeY, 2) + pow(costeZ, 2);
    coste = sqrt(coste);

    int costeFinal = nodo.costSoFar + (int) coste;
    cout << "Coste final " << costeFinal <<endl;
    return costeFinal;
}
/********** GetSmallest, devuelve la mas pequeña ************
 * Descripcion: Metodo que devuelve el nodo de la lista abierta
 * con un menor coste estimado de llegada
 * Entradas:  
 */
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
/********** Coincide, Coincidencia de dos salas ************
 * Descripcion: Metodo que compara si dos salas son la misma
 * Entradas:
 *      *nodoA: sala 1 de la comparacion
 *      *nodoB: sala 2 de la comparacion  
 */
bool Pathfinder::coincide(Sala *nodoA, Sala *nodoB)
{
    if(nodoA->getPosicionEnGrafica() == nodoB->getPosicionEnGrafica())
    {
        return true;
    }
    return false;
}
/*******Pathfinder, buscador del camino mas corto*******
 * Descripcion: Metodo que sirve para hallar el camino 
 * mas corto entre dos salas del mapa (dos nodos de un grafo)
 * Entradas:
 *      *start: sala desde donde se empieza el camino
 *      *end: sala de destino del camino  
 */
std::vector <struct Pathfinder::NodeRecord> Pathfinder::encontrarCamino(Sala *start, Sala *end)
{

    cout << "Entra" << endl;
    startNodo.nodo = start;
    startNodo.costSoFar = 0;
    startNodo.estimatedTotalCost = calcularCostes(startNodo, end);

    vector <Sala*> salas;

    listaAbierta.push_back(startNodo);

    bool termina;
    
    unsigned int i = 0;

    //Mientras que haya nodos visitados por procesar se busca el camino
    while(listaAbierta.size() > 0)
    {
        int estaCerrado = -1, estaAbierto = -1;
        Pathfinder::getSmallest();                            //Se obtiene el nodo con menor coste estimado
        termina = coincide(actualNodo.nodo, end);             //SE comprueba si es el último (la primera vez solo comprueba la sala start).

        //Si las salas coinciden, se ha llegado al final y se acaba la ejecucion.
        if(termina)                                 
        {
            cout << "Termina" <<endl;
            //Se monta el camino de nodos que se devuelve en la funcion
            while(!coincide(actualNodo.nodo, start))
            {
                cout << "¿Coincide?" <<endl;
                cout << "Nodo " <<actualNodo.nodo->getPosicionEnGrafica() << endl;
                cout << "Nodo " <<start->getPosicionEnGrafica() << endl;
                cout << "Conexion " <<actualNodo.conexion.desde->getPosicionEnGrafica() << endl;
                camino.insert(camino.begin(), actualNodo);

                i = 0;
                //Busca los nodos de las conexiones en la lista de nodos procesados para hallar el siguiente nodo del camino
                while (!coincide(actualNodo.conexion.desde, listaCerrada.at(i).nodo) || actualNodo.conexion.estimatedTotalCost != listaCerrada.at(i).estimatedTotalCost)
                {
                    i++;
                } 
                actualNodo = listaCerrada.at(i);
            }
            cout << "Sale" <<endl;
            cout << "Nodo " <<actualNodo.nodo->getPosicionEnGrafica() << endl;
            cout << "Nodo " <<start->getPosicionEnGrafica() << endl;
            camino.insert(camino.begin(), actualNodo);

            return camino;
        }
        //En caso contrario comprobamos las demas salas conectadas a la sala actual
        else
        {
            cout << "No devuelve el camino" << endl;
            salas = actualNodo.nodo->getSalidas();
            for(i = 0; i < salas.size(); i++)
            {
                Sala * sala = salas.at(i);
                int costeLlegada = calcularCostes(actualNodo, sala);

                //Se comprueba si la sala actual esta en la lista cerrada
                estaCerrado = comprobarListas(sala, listaCerrada);

                //Se comprueba si la sala actual esta en la lista cerrada
                estaAbierto = comprobarListas(sala, listaAbierta);

                //Si estaCerrado >= 0, la sala se encuentra en la lista cerrada
                if(estaCerrado >= 0)
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

                //Si estaAbierto >= 0, la sala se encuentra en la lista abierta
                else if(estaAbierto >= 0)
                {
                    endNodo = listaAbierta.at(estaAbierto);

                    //Si en el actual recorrido hemos encontrado un coste menor,
                    //sacamos el nodo de la lista cerrada
                    if(endNodo.costSoFar > costeLlegada)
                    {
                        endNodo.estimatedTotalCost -= endNodo.costSoFar;
                    }
                }

                //No esta en ninguna lista
                else
                {
                    endNodo.nodo = sala;
                    endNodo.costSoFar = costeLlegada;
                    endNodo.estimatedTotalCost = calcularCostes(endNodo, end);
                }

                //Se han hecho todas las comprobaciones y se deben
                //terminar de rellenar todos los datos del nuevo nodo (endNodo)
                endNodo.conexion.desde = actualNodo.nodo;
                endNodo.conexion.estimatedTotalCost = actualNodo.estimatedTotalCost;
                endNodo.estimatedTotalCost += costeLlegada;

                //Si el nodo comprobado en la conexion no esta visitado (en la listaAbierta)
                //se añade al vector listaAbierta
                estaAbierto = comprobarListas(endNodo.nodo, listaAbierta);
                if(estaAbierto < 0)
                {
                    listaAbierta.push_back(endNodo);
                }
            }
            //El nodo procesado (actualNodo) se elimina de la lista de nodos visitados (listaAbierta)
            //y se anyade a la lista de nodos procesados (listaCerrada)
            estaAbierto = comprobarListas(actualNodo.nodo, listaAbierta);
            listaAbierta.erase(listaAbierta.begin() + estaAbierto);
            listaCerrada.push_back(actualNodo);
        }
    }
    return camino;
}