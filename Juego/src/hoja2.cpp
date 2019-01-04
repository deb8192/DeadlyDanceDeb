#include "hoja2.hpp"

hoja2::hoja2(hoja2 * padr, hoja2 * hij)
{
    padre = padr;//se agrega como padre
    hijos.push_back(hij);//se agrega como hijo
    
    esRepetitivo = false;
    numeroRepeticiones = 0;
    repeticionActual = 0;
    comportamiento = -1;
}

hoja2::hoja2()
{
    padre = nullptr;
    esRepetitivo = false;
    numeroRepeticiones = 0;
    repeticionActual = 0;
    comportamiento = -1;
}

hoja2::~hoja2(void)
{
    if(hijos.size() > 0)
    {
        for(std::size_t i=0;i<hijos.size();i++)
        {
            //hijos[i].~hoja2();
            //delete hijos[i];
        }
    }
    //el resto de variables se destruyen solas al no ser news
}

void hoja2::setPadre(hoja2 * padr)
{
    padre = padr; //se pone la hoja que se ha pasado como padre de esta hoja, esto no significa que sea la raiz solo que es su padre
}

void hoja2::agregarHijo(hoja2 * hij)
{
    hijos.push_back(hij);//se agrega como hijo
}

//si es cero es la raiz por lo que no tiene comportamiento solo pasa al primer hijo si este devuelve false al siguiente y asi sucesivamente a no ser que sea repetitiva
void hoja2::definirComportamientoHoja(int tipo)
{
    comportamiento = tipo;// el -1 es que no esta definido, 0 es que es la raiz
}

void hoja2::definirRepiticion(bool rep)
{
    esRepetitivo = rep; 
}

void hoja2::definirNumeroRepeticiones(int numero)
{
    numeroRepeticiones = numero;
}

int hoja2::conseguirComportamiento()
{
    return comportamiento;
}

hoja2 * hoja2::siguiente(hoja2 * yo)
{
    hoja2 * nueva = nullptr;

    if(hijos.size() > 0)
    {
        for(std::size_t i=0;i<hijos.size();i++)
        {
            if(nueva == nullptr && yo != hijos[i])//para el primero si no coincide con el que nos han pasado lo ponemos como el primero
            {
                nueva = hijos[i];
            }
            else //si coincide alguna vez lo ponemos como nullptr
            {
                if(yo == hijos[i])
                {
                    nueva = nullptr; //si bay un proximo hijo lo pasara
                }
            }
        }
    }

    return nueva;
}

hoja2 * hoja2::siguienteRama(hoja2 * yo)
{
    if(getPadre() != nullptr)
    {
        hoja2 * nueva = nullptr; //asignamos nulo
        hoja2 * padre_yo = getPadre(); //esto nos da el padre de la hoja donde estamos para comprobar los hijos
        nueva = padre_yo->siguiente(yo);//nos da el siguiente hijo de la rama padre (la hermana de esta rama)
        
        if(nueva != nullptr)
        {
            return nueva; 
        }
        else
        {
            nueva = padre_yo->siguienteRama(padre_yo); //hacemos llamada recursiva entre hojas para encontrar una rama
            return nueva;
        }
        //buscamos de nuevo el padre esta si tiene hijos
    }
    return nullptr;
}

bool hoja2::getEsRepetitivo()
{
    return esRepetitivo;
}

int hoja2::getNumeroRepeticiones()
{
    return numeroRepeticiones;
}

void hoja2::setRepeticionActual(int valor)
{
    repeticionActual = valor;
}

int hoja2::getRepeticionActual()
{
    return repeticionActual;
}

hoja2 * hoja2::getPadre()
{
    return padre;
}