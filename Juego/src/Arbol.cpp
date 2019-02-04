#include "Arbol.hpp"

Arbol::Arbol(Nodo *root, const char* name)
{
    raiz = root;
    nodoEnEjecucionDirecta = nullptr;
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

int Arbol::ContinuarSiguienteNodo(bool primeraVez)
{
    Composicion *comp;
    Decorador *deco;
    bool desciende = true;  //Permite o bloquea el descenso segun si hay mas hijos o no
    
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
        (comp != nullptr && comp->GetAccion() != "") && desciende) || primeraVez)
        {
            comp = (Composicion*) nodoEnEjecucionDirecta;
            //Es para asegurar que entra en el recorrido en caso de que tenga que ascender
            if(primeraVez)
            {
                primeraVez = false;
            }

            unsigned int i = 0;
            //Si el nodo actual es una composicion se hace downcasting hacia dicha clase
            if(comp != nullptr)
            {

                //Se accede al hijo que toca en funcion del ultimo ID registrado en el recorrido
                while(ID >= comp->getHijos().at(i)->getID())
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
                deco = (Decorador*) nodoEnEjecucionDirecta;
                //Se accede al hijo que toca en funcion del ultimo ID registrado en el recorrido
                while(ID >= deco->getHijos().at(i)->getID())
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
        }
        if(nodoEnEjecucionDirecta != nullptr)
        {
            return 1;
        }
        else
        {
            return 0;
        }
        
    }

    else
        {
            //Se comienza a recorrer el arbol
            if(raiz == nullptr) //si es nula la raiz no se ha definido arbol
            {
                desciende = false;
                return 0;
            }
            else
            {
                nodoEnEjecucionDirecta = raiz;   //Obtenemos la raiz del arbol
                ID++;
                return 1;
            }
        }
    
    

    estado = true;//sale arbol*/
    return 0;//no hace nada
}

Nodo * Arbol::GetRaiz()
{
    return raiz;
}

Nodo * Arbol::GetNodoEnEjecucionDirecta()
{
    return nodoEnEjecucionDirecta;
}