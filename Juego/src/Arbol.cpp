#include "Arbol.hpp"

Arbol::Arbol(Nodo *root, const char* name)
{
    raiz = (Composicion*) root;
}
/**************     anyadirHijosComposicionf      *****************
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
        raiz->addHijo(nod);
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

int Arbol::ContinuarSiguienteNodo(bool valor)
{
    Composicion comp;
    Decorador deco;
    /*if(nodoEnEjecucionDirecta != nullptr)//esto significa que este arbol se esta ejecutando o entrado en una tarea repetitiva
    {
        if(valor)
        {
            if(strcmp(nodoEnEjecucionDirecta->getNombre(), COMPOSICION) == 0)
            {
                Composicion*
            }
            Nodo * nodo = nodoEnEjecucionDirecta->siguiente(nodoEnEjecucionDirecta);
            nodoEnEjecucionDirecta = nodo;
            if(nodoEnEjecucionDirecta == nullptr)
            {
                //esto significa que no hay mas tareas en esta rama por lo que reiniciamos 
                estado = false;
                return 0;//esto significa que no hay mas tareas en esta rama por lo que reiniciamos 
            }
            else
            {
                //esto significa que hay una siguiente tarea que comprobar
                estado = true;
                return nodoEnEjecucionDirecta->conseguirComportamiento();
            }
        }
        else
        {
            //es false por lo que pasamos a la siguiente rama por arriba o hermana vamos al padre y le preguntamos si tiene otro hijo despues que este, si lo tiene se lo pedimos
            Nodo * nodo = nodoEnEjecucionDirecta->siguienteRama(nodoEnEjecucionDirecta);
            nodoEnEjecucionDirecta = nodo;
            if(nodoEnEjecucionDirecta == nullptr)//no hay mas ramas no se cumple nada (se puede decir que se queda parado)
            {
                estado = false;
                return 0;
            }
            else
            {
                //si que hay rama a comprobar
                estado = true;
                return nodoEnEjecucionDirecta->conseguirComportamiento();
            }
        } 
    }*/
    bool primeraVez = true;
    bool desciende = true;  //Permite o bloquea el descenso segun si hay mas hijos o no
    int ID = 0;             //Por cada descenso, aumentara el ID y servira para elegir al siguiente hijo
    
    //El bucle continua mientras el nodo actual no sea una tarea o tenga hijos para descender
    while((std::strcmp(nodoEnEjecucionDirecta->getNombre(), HOJA) != 0 && 
    (std::strcmp(nodoEnEjecucionDirecta->getNombre(), COMPOSICION) != 0 && 
    (Composicion *) nodoEnEjecucionDirecta->GetAccion() != NULL) && desciende) || primeraVez)
    {
        if(primeraVez)
        {
            primeraVez = false;
        }
        //No se comienza a recorrer el arbol
        if(nodoEnEjecucionDirecta != nullptr)
        {
            unsigned int i = 0;
            //Si el nodo actual es una composicion se hace downcasting hacia dicha clase
            if(std::strcmp(nodoEnEjecucionDirecta->getNombre(), COMPOSICION) == 0)
            {
                Composicion comp = (Composicion) nodoEnEjecucionDirecta;

                //Se accede al hijo que toca en funcion del ultimo ID registrado en el recorrido
                while(ID <= comp.getHijos().at(i)->getID())
                {
                    i++;
                }

                //De haber un hijo cuyo ID es superior al registrado, ese es el nuevo nodo
                if(i < comp.getHijos().size())
                {
                    nodoEnEjecucionDirecta = comp.getHijos().at(i);
                    ID++;
                }
                //En caso contrario, se asciende por el arbol para cambiar de rama
                else
                {
                    nodoEnEjecucionDirecta = nodoEnEjecucionDirecta->getPadre();
                }
            }

            //Si el nodo actual es un decorador se hace downcasting hacia dicha clase
            else if(std::strcmp(nodoEnEjecucionDirecta->getNombre(), DECORADOR) == 0)
            {
                Decorador deco = (Decorador) nodoEnEjecucionDirecta;
                
                //Se accede al hijo que toca en funcion del ultimo ID registrado en el recorrido
                while(ID <= deco.getHijos().at(i)->getID())
                {
                    i++;
                }

                //De haber un hijo cuyo ID es superior al registrado, ese es el nuevo nodo
                if(i < deco.getHijos().size())
                {
                    nodoEnEjecucionDirecta = deco.getHijos().at(i);
                    ID++;
                }
                //En caso contrario, se asciende por el arbol para cambiar de rama
                else
                {
                    nodoEnEjecucionDirecta = nodoEnEjecucionDirecta->getPadre();
                }
            }
        }
        else
        {
            //Se comienza a recorrer el arbol
            if(raiz == nullptr) //si es nula la raiz no se ha definido arbol
            {
                desciende = false;
            }
            else
            {
                nodoEnEjecucionDirecta = raiz;   //Obtenemos la raiz del arbol
                ID++;
            }


            /*nodoEnEjecucionDirecta = raiz;   //Obtenemos la raiz del arbol
            if(nodoEnEjecucionDirecta == nullptr)
            {
                estado = false;
                return 0;
            }
            else
            {
                if(std::strcmp(nodoEnEjecucionDirecta->getNombre(), COMPOSICION) == 0)
                {

                }
                estado = true;
                return nodoEnEjecucionDirecta->conseguirComportamiento();
            }*/
        }
    }

    estado = true;//sale arbol*/
    return 0;//no hace nada
}