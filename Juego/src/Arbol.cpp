#include "Arbol.hpp"

Arbol::Arbol(Nodo *root, const char* name)
{
    raiz = root;
    nodoEnEjecucionDirecta = nullptr;
    arrayTareaObjetivo = new int[2];
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
            if(strcmp(buscador->getNombre(), RAIZ) == 0 || strcmp(buscador->getNombre(), COMPOSICION) == 0)
            {
                cout<<typeid(buscador).name()<<endl;
                finderA = (Composicion*) buscador;
            }

            //Si el nodo actual encontrado "buscador" es un decorador entra
            else if(strcmp(buscador->getNombre(), DECORADOR) == 0)
            {
                cout<<typeid(buscador).name()<<endl;
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
                            if(strcmp(buscador->getNombre(), DECORADOR) == 0)
                            {
                                Decorador* padre = finderB;
                                padre->addHijo((Nodo*) nod);
                                
                                i = descendientes.size();
                                desciende = false;
                                return (Nodo*) padre;
                            }
                            //El padre es una composicion y se anade su nuevo hijo a la misma
                            else if(strcmp(buscador->getNombre(), COMPOSICION) == 0)
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
                    if(strcmp(buscador->getNombre(), DECORADOR) == 0)
                    {
                        Decorador* padre = (Decorador*) buscador;
                        padre->addHijo((Nodo*) nod);
                        desciende = false;
                        return (Nodo*) padre;
                    }
                    else if(strcmp(buscador->getNombre(), COMPOSICION) == 0)
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

int* Arbol::ContinuarSiguienteNodo(bool exito)
{
    Composicion *comp = nullptr;
    Decorador *deco = nullptr;
    bool desciende = true;  //Permite o bloquea el descenso segun si hay mas hijos o no
    bool primeraVez = true;
    unsigned int i = 0;
    
    //Si el arbol de esta recorrendo
    if(nodoEnEjecucionDirecta != nullptr) //TO DO
    {        
        if(std::strcmp(nodoEnEjecucionDirecta->getNombre(), COMPOSICION) == 0 || std::strcmp(nodoEnEjecucionDirecta->getNombre(), RAIZ) == 0)
        {
            comp = (Composicion*) nodoEnEjecucionDirecta;
        }
        else if(std::strcmp(nodoEnEjecucionDirecta->getNombre(), DECORADOR) == 0)
        {
            deco = (Decorador*) nodoEnEjecucionDirecta;
        }
        //El bucle continua mientras el nodo actual no sea una tarea o tenga hijos para descender
        while((std::strcmp(nodoEnEjecucionDirecta->getNombre(), HOJA) != 0 && 
        (comp != nullptr && strlen(comp->GetAccion()) != 0) && desciende) || primeraVez)
        {
            if(std::strcmp(nodoEnEjecucionDirecta->getNombre(), COMPOSICION) == 0 || std::strcmp(nodoEnEjecucionDirecta->getNombre(), RAIZ) == 0)
            {
                comp = (Composicion*) nodoEnEjecucionDirecta;
            }
            else if(std::strcmp(nodoEnEjecucionDirecta->getNombre(), DECORADOR) == 0)
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
                //Se accede al hijo que toca en funcion del ultimo ID registrado en el recorrido
                while(ID >= comp->getHijos().at(i)->getID() && i < comp->getHijos().size())
                {
                    i++;
                }

                //De haber un hijo cuyo ID es superior al registrado, ese es el nuevo nodo
                if(i < comp->getHijos().size())
                {
                    nodoEnEjecucionDirecta = comp->getHijos().at(i);
                    ID++;
                }

                //En caso contrario, se asciende por el arbol para cambiar de rama hasta que no se pueda
                else if(nodoEnEjecucionDirecta->getPadre() != nullptr)
                {
                    nodoEnEjecucionDirecta = nodoEnEjecucionDirecta->getPadre();
                }

                //Si se ha llegado a la raiz y ya se ha recorrido el arbol
                else
                {
                    nodoEnEjecucionDirecta = nullptr;
                    ID = 0;
                }
                
            }

            //Si el nodo actual es un decorador se hace downcasting hacia dicha clase
            else if(deco != nullptr)
            {
                //Se comprueba el ID del decorador para saber si coincide y entra
                if(deco->getID() == ID)
                {
                    //Se detecta que tipo de final tiene el bucle del decorador
                    
                    const char * finalDecorador = deco->GetFin();

                    if(strcmp(finalDecorador, VERDADERO) == 0)
                    {
                        finBucle.push_back(0);
                    }
                    else if(strcmp(finalDecorador, RANDOM) == 0)
                    {
                        finBucle.push_back(1);
                    }
                    else
                    {
                        finBucle.push_back(-1);
                    }
                    bucleDecorador = true;
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

                //Si algun hijo falla en su tarea, el booleano es falso por lo tanto se igual el contador ID
                //al del decorador para volver a entrar al bucle
                else if(!exito)
                {
                    ID = nodoEnEjecucionDirecta->getID();
                }

                //Se accede al hijo que toca en funcion del ultimo ID registrado en el recorrido
                while(ID >= deco->getHijos().at(i)->getID() && i < deco->getHijos().size())
                {
                    i++;
                }

                //De haber un hijo cuyo ID es superior al registrado, ese es el nuevo nodo
                if(i < deco->getHijos().size())
                {
                    nodoEnEjecucionDirecta = deco->getHijos().at(i);
                    ID++;
                }
                //En caso contrario, se asciende por el arbol para cambiar de rama
                else
                {
                    nodoEnEjecucionDirecta = nodoEnEjecucionDirecta->getPadre();
                }
            }
            //En caso contrario, se asciende por el arbol para cambiar de rama
            else
            {
                nodoEnEjecucionDirecta = nodoEnEjecucionDirecta->getPadre();
            }
            comp = nullptr;
            deco = nullptr;
        }
        if(nodoEnEjecucionDirecta != nullptr)
        {
            Hoja  *hoja = (Hoja*) nodoEnEjecucionDirecta;
            //Se indican la tarea y el objetivo a ejecutar
            //Tarea
            const char* accion = hoja->GetAccion();
            if(strcmp(accion, MOVERSE) == 0)
            {
                arrayTareaObjetivo[0] = 0;
            }
            else if(strcmp(accion, ATACAR) == 0)
            {
                arrayTareaObjetivo[0] = 1;
            }
            else
            {
                arrayTareaObjetivo[0] = -1;
            }

            //Objetivo
            const char* objetivo = hoja->GetObjetivo();
            if(strcmp(objetivo, JUGADOR) == 0)
            {
                arrayTareaObjetivo[1] = 0;
            }
            else if(strcmp(objetivo, ZONA_COFRES) == 0)
            {
                arrayTareaObjetivo[1] = 1;
            }
            else
            {
                arrayTareaObjetivo[1] = -1;
            }
        }
        else
        {
            arrayTareaObjetivo[0] = -1;
            arrayTareaObjetivo[1] = -1;
            return 0;
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
            return 0;
        }
        else
        {
            nodoEnEjecucionDirecta = raiz;   //Obtenemos la raiz del arbol
            ID++;
            arrayTareaObjetivo[0] = -1;
            arrayTareaObjetivo[1] = -1;
            return 0;
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