#include "Interfaz.hpp"

Interfaz::Interfaz()
{
    _raiz = new TNodo();//se crea un nodo raiz(sin entidad) para agregar ramas (camaras,mallas,luces)
    camaras.reserve(3);//dos camaras maximas
    luces.reserve(40);//30 luces como maximo
    imagenes.reserve(20);//20 imagenes de interfaz
    textos.reserve(20);//20 imagenes de textos
    gestorDeRecursos = new CatOpengl::Gestor;
    ventana_inicializada = true;//se pone para que entra a inicializar por defecto
    window = nullptr;//se pone para saber que no esta inicializada
    nodos.reserve(600);//para almacenar el objeto
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    ModoOneCamara = true;
}

Interfaz::~Interfaz()
{

}

unsigned short Interfaz::AddCamara()
{
    //std::cout << "SE CREA LUZ" << std::endl;
    if(ModoOneCamara && camaras.size() > 0)
    {
        //se devuelve el id de la primera camara 
        return camaras[0]->id;
    }
    else
    {
        //std::cout << "SE CREA CAMARA" << std::endl;
        if(ventana_inicializada)
        {
            ventanaInicializar();
            ventana_inicializada = false;
        }

        TNodo * traslacion = new TNodo;
        TTransform * traslacionEnt = new TTransform;
        traslacionEnt->trasladar(0,0,0);
        traslacion->setEntidad(traslacionEnt);

        TNodo * rotacion = new TNodo;
        TTransform * rotacionEnt = new TTransform;
        rotacionEnt->rotar(0,1,1,1);
        rotacion->setEntidad(rotacionEnt);

        TNodo * escalado = new TNodo;
        TTransform * escaladoEnt = new TTransform;
        escaladoEnt->escalar(1,1,1);
        escalado->setEntidad(escaladoEnt);

        //escalado al ser el nodo padre del objeto en cuestion (sea luz, camara, o malla), debe ser el que se le diga que no se ejecuta
        escaladoEnt->EsCamara();
        escaladoEnt->NoEjecutar();

        TNodo * camara = new TNodo;
        TCamara * camaraEn = new TCamara(window->getWidth(),window->getHeight());
        camaraEn->SetShader(shaders[0]);
        camara->setEntidad(camaraEn);

        escalado->addHijo(rotacion);
        rotacion->addHijo(traslacion);
        traslacion->addHijo(camara);

        if(_raiz != nullptr)
        {
            _raiz->addHijo(escalado);
            unsigned short idnuevo = generarId();
            Nodo * nodo = new Nodo();
            nodo->id = idnuevo;//se pone el id
            nodo->recurso = escalado;//se agrega el nodo raiz de este recurso
            nodo->tipo = 0;
            nodo->activo = true;//activo la camara por defecto cuando se activa
            camaras.push_back(nodo);
            nodos.push_back(nodo);//se agrega a la lista de nodos general
            return idnuevo;
        }
    }

    return 0;
}

unsigned short Interfaz::AddLuz(int tipo)
{
    //std::cout << "SE CREA LUZ" << std::endl;
    if(ventana_inicializada)
    {
        ventanaInicializar();
        ventana_inicializada = false;
    }

    TNodo * traslacion = new TNodo;
    TTransform * traslacionEnt = new TTransform;
    traslacionEnt->trasladar(0,0,0);
    traslacion->setEntidad(traslacionEnt);

    TNodo * rotacion = new TNodo;
    TTransform * rotacionEnt = new TTransform;
    rotacionEnt->rotar(0,1,1,1);
    rotacion->setEntidad(rotacionEnt);

    TNodo * escalado = new TNodo;
    TTransform * escaladoEnt = new TTransform;
    escaladoEnt->escalar(1,1,1);
    escalado->setEntidad(escaladoEnt);

    escaladoEnt->NoEjecutar();

    TNodo * luz = new TNodo;
    TLuz * luzEn = new TLuz(tipo);
    luzEn->SetShader(shaders[0]);
    luzEn->setNumberoflight(luces.size());
    luz->setEntidad(luzEn);

    escalado->addHijo(rotacion);
    rotacion->addHijo(traslacion);
    traslacion->addHijo(luz);

    if(_raiz != nullptr)
    {
       
        _raiz->addHijo(escalado);

        unsigned short idnuevo = generarId();

        Nodo * nodo = new Nodo();
        nodo->id = idnuevo;//se pone el id
        nodo->recurso = escalado;//se agrega el nodo raiz de este recurso
        nodo->tipo = 1;
        nodo->activo = true;
        nodos.push_back(nodo);//se agrega a la lista de nodos general
        luces.push_back(nodo);//se agrega la luz a la lista de luces

        return idnuevo;
    }

    return 0;//no se hizo la luz
}

unsigned short Interfaz::AddMalla(const char * archivo, int initf)
{
    //std::cout << "SE CREA MALLA" << std::endl;
    if(ventana_inicializada)
    {
        ventanaInicializar();
        ventana_inicializada = false;
    }

    TNodo * traslacion = new TNodo;
    TTransform * traslacionEnt = new TTransform;
    traslacionEnt->trasladar(0,0,0);
    traslacion->setEntidad(traslacionEnt);

    TNodo * rotacion = new TNodo;
    TTransform * rotacionEnt = new TTransform;
    rotacionEnt->rotar(0,1,1,1);
    rotacion->setEntidad(rotacionEnt);

    TNodo * escalado = new TNodo;
    TTransform * escaladoEnt = new TTransform;
    escaladoEnt->escalar(1,1,1);
    escalado->setEntidad(escaladoEnt);

    TNodo * malla = new TNodo;
    TMalla * mallaEn = new TMalla(initf);
    mallaEn->SetShader(shaders[0]);
    malla->setEntidad(mallaEn);

    escalado->addHijo(rotacion);
    rotacion->addHijo(traslacion);
    traslacion->addHijo(malla);

    unsigned short id_recurso = gestorDeRecursos->ObtenerRecurso(archivo,malla,initf);//obtenemos el id del recurso en memoria (para ser procesado por opengl)


    if(id_recurso != 0)
    {
        if(_raiz != nullptr)
        {
            _raiz->addHijo(escalado);//se agrega al arbol
            unsigned short idnuevo = generarId();//se genera un id

            Nodo * nodo = new Nodo();
            nodo->id = idnuevo;//se pone el id
            nodo->recurso = escalado;//se agrega el nodo raiz de este recurso
            nodo->idRecurso = id_recurso;//se agrega id del recurso (por si se queria cambiar o borrar)
            nodo->tipo = 2;
            nodo->activo = true;
            nodos.push_back(nodo);//se agrega a la lista de nodos general
            return idnuevo;
        }
    }
    //ahora le pasamos este al cargador para asociar la malla a este id
    return 0;
}

unsigned short Interfaz::AddImagen(const char * archivo, unsigned int x, unsigned int y, float scale)
{
    //std::cout << "SE CREA IMAGEN" << std::endl;
    if(ventana_inicializada)
    {
        ventanaInicializar();
        ventana_inicializada = false;
    }

    TNodo * traslacion = new TNodo;
    TTransform * traslacionEnt = new TTransform;
    traslacionEnt->trasladar(0,0,0);
    traslacion->setEntidad(traslacionEnt);

    TNodo * rotacion = new TNodo;
    TTransform * rotacionEnt = new TTransform;
    rotacionEnt->rotar(0,1,1,1);
    rotacion->setEntidad(rotacionEnt);

    TNodo * escalado = new TNodo;
    TTransform * escaladoEnt = new TTransform;
    escaladoEnt->escalar(1,1,1);
    escalado->setEntidad(escaladoEnt);

    escaladoEnt->EsGui();
    escaladoEnt->NoEjecutar();

    TNodo * imagen = new TNodo;
    TPlano * imagenEn = new TPlano(archivo,x,y,scale,shaders[1],window->getWidth(), window->getHeight());
    imagen->setEntidad(imagenEn);

    escalado->addHijo(rotacion);
    rotacion->addHijo(traslacion);
    traslacion->addHijo(imagen);

    if(_raiz != nullptr)
    {
        _raiz->addHijo(escalado);

        unsigned short idnuevo = generarId();

        Nodo * nodo = new Nodo();
        nodo->id = idnuevo;//se pone el id
        nodo->recurso = escalado;//se agrega el nodo raiz de este recurso
        nodo->tipo = 4;
        nodo->activo = true;
        nodos.push_back(nodo);//se agrega a la lista de nodos general
        imagenes.push_back(nodo);//se agrega a la lista de imagenes
        return idnuevo;
    }

    return 0;
}

unsigned short Interfaz::AddTexto(std::string font, GLuint fontSize)
{
    //std::cout << "SE CREA TEXTO" << std::endl;

    if(ventana_inicializada)
    {
        ventanaInicializar();
        ventana_inicializada = false;
    }

    TNodo * traslacion = new TNodo;
    TTransform * traslacionEnt = new TTransform;
    traslacionEnt->trasladar(0,0,0);
    traslacion->setEntidad(traslacionEnt);

    TNodo * rotacion = new TNodo;
    TTransform * rotacionEnt = new TTransform;
    rotacionEnt->rotar(0,1,1,1);
    rotacion->setEntidad(rotacionEnt);

    TNodo * escalado = new TNodo;
    TTransform * escaladoEnt = new TTransform;
    escaladoEnt->escalar(1,1,1);
    escalado->setEntidad(escaladoEnt);

    escaladoEnt->EsGui();
    escaladoEnt->NoEjecutar();

    TNodo * texto = new TNodo;
    TTexto * textoEn = new TTexto(window->getWidth(),window->getHeight(),shaders[2]);
    textoEn->CargarFuente(font,fontSize);
    texto->setEntidad(textoEn);

    escalado->addHijo(rotacion);
    rotacion->addHijo(traslacion);
    traslacion->addHijo(texto);

    if(_raiz != nullptr)
    {
        _raiz->addHijo(escalado);

        unsigned short idnuevo = generarId();

        Nodo * nodo = new Nodo();
        nodo->id = idnuevo;//se pone el id
        nodo->recurso = escalado;//se agrega el nodo raiz de este recurso
        nodo->tipo = 5;
        nodo->activo = true;
        nodos.push_back(nodo);//se agrega a la lista de nodos general
        textos.push_back(nodo);//se agrega a la lista de textos

        return idnuevo;
    }

    return 0;
}

void Interfaz::Draw()
{
    //std::cout << "TAMANO NODOS " << nodos.size() << std::endl;
    if(ventana_inicializada)
    {
        ventanaInicializar();
        ventana_inicializada = false;
    }

    window->UpdateLimpiar();

    if(_raiz != nullptr)
    {
        if(camaras.size() > 0)
        {
            for(unsigned int i = 0; i < camaras.size(); i++)
            {
                if(camaras[i]->activo)
                {
                    camaras[i]->recurso->draw(1);
                    i = camaras.size()+1;
                }
            }

            for(unsigned int i = 0; i < luces.size(); i++)
            {
                if(luces[i] != nullptr && luces[i]->recurso != nullptr && luces[i]->activo)
                {
                    luces[i]->recurso->draw(1);
                }
            }

            //primero calculamos las matrices de view y projection
            //¿¿¿¿¿¿????????
            //esto seria lo ultimo vamos a las model

            _raiz->draw(0);

            for(unsigned int i = 0; i < imagenes.size(); i++)
            {
                if(imagenes[i] != nullptr && imagenes[i]->recurso != nullptr && imagenes[i]->activo)
                {
                    imagenes[i]->recurso->draw(1);
                }
            }

            for(unsigned int i = 0; i < textos.size(); i++)
            {
                if(textos[i] != nullptr && textos[i]->recurso != nullptr && textos[i]->activo)
                {
                    textos[i]->recurso->draw(1);
                }
            }
        }
    }

    window->UpdateDraw();
}

unsigned short Interfaz::generarId()
{
    return ++ids;
}

Interfaz::Nodo * Interfaz::buscarNodo(unsigned short id)
{
    if(id != 0)
    {
        unsigned short Iarriba = ((unsigned short)(nodos.size()-1));
        unsigned short Iabajo = 0;
        unsigned short Icentro;
        while (Iabajo <= Iarriba)
        {
            Icentro = (Iarriba + Iabajo)/2;
            if (nodos[Icentro]->id == id)
            {
                cualborrar = Icentro;
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
    }
    return nullptr;
}

void Interfaz::Trasladar(unsigned short id,float x,float y,float z)
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

void Interfaz::Rotar(unsigned short id,float grados,float x,float y,float z)
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

void Interfaz::Escalar(unsigned short id,float x,float y,float z)
{
    Nodo * nodo = buscarNodo(id);

    if(nodo != nullptr)
    {
        nodo->recurso->GetEntidad()->escalar(x,y,z);
    }
}

bool Interfaz::VentanaEstaAbierta()
{
    if(ventana_inicializada)
    {
        ventanaInicializar();
        ventana_inicializada = false;
    }

    return window->SigueAbierta();
}

void Interfaz::ventanaInicializar()
{
    if(window == nullptr)
    {
        window = new Ventana();
    }
    //se inicializa por defecto a estos valores la ventana, se puede cambiar los valores por defecto llamando a las funciones de ventana
    window->CrearVentana(600,800,true," Sin titulo ");

    shaders[0] = new Shader("assets/shaders/shaderlucesvs.glsl","assets/shaders/shaderlucesfs.glsl");
    shaders[1] = new Shader("assets/shaders/shaderguivs.glsl","assets/shaders/shaderguifs.glsl");
    shaders[2] = new Shader("assets/shaders/shadertextvs.glsl","assets/shaders/shadertextfs.glsl");
}

void Interfaz::ventanaLimpiar()
{
    if(window != nullptr && VentanaEstaAbierta())
    {
        window->Drop();
        window = nullptr;
        ventana_inicializada = true;
    }
}

double * Interfaz::GetPosicionRaton()
{
    return window->RecuperarPosicionesMouse();
}

void Interfaz::EliminarCamara(unsigned short)
{

}

void Interfaz::LimpiarEscena()
{
    //limpia todos los elementos que no son gui
    if(_raiz != nullptr)
    {

        _raiz->BorrarEscena();
    }
}

void Interfaz::LimpiarGui()
{
    //limpia todos los elementos gui
    if(_raiz != nullptr)
    {
        _raiz->BorrarGui();
        imagenes.resize(0);
        imagenes.reserve(20);
        textos.resize(0);
        textos.reserve(20);
        for(std::size_t i=0 ; i < nodos.size() ; i++)
        {
            if(nodos[i] != nullptr && (nodos[i]->tipo == 4 || nodos[i]->tipo == 5))
            {
                nodos[i]->recurso = nullptr;
                delete nodos[i];
                nodos.erase(nodos.begin()+i); 
                i--;
            }
        }
    }
}

void Interfaz::CambiarFondo(float r, float g, float b,float a)
{

    if(window != nullptr)
    {
        window->CambiarColorFondo(r,g,b,a);
    }
}

void Interfaz::DefinirVentana(short unsigned int width, short unsigned int height, const char * title)
{
    if(ventana_inicializada)
    {
        ventanaInicializar();
        ventana_inicializada = false;
    }

    if(window != nullptr)
    {
        window->UpdateTitle(title);
        window->UpdateSize(width,height);
    }
}

unsigned short Interfaz::CrearTexto(std::string texto, short x, short y,float r, float g, float b)
{
    unsigned short idn = AddTexto("assets/fonts/arial.ttf",18);//se crea el texto con su tipo de fuente y tamaño inicial
    Nodo * nodo = buscarNodo(idn);

    if(nodo != nullptr)
    {
        TNodo * tnodo = nodo->recurso->GetNieto(1)->GetHijo(1);//nodo que contiene ttexto en el arbol
        dynamic_cast<TTexto*>(tnodo->GetEntidad())->CrearTexto(texto,x,y,200.0f,1.0f,1.0f,r,g,b);//direc5 de memoria de TTexto
    }
    else
    {
        return 0;
    }

    return idn;
}

bool Interfaz::IsKeyDown(short tecla)
{
    if(window->EstaPulsada(tecla))
    {
        return true;
    }

    return false;
}

bool Interfaz::IsMouseClick(short boton)
{
    if(window->MouseEstaPulsado(boton))
    {
        return true;
    }

    return false;
}

void Interfaz::ChangeTargetCamara(unsigned short id, float x, float y, float z)
{
    Nodo * nodo = buscarNodo(id);
    if(nodo != nullptr)
    {
        TNodo * tnodo = nodo->recurso->GetNieto(1)->GetHijo(1);//nodo que contiene ttexto en el arbol
        dynamic_cast<TCamara*>(tnodo->GetEntidad())->setTarget(x,y,z);//direc5 de memoria de TTexto
    }
}

//Le asigna una id a un plano para hacerlo un boton
void Interfaz::DeclararBoton(unsigned short id, unsigned short newid)
{
    Nodo * nodo = buscarNodo(id);
    if(nodo != nullptr)
    {
        TNodo * tnodo = nodo->recurso->GetNieto(1)->GetHijo(1);//nodo que contiene ttexto en el arbol
        dynamic_cast<TPlano*>(tnodo->GetEntidad())->CambiarId(newid);//direc5 de memoria de TTexto
    }
}

//Detectar pulsaciones de botones
bool Interfaz::DetectarPulsacion(int did)
{
    for(unsigned int i = 0; i < imagenes.size(); i++)
    {
        TNodo * tnodo = imagenes[i]->recurso->GetNieto(1)->GetHijo(1);
        if(dynamic_cast<TPlano*>(tnodo->GetEntidad())->Comprobar()) //Si la imagen es un boton
        {
            if(did == dynamic_cast<TPlano*>(tnodo->GetEntidad())->getID()) //Si es la misma id
            {
                double * datos = window->RecuperarPosicionesMouse();
                if(dynamic_cast<TPlano*>(tnodo->GetEntidad())->botonPulsado(datos))//Si pulsas el boton
                    return true;
            }
        }
    }
    return false;
}

void Interfaz::DeshabilitarObjeto(unsigned short did)
{
    Nodo * nodo = buscarNodo(did);

    if(nodo != nullptr)
    {
        nodo->activo = false;
    }
}

void Interfaz::HabilitarObjeto(unsigned short did)
{
    Nodo * nodo = buscarNodo(did);

    if(nodo != nullptr)
    {
        nodo->activo = true;
    }
}

float * Interfaz::GetPosicion(unsigned short did)
{
    Nodo * nodo = buscarNodo(did);

    if(nodo != nullptr)
    {
        TNodo * tnodo = nodo->recurso->GetNieto(1);
        if(tnodo->GetEntidad() != nullptr)
        {
            return dynamic_cast<TTransform*>(tnodo->GetEntidad())->GetPosicion();
        }
    }

    return nullptr;
}

float * Interfaz::GetTarget(unsigned short did)
{
    Nodo * nodo = buscarNodo(did);
    
    if(nodo != nullptr)
    {
        TNodo * tnodo = nodo->recurso->GetNieto(1)->GetHijo(1);
        if(tnodo != nullptr)
        {
            return dynamic_cast<TCamara*>(tnodo->GetEntidad())->GetTarget();
        }
    }
    return nullptr;
}

void Interfaz::RemoveObject(unsigned short object)
{
    if(object != 0)
    {
        //borrar objeto que se le pasa
        Nodo * nodo = buscarNodo(object);

        if(nodo != nullptr)
        {
            if(nodo->recurso != nullptr)
            {
                _raiz->remHijo(nodo->recurso);
                delete nodo->recurso;
                nodo->recurso = nullptr;
                delete nodo;
            }
            nodos.erase(nodos.begin()+cualborrar); 
        }
    }
}

void Interfaz::EscalarImagen(unsigned short nid,float x,float y,bool enx, bool eny)
{
    //escalar la imagen
}

void Interfaz::CambiarTexto(unsigned short nid,std::string texto)
{
    //cambiar string del texto
}