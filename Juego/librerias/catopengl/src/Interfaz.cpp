#include "Interfaz.hpp"

Interfaz::Interfaz()
{
    _raiz = new TNodo();
    camaras.reserve(3);//dos camaras maximas
    luces.reserve(40);//30 luces como maximo
    gestorDeRecursos = new CatOpengl::Gestor;
}

Interfaz::~Interfaz()
{

}

void Interfaz::Remove()
{
    this->~Interfaz();
}

unsigned short Interfaz::AddCamara()
{

    TNodo * traslacion = new TNodo;
    TTransform * traslacionEnt = new TTransform;
    traslacion->setEntidad(traslacionEnt);

    TNodo * rotacion = new TNodo;
    TTransform * rotacionEnt = new TTransform;
    rotacion->setEntidad(rotacionEnt);

    TNodo * escalado = new TNodo;
    TTransform * escaladoEnt = new TTransform;
    escalado->setEntidad(escaladoEnt);

    //escalado al ser el nodo padre del objeto en cuestion (sea luz, camara, o malla), debe ser el que se le diga que no se ejecuta
    escaladoEnt->NoEjecutar();

    TNodo * camara = new TNodo;
    TCamara * camaraEn = new TCamara;
    camara->setEntidad(camaraEn);

    escalado->addHijo(rotacion);
    rotacion->addHijo(traslacion);
    traslacion->addHijo(camara);

    if(_raiz != nullptr)
    {
        camaras.push_back(escalado);
        _raiz->addHijo(escalado);

        unsigned short idnuevo = generarId();
        Nodo * nodo = new Nodo(); 
        nodo->id = idnuevo;//se pone el id
        nodo->recurso = escalado;//se agrega el nodo raiz de este recurso
        nodos.push_back(nodo);//se agrega a la lista de nodos general

        return idnuevo;
    }

    return 0;
}

unsigned short Interfaz::AddLuz()
{
    TNodo * traslacion = new TNodo;
    TTransform * traslacionEnt = new TTransform;
    traslacion->setEntidad(traslacionEnt);

    TNodo * rotacion = new TNodo;
    TTransform * rotacionEnt = new TTransform;
    rotacion->setEntidad(rotacionEnt);

    TNodo * escalado = new TNodo;
    TTransform * escaladoEnt = new TTransform;
    escalado->setEntidad(escaladoEnt);

    escaladoEnt->Ejecutar();
    
    TNodo * luz = new TNodo;
    TLuz * luzEn = new TLuz;
    luz->setEntidad(luzEn);

    escalado->addHijo(rotacion);
    rotacion->addHijo(traslacion);
    traslacion->addHijo(luz);

    if(_raiz != nullptr)
    {
        luces.push_back(escalado);
        _raiz->addHijo(escalado);
        
        unsigned short idnuevo = generarId();
        
        Nodo * nodo = new Nodo(); 
        nodo->id = idnuevo;//se pone el id
        nodo->recurso = escalado;//se agrega el nodo raiz de este recurso
        nodos.push_back(nodo);//se agrega a la lista de nodos general
        
        return idnuevo;
    }

    return 0;//no se hizo la luz
}

unsigned short Interfaz::AddMalla()
{
    return -1;
}


void Interfaz::Draw()
{
    if(_raiz != nullptr)
    {
        if(camaras.size() > 0)
        {
            //primero calculamos las matrices de view y projection

            //esto seria lo ultimo vamos a las model
            _raiz->draw();
        }
    }
}

unsigned short Interfaz::generarId()
{
    return ids++;
}