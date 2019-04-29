#include "TNodo.hpp"
#include <iostream>

//USO::inicializa las variables de entidad y padre a nullptr
TNodo::TNodo()
{
    entidad = nullptr;
    padre = nullptr;
}

//USO: sirve para eliminarse a si mismo y a sus hijos
TNodo::~TNodo()
{
    if(entidad != nullptr)
    {
        delete entidad;
    }
    
    entidad = nullptr;
    
    if(hijos.size() > 0)
    {
        for(std::size_t i=0 ; i < hijos.size() ; i++)
        {
            if(hijos[i] && hijos[i] != nullptr)
            {
                delete hijos[i];
            }
        }

        hijos.clear();
    }  

    padre = nullptr;
}

//USO: comprueba si existe el hijo y te devuelve una salida
//SALIDAS: si existe - true, no existe - false  
bool TNodo::existeHijo(TNodo* hijo)
{
    if(hijos.size() > 0) //comprobamos que el vector sea mayor que 0 de longitud
    {
        //nos recorremos la lista de vectores comprobando si son iguales
        for(std::size_t i=0 ; i < hijos.size() ; i++)
        {
            if(hijo == hijos[i])
            {
                return true;
            }
        }
    }

    return false;
}

//USO: se agrega un hijo al final del vector de hijos, se devuelve la posicion en donde se ha agregado o -1 si ya existia
//SALIDAS: => 0 (posicion del hijo), -1 ya existia el hijo
int TNodo::addHijo(TNodo* hijo)
{
    //comprobamos que no existe el hijo
    if(existeHijo(hijo))
    {
        return -1;//no se puede agregar porque ya existe
    }

    //agregamos el hijo al final del vector
    hijos.push_back(move(hijo));

    std::size_t longitud = hijos.size();//recuperamos la longitud
    int posicion = (int)longitud;//la pasamos a int
    posicion = posicion-1;//le restamos una para que se la posicion real del vector (porque empieza por cero)
    return posicion;//le devolvemos la posicion del hijo que se agregado
}

//USO: se elimina un hijo del vector de hijos en el caso de que exista, y se devuelve la posicon que se ha borrado
//SALIDAS: => 0 (posicion borrada del hijo), -1 (no existe el hijo o no tiene hijos)
//CUIDADO: No se elimina el hijo solo el puntero al hijo, esto se hace por si se quiere mover a otra rama
int TNodo::remHijo(TNodo* hijo)
{
    if(hijos.size() > 0) //comprobamos que el vector sea mayor que 0 de longitud
    {
        //nos recorremos la lista de vectores comprobando si son iguales
        for(std::size_t i=0 ; i < hijos.size() ; i++)
        {
            if(hijo == hijos[i])
            {
                hijos[i] = nullptr;
                hijos.erase(hijos.begin() + i);
                return (int)i;
            }
        }
    }

    return -1;
}

//USO: define la entidad(funcionalidad) que tiene este nodo, eso si es compatible con su estado (transformacion o luz,camara,malla)
//SALIDA: true (si se ha cambiado), false (no se cambio porque no es compatible con el tipo de funcion (transformacion o luz,camara,malla)) 
bool TNodo::setEntidad(TEntidad * en)
{
    if(entidad == nullptr || en != entidad)
    {
        entidad = en;
        return true;
    }
    return false;
}

//USO: devuelve el padre 
//SALIDAS: puntero a TNodo si existe padre, nullptr si no existe
TNodo * TNodo::getPadre()
{
    return padre;
}

//USO: modifica el padre de este nodo
void TNodo::setPadre(TNodo * papa)
{
    padre = papa;
}

//USO: se recorre sus nodos en postorden
//SALIDAS: Llama a todas las funciones no hay salida aparte de lo que hace la funcion internamente
void TNodo::draw(unsigned int modo)
{

    if(entidad != nullptr)
    {
        entidad->beginDraw();
    }

    for(std::size_t i=0 ; i < hijos.size() ; i++)
    {
        if(modo == 0 && entidad == nullptr && hijos[i] != nullptr && hijos[i]->GetEntidad() != nullptr)
        {
            if(hijos[i]->GetEntidad()->GetEjecutar())
            {
                //std::cout << "entro aqui" << std::endl;
                hijos[i]->draw(0);
            }
        }
        else
        {
            if(hijos[i] != nullptr && hijos[i]->GetEntidad() != nullptr)
            {
                //std::cout << "entro alli" << std::endl;
                hijos[i]->draw(0);
            }
        }
    }

    if(entidad != nullptr)
    {
        entidad->endDraw();
    }



}

//Uso: devuelve la entidad que tiene este nodo
//Salida: puntero a entidads
TEntidad * TNodo::GetEntidad()
{
    return entidad;
}

//Uso:: devuelve el nodo hijo que le pidas, estan en orden de insercion
//Entradas: se empieza desde el hijo 1
//Salida: TNodo puntero
TNodo * TNodo::GetHijo(unsigned short numeroDeHijo)
{
    if(((long unsigned int)(numeroDeHijo-1)) < hijos.size())
    {
        return hijos[(numeroDeHijo-1)];
    }
    
    return nullptr;
}

TNodo * TNodo::GetNieto(unsigned short numeroDeHijo)
{
    if(((long unsigned int)(numeroDeHijo-1)) < hijos.size())
    {
        TNodo * hijo = hijos[(numeroDeHijo-1)];
        if(hijo != nullptr)
        {
            return hijo->GetHijo(1);
        }
    }
    
    return nullptr;
}

void TNodo::BorrarEscena()
{
    if(entidad == nullptr)//solo se ejecuta en raiz
    {
        for(std::size_t i=0 ; i < hijos.size() ; i++)
        {
            if(hijos[i] != nullptr)//comprobamos que no sea nulo para borrarlo si lo es se borra su posicion
            {
                if(!hijos[i]->GetEntidad()->GetGui()  && (!hijos[i]->GetEntidad()->GetCamara()))
                {
                    //no es gui por lo que borramos
                    delete hijos[i];
                    hijos.erase(hijos.begin()+i); 
                    i--;
                }
            }
        }      
    }
}

void TNodo::BorrarGui()
{
    if(entidad == nullptr)//solo se ejecuta en raiz
    {
        for(std::size_t i=0 ; i < hijos.size() ; i++)
        {
            if(hijos[i] != nullptr)//comprobamos que no sea nulo para borrarlo si lo es se borra su posicion
            {
                if(hijos[i]->GetEntidad())
                {
                    if(hijos[i]->GetEntidad()->GetGui() && (!hijos[i]->GetEntidad()->GetCamara()))
                    {
                        //es gui por lo que borramos
                        delete hijos[i];
                        hijos.erase(hijos.begin()+i); 
                        i--;
                    }
                }
                else
                {
                    hijos.erase(hijos.begin()+i); 
                    i--;                   
                }
                
            }
        }      
    }
}

void TNodo::DeshabilitarNodo()
{
    if(entidad != nullptr)
    {
        entidad->NoEjecutar();
    }
}

void TNodo::HabilitarNodo()
{
    if(entidad != nullptr)
    {
        entidad->Ejecutar();
    }
}