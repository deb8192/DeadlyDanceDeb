#include "TNodo.hpp"
#include "iostream"

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
        entidad->remove();
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
            hijos[i] = nullptr;
            hijos.erase(hijos.begin() + i); 
        }

        hijos.resize(0);
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
    hijos.push_back(hijo);

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
void TNodo::draw()
{
    
    std::cout << " Pintando nodo " << std::endl;

    if(entidad && entidad != nullptr)
    {
        entidad->beginDraw();
    }

    for(std::size_t i=0 ; i < hijos.size() ; i++)
    {
        hijos[i]->draw();
    }

    if(entidad && entidad != nullptr)
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