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

unsigned short Interfaz::AddCamara()
{

    TNodo * traslacion = new TNodo;
    TTransform * traslacionEnt = new TTransform;
    traslacionEnt->trasladar(0,0,0);
    traslacion->setEntidad(traslacionEnt);

    TNodo * rotacion = new TNodo;
    TTransform * rotacionEnt = new TTransform;
    rotacionEnt->rotar(0,0,0,0);
    rotacion->setEntidad(rotacionEnt);

    TNodo * escalado = new TNodo;
    TTransform * escaladoEnt = new TTransform;
    rotacionEnt->escalar(0,0,0);
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
    traslacionEnt->trasladar(0,0,0);
    traslacion->setEntidad(traslacionEnt);

    TNodo * rotacion = new TNodo;
    TTransform * rotacionEnt = new TTransform;
    rotacionEnt->rotar(0,0,0,0);
    rotacion->setEntidad(rotacionEnt);

    TNodo * escalado = new TNodo;
    TTransform * escaladoEnt = new TTransform;
    rotacionEnt->escalar(0,0,0);
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

unsigned short Interfaz::AddMalla(const char * archivo)
{
    
    TNodo * traslacion = new TNodo;
    TTransform * traslacionEnt = new TTransform;
    traslacionEnt->trasladar(0,0,0);
    traslacion->setEntidad(traslacionEnt);

    TNodo * rotacion = new TNodo;
    TTransform * rotacionEnt = new TTransform;
    rotacionEnt->rotar(0,0,0,0);
    rotacion->setEntidad(rotacionEnt);

    TNodo * escalado = new TNodo;
    TTransform * escaladoEnt = new TTransform;
    rotacionEnt->escalar(0,0,0);
    escalado->setEntidad(escaladoEnt);

    TNodo * malla = new TNodo;
    TMalla * mallaEn = new TMalla;
    malla->setEntidad(mallaEn);

    escalado->addHijo(rotacion);
    rotacion->addHijo(traslacion);
    traslacion->addHijo(malla);

    std::cout << "00" << std::endl;
    unsigned short id_recurso = gestorDeRecursos->ObtenerRecurso(archivo,malla);//obtenemos el id del recurso en memoria (para ser procesado por opengl)
    std::cout << "0" << std::endl;

    if(id_recurso != 0)
    {
        if(_raiz != nullptr)
        {
            std::cout << "1" << std::endl;
            _raiz->addHijo(escalado);//se agrega al arbol
            std::cout << "2" << std::endl;
            unsigned short idnuevo = generarId();//se genera un id 
            std::cout << "3" << std::endl;
            
            Nodo * nodo = new Nodo(); 
            std::cout << "4" << std::endl;
            nodo->id = idnuevo;//se pone el id
            std::cout << "5" << std::endl;
            nodo->recurso = escalado;//se agrega el nodo raiz de este recurso
            std::cout << "6" << std::endl;
            nodo->idRecurso = id_recurso;//se agrega id del recurso (por si se queria cambiar o borrar)
            std::cout << "7" << std::endl;
            nodos.push_back(nodo);//se agrega a la lista de nodos general
            std::cout << "8" << std::endl;

            return idnuevo;
        }
    }

    //ahora le pasamos este al cargador para asociar la malla a este id
    return 0;
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
    return ++ids;
}

Interfaz::Nodo * Interfaz::buscarNodo(unsigned short id)
{
    unsigned short Iarriba = ((unsigned short)(nodos.size()-1));
    unsigned short Iabajo = 0;
    unsigned short Icentro;
    while (Iabajo <= Iarriba)
    {
        Icentro = (Iarriba + Iabajo)/2;
        if (nodos[Icentro]->id == id)
        {
            return nodos[Icentro];
        }
        else
        {
            if (id < nodos[Icentro]->id)
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

void Interfaz::Trasladar(unsigned char id,float x,float y,float z)
{
    Nodo * nodo = buscarNodo(id);

    if(nodo != nullptr) 
    {
        TNodo * tnodo = nodo->recurso->GetNieto(1);
        if(tnodo != nullptr)
        {
            tnodo->GetEntidad()->trasladar(x,y,z);  
        }
    }
}   

void Interfaz::Rotar(unsigned char id,float grados,float x,float y,float z)
{
    Nodo * nodo = buscarNodo(id);

    if(nodo != nullptr)
    {
        TNodo * tnodo = nodo->recurso->GetHijo(1);
        if(tnodo != nullptr)
        {
            tnodo->GetEntidad()->rotar(grados,x,y,z);
        }
    }
}

void Interfaz::Escalar(unsigned char id,float x,float y,float z)
{
    Nodo * nodo = buscarNodo(id);

    if(nodo != nullptr)
    {
        nodo->recurso->GetEntidad()->escalar(x,y,z);
    }
}