#include "CatOpengl.hpp"

Gestor::Gestor()
{
    archivadores.reserve(40);//se reserva para cuarenta inicialmente (lo que veo mucho)
}

Gestor::~Gestor()
{

}

void Gestor::Remove()
{
    this->~Gestor();
}

//Uso: se utiliza para buscar el recurso si lo encuentra y no lo tiene ya instanciado se instancia en memoria, devolviendo un id este id le sirve al que tiene la interfaz para crear objetos
//Entradas: recurso -> string de donde esta el archivo (ruta)
//Salidas: 0 significa que no se ha obtenido el recurso, => 1 significa que esta instanciado en esa direccion de memoria.
unsigned short Gestor::ObtenerRecurso(const char * _recurso,TNodo * _nodo)
{
    unsigned short existeArchivador = buscarRecurso(_recurso); 
    
    //comprobamos si existe
    if(existeArchivador > 0)
    {
        //existe archivador por lo que devolvemos el id
        return existeArchivador;
    }//no existe lo creamos
    else
    {
        //comprobamos que no vamos a salirnos del limite de objetos que son 65535
        if((ids+1) <= 65535)
        {
           
            Archivador * archivador = new Archivador;
            archivador->id = generarId();
            archivador->_nombre = _recurso;
            archivador->_recursos = new RMalla();
            archivador->_recursos->CargarRecurso(_recurso);
            //detectar tipo de recurso y crear su clase especializada (imagen,malla o texto plano, faltarian fuentes)

            archivadores.push_back(archivador);
            
            return archivador->id;
        }
    }
    
    return 0;
}

//Uso: destruye el objeto en memoria
//Entradas: IDrecurso este id es el archivador que tiene asignado busca entre los ids y si es lo borra de memoria
//Salidas: true si lo ha eliminado, false si no ha podido eliminarlo bien porque no exista o porque este vacio los archivadores.
bool Gestor::DestruirObjeto(unsigned short IDrecurso)
{
    return false;
}

//Uso: genera un id para los archivadores
//Salidas: devuelve un numero como id
unsigned short Gestor::generarId()
{
    ids++;
    return ids;
}

//Uso: cuando se quiere saber si un elemento con un id existe se debe utilizar esta funcion
//Entradas: id del recurso a buscar
//Salidas: true si existe, false si no existe
bool Gestor::buscarRecurso(unsigned short id)
{
    //se realiza una busqueda binaria
    unsigned short Iarriba = ((unsigned short)(archivadores.size()-1));
    unsigned short Iabajo = 0;
    unsigned short Icentro;
    while (Iabajo <= Iarriba)
    {
        Icentro = (Iarriba + Iabajo)/2;
        if (archivadores[Icentro]->id == id)
        {
            return true;
        }
        else
        {
            if (id < archivadores[Icentro]->id)
            {
                Iarriba=Icentro-1;
            }
            else
            {
                Iabajo=Icentro+1;
            }
        }
    }
    return false;
}

//Uso: busca el recurso en el vector de recursos
//Entradas: cadena char *
//Salidas: 0 si no la encuentra, igual o mayor que 1 si la encuentra (este es el id del archivador en memoria)
unsigned short Gestor::buscarRecurso(const char * rutaRecurso)
{
    //se realiza una busqueda completa hasta que se encuentra (esto queda para OPTIMIZAR)
    std::string cadena_recurso = rutaRecurso;
    for(long unsigned int i = 0; i < archivadores.size();i++)
    {
        std::string cadena_actual = archivadores[i]->_nombre;

        if(cadena_recurso.compare(cadena_actual) == 0)
        {
            return archivadores[i]->id;
        }

    }

    return 0;
}