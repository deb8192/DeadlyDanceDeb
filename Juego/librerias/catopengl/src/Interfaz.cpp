#include "Interfaz.hpp"

Interfaz::Interfaz()
{
    _raiz = new TNodo();//se crea un nodo raiz(sin entidad) para agregar ramas (camaras,mallas,luces)
    camaras.reserve(3);//dos camaras maximas
    luces.reserve(40);//30 luces como maximo
    imagenes.reserve(20);//20 imagenes de interfaz
    textos.reserve(20);//20 imagenes de textos
    boards.reserve(30); //30 billboards
    gestorDeRecursos = new CatOpengl::Gestor;
    ventana_inicializada = true;//se pone para que entra a inicializar por defecto
    window = nullptr;//se pone para saber que no esta inicializada
    nodos.reserve(600);//para almacenar el objeto
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    ModoOneCamara = true;

    for(unsigned int e = 0;e < 65535;e++)
    {
        banco_ids[e] = false;
    }
}

Interfaz::~Interfaz()
{
    LimpiarEscena();
    LimpiarGui();
    ventanaLimpiar();
    delete gestorDeRecursos;
}

void Interfaz::CerrarVentana()
{
    if(window != nullptr && VentanaEstaAbierta())
    {
        window->Close();
    }
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
        rotacionEnt->rotar(0,0,0);
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
        camaraEn->SetShader(shaders[4]);
        camaraEn->SetShader2(shaders[3]);
        camaraEn->SetShader3(shaders[5]);
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
    rotacionEnt->rotar(0,0,0);
    rotacion->setEntidad(rotacionEnt);

    TNodo * escalado = new TNodo;
    TTransform * escaladoEnt = new TTransform;
    escaladoEnt->escalar(1,1,1);
    escalado->setEntidad(escaladoEnt);

    escaladoEnt->NoEjecutar();

    TNodo * luz = new TNodo;
    TLuz * luzEn = new TLuz(tipo);
    luzEn->SetShader(shaders[4]);
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

unsigned short Interfaz::AddMalla(const char * archivo, int initf, int shader) //shader sinluz = 1, shader cartoon = other
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
    rotacionEnt->rotar(0,0,0);
    rotacion->setEntidad(rotacionEnt);

    TNodo * escalado = new TNodo;
    TTransform * escaladoEnt = new TTransform;
    escaladoEnt->escalar(1,1,1);
    escalado->setEntidad(escaladoEnt);

    TNodo * malla = new TNodo;
    TMalla * mallaEn = new TMalla(initf);
    //Depende del shader
    if(shader == 0)
    {
        mallaEn->SetShader(shaders[4]);
    }
    else
    {
        mallaEn->SetShader(shaders[5]);
    }

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

unsigned short Interfaz::AddImagen(const char * archivo, unsigned int x, unsigned int y, float scale,  const char * rutapulsado , const char * rutaencima )
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
    rotacionEnt->rotar(0,0,0);
    rotacion->setEntidad(rotacionEnt);

    TNodo * escalado = new TNodo;
    TTransform * escaladoEnt = new TTransform;
    escaladoEnt->escalar(1,1,1);
    escalado->setEntidad(escaladoEnt);

    escaladoEnt->EsGui();
    escaladoEnt->NoEjecutar();

    TNodo * imagen = new TNodo;

    TPlano * imagenEn = nullptr;

    if(rutapulsado != nullptr || rutaencima != nullptr)
    {
        imagenEn = new TPlano(archivo,x,y,scale,shaders[1],window->getWidth(), window->getHeight(), rutapulsado , rutaencima);
    }
    else
    {
        imagenEn = new TPlano(archivo,x,y,scale,shaders[1],window->getWidth(), window->getHeight());
    }

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
        nodo->tipo = 3;
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
    rotacionEnt->rotar(0,0,0);
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
        nodo->tipo = 4;
        nodo->activo = true;
        nodos.push_back(nodo);//se agrega a la lista de nodos general
        textos.push_back(nodo);//se agrega a la lista de textos

        return idnuevo;
    }

    return 0;
}

unsigned short Interfaz::AddBoard(float x, float y, float z, float movx, float movy, const char * _ruta, float priority)
{
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
    rotacionEnt->rotar(0,0,0);
    rotacion->setEntidad(rotacionEnt);

    TNodo * escalado = new TNodo;
    TTransform * escaladoEnt = new TTransform;
    escaladoEnt->escalar(1,1,1);
    escalado->setEntidad(escaladoEnt);

    escaladoEnt->EsGui();
    escaladoEnt->NoEjecutar();

    TNodo * board = new TNodo;
    TBillboard * boardEn = new TBillboard(x,y,z,_ruta,shaders[3],movx,movy,priority);
    board->setEntidad(boardEn);

    escalado->addHijo(rotacion);
    rotacion->addHijo(traslacion);
    traslacion->addHijo(board);

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
        boards.push_back(nodo);//se agrega a la lista de billboards

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

            for(unsigned int i = 0; i < boards.size(); i++)
            {
                if(boards[i] != nullptr && boards[i]->recurso != nullptr && boards[i]->activo)
                {
                    boards[i]->recurso->draw(1);
                }
            }

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

Interfaz::Nodo * Interfaz::buscarNodo2(unsigned short id)
{
    for(unsigned int i = 0; i < nodos.size(); i++)
    {
        if (nodos[i] != nullptr && nodos[i]->id == id)
        {
            cualborrar = i;
            return nodos[i];
        }
    }
    return nullptr;
}

Interfaz::Nodo * Interfaz::buscarNodo3(signed int idPerson)
{
    for(unsigned int i = 0; i < nodos.size(); i++)
    {
        if (nodos[i] != nullptr && nodos[i]->idPersonalizado == idPerson)
        {
            cualborrar = i;
            return nodos[i];
        }
    }
    return nullptr;
}

void Interfaz::Trasladar(unsigned short id,float x,float y,float z)
{
    Nodo * nodo = buscarNodo2(id);

    if(nodo != nullptr)
    {
        if(nodo->recurso != nullptr)
        {
            TNodo * tnodo = nodo->recurso->GetNieto(1);
            if(tnodo != nullptr)
            {
                tnodo->GetEntidad()->trasladar(x,y,z);
            }
        }
    }
}

void Interfaz::Rotar(unsigned short id,float gx,float gy,float gz)
{
    Nodo * nodo = buscarNodo2(id);

    if(nodo != nullptr)
    {
        TNodo * tnodo = nodo->recurso->GetHijo(1);
        if(tnodo != nullptr)
        {
            tnodo->GetEntidad()->rotar(gx,gy,gz);
        }
    }
}

void Interfaz::Escalar(unsigned short id,float x,float y,float z)
{
    Nodo * nodo = buscarNodo2(id);

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
    shaders[3] = new Shader("assets/shaders/shaderboardsvs.glsl","assets/shaders/shaderboardsfs.glsl");
    shaders[4] = new Shader("assets/shaders/shadertoonvs.glsl","assets/shaders/shadertoonfs.glsl");
    shaders[5] = new Shader("assets/shaders/shadernolucesvs.glsl","assets/shaders/shadernolucesfs.glsl");
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
        luces.resize(0);
        luces.reserve(40);//30 luces como maximo
        for(std::size_t i=0 ; i < nodos.size() ; i++)
        {
            if(nodos[i] != nullptr && (nodos[i]->tipo == 2 || nodos[i]->tipo == 1))
            {
                nodos[i]->recurso = nullptr;
                eliminarID((nodos[i]->id));
                delete nodos[i];
                nodos.erase(nodos.begin()+i);
                i--;
            }
        }
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
            if(nodos[i] != nullptr && (nodos[i]->tipo == 3 || nodos[i]->tipo == 4))
            {
                nodos[i]->recurso = nullptr;
                eliminarID((nodos[i]->id));
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
    Nodo * nodo = buscarNodo2(idn);

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

bool Interfaz::IsMouseUp(short boton)
{
    if(window != nullptr)
    {
        return window->MouseEstaLibre(boton);
    }
    return false;
}

void Interfaz::ChangeTargetCamara(unsigned short id, float x, float y, float z)
{
    Nodo * nodo = buscarNodo2(id);
    if(nodo != nullptr)
    {
        TNodo * tnodo = nodo->recurso->GetNieto(1)->GetHijo(1);//nodo que contiene ttexto en el arbol
        dynamic_cast<TCamara*>(tnodo->GetEntidad())->setTarget(x,y,z);//direc5 de memoria de TTexto
    }
}

//Le asigna una id a un plano para hacerlo un boton
void Interfaz::DeclararBoton(unsigned short id, unsigned short newid)
{
    Nodo * nodo = buscarNodo2(id);
    if(nodo != nullptr)
    {
        TNodo * tnodo = nodo->recurso->GetNieto(1)->GetHijo(1);//nodo que contiene ttexto en el arbol
        dynamic_cast<TPlano*>(tnodo->GetEntidad())->CambiarId(newid);//direc5 de memoria de TTexto
    }
}

//Detectar si esta encima del boton
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
                TPlano * imagen = dynamic_cast<TPlano*>(tnodo->GetEntidad());
                if(imagen != nullptr)//Si pulsas el boton
                {
                    if(imagen->botonPulsado(datos))
                    {
                        //imagen->CambiarEstado(2);
                        return true;
                    }

                    //imagen->CambiarEstado(1);
                    return false;
                }
            }
        }
    }
    return false;
}

void Interfaz::DeshabilitarObjeto(unsigned short did)
{
    Nodo * nodo = buscarNodo2(did);

    if(nodo->tipo == 2)
    {
        nodo->recurso->DeshabilitarNodo();
    }
    else
    {
        nodo->activo = false;
    }
}

void Interfaz::HabilitarObjeto(unsigned short did)
{
    Nodo * nodo = buscarNodo2(did);

    if(nodo != nullptr)
    {
        if(nodo->tipo == 2)
        {
            nodo->recurso->HabilitarNodo();
        }
        else
        {
            nodo->activo = true;
        }
    }
}

float * Interfaz::GetPosicion(unsigned short did)
{
    Nodo * nodo = buscarNodo2(did);

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
    Nodo * nodo = buscarNodo2(did);

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
        Nodo * nodo = buscarNodo2(object);

        unsigned short auxiliar = cualborrar;
        if(nodo != nullptr)
        {
            if(nodo->id_texto != 0 && nodo->tipo == 3)
            {
               RemoveObject(nodo->id_texto);
            }

            if(nodo->recurso != nullptr)
            {
                _raiz->remHijo(nodo->recurso);
                delete nodo->recurso;
                nodo->recurso = nullptr;
            }

            pulgarReferencia(nodo,nodo->tipo);
            eliminarID((nodo->id));
            delete nodo;
            nodos.erase(nodos.begin()+auxiliar);

        }
    }
}

void Interfaz::EscalarImagen(unsigned short nid,float x,float y,bool enx, bool eny)
{
    if(nid != 0)
    {
        Nodo * nodo = buscarNodo2(nid);
        if(nodo != nullptr)
        {
            if(nodo->recurso != nullptr)
            {
                TNodo * tnodo = nodo->recurso->GetNieto(1)->GetHijo(1);
                if(tnodo != nullptr)
                {
                    //escalar la imagen
                    if(enx)
                    {
                        dynamic_cast<TPlano*>(tnodo->GetEntidad())->setScaleX(x);
                    }

                    if(eny)
                    {
                        dynamic_cast<TPlano*>(tnodo->GetEntidad())->setScaleY(y);
                    }
                }
            }
        }
    }
}

void Interfaz::CambiarTexto(unsigned short nid,std::string texto)
{
    //cambiar string del texto
    if(nid != 0)
    {
        Nodo * nodo = buscarNodo2(nid);
        if(nodo != nullptr)
        {
            if(nodo->recurso != nullptr)
            {
                TNodo * tnodo = nodo->recurso->GetNieto(1)->GetHijo(1);
                if(tnodo != nullptr)
                {
                    dynamic_cast<TTexto*>(tnodo->GetEntidad())->CambiarTexto(texto);
                }
            }
        }
    }
}

void Interfaz::CambiarPosicionTexto(unsigned short nid, float x, float y)
{
    //cambiar string del texto
    if(nid != 0)
    {
        Nodo * nodo = buscarNodo2(nid);
        if(nodo != nullptr)
        {
            if(nodo->recurso != nullptr)
            {
                TNodo * tnodo = nodo->recurso->GetNieto(1)->GetHijo(1);
                if(tnodo != nullptr)
                {
                    dynamic_cast<TTexto*>(tnodo->GetEntidad())->CambiarPosicion(x,y);
                }
            }
        }
    }
}

void Interfaz::eliminarID(unsigned short x)
{
    if(x >= 0 && x < 65535)
    {
        banco_ids[x-1] = false;
    }
}

unsigned short Interfaz::generarId()
{
    for(unsigned short e = 0;e < 65535;e++)
    {
        if(banco_ids[e] == false)
        {
            banco_ids[e]=true;
            return (e+1);
        }
    }

    return 0;
}

int Interfaz::getStartFrame(unsigned short did)
{
    if(did != 0)
    {
        Nodo * nodo = buscarNodo2(did);

        if(nodo != nullptr)
        {
            if(nodo->recurso != nullptr)
            {
                TNodo * tnodo = nodo->recurso->GetNieto(1)->GetHijo(1);
                if(tnodo != nullptr)
                {
                    return (int)dynamic_cast<TMalla*>(tnodo->GetEntidad())->getFrameInicio();
                }
            }
        }
    }
    return -1;
}

int Interfaz::getFrameNr(unsigned short did)
{
    if(did != 0)
    {
        Nodo * nodo = buscarNodo2(did);
        if(nodo != nullptr)
        {
            if(nodo->recurso != nullptr)
            {
                TNodo * tnodo = nodo->recurso->GetNieto(1)->GetHijo(1);
                if(tnodo != nullptr)
                {
                    return (int)dynamic_cast<TMalla*>(tnodo->GetEntidad())->getFrameActual();
                }
            }
        }
    }
    return -1;
}

void Interfaz::setFrameLoop(unsigned short did,int start,int end)
{
    if(did != 0)
    {
        Nodo * nodo = buscarNodo2(did);
        if(nodo != nullptr)
        {
            if(nodo->recurso != nullptr)
            {
                TNodo * tnodo = nodo->recurso->GetNieto(1)->GetHijo(1);
                if(tnodo != nullptr)
                {
                    dynamic_cast<TMalla*>(tnodo->GetEntidad())->BucleAnimacion((unsigned short)start,(unsigned short)end);
                }
            }
        }
    }
}

void Interfaz::setAnimationSpeed(unsigned short did,int velocidad)
{
    if(did != 0)
    {
        Nodo * nodo = buscarNodo2(did);
        if(nodo != nullptr)
        {
            if(nodo->recurso != nullptr)
            {
                TNodo * tnodo = nodo->recurso->GetNieto(1)->GetHijo(1);
                if(tnodo != nullptr)
                {
                    dynamic_cast<TMalla*>(tnodo->GetEntidad())->setVelocidadAnimacion((float)velocidad);
                }
            }
        }
    }
}

void Interfaz::SetColor(unsigned short did, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    if(did != 0)
    {
        Nodo * nodo = buscarNodo2(did);
        if(nodo != nullptr)
        {
            if(nodo->recurso != nullptr)
            {
                TNodo * tnodo = nodo->recurso->GetNieto(1)->GetHijo(1);
                if(tnodo != nullptr)
                {
                    dynamic_cast<TMalla*>(tnodo->GetEntidad())->setColor(r,g,b,a);
                }
            }
        }
    }
}

void Interfaz::SetTexture(unsigned short did, const char * _ruta)
{
    if(did != 0)
    {
        Nodo * nodo = buscarNodo2(did);
        if(nodo != nullptr)
        {
            if(nodo->recurso != nullptr)
            {
                TNodo * tnodo = nodo->recurso->GetNieto(1)->GetHijo(1);
                if(tnodo != nullptr)
                {
                    dynamic_cast<TMalla*>(tnodo->GetEntidad())->setTexture(_ruta);
                }
            }
        }
    }
}


void Interfaz::RemoveObjectForID(signed int idPerson)
{
    Nodo * nodo = buscarNodo3(idPerson);
    if(nodo != nullptr)
    {
        RemoveObject(nodo->id);
    }
}

void Interfaz::DefinirIdPersonalizado(unsigned short did, signed int idPerson)
{
    Nodo * nodo = buscarNodo2(did);

    if(nodo != nullptr)
    {
        nodo->idPersonalizado = idPerson;
    }
}

void Interfaz::pulgarReferencia(Nodo * referencia,unsigned short tipo)
{
        if(tipo == 0)
        {
            for(unsigned int i = 0; i < camaras.size(); i++)
            {
                if(camaras[i] != nullptr && referencia == camaras[i])
                {
                    camaras.erase(camaras.begin()+i);
                    return;
                }
            }
        }

        if(tipo == 1)
        {
            for(unsigned int i = 0; i < luces.size(); i++)
            {
                if(luces[i] != nullptr && referencia == luces[i])
                {
                    luces.erase(luces.begin()+i);
                    return;
                }
            }
        }

        if(tipo == 3)
        {
            for(unsigned int i = 0; i < imagenes.size(); i++)
            {
                if(imagenes[i] != nullptr && referencia == imagenes[i])
                {
                    imagenes.erase(imagenes.begin()+i);
                    return;
                }
            }
        }

        if(tipo == 4)
        {
            for(unsigned int i = 0; i < textos.size(); i++)
            {
                if(textos[i] != nullptr && referencia == textos[i])
                {
                    textos.erase(textos.begin()+i);
                    return;
                }
            }
        }

        if(tipo == 5)
        {
            for(unsigned int i = 0; i < boards.size(); i++)
            {
                if(boards[i] != nullptr && referencia == boards[i])
                {
                    boards.erase(boards.begin()+i);
                    return;
                }
            }
        }
}

void Interfaz::DefinirTextoBoton(unsigned short imagen,unsigned short texto)
{
    Nodo * nodo = buscarNodo2(imagen);

    if(nodo != nullptr)
    {
        nodo->id_texto = texto;
    }
}

void Interfaz::DistanciaLuz(unsigned short luz, float d)
{
    if(luz != 0)
    {
        Nodo * nodo = buscarNodo2(luz);
        if(nodo != nullptr)
        {
            if(nodo->recurso != nullptr)
            {
                TNodo * tnodo = nodo->recurso->GetNieto(1)->GetHijo(1);
                if(tnodo != nullptr)
                {
                    dynamic_cast<TLuz*>(tnodo->GetEntidad())->setLightRange(d);
                }
            }
        }
    }
}

void Interfaz::ColorAmbiental(unsigned short luz, float r,float g,float b)
{
    if(luz != 0)
    {
        Nodo * nodo = buscarNodo2(luz);
        if(nodo != nullptr)
        {
            if(nodo->recurso != nullptr)
            {
                TNodo * tnodo = nodo->recurso->GetNieto(1)->GetHijo(1);
                if(tnodo != nullptr)
                {
                    dynamic_cast<TLuz*>(tnodo->GetEntidad())->setAmbient(r,g,b);
                }
            }
        }
    }
}

void Interfaz::ColorDifusa(unsigned short luz, float r,float g,float b)
{
    if(luz != 0)
    {
        Nodo * nodo = buscarNodo2(luz);
        if(nodo != nullptr)
        {
            if(nodo->recurso != nullptr)
            {
                TNodo * tnodo = nodo->recurso->GetNieto(1)->GetHijo(1);
                if(tnodo != nullptr)
                {
                    dynamic_cast<TLuz*>(tnodo->GetEntidad())->setDiffuse(r,g,b);
                }
            }
        }
    }
}

void Interfaz::ColorSpecular(unsigned short luz, float r,float g,float b)
{
    if(luz != 0)
    {
        Nodo * nodo = buscarNodo2(luz);
        if(nodo != nullptr)
        {
            if(nodo->recurso != nullptr)
            {
                TNodo * tnodo = nodo->recurso->GetNieto(1)->GetHijo(1);
                if(tnodo != nullptr)
                {
                    dynamic_cast<TLuz*>(tnodo->GetEntidad())->setSpecular(r,g,b);
                }
            }
        }
    }
}

void Interfaz::setBucle(unsigned short idMalla, bool estaEnBucle)
{
    if(idMalla != 0)
    {
        Nodo * nodo = buscarNodo2(idMalla);

        if(nodo != nullptr)
        {
            if(nodo->recurso != nullptr)
            {
                TNodo * tnodo = nodo->recurso->GetNieto(1)->GetHijo(1);
                if(tnodo != nullptr)
                {
                    TMalla * malla = dynamic_cast<TMalla*>(tnodo->GetEntidad());
                    if(malla != nullptr)
                    {
                        malla->EstaEnBucleAnimacion(estaEnBucle);
                    }
                }
            }
        }
    }
}

void Interfaz::SetLejaniaCamara(unsigned short camara,float lejania)
{
    //cambiar lejania de la camara
    if(camara != 0)
    {
        Nodo * nodo = buscarNodo2(camara);
        if(nodo != nullptr)
        {
            if(nodo->recurso != nullptr)
            {
                TNodo * tnodo = nodo->recurso->GetNieto(1)->GetHijo(1);
                if(tnodo != nullptr)
                {
                    TCamara* _camara = dynamic_cast<TCamara*>(tnodo->GetEntidad());
                    if(_camara != nullptr)
                    {
                        _camara->setLejano(lejania);
                        _camara->setPerspectiva();//redefinimos la vista perspectiva
                    }
                }
            }
        }
    }
}

void Interfaz::SetCercaniaCamara(unsigned short camara,float cercania)
{
    //cambiar cercania de la camara
    if(camara != 0)
    {
        Nodo * nodo = buscarNodo2(camara);
        if(nodo != nullptr)
        {
            if(nodo->recurso != nullptr)
            {
                TNodo * tnodo = nodo->recurso->GetNieto(1)->GetHijo(1);
                if(tnodo != nullptr)
                {
                    TCamara* _camara = dynamic_cast<TCamara*>(tnodo->GetEntidad());
                    if(_camara != nullptr)
                    {
                        _camara->setCercano(cercania);
                        _camara->setPerspectiva();//redefinimos la vista perspectiva
                    }
                }
            }
        }
    }
}

bool Interfaz::IsKeyRelease(short tecla)
{
    if(window != nullptr)
    {
        return window->EstaLiberado(tecla);
    }

    return false;
}

void Interfaz::AnchoTexto(unsigned short did,unsigned int anchoNuevo)
{
    if(did != 0)
    {
        Nodo * nodo = buscarNodo2(did);
        if(nodo != nullptr)
        {
            if(nodo->recurso != nullptr)
            {
                TNodo * tnodo = nodo->recurso->GetNieto(1)->GetHijo(1);
                if(tnodo != nullptr)
                {
                    TTexto* _texto = dynamic_cast<TTexto*>(tnodo->GetEntidad());
                    if(_texto != nullptr)
                    {
                        _texto->CambiarAnchura(anchoNuevo);
                    }
                }
            }
        }
    }
}

void Interfaz::CambiarEstadoImagen(unsigned int event,unsigned int nuevoEstado)
{
    for(unsigned int i = 0; i < imagenes.size(); i++)
    {
        TNodo * tnodo = imagenes[i]->recurso->GetNieto(1)->GetHijo(1);
        if(dynamic_cast<TPlano*>(tnodo->GetEntidad())->Comprobar()) //Si la imagen es un boton
        {
            if(event == (unsigned int)dynamic_cast<TPlano*>(tnodo->GetEntidad())->getID()) //Si es la misma id
            {
                TPlano * imagen = dynamic_cast<TPlano*>(tnodo->GetEntidad());
                if(imagen != nullptr)//Si pulsas el boton
                {
                    imagen->CambiarEstado(nuevoEstado);
                }
            }
        }
    }
}



void Interfaz::ActivarCapturaTexto()
{
    if(window)
    {
        window->ActivarRecogida();
    }
}

void Interfaz::DesactivarCapturaTexto()
{
    if(window)
    {
        window->DesactivarRecogida();
    }
}

void Interfaz::InicializarCapturaTexto(const char * texto)
{
    if(window)
    {
        window->InicializarLetra(texto);
    }
}

char * Interfaz::DevolverTextoCapturado()
{
    if(window)
    {
        return window->RecogerLetra();
    }
    return nullptr;
}

void Interfaz::BorrarUltimaLetra()
{
    if(window)
    {
        window->BorrarUltimaTecla();
    }
}

void Interfaz::CambiarColorTexto(unsigned int did,float r, float g, float b)
{
    if(did != 0)
    {
        Nodo * nodo = buscarNodo2(did);
        if(nodo != nullptr)
        {
            if(nodo->recurso != nullptr)
            {
                TNodo * tnodo = nodo->recurso->GetNieto(1)->GetHijo(1);
                if(tnodo != nullptr)
                {
                    TTexto* _texto = dynamic_cast<TTexto*>(tnodo->GetEntidad());
                    if(_texto != nullptr)
                    {
                        _texto->CambiarColor(r,g,b);
                    }
                }
            }
        }
    }
}
