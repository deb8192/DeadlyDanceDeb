#include "Arbol.hpp"
#include "ConstantesComunes.hpp"

Arbol::Arbol(Nodo *root, const char* name)
{
    raiz = root;
    nodoEnEjecucionDirecta = nullptr;
    arrayTareaObjetivo = new short int [2];
    ID = 0;
}

/**************     anyadirHijosComposicion      *****************
 * Funcion que anyade un hijo de tipo composicion al arbol
 * Entradas:
 *          com: composicion a anyadir al arbol
 *          nivel: nivel del nodo a anyadir
 */
Nodo* Arbol::anyadirHijo(Nodo * nod)
{
    Constantes constantes;
    unsigned int i = 0;
    bool desciende = true;
    Nodo* buscador = raiz;
    Nodo* actual = nullptr;
    Composicion *finderA = nullptr;
    Decorador *finderB = nullptr;
    vector <Nodo*> descendientes;
    
    if(raiz->getNivel() == nod->getNivel() - 1)
    {
        Composicion *root = (Composicion *) raiz;
        root->addHijo(nod);
        raiz = (Nodo*) root;
        return raiz;
    }
    //Entra en los hijos de la raiz del arbol
    else
    {
        //Comprueba el nivel del nodo composicion a 
        //introducir y el nivel del nodo actual encontrado "buscador"
        while(buscador->getNivel() < nod->getNivel() && desciende)
        {
            finderA = nullptr;
            finderB = nullptr;

            //Si el nodo actual encontrado "buscador" es una composicion entra
            if(strcmp(buscador->getNombre(), constantes.RAIZ) == 0 || strcmp(buscador->getNombre(), constantes.COMPOSICION) == 0)
            {
                finderA = (Composicion*) buscador;
            }

            //Si el nodo actual encontrado "buscador" es un decorador entra
            else if(strcmp(buscador->getNombre(), constantes.DECORADOR) == 0)
            {
                finderB = (Decorador*) buscador;
            }  
            //Si no hay nodos en ese nivel o dichos nodos no tienen hijos hijos, desactiva el descenso para retroceder en las ramas del arbol 
            if((finderA == nullptr || finderA->getHijos().size() <= 0) && (finderB == nullptr || finderB->getHijos().size() <= 0))
            {
                desciende = false;
            }
            else if(finderA != nullptr && finderA->getHijos().size() > 0)
            {
                descendientes = finderA->getHijos();          //Obtenemos los hijos de una composicion
            }
            else if(finderB != nullptr && finderB->getHijos().size() > 0)
            {
                descendientes = finderB->getHijos();          //Obtenemos los hijos de un decorador
            }
            
            //Si hay hijos se busca entre ellos, mientras los haya, el lugar que le corresponde al nuevo nodo en funcion de su ID
            if(!descendientes.empty())
            {
                while(i < descendientes.size())
                {
                    actual = descendientes.at(i);

                    //Si el ID del padre "buscador" es menor que el de nuevo nodo "nod" y el ID del 
                    if(actual != nullptr && buscador->getID() < nod->getID() && actual->getID() > nod->getID())
                    {
                        //SI la diferencia de niveles entre el padre "buscador" y
                        //su supuesto hijo "nod" es 1, son padre e hijo y entra
                        if(nod->getNivel() - buscador->getNivel() == 1)
                        {
                            //El padre es un decorador y se anade su nuevo hijo al mismo
                            if(strcmp(buscador->getNombre(), constantes.DECORADOR) == 0)
                            {
                                Decorador* padre = finderB;
                                padre->addHijo((Nodo*) nod);
                                
                                i = descendientes.size();
                                desciende = false;
                                return (Nodo*) padre;
                            }
                            //El padre es una composicion y se anade su nuevo hijo a la misma
                            else if(strcmp(buscador->getNombre(), constantes.COMPOSICION) == 0)
                            {
                                Composicion* padre = finderA;
                                padre->addHijo((Nodo*) nod);
                                
                                i = descendientes.size();
                                desciende = false;
                                return (Nodo*) padre;
                            }
                        }
                    }
                    else if(actual != nullptr && actual->getID() < nod->getID())
                    {

                        if(actual != nullptr)
                        {
                            buscador = actual;
                        }
                    }
                    i++;
                }
                if(nod->getNivel() - buscador->getNivel() == 1)
                {
                    if(strcmp(buscador->getNombre(), constantes.DECORADOR) == 0)
                    {
                        Decorador* padre = (Decorador*) buscador;
                        padre->addHijo((Nodo*) nod);
                        desciende = false;
                        return (Nodo*) padre;
                    }
                    else if(strcmp(buscador->getNombre(), constantes.COMPOSICION) == 0)
                    {
                        Composicion* padre = (Composicion*) buscador;
                        padre->addHijo((Nodo*) nod);
                        desciende = false;
                        return (Nodo*) padre;
                    }
                }
                i = 0;
            }
        }
    }
    return nullptr;
}

void Arbol::finBucleDecorador()
{
    finBucle.pop_back();
    if(finBucle.empty())
    {
        bucleDecorador = false;
    }
}

Composicion * Arbol::devolverPadre()
{
    Constantes constantes;
    nodoEnEjecucionDirecta = nodoEnEjecucionDirecta->getPadre();
    if(std::strcmp(nodoEnEjecucionDirecta->getNombre(), constantes.COMPOSICION) == 0)
    {
        return (Composicion *) nodoEnEjecucionDirecta;
    }
    else
    {
        return nullptr;
    }
}

void Arbol::CambiarNodo(const short *_nodo)
{
    Constantes constantes;
    ID = *_nodo;
    Nodo *_actual = raiz;
    size_t i = 0;
    bool recorre = true;
    Decorador *_deco;
    Composicion *_comp;
    vector <Nodo*> hijos;
    while(_actual->getID() != ID && recorre)
    {
        if(strcmp(_actual->getNombre(), constantes.DECORADOR) == 0)
        {
            _deco = (Decorador*) _actual;
            hijos.resize(_deco->getHijos().size());
            hijos = _deco->getHijos();
        }
        else if(strcmp(_actual->getNombre(), constantes.COMPOSICION) == 0 || strcmp(_actual->getNombre(), constantes.RAIZ) == 0)
        {
            _comp = (Composicion*) _actual;
            hijos.resize(_comp->getHijos().size());
            hijos = _comp->getHijos();
        }
        if(i < hijos.size())
        {
            if(hijos.at(i)->getID() <= ID && hijos.at(i + constantes.UNO)->getID() > ID)
            {
                _actual = hijos.at(i);
                if(_actual->getID() == ID)
                {
                    nodoEnEjecucionDirecta = _actual;
                    recorre = false;
                }
                i = 0;
            }
            else
            {
                i++;
            }
        }
        else
        {
            recorre = false;
        }
    }
    _actual = nullptr;
    _deco = nullptr;
    _comp = nullptr;
}

/***************** ContinuarSiguenteNodo *******************
 * Funcion que recorre el arbol de comportamiento de cada
 * enemigo cada vez que se le llame, continuando desde el ultimo
 * nodo en ejecucion si lo hay o comenzando desde la raiz
 * 
 * Entradas:
 *          bool exito: valor booleano que indica si 
 *              la ultima accion ha tenido exito o no
*/
short int* Arbol::ContinuarSiguienteNodo(bool exito)
{
    Constantes constantes;
    Composicion *comp = nullptr;
    Composicion *compo = nullptr;
    Decorador *deco = nullptr;
    bool desciende = true;  //Permite o bloquea el descenso segun si hay mas hijos o no
    bool primeraVez = true;
    unsigned int i = 0;
    
    //Si el arbol de esta recorrendo
    if(nodoEnEjecucionDirecta != nullptr)
    {        
        if(std::strcmp(nodoEnEjecucionDirecta->getNombre(), constantes.COMPOSICION) == 0 || std::strcmp(nodoEnEjecucionDirecta->getNombre(), constantes.RAIZ) == 0)
        {
            comp = (Composicion*) nodoEnEjecucionDirecta;
            compo = comp;
        }
        else if(std::strcmp(nodoEnEjecucionDirecta->getNombre(), constantes.DECORADOR) == 0)
        {
            deco = (Decorador*) nodoEnEjecucionDirecta;
        }
        //El bucle continua mientras el nodo actual no sea una tarea o tenga hijos para descender
        while(((nodoEnEjecucionDirecta != nullptr && std::strcmp(nodoEnEjecucionDirecta->getNombre(), constantes.HOJA) != 0) && 
        (compo != nullptr && strcmp(compo->GetAccion(), constantes.FALSO) == 0) && desciende) || primeraVez)
        {
            if(std::strcmp(nodoEnEjecucionDirecta->getNombre(), constantes.COMPOSICION) == 0 || std::strcmp(nodoEnEjecucionDirecta->getNombre(), constantes.RAIZ) == 0)
            {
                comp = (Composicion*) nodoEnEjecucionDirecta;
            }
            else if(std::strcmp(nodoEnEjecucionDirecta->getNombre(), constantes.DECORADOR) == 0)
            {
                deco = (Decorador*) nodoEnEjecucionDirecta;
            }
            //Es para asegurar que entra en el recorrido en caso de que tenga que ascender
            if(primeraVez)
            {
                primeraVez = false;
            }

            //Si el nodo actual es una composicion se hace downcasting hacia dicha clase
            if(comp != nullptr)
            {
                i = 0;

                //Si la composicion es una secuencia y la accion anterior ha tenido exito
                //o si es un selector y la accion anterior no ha tenido exito, se busca el siguiente hijo
                if((comp->getTipo() == 2 && exito) || (comp->getTipo() == 3 && (!exito || ID < comp->getHijos().front()->getID())))
                {
                    //Se accede al hijo que toca en funcion del ultimo ID registrado en el recorrido
                    while(i < comp->getHijos().size() && ID >= comp->getHijos().at(i)->getID())
                    {
                        i++;
                    }
                    //De haber un hijo cuyo ID es superior al registrado, ese es el nuevo nodo
                    if(i < comp->getHijos().size())
                    {
                        nodoEnEjecucionDirecta = comp->getHijos().at(i);
                        if(std::strcmp(nodoEnEjecucionDirecta->getNombre(), constantes.COMPOSICION) == 0)
                        {
                            comp = (Composicion*) nodoEnEjecucionDirecta;
                        }
                        else if(std::strcmp(nodoEnEjecucionDirecta->getNombre(), constantes.DECORADOR) == 0)
                        {
                            deco = (Decorador*) nodoEnEjecucionDirecta;
                        }
                        ID++;
                    }
                    //En caso contrario, se asciende por el arbol para cambiar de rama hasta que no se pueda
                    else if(nodoEnEjecucionDirecta->getPadre() != nullptr)
                    {
                        comp = this->devolverPadre();
                    }

                    //Si se ha llegado a la raiz y ya se ha recorrido el arbol
                    else
                    {
                        nodoEnEjecucionDirecta = nullptr;
                        ID = 0;
                    }
                }
                //Si la composicion es una secuencia y la accion anterior no ha tenido exito
                //o si es un selector y la accion anterior ha tenido exito, se asciende para seleccionar otro nodo no hijo
                else if((comp->getTipo() == 2 && !exito) || (comp->getTipo() == 3 && exito && ID >= comp->getHijos().front()->getID()))
                {
                    //Se iguala el ID al ultimo de los hijos para continuar
                    //la lectura del arbol en otra rama y no bajar a los hijos restantes
                    ID = comp->getHijos().back()->getID();
                    if(nodoEnEjecucionDirecta->getPadre() != nullptr)
                    {
                        comp = this->devolverPadre();
                    }

                    //Si se ha llegado a la raiz y ya se ha recorrido el arbol
                    else
                    {
                        nodoEnEjecucionDirecta = nullptr;
                        ID = 0;
                    }
                }              
            }
            //Si el nodo actual es un decorador se hace downcasting hacia dicha clase
            else if(deco != nullptr)
            {
                i = 0;
                //Se comprueba el ID del decorador para saber si coincide y entra
                if(deco->getID() == ID)
                {
                    //Se detecta que tipo de final tiene el bucle del decorador
                    const char * finalDecorador = deco->GetFin();

                    if(strcmp(finalDecorador, constantes.VERDADERO) == 0)
                    {
                        finBucle.push_back(0);
                    }
                    else if(strcmp(finalDecorador, constantes.RANDOM) == 0)
                    {
                        finBucle.push_back(1);
                        contadorRandom = rand() % 5 + 1;
                    }
                    else
                    {
                        finBucle.push_back(-1);
                    }
                    bucleDecorador = true;
                }

                //Si algun hijo falla en su tarea, el booleano es falso por lo tanto se igual el contador ID
                //al del decorador para volver a entrar al bucle
                else if(!exito)
                {
                    ID = nodoEnEjecucionDirecta->getID();
                    exito = true;
                    if(finBucle.back() > 0)
                    {
                        contadorRandom--;
                        if(contadorRandom == 0)
                        {
                            this->finBucleDecorador();
                        }
                    }
                }

                //Se comprueba el ID del ultimo hijo del decorador para saber si sale
                else if(deco->getHijos().back()->getID() < ID && exito)
                {
                    if(finBucle.back() > 0)
                    {
                        contadorRandom--;
                        if(contadorRandom == 0)
                        {
                            this->finBucleDecorador();
                        }
                    }
                    else if (finBucle.back() == 0)
                    {
                        this->finBucleDecorador();
                    }
                }

                //Se accede al hijo que toca en funcion del ultimo ID registrado en el recorrido
                while(i < deco->getHijos().size() && ID >= deco->getHijos().at(i)->getID())
                {
                    i++;
                }

                //De haber un hijo cuyo ID es superior al registrado, ese es el nuevo nodo
                if(i < deco->getHijos().size())
                {
                    nodoEnEjecucionDirecta = deco->getHijos().at(i);
                    if(std::strcmp(nodoEnEjecucionDirecta->getNombre(), constantes.COMPOSICION) == 0)
                    {
                        comp = (Composicion*) nodoEnEjecucionDirecta;
                    }
                    else if(std::strcmp(nodoEnEjecucionDirecta->getNombre(), constantes.DECORADOR) == 0)
                    {
                        deco = (Decorador*) nodoEnEjecucionDirecta;
                    }
                    ID++;
                }
                //En caso contrario, se asciende por el arbol para cambiar de rama
                else if(nodoEnEjecucionDirecta->getPadre() != nullptr)
                {
                    comp = this->devolverPadre();
                }

                //Si se ha llegado a la raiz y ya se ha recorrido el arbol
                else
                {
                    nodoEnEjecucionDirecta = nullptr;
                    ID = 0;
                }
            }
            //En caso contrario, se asciende por el arbol para cambiar de rama
            else if(nodoEnEjecucionDirecta->getPadre() != nullptr)
            {
                comp = this->devolverPadre();
            }
            //Si se ha llegado a la raiz y ya se ha recorrido el arbol
            else
            {
                nodoEnEjecucionDirecta = nullptr;
                ID = 0;
            }
            if(comp != nullptr)
            {
                compo = comp;
            }
            comp = nullptr;
            deco = nullptr;
        }
        if(nodoEnEjecucionDirecta != nullptr)
        {
            if(strcmp(nodoEnEjecucionDirecta->getNombre(), constantes.HOJA) == 0)
            {
                Hoja  *hoja = (Hoja*) nodoEnEjecucionDirecta;
                //Se indican la tarea y el objetivo a ejecutar
                //Tarea
                const char* accion = hoja->GetAccion();

                //La accion es moverse
                if(strcmp(accion, constantes.MOVERSE) == 0)
                {
                    arrayTareaObjetivo[0] = 0;
                }
                //La accion es atacar
                else if(strcmp(accion, constantes.ATACAR) == 0)
                {
                    arrayTareaObjetivo[0] = 1;
                }
                //La accion es ver
                else if(strcmp(accion, constantes.VER) == 0)
                {
                    arrayTareaObjetivo[0] = 2;
                }
                //La accion es pedir ayuda
                else if(strcmp(accion, constantes.PIDE_AYUDA) == 0)
                {
                    arrayTareaObjetivo[0] = 3;
                }
                //La accion es merodear
                else if(strcmp(accion, constantes.MERODEA) == 0)
                {
                    arrayTareaObjetivo[0] = 4;
                }
                else
                {
                    arrayTareaObjetivo[0] = -1;
                }

                //Objetivo
                const char* objetivo = hoja->GetObjetivo();
                if(strcmp(objetivo, constantes.JUGADOR) == 0)
                {
                    arrayTareaObjetivo[1] = 0;
                }
                else if(strcmp(objetivo, constantes.ZONA_COFRES) == 0)
                {
                    arrayTareaObjetivo[1] = 1;
                }
                else
                {
                    arrayTareaObjetivo[1] = -1;
                }
            }
            else if(strcmp(nodoEnEjecucionDirecta->getNombre(), constantes.COMPOSICION) == 0)
            {
                /*if(strcmp(compo->GetAccion(), constantes.FALSO) != 0)
                {
                    //Se indican la tarea y el objetivo a ejecutar
                    //Tarea
                    const char* accion = compo->GetAccion();
                    if(strcmp(accion, constantes.MOVERSE) == 0)
                    {
                        arrayTareaObjetivo[0] = 0;
                    }
                    else if(strcmp(accion, constantes.ATACAR) == 0)
                    {
                        arrayTareaObjetivo[0] = 1;
                    }
                    else
                    {
                        arrayTareaObjetivo[0] = -1;
                    }

                    //Objetivo
                    const char* objetivo = comp->GetObjetivo();
                    if(strcmp(objetivo, constantes.JUGADOR) == 0)
                    {
                        arrayTareaObjetivo[1] = 0;
                    }
                    else if(strcmp(objetivo, constantes.ZONA_COFRES) == 0)
                    {
                        arrayTareaObjetivo[1] = 1;
                    }
                    else
                    {
                        arrayTareaObjetivo[1] = -1;
                    }
                }*/
            }
            else
            {
                arrayTareaObjetivo[0] = -1;
                arrayTareaObjetivo[1] = -1;
                return arrayTareaObjetivo;
            }
        }
        else
        {
            nodoEnEjecucionDirecta = raiz;   //Obtenemos la raiz del arbol
            ID++;
            arrayTareaObjetivo[0] = -1;
            arrayTareaObjetivo[1] = -1;
            return arrayTareaObjetivo;
        }
        
    }

    else
    {
        //Se comienza a recorrer el arbol
        if(raiz == nullptr) //si es nula la raiz no se ha definido arbol
        {
            desciende = false;
            arrayTareaObjetivo[0] = -1;
            arrayTareaObjetivo[1] = -1;
            return arrayTareaObjetivo;
        }
        else
        {
            nodoEnEjecucionDirecta = raiz;   //Obtenemos la raiz del arbol
            ID++;
            arrayTareaObjetivo[0] = -1;
            arrayTareaObjetivo[1] = -1;
            return this->ContinuarSiguienteNodo(exito);
        }
    }  
    return arrayTareaObjetivo;
}

Nodo * Arbol::GetRaiz()
{
    return raiz;
}

Nodo * Arbol::GetNodoEnEjecucionDirecta()
{
    return nodoEnEjecucionDirecta;
}