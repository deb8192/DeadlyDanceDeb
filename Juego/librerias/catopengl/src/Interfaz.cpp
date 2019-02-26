#include "Interfaz.hpp"

Interfaz::Interfaz()
{
    _raiz = new TNodo();//se crea un nodo raiz(sin entidad) para agregar ramas (camaras,mallas,luces)
    camaras.reserve(3);//dos camaras maximas
    luces.reserve(40);//30 luces como maximo
    gestorDeRecursos = new CatOpengl::Gestor;
    ventana_inicializada = true;//se pone para que entra a inicializar por defecto
    window = nullptr;//se pone para saber que no esta inicializada
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

Interfaz::~Interfaz()
{

}

unsigned short Interfaz::AddCamara()
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
    rotacionEnt->rotar(0,0,0,0);
    rotacion->setEntidad(rotacionEnt);

    TNodo * escalado = new TNodo;
    TTransform * escaladoEnt = new TTransform;
    rotacionEnt->escalar(1,1,1);
    escalado->setEntidad(escaladoEnt);

    //escalado al ser el nodo padre del objeto en cuestion (sea luz, camara, o malla), debe ser el que se le diga que no se ejecuta
    escaladoEnt->NoEjecutar();

    TNodo * camara = new TNodo;
    TCamara * camaraEn = new TCamara;
    camaraEn->SetShader(shaders[0]);
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
    rotacionEnt->rotar(0,0,0,0);
    rotacion->setEntidad(rotacionEnt);

    TNodo * escalado = new TNodo;
    TTransform * escaladoEnt = new TTransform;
    rotacionEnt->escalar(1,1,1);
    escalado->setEntidad(escaladoEnt);

    escaladoEnt->Ejecutar();

    TNodo * luz = new TNodo;
    TLuz * luzEn = new TLuz;
    luzEn->SetShader(shaders[0]);
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
    rotacionEnt->rotar(0,0,0,0);
    rotacion->setEntidad(rotacionEnt);

    TNodo * escalado = new TNodo;
    TTransform * escaladoEnt = new TTransform;
    rotacionEnt->escalar(1,1,1);
    escalado->setEntidad(escaladoEnt);

    TNodo * malla = new TNodo;
    TMalla * mallaEn = new TMalla;
    mallaEn->SetShader(shaders[0]);
    malla->setEntidad(mallaEn);

    escalado->addHijo(rotacion);
    rotacion->addHijo(traslacion);
    traslacion->addHijo(malla);

    unsigned short id_recurso = gestorDeRecursos->ObtenerRecurso(archivo,malla);//obtenemos el id del recurso en memoria (para ser procesado por opengl)

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
            nodos.push_back(nodo);//se agrega a la lista de nodos general

            return idnuevo;
        }
    }

    //ahora le pasamos este al cargador para asociar la malla a este id
    return 0;
}


void Interfaz::Draw()
{



    if(ventana_inicializada)
    {
        ventanaInicializar();
        ventana_inicializada = false;
    }

    glm::vec3 pointLightPositions[] = {  //Posiciones de 4 cubos de luz
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };

    window->UpdateLimpiar();

    shaders[0]->Use();
    shaders[0]->setInt("material.diffuse", 0);
    shaders[0]->setInt("material.specular", 1);
    shaders[0]->setFloat("material.shininess", 32.0f);
    //Luz direccional (Luz que llega a todos sitios y mira siempre en la misma direccion, como la luz del sol)
    shaders[0]->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f); //Enviar la direccion donde mira la luz direccional
    shaders[0]->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    shaders[0]->setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    shaders[0]->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

    //Punto de luz 1
    shaders[0]->setVec3("pointLights[0].position", pointLightPositions[0]);
    shaders[0]->setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
    shaders[0]->setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
    shaders[0]->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
    //Propiedades de atenuacion de la luz (segun la distancia mirar en: http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation)
    shaders[0]->setFloat("pointLights[0].constant", 1.0f);
    shaders[0]->setFloat("pointLights[0].linear", 0.09);
    shaders[0]->setFloat("pointLights[0].quadratic", 0.032);
    //Punto de luz 2
    shaders[0]->setVec3("pointLights[1].position", pointLightPositions[1]);
    shaders[0]->setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
    shaders[0]->setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
    shaders[0]->setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
    shaders[0]->setFloat("pointLights[1].constant", 1.0f);
    shaders[0]->setFloat("pointLights[1].linear", 0.09);
    shaders[0]->setFloat("pointLights[1].quadratic", 0.032);
    //Punto de luz 3
    shaders[0]->setVec3("pointLights[2].position", pointLightPositions[2]);
    shaders[0]->setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
    shaders[0]->setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
    shaders[0]->setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
    shaders[0]->setFloat("pointLights[2].constant", 1.0f);
    shaders[0]->setFloat("pointLights[2].linear", 0.09);
    shaders[0]->setFloat("pointLights[2].quadratic", 0.032);
    //Punto de luz 4
    shaders[0]->setVec3("pointLights[3].position", pointLightPositions[3]);
    shaders[0]->setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
    shaders[0]->setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
    shaders[0]->setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
    shaders[0]->setFloat("pointLights[3].constant", 1.0f);
    shaders[0]->setFloat("pointLights[3].linear", 0.09);
    shaders[0]->setFloat("pointLights[3].quadratic", 0.032);

    if(_raiz != nullptr)
    {
        if(camaras.size() > 0)
        {
            //primero calculamos las matrices de view y projection
            //¿¿¿¿¿¿????????
            //esto seria lo ultimo vamos a las model
            _raiz->draw();
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
    shaders[1] = new Shader("assets/shaders/shaderdefectovs.glsl","assets/shaders/shaderdefectofs.glsl");
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
