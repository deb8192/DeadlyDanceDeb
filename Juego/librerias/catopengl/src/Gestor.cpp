#include "Gestor.hpp"

//para clases singleton deben tener un indicador de que se ha creado el unico objeto
Gestor* Gestor::_unica_instancia = 0;
//fin indicador singleton

Gestor::Gestor()
{
    archivadores.reserve(300);//se reserva para cuarenta inicialmente (lo que veo mucho)
    imagenes.reserve(80);//reserva para las imagenes
}

Gestor::~Gestor()
{
    if(_unica_instancia && _unica_instancia != 0)
    {
        LimpiarRecursos();//borramos todos los recursos a nuestro cargo
        LimpiarImagenes();
        _unica_instancia = 0;//ponemos la variable static en blanco para que luego se pueda reiniciarlizar
    }
}

//Uso: se utiliza para buscar el recurso si lo encuentra y no lo tiene ya instanciado se instancia en memoria, devolviendo un id este id le sirve al que tiene la interfaz para crear objetos
//Entradas: recurso -> string de donde esta el archivo (ruta)
//Salidas: 0 significa que no se ha obtenido el recurso, => 1 significa que esta instanciado en esa direccion de memoria.
unsigned short Gestor::ObtenerRecurso(const char * _recurso,TNodo * _nodo, int num)
{
    unsigned short existeArchivador = buscarRecurso(_recurso);

    //comprobamos si existe
    if(existeArchivador > 0)
    {
        //existe archivador por lo que devolvemos el id
        Archivador * _archivador = recuperarRecurso(existeArchivador);

        if(_archivador != nullptr)
        {
            RMalla * malla = dynamic_cast<RMalla*>(_archivador->_recursos);//obtenemos recurso
            _nodo->GetEntidad()->setRecursoObjeto(malla);
        }

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
            archivador->_recursos = new RMalla(num);
            archivador->_recursos->CargarRecurso(_recurso);

            if(_nodo != nullptr)
            {
                RMalla * malla = dynamic_cast<RMalla*>(archivador->_recursos);
                _nodo->GetEntidad()->setRecursoObjeto(malla);
            }

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

Gestor::Archivador * Gestor::recuperarRecurso(unsigned short id)
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
            return archivadores[Icentro];
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
    return nullptr;
}

bool Gestor::LimpiarRecursos()
{
    if(archivadores.size() < 1)
    {
        return false;
    }

    for(long unsigned int i = 0; i < archivadores.size();i++)
    {
        if(archivadores[i]->_recursos != nullptr)
        {
            //std::cout << "Se borra recurso " << std::endl;
            delete archivadores[i]->_recursos;
            archivadores[i]->_recursos = nullptr;
        }

        delete archivadores[i];
    }
    archivadores.clear();

    return true;
}

bool Gestor::LimpiarImagenes()
{
    if(archivadores.size() < 1)
    {
        return false;
    }

    for(long unsigned int i = 0; i < imagenes.size();i++)
    {
        //std::cout << "Se borra image " << std::endl;
        delete imagenes[i];
    }

    imagenes.clear();

    return true;
}

unsigned char * Gestor::CargarImagen(const char * _ruta,int * height, int * width, int * nrComponents)
{
    //char * nombre = new char [strlen(_ruta)];//creamos la longitud de la ruta

    //strcpy(nombre,_ruta);//copiamos el contenido de la ruta al nombre
    //std::cout << "direccion memoria -> " << &_ruta << std::endl;
    int idImagen = buscarImagen(_ruta);//si existe nos devolvera el indice del vector imagenes

    if(idImagen != -1)
    {
        //sabiendo el indice le pasamos directamente el dato
        //std::cout << "Se carga imagen ya existente " << _ruta << std::endl;
        *height = imagenes[idImagen]->height;
        *width = imagenes[idImagen]->width;
        *nrComponents = imagenes[idImagen]->nrComponents;
        return imagenes[idImagen]->_imagen;
    }
    else
    {
        //creamos una imagen nueva y la metemos en el vector de imagenes
        Imagen * imagen = new Imagen();
        unsigned char * data = stbi_load(_ruta, &imagen->width, &imagen->height, &imagen->nrComponents, 0);
        
        if(data)
        {
            //std::cout << "Se crea nueva imagen " << _ruta << std::endl;
            imagen->_imagen = data;
            //imagen->_nombre = _ruta;
            imagen->_nombre = _ruta;
            //imagen->_nombre = _ruta;
            imagenes.push_back(imagen);
            *height = imagen->height;
            *width = imagen->width;
            *nrComponents = imagen->nrComponents;
            return imagen->_imagen;
        }
        else
        {
            //std::cout << "Fallo al cargar la textura: " << _ruta << std::endl;
            stbi_image_free(data);
            delete imagen;
        }

        //unsigned int * data = 
    }
    
    return nullptr;
}

int Gestor::buscarImagen(const char * ruta)
{
    //se realiza una busqueda completa hasta que se encuentra (esto queda para OPTIMIZAR)
    std::string cadena_recurso = ruta;//pasamos el const char a string 

    for(long unsigned int i = 0; i < imagenes.size();i++)
    {
        std::string cadena_actual = imagenes[i]->_nombre;//convertimos el nombre de la imagen a string

        if(cadena_recurso.compare(cadena_actual) == 0)//si es igual a 0, existe el recurso
        {
            return i;//devolvemos posicion vector 
        }

    }

    return -1;   
}