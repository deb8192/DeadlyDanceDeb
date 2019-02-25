#include "MotorGrafico.hpp" //se llama a su cabecera para cargar las dependencias
#include "../Times.hpp"
#include "../ConstantesComunes.hpp"

//para clases singleton deben tener un indicador de que se ha creado el unico objeto
MotorGrafico* MotorGrafico::_unica_instancia = 0;
//fin indicador singleton

/*Tipo 1(640x480), Tipo 2(800x600), Tipo 3(1280x1024), Default(1024x768)
Esta clase define que tipo de pantalla quieres
*/

MotorGrafico::MotorGrafico()
{
    input.setDevice(_device);//lo  utilizamos para que los eventos puedan llamar a funciones de
    debugGrafico = false;
    actual = nullptr;
    actualTexture = nullptr;

    // Para las torres de HANNOI
    _nodoSeleccionado = nullptr;

    frame_actual = 0;
}

MotorGrafico::~MotorGrafico()
{
    //Inputs input
    //position2di initialCursorPosition;        // Posicion del clic raton
    //position2di initialObjectPosition;        // Posicion del objeto que intersecta con el ray
    
    // Punteros sin new
    _device = nullptr;
    _driver = nullptr;
    _smgr   = nullptr;
    _guienv = nullptr;
    _geometryCreator = nullptr;
    _collmgr = nullptr;
    _camera  = nullptr;
    _font    = nullptr;
    _skin    = nullptr;

    _armaEnEscena = nullptr;
    _armaEsp = nullptr;
    _armaEspJugador = nullptr;
    _jugEscena = nullptr;
    _linea = nullptr;
    _caja = nullptr;
    _tmpObjEscena = nullptr;

    // Puzzles
    _myTextBox = nullptr;
    _fichaMesh = nullptr;
    _ficha = nullptr;
    _nodoSeleccionado = nullptr;
    _img = nullptr;
    _puzParticleTexture = nullptr;
    WIDTH_AUX = 0; WIDTH = 0; HEIGHT = 0;
    x_linea1 = 0; x_linea2 = 0;

    // Texturas
    vidaI = nullptr;
    energiaI = nullptr;
    dineroI = nullptr;
    armaI = nullptr;
    BarraVidaI = nullptr;
    BarraEnergiaI = nullptr;
    manosI = nullptr;
    llaveI = nullptr;
    espadaI = nullptr;
    dagaI = nullptr;
    moneyI = nullptr;
    vida_textura = nullptr;
    energia_textura = nullptr;
    dinero_textura = nullptr;
    arma_textura = nullptr;
    barraVida_textura = nullptr;
    barraEnergia_textura = nullptr;
    manos_textura = nullptr;
    llave_textura = nullptr;
    espada_textura = nullptr;
    daga_textura = nullptr;

    // Cinematicas
    actual = nullptr;
    actualTexture = nullptr;
    frame_actual = 0;
    tiempoUltimoFrame = 0;


    width = 0; height = 0;
    debugGrafico = false;
    pathfinding = false;

    // Liberar memoria
    short tam = Plataformas_Scena.size();
    for(short i=0; i < tam; i++)
    {
        delete Plataformas_Scena.at(i);
    }
    Plataformas_Scena.clear();

    tam = Luces_Scena.size();
    for(short i=0; i < tam; i++)
    {
        delete Luces_Scena.at(i);
    }
    Luces_Scena.clear();

    tam = Enemigos_Scena.size();
    for(short i=0; i < tam; i++)
    {
        delete Enemigos_Scena.at(i);
    }
    Enemigos_Scena.clear();

    tam = Objetos_Scena.size();
    for(short i=0; i < tam; i++)
    {
        delete Objetos_Scena.at(i);
    }
    Objetos_Scena.clear();

    tam = Recolectables_Scena.size();
    for(short i=0; i < tam; i++)
    {
        delete Recolectables_Scena.at(i);
    }
    Recolectables_Scena.clear();

    tam = PowerUP_Scena.size();
    for(short i=0; i < tam; i++)
    {
        delete PowerUP_Scena.at(i);
    }
    PowerUP_Scena.clear();

    tam = Objetos_Debug.size();
    for(short i=0; i < tam; i++)
    {
        delete Objetos_Debug.at(i);
    }
    Objetos_Debug.clear();

    tam = Objetos_Debug2.size();
    for(short i=0; i < tam; i++)
    {
        delete Objetos_Debug2.at(i);
    }
    Objetos_Debug2.clear();

    tam = fichasMesh.size();
    for(short i=0; i < tam; i++)
    {
        delete fichasMesh.at(i);
    }
    fichasMesh.clear();
    
    //TO DO: Pendiente de utilizar en puzzles
    /*tam = imagenes.size();
    for(short i=0; i < tam; i++)
    {
        delete imagenes.at(i);
    }
    imagenes.clear();*/
}

void MotorGrafico::LimpiarMotorGrafico()
{
    //hay que tener  cuidado porque si se borra previamente los objetos apuntan a objetos con memoria no accesible

    if(_jugEscena)
    {
        _jugEscena = nullptr;
    }

    if(Enemigos_Scena.size() > 0)
    {
        for(std::size_t i=0;i<Enemigos_Scena.size();i++)
        {
            Enemigos_Scena[i] = nullptr;
        }

        Enemigos_Scena.resize(0);
    }

    if(Plataformas_Scena.size() > 0)
    {
        for(std::size_t i=0;i < Plataformas_Scena.size();i++)
        {
            Plataformas_Scena[i] = nullptr;
        }

       Plataformas_Scena.resize(0);
    }

    if(Luces_Scena.size() > 0)
    {
        for(std::size_t i=0;i < Luces_Scena.size();i++)
        {
            Luces_Scena[i] = nullptr;
        }

       Luces_Scena.resize(0);
    }

    if(Objetos_Scena.size() > 0)
    {
        for(std::size_t i=0;i < Objetos_Scena.size();i++)
        {
           Objetos_Scena[i] = nullptr;
        }

       Objetos_Scena.resize(0);
    }

    if(Recolectables_Scena.size() > 0)
    {
        for(std::size_t i=0;i < Recolectables_Scena.size();i++)
        {
           Recolectables_Scena[i] = nullptr;
        }

       Recolectables_Scena.resize(0);
    }

    if(PowerUP_Scena.size() > 0)
    {
        for(std::size_t i=0;i < PowerUP_Scena.size();i++)
        {
           PowerUP_Scena[i] = nullptr;
        }

       PowerUP_Scena.resize(0);
    }

    _armaEnEscena = nullptr;
    _armaEsp = nullptr;

    /*for (std::vector<Enemigos_Scena*>::iterator it = Enemigos_Scena.begin(); it!=Enemigos_Scena.end(); ++it){
        delete *it;
    }
    Enemigos_Scena.clear();*/
}

bool MotorGrafico::CrearVentana(short tipo)
{
    std::string titulo = "";
    switch(tipo)
    {
        case 1:
            width=640; height=480;
            titulo = "DeadlyDance LowResolution";
            break;

        case 2:
            width=800; height=600;
            titulo = "DeadlyDance MediumResolution";
            break;

        case 3:
            width=1280; height=1024;
            titulo = "DeadlyDance HightResolution";
            break;

        default:
            width=1024; height=768;
            titulo = "DeadlyDance NormalResolution";
            break;
    }
    _device = createDevice( video::EDT_SOFTWARE, dimension2d<u32>(width, height), 16,false, false, false, &input);

    std::wstring widestr = std::wstring(titulo.begin(), titulo.end());
    _device->setWindowCaption(widestr.c_str());

    _device->setResizable(false);
    propiedadesDevice();
    return true;
}

bool MotorGrafico::VentanaAbierta()
{
    return _device->run();
}

void MotorGrafico::CerrarJuego()
{
    _device->closeDevice();
}

/* Una vez que hayamos terminado con el bucle de procesamiento, debemos eliminar 
 * el dispositivo creado antes con createDevice()
 */
void MotorGrafico::LimpiarDevice()
{
    _device->drop();
}

void MotorGrafico::propiedadesDevice()
{
    //cout << "\e[32m Aplicando propiedades a _device \e[0m" << endl;
    _driver = _device->getVideoDriver();
	_smgr = _device->getSceneManager();
	_guienv = _device->getGUIEnvironment();
    _geometryCreator = _smgr->getGeometryCreator();
    _collmgr = _smgr->getSceneCollisionManager();

    //cout << "\e[32m Propiedades aplicadas \e[0m" << endl;
}

void MotorGrafico::ActivarFuenteDefault()
{
    _skin = _guienv->getSkin();
    _font = _guienv->getFont("assets/fonts/default.bmp");
    if (_font)
    {
        _skin->setFont(_font);
        //cout << "\e[36m Se encuentra fuente \e[0m" << endl;
    }
    _skin->setFont(_guienv->getBuiltInFont(), EGDF_TOOLTIP);
}

// Se puede dibujar cualquier cosa entre una llamada beginScene() y una llamada endScene()
void MotorGrafico::FondoEscena(short a, short r, short g, short b)
{
    //Borra la pantalla con un color
    _driver->beginScene(true, true, SColor(a,r,g,b));
}

void MotorGrafico::RenderEscena()
{
    // Antes de dibujar el contenido, se llama a FondoEscena en los renders de estado
    _smgr->drawAll();
	_guienv->drawAll();
	_driver->endScene(); // Termina y saca por pantalla
}

void MotorGrafico::BorrarScena()
{
    _smgr->clear();
}

void MotorGrafico::BorrarGui()
{
    _guienv->clear();
}

void MotorGrafico::CrearTexto(std::string texto, short x1, short y1, short x2, short y2)
{
    std::wstring widestr = std::wstring(texto.begin(), texto.end());
    // Parametro false, indica que no pinte el recuadro alrededor del texto
    _guienv->addStaticText(widestr.c_str(), rect<s32>(x1, y1, x2, y2), false);
}

void MotorGrafico::CrearBoton(short x, short y, short x2, short y2, s32 id, 
    const wchar_t* texto, const wchar_t* texto2)
{
    _guienv->addButton(rect<s32>(x,y,x2,y2), 0, id, texto, texto2);
}

bool MotorGrafico::OcurreEvento(short event)
{
    return input.IsEventOn(event);
}

void MotorGrafico::ResetEvento(short event)
{
    input.ResetEvento(event);
}

bool MotorGrafico::EstaPulsado(short boton)
{
    switch(boton)
    {
        case KEY_A:
            return input.IsKeyDown(irr::KEY_KEY_A);

        case KEY_S:
            return input.IsKeyDown(irr::KEY_KEY_S);

        case KEY_D:
            return input.IsKeyDown(irr::KEY_KEY_D);

        case KEY_W:
            return input.IsKeyDown(irr::KEY_KEY_W);

        case KEY_ESC:
            return input.IsKeyDown(irr::KEY_ESCAPE);

        case KEY_ESPACIO:
            return input.IsKeyDown(irr::KEY_SPACE);

        case KEY_ACEPTAR:
            return input.IsKeyDown(irr::KEY_ACCEPT);

        case KEY_G_DEBUG:
            return input.IsKeyDown(irr::KEY_KEY_G);//para modo debug

        case KEY_P:
            return input.IsKeyDown(irr::KEY_KEY_P);

        case KEY_K:
            return input.IsKeyDown(irr::KEY_KEY_K);
        
        case KEY_C:
            return input.IsKeyDown(irr::KEY_KEY_C);//activa pathdinding

        case RMOUSE_PRESSED_DOWN:
            return input.IsMouseClick(irr::EMIE_RMOUSE_PRESSED_DOWN);

        case LMOUSE_PRESSED_DOWN:
            return input.IsMouseClick(irr::EMIE_LMOUSE_PRESSED_DOWN);

        case MOUSE_MOVED:
            return input.IsMouseClick(irr::EMIE_MOUSE_MOVED);

        case KEY_Q:
            return input.IsKeyDown(irr::KEY_KEY_Q);

        case KEY_J:
            return input.IsKeyDown(irr::KEY_KEY_J);//Para matar al jugador (16)

        case KEY_E:
            return input.IsKeyPressed(irr::KEY_KEY_E);//actua una sola vez aunque se mantenga pulsado
    }
    return false;
}

void MotorGrafico::ResetKey(short event)
{
    switch(event)
    {
        case KEY_A:
            input.ResetKey(irr::KEY_KEY_A);
        break;
        case KEY_S:
            input.ResetKey(irr::KEY_KEY_S);
        break;
        case KEY_D:
            input.ResetKey(irr::KEY_KEY_D);
        break;
        case KEY_W:
            input.ResetKey(irr::KEY_KEY_W);
        break;
        case KEY_ESC:
            input.ResetKey(irr::KEY_ESCAPE);
        break;
        case KEY_ESPACIO:
            input.ResetKey(irr::KEY_SPACE);
        break;
        case KEY_ACEPTAR:
            input.ResetKey(irr::KEY_ACCEPT);
        break;
        case KEY_G_DEBUG:
            input.ResetKey(irr::KEY_KEY_G);//para modo debug
        break;
        case KEY_P:
            input.ResetKey(irr::KEY_KEY_P);
        break;
        case KEY_K:
            input.ResetKey(irr::KEY_KEY_K);
        break;
        case KEY_C:
            input.ResetKey(irr::KEY_KEY_C);
        break;
        case KEY_Q:
            input.ResetKey(irr::KEY_KEY_Q);
        break;
        case KEY_J:
            input.IsKeyDown(irr::KEY_KEY_J);//Para matar al jugador (16)
        break; 
        case KEY_E:
            input.ResetKey(irr::KEY_KEY_E);
        break;
    }
}

bool MotorGrafico::PulsadoClicDer()
{
    return input.PulsadoClicDer();
}

bool MotorGrafico::PulsadoClicIzq()
{
    return input.PulsadoClicIzq();
}

bool MotorGrafico::SueltoClicDer()
{
    return input.SueltoClicDer();
}

bool MotorGrafico::SueltoClicIzq()
{
    return input.SueltoClicIzq();
}

void MotorGrafico::ResetEventoMoveRaton()
{
    input.ResetEventoRaton(irr::EMIE_MOUSE_MOVED);
}

position2di MotorGrafico::GetPosicionRaton()
{
    return input.GetMouseState().Position;
}

void MotorGrafico::CrearCamara()
{
  //primer vector traslacion, segundo rotacion
  //  _smgr->addCameraSceneNode(0, vector3df(0,0,90), vector3df(0,0,0));
  _camera = _smgr->addCameraSceneNode(0, vector3df(0,20,-20), vector3df(0,0,0));
  //camera->setNearValue(0.5f);
  //camera->setFarValue(100.0f);
}

bool MotorGrafico::GetDebugActivado()
{
    return debugGrafico;
}


// ------------------------------------ Revisar

int MotorGrafico::CargarPlataformas(int x,int y,int z, int ancho, int largo, int alto, const char *ruta_objeto,const char *ruta_textura)
{
    IAnimatedMesh* objeto = _smgr->getMesh(ruta_objeto); //creamos el objeto en memoria
	if (!objeto)
	{
		//error
        return -1;//no se ha podido crear esta sala
	}
    else
    {
        IAnimatedMeshSceneNode* _objetoEnEscena = _smgr->addAnimatedMeshSceneNode(objeto); //metemos el objeto en el escenario para eso lo pasamos al escenario
        _objetoEnEscena->setPosition(core::vector3df(x,y,z));
        _objetoEnEscena->setMaterialTexture(0, _driver->getTexture(ruta_textura));
        Plataformas_Scena.push_back(_objetoEnEscena);
        return (Plataformas_Scena.size()-1);
    }
}

void MotorGrafico::CargarLuces(int x,int y,int z)
{
    // add light 1 (more green)
    scene::ILightSceneNode* light1 =
    _smgr->addLightSceneNode(0, core::vector3df(x,y,z),video::SColorf(0.5f, 1.0f, 0.5f, 0.0f), 100.0f);

    light1->setDebugDataVisible ( scene::EDS_BBOX );


    // add fly circle animator to light 1
    scene::ISceneNodeAnimator* anim = _smgr->createFlyCircleAnimator (core::vector3df(x,y,z),0.0f, -0.003f);
    light1->addAnimator(anim);
    anim->drop();

    Luces_Scena.push_back(light1);
    // attach billboard to the light
    scene::IBillboardSceneNode* bill =
        _smgr->addBillboardSceneNode(light1, core::dimension2d<f32>(10, 10));

    bill->setMaterialFlag(video::EMF_LIGHTING, false);
    bill->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
    bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    bill->setMaterialTexture(0, _driver->getTexture("assets/models/particlegreen.jpg"));
}

void MotorGrafico::CargarEnemigos(int accion, int x,int y,int z, int ancho, int largo, int alto, const char *ruta_objeto, const char *ruta_textura)
{
    IAnimatedMesh* enemigo = _smgr->getMesh(ruta_objeto); //creamos el objeto en memoria

	if (!enemigo)
	{
		//error
	}
    else
    {
        IAnimatedMeshSceneNode* enemigo_en_scena = _smgr->addAnimatedMeshSceneNode(enemigo); //metemos el objeto en el escenario para eso lo pasamos al escenario
        enemigo_en_scena->setPosition(core::vector3df(x,y,z));
        Enemigos_Scena.push_back(enemigo_en_scena);
    }
}

/******----------------Crear Jugador------------------******
 * Metodo que sirve para generar la malla 3D de un jugador
 * al iniciar estado Juego.
 * Entradas:
 *      ruta_objeto: string con la direccion del modelo 3D
 *      ruta_textura: string con la ruta de la textura
 */
void MotorGrafico::CargarJugador(int x,int y,int z, int ancho, int largo, int alto, const char* ruta_objeto, const char* ruta_textura)
{
    IAnimatedMesh* jugador = _smgr->getMesh(ruta_objeto); //creamos el objeto en memoria
	// Si se ha podido crear el objeto, se mete en escena
    if (jugador)
    {
        _jugEscena = _smgr->addAnimatedMeshSceneNode(jugador); //metemos el objeto en el escenario para eso lo pasamos al escenario
        //cout << x << " " << y << " " << z << " " << endl;
        _jugEscena->setPosition(core::vector3df(x,y,z));
        _jugEscena->setScale(core::vector3df(1.75,1.75,1.75));
        _jugEscena->setFrameLoop(30, 44);
		_jugEscena->setAnimationSpeed(10);
        colorearJugador(255, 255, 255, 255);
        //const SColor COLOR  = SColor(255,0,0,255);
        //smgr->getMeshManipulator()->setVertexColors(_jugEscena->getMesh(),COLOR);
    }
    //jugador = nullptr;
}

int MotorGrafico::CargarObjetos(int accion, int x,int y,int z, int ancho, int largo, int alto, const char *ruta_objeto, const char *ruta_textura)
{
    IAnimatedMesh* objeto = _smgr->getMesh(ruta_objeto); //creamos el objeto en memoria
  	if (objeto)
  	{
        IAnimatedMeshSceneNode* _objetoEnEscena = _smgr->addAnimatedMeshSceneNode(objeto); //metemos el objeto en el escenario para eso lo pasamos al escenario
        _objetoEnEscena->setPosition(core::vector3df(x,y,z));

        if(accion == 4)
        {
          PowerUP_Scena.push_back(_objetoEnEscena);
          return PowerUP_Scena.size() - 1;
        }

        //de momento en el escenario solo se diferencia entre recolectables (2) y el resto de objetos al cargarlos
        accion == 2 ?
            Recolectables_Scena.push_back(_objetoEnEscena) :
            Objetos_Scena.push_back(_objetoEnEscena);
    }
    return Objetos_Scena.size() - 1;
}

void MotorGrafico::CargarArmaJugador(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura)
{
    IAnimatedMesh* _arma = _smgr->getMesh(ruta_objeto); //creamos el objeto en memoria
    if (_arma)
    {
        _armaEnEscena = _smgr->addAnimatedMeshSceneNode(_arma); //metemos el objeto en el escenario para eso lo pasamos al escenario
        _armaEnEscena->setPosition(core::vector3df(x,y,z));
    }
    _arma = nullptr;
}

void MotorGrafico::CargarArmaEspecial(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura)
{
    _armaEsp = _smgr->getMesh(ruta_objeto); //creamos el objeto en memoria
}

void MotorGrafico::CargarRecolectable(int id, int x,int y,int z, const char *ruta_objeto, const char *ruta_textura)
{
    IAnimatedMesh* recol = _smgr->getMesh(ruta_objeto); //creamos el objeto en memoria
    if (recol)
    {
        IAnimatedMeshSceneNode* recol_en_scena = _smgr->addAnimatedMeshSceneNode(recol); //metemos el objeto en el escenario para eso lo pasamos al escenario
        recol_en_scena->setPosition(core::vector3df(x,y,z));
        Recolectables_Scena.push_back(recol_en_scena);
    }
}

void MotorGrafico::llevarObjeto(float x, float y, float z, float rx, float ry, float rz)
{
    if(_armaEnEscena)
    {
        _armaEnEscena->setPosition(core::vector3df(x,y,z));
        _armaEnEscena->setRotation(core::vector3df(rx,ry,rz));
    }
}

void MotorGrafico::mostrarJugador(float x, float y, float z, float rx, float ry, float rz)
{
    // Variables de la camara
    core::vector3df nodeCamPosition = _camera->getPosition();
    core::vector3df nodeCamTarget = _camera->getTarget();

    // Centrar la camara
    nodeCamPosition.X = x;
    nodeCamPosition.Y = y+20;
    nodeCamPosition.Z = z-20;
    nodeCamTarget.X = x;
    nodeCamTarget.Y = y;
    nodeCamTarget.Z = z;

    _camera->setPosition(nodeCamPosition);
    _camera->setTarget(nodeCamTarget);

    _jugEscena->setPosition(core::vector3df(x,y,z));
    _jugEscena->setRotation(core::vector3df(rx,ry-180,rz));

}

void MotorGrafico::mostrarEnemigos(float x, float y, float z, float rx, float ry, float rz, unsigned int i)
{
    if(Enemigos_Scena.size()>0 && Enemigos_Scena.size()>i && Enemigos_Scena[i] != nullptr){
        Enemigos_Scena.at(i)->setPosition(core::vector3df(x,y,z));
        Enemigos_Scena.at(i)->setRotation(core::vector3df(rx,ry,rz));
    }
}

void MotorGrafico::mostrarObjetos(float x, float y, float z, float rx, float ry, float rz, unsigned int i)
{
    Objetos_Scena.at(i)->setPosition(core::vector3df(x,y,z));
    Objetos_Scena.at(i)->setRotation(core::vector3df(rx,ry,rz));
}

void MotorGrafico::mostrarArmaEspecial(float x, float y, float z, float rx, float ry, float rz)
{
    Constantes constantes;
    if (_armaEsp)
	{
        if(_armaEspJugador)
        {
            this->borrarArmaEspecial();
        }
        _armaEspJugador = _smgr->addAnimatedMeshSceneNode(_armaEsp); //metemos el objeto en el escenario para eso lo pasamos al escenario
        _armaEspJugador->setPosition(core::vector3df(x + 5*(sin(constantes.DEG_TO_RAD*ry)),y,z + 5*(cos(constantes.DEG_TO_RAD*ry))));
        _armaEspJugador->setRotation(core::vector3df(rx,ry,rz));
        _smgr->getMeshManipulator()->setVertexColors(_armaEspJugador->getMesh(),SColor(255, 125, 150, 160));
    }
}

void MotorGrafico::borrarArmaEspecial()
{
    _armaEspJugador->remove();
    _armaEspJugador = nullptr;
}

void MotorGrafico::activarDebugGrafico()
{
    if(debugGrafico)
    {
        debugGrafico = false;
        if(Objetos_Debug.size()>0)
        {
            for(std::size_t i=0;i<Objetos_Debug.size();i++)
            {
                Objetos_Debug[i]->remove();
                Objetos_Debug[i] = NULL;
                delete Objetos_Debug[i];
            }
            Objetos_Debug.resize(0);
        }
        cout << "\e[38m Modo Debug Desactivado \e[0m" << endl;
    }
    else
    {
        debugGrafico = true;
        cout << "\e[38m Modo Debug Activado \e[0m" << endl;
    }
}

void MotorGrafico::activarPathfinding()
{
    if(pathfinding)
    {
        pathfinding = false;
        cout << "\e[38m Pathfinding Desactivado \e[0m" << endl;
    }
    else
    {
        pathfinding = true;
        cout << "\e[38m Pathfinding Activado \e[0m" << endl;
    }
}

void MotorGrafico::clearDebug()
{
    if(Objetos_Debug.size()>0)
    {
        for(std::size_t i=0;i<Objetos_Debug.size();i++)
        {
            Objetos_Debug[i]->remove();
            Objetos_Debug[i] = NULL;
            delete Objetos_Debug[i];
        }
        Objetos_Debug.resize(0);
    }
}

void MotorGrafico::clearDebug2()
{
    if(Objetos_Debug2.size()>0)
    {
        for(std::size_t i=0;i<Objetos_Debug2.size();i++)
        {
            Objetos_Debug2[i]->remove();
            Objetos_Debug2[i] = NULL;
            delete Objetos_Debug2[i];
        }
        Objetos_Debug2.resize(0);
    }
}

void MotorGrafico::dibujarCirculoEventoSonido(int x, int y, int z, float intensidad)
{
    if(debugGrafico)
    {
        IAnimatedMesh* circulo = _smgr->getMesh("assets/models/circuloDebugSonido.obj");
        if(!circulo)
        {
            //no se ha podido cargar
        }
        else
        {
            //vamos a cargar el circulo en su posicion con su intensidad
            //cout << "\e[36m Generamos Circulo \e[0m" << endl;
            IAnimatedMeshSceneNode* _objetoEnEscena = _smgr->addAnimatedMeshSceneNode(circulo); //metemos el objeto en el escenario para eso lo pasamos al escenario
            SColor COLOR  = SColor(127, 255, 0, 0);
            _smgr->getMeshManipulator()->setVertexColors(_objetoEnEscena->getMesh(),COLOR);
            _objetoEnEscena->setPosition(core::vector3df(x,y,z));
            _objetoEnEscena->setScale(core::vector3df(intensidad,1,intensidad));
            Objetos_Debug.push_back(_objetoEnEscena);
        }
    }
}

void MotorGrafico::dibujarZona(int x, int y, int z, float ancho, float alto, float profund)
{
  if(debugGrafico)
  {
    IAnimatedMesh* tmpobjt = _smgr->getMesh("assets/models/zona.obj");
    _tmpObjEscena = _smgr->addAnimatedMeshSceneNode(tmpobjt);
    _tmpObjEscena->setPosition(core::vector3df(x,y,z));
    _tmpObjEscena->setScale(core::vector3df(ancho,1.0f,profund));
    SColor COLOR  = SColor(255,255,255,0);
    _smgr->getMeshManipulator()->setVertexColors(_tmpObjEscena->getMesh(),COLOR);
    Objetos_Debug.push_back(_tmpObjEscena);
    _tmpObjEscena = nullptr;
  }
}

void MotorGrafico::dibujarObjetoTemporal(int x, int y, int z, int rx, int ry, int rz ,int ancho, int alto, int profund, int tipo)
{
  if(debugGrafico)
  {
    //Crear objetos debug
    IAnimatedMesh* tmpobjt;
    if(tipo == 1)
    {
      tmpobjt = _smgr->getMesh("assets/models/sphere.obj");
    }else if(tipo == 2)
    {
      tmpobjt = _smgr->getMesh("assets/models/cube.obj");
    }else if(tipo == 3)
    {
      tmpobjt = _smgr->getMesh("assets/models/capsule.obj");
    }
    _tmpObjEscena = _smgr->addAnimatedMeshSceneNode(tmpobjt);
    _tmpObjEscena->setPosition(core::vector3df(x,y,z));
    _tmpObjEscena->setRotation(core::vector3df(rx,ry,rz));
    _tmpObjEscena->setScale(core::vector3df(ancho,alto,profund));
    SColor COLOR  = SColor(255,255,0,255);
    _smgr->getMeshManipulator()->setVertexColors(_tmpObjEscena->getMesh(),COLOR);
    Objetos_Debug2.push_back(_tmpObjEscena);
    _tmpObjEscena = nullptr;
  }
}

bool MotorGrafico::colisionRayo(int x,int y, int z, int rx, int ry, int rz ,int dimension)
{
    return true;
}

/*void MotorGrafico::dibujarRayo(int x,int y, int z, int rx, int ry, int rz ,int dimension)
{
    if(debugGrafico)
    {
        if(!_linea)
        {
            _linea = _smgr->getMesh("assets/models/linea.obj");
        }
        else
        {
            // TO DO:objeto_en_scena -> _objetoEnEscena
            IAnimatedMeshSceneNode* _objetoEnEscena = _smgr->addAnimatedMeshSceneNode(_linea);
            _objetoEnEscena->setPosition(core::vector3df(x,y,z));
            _objetoEnEscena->setRotation(core::vector3df(rx,ry,rz));
            _objetoEnEscena->setScale(core::vector3df(dimension,0.2,0.5));
            Objetos_Debug.push_back(_objetoEnEscena);
        }
    }
}*/

void MotorGrafico::colorearJugador(int a, int r, int g, int b)
{
  SColor COLOR  = SColor(a, r, g, b);
  _smgr->getMeshManipulator()->setVertexColors(_jugEscena->getMesh(),COLOR);
}

void MotorGrafico::colorearEnemigo(int a, int r, int g, int b, int enem)
{
  SColor COLOR  = SColor(a, r, g, b);
  long unsigned int valor = enem;
  if(Enemigos_Scena.size() > 0 && valor < Enemigos_Scena.size())//para no salirnos si no existe en motorgrafico
  _smgr->getMeshManipulator()->setVertexColors(Enemigos_Scena[enem]->getMesh(),COLOR);
}

/*void MotorGrafico::colorearObjeto(int a, int r, int g, int b, int obj)
{
  SColor COLOR  = SColor(a, r, g, b);
  long unsigned int valor = obj;
  if(Objetos_Scena.size() > 0 && valor < Objetos_Scena.size())//para no salirnos si no existe en motorgrafico
  _smgr->getMeshManipulator()->setVertexColors(Objetos_Scena[obj]->getMesh(),COLOR);
}*/

IAnimatedMeshSceneNode* MotorGrafico::getArmaEspecial()
{
    return _armaEspJugador;
}

// TO DO: revisar vector
void MotorGrafico::EraseColectable(long unsigned int idx)
{
    if(Recolectables_Scena[idx] && idx < Recolectables_Scena.size())
    {
        Recolectables_Scena[idx]->setVisible(false);
        Recolectables_Scena[idx]->remove();
        Recolectables_Scena.erase(Recolectables_Scena.begin() + idx);
    }
}

void MotorGrafico::ErasePowerUP(long unsigned int idx)
{
    if(PowerUP_Scena[idx] && idx < PowerUP_Scena.size())
    {
        PowerUP_Scena[idx]->setVisible(false);
        PowerUP_Scena[idx]->remove();
        PowerUP_Scena.erase(PowerUP_Scena.begin() + idx);
    }
}

//Cuando enemigo muere lo borramos
void MotorGrafico::EraseEnemigo(std::size_t i){
    long unsigned int valor = i;

    if(valor >= 0 && valor < Enemigos_Scena.size())
    {
        Enemigos_Scena[i]->setVisible(false);
        Enemigos_Scena[i]->remove();
        Enemigos_Scena.erase(Enemigos_Scena.begin() + i);
    }
}

//Cuando jugador muere lo borramos
void MotorGrafico::EraseJugador(){
    _jugEscena->setVisible(false);
    _jugEscena->remove();
}

void MotorGrafico::EraseArma()
{
    _armaEnEscena->setVisible(false);
    _armaEnEscena->remove();
}

//Devolver cantidad de enemigos en escena para recorrerlos en metodo muerteEnemigo
/*int MotorGrafico::getEnemigos_Scena(){
    return Enemigos_Scena.size();
}*/

//Devolver cantidad de objetos en escena para recorrerlos en metodo muerteEnemigo
/*int MotorGrafico::getObjetos_Scena(){
    return Objetos_Scena.size();
}*/

//esta funcion es para ver la caja del bounding box creada en motor fisicas
//abra que pasarle el numero de caja
void MotorGrafico::debugBox(int x,int y, int z,int ancho, int alto, int largo)
{
    if(debugGrafico)
    {
        //cout << x << y << z << ancho << largo << alto << endl;
        if(_caja)
        {
            _caja->setMaterialFlag(video::EMF_LIGHTING, false);
            //_caja->setPosition(core::vector3df(x,y,z));
            //_caja->setScale(core::vector3df(ancho/5,alto/5,largo/5));
            _caja->setPosition(core::vector3df(0,0,20));
            _caja->setScale(core::vector3df(4,1,0.2));
        }
        else
        {
            _caja = _smgr->addCubeSceneNode();
        }
    }
}

void MotorGrafico::debugVision(float x, float y, float z, float rotacion, float longitud)
{
    if(debugGrafico)
    {
        if(!_conoVision)
        {

            _conoVision = _smgr->getMesh("assets/models/conoVision.obj");
        }

        if(_conoVision) // Si se ha cargado
        {
            IAnimatedMeshSceneNode* _objetoEnEscena = _smgr->addAnimatedMeshSceneNode(_conoVision); //metemos el objeto en el escenario para eso lo pasamos al escenario
            _objetoEnEscena->setPosition(core::vector3df(x,y+1,z));
            SColor COLOR  = SColor(0, 255, 0, 0);
            _smgr->getMeshManipulator()->setVertexColors(_objetoEnEscena->getMesh(),COLOR);

            core::vector3df rotation = _objetoEnEscena->getRotation();
            _objetoEnEscena->setRotation(core::vector3df(rotation.X,rotacion,rotation.Z));

            rotation = _objetoEnEscena->getRotation();

            _objetoEnEscena->setScale(core::vector3df(longitud/2,1.0f,0.01f));
            Objetos_Debug.push_back(_objetoEnEscena);
        }
    }
}

void MotorGrafico::cargarInterfaz()
{
    //activamos la interfaz
    InterfazJugador * interfaz = InterfazJugador::getInstance();
    interfaz->activar();//activamos la interfaz por defecto
    //creamos texturas
    vida_textura = _driver->getTexture("assets/images/51.png");
    energia_textura = _driver->getTexture("assets/images/21.png");
    dinero_textura = _driver->getTexture("assets/images/61.png");
    arma_textura = _driver->getTexture("assets/images/11.png");
    barraVida_textura = _driver->getTexture("assets/images/4.png");
    barraEnergia_textura = _driver->getTexture("assets/images/3.png");
    manos_textura = _driver->getTexture("assets/images/manos.png");
    llave_textura = _driver->getTexture("assets/images/llave.png");
    espada_textura = _driver->getTexture("assets/images/espada.png");
    daga_textura = _driver->getTexture("assets/images/daga.png");
    //aplicamos texturas
    vidaI = _guienv->addImage(vida_textura,position2d<int>(10,10));
    energiaI = _guienv->addImage(energia_textura,position2d<int>(10,58));
    dineroI = _guienv->addImage(dinero_textura,position2d<int>(680,10));
    armaI = _guienv->addImage(arma_textura,position2d<int>(730,530));
    BarraVidaI = _guienv->addImage(barraVida_textura,position2d<int>(50,15));
    BarraEnergiaI = _guienv->addImage(barraEnergia_textura,position2d<int>(48,65));

    //imagenes tipo objeto que se lleva por defecto manos
    manosI = _guienv->addImage(manos_textura,position2d<int>(738,534));
    llaveI = _guienv->addImage(llave_textura,position2d<int>(738,534));
    espadaI = _guienv->addImage(espada_textura,position2d<int>(738,534));
    dagaI = _guienv->addImage(daga_textura,position2d<int>(738,534));

    BarraVidaI->setMaxSize(dimension2du(121,29));//maximo 121/100 y esto multiplicado por la cantidad de vida
    BarraEnergiaI->setMaxSize(dimension2du(63,27));//maximo 63/100 y esto multiplicado por la cantidad de energia
    font2 = _guienv->getFont("assets/fonts/myfont.xml");

    //moneyI = _guienv->addStaticText(L"1000 M",rect<s32>(710,21,750,40),false); //falta ver los cambios de fuente y ponerlo correctamente
    moneyI = _guienv->addStaticText(L"0 M",rect<s32>(710,21,750,40),false); //falta ver los cambios de fuente y ponerlo correctamente

    SColor COLOR  = SColor(255, 255, 255, 0);
    moneyI->enableOverrideColor(true);
    moneyI->setOverrideColor(COLOR);
    if(font2)
        moneyI->setOverrideFont(font2);

}

void MotorGrafico::destruirInterfaz()
{
    if(vidaI)
    {
        vidaI->remove();
    }

    if(energiaI)
    {
        energiaI->remove();
    }

    if(dineroI)
    {
        dineroI->remove();
    }

    if(armaI)
    {
         armaI->remove();
    }

    if(manosI)
        manosI->remove();

    if(dagaI)
        dagaI->remove();

    if(espadaI)
        espadaI->remove();

    if(llaveI)
        llaveI->remove();

    if(BarraEnergiaI)
        BarraEnergiaI->remove();

    if(BarraVidaI)
        BarraVidaI->remove();

    if(moneyI)
        moneyI->remove();

    _driver->removeTexture(vida_textura);
    _driver->removeTexture(energia_textura);
    _driver->removeTexture(dinero_textura);
    _driver->removeTexture(arma_textura);
    _driver->removeTexture(barraVida_textura);
    _driver->removeTexture(barraEnergia_textura);
    _driver->removeTexture(manos_textura);
    _driver->removeTexture(llave_textura);
    _driver->removeTexture(espada_textura);
    _driver->removeTexture(daga_textura);

}

void MotorGrafico::updateInterfaz()
{
    //vamos a conseguir los datos de la interfaz
    InterfazJugador * interfaz = InterfazJugador::getInstance();

    if(interfaz->getEstado())
    {
        if(vidaI)
        vidaI->setVisible(true);
        if(energiaI)
        energiaI->setVisible(true);
        if(dineroI)
        dineroI->setVisible(true);
        if(armaI)
        armaI->setVisible(true);
        if(BarraEnergiaI)
        BarraEnergiaI->setVisible(true);
        if(BarraVidaI)
        BarraVidaI->setVisible(true);
        if(moneyI)
        moneyI->setVisible(true);

        int * datos = interfaz->getUpdate();
        //vamos a calcular vida
        if(BarraVidaI)
        {
            float unidad = ((float)121/100);
            float resultado = unidad*(float)datos[1];
            if(resultado <= 0)
            {
                BarraVidaI->setMaxSize(dimension2du(1,29));//maximo 121/100 y esto multiplicado por la cantidad de vida
            }
            else
            {
                BarraVidaI->setMaxSize(dimension2du(resultado,29));//maximo 121/100 y esto multiplicado por la cantidad de vida
            }
        }

        if(moneyI)
        {
            stringw str = L"";
            str += datos[3];
            moneyI->setText(str.c_str());
        }

        if(BarraEnergiaI)
        {
            float unidad = ((float)63/100);
            float resultado = unidad*(float)datos[2];
            //cout << datos[2] << " " << unidad << " " << resultado << endl ;
            if(resultado <= 0)
            {
                BarraEnergiaI->setMaxSize(dimension2du(1,27));//maximo 121/100 y esto multiplicado por la cantidad de vida
            }
            else
            {
                BarraEnergiaI->setMaxSize(dimension2du(resultado,27));//maximo 121/100 y esto multiplicado por la cantidad de vida
            }
        }

        switch(datos[4])
        {
            case 0:
            //son las manos
            manosI->setVisible(true);
            dagaI->setVisible(false);
            espadaI->setVisible(false);
            llaveI->setVisible(false);
            break;
            case 1:
            //es una llave
            manosI->setVisible(false);
            dagaI->setVisible(false);
            espadaI->setVisible(false);
            llaveI->setVisible(true);
            break;
            case 2:
            //objeto ataque directo
            manosI->setVisible(false);
            dagaI->setVisible(false);
            espadaI->setVisible(true);
            llaveI->setVisible(false);
            break;
            case 3:
            //objeto ataque a distancia
            manosI->setVisible(false);
            dagaI->setVisible(true);
            espadaI->setVisible(false);
            llaveI->setVisible(false);
            break;
        }
        delete [] datos;
    }
    else
    {
        if(vidaI)
        vidaI->setVisible(false);
        if(energiaI)
        energiaI->setVisible(false);
        if(dineroI)
        dineroI->setVisible(false);
        if(armaI)
        armaI->setVisible(false);
        if(BarraEnergiaI)
        BarraEnergiaI->setVisible(false);
        if(BarraVidaI)
        BarraVidaI->setVisible(false);
        if(manosI)
        manosI->setVisible(false);
        if(dagaI)
        dagaI->setVisible(false);
        if(espadaI)
        espadaI->setVisible(false);
        if(llaveI)
        llaveI->setVisible(false);
        if(moneyI)
        moneyI->setVisible(false);
    }

}

void MotorGrafico::cambiarAnimacionJugador(int estado)
{
    int frame = _jugEscena->getStartFrame();
    int frame_actual = _jugEscena->getFrameNr();
    //animaciones para heavy
    if(estado == 0 && frame != 30 && frame != 120) //esta quieto
    {
        if(_jugEscena)
        {
            _jugEscena->setFrameLoop(30, 44);
		    _jugEscena->setAnimationSpeed(10);
        }
    }

    if(estado == 1 && frame != 0 && frame != 120) //se mueve
    {
        if(_jugEscena)
        {
            _jugEscena->setFrameLoop(0, 30);
		    _jugEscena->setAnimationSpeed(20);
        }
    }

    if(estado == 2 && frame != 48  && frame != 120) //ataca
    {
        if(_jugEscena)
        {
            _jugEscena->setFrameLoop(48, 70);
		    _jugEscena->setAnimationSpeed(15);
        }
    }

    if(estado == 3 && frame != 72  && frame != 120) //ataque especial
    {
        if(_jugEscena)
        {
            _jugEscena->setFrameLoop(72, 98);
		    _jugEscena->setAnimationSpeed(10);
        }
    }

    if(estado == 4  && frame != 99  && frame != 120) //coger objeto
    {
        if(_jugEscena)
        {
            _jugEscena->setFrameLoop(99, 112);
		    _jugEscena->setAnimationSpeed(10);
        }
    }

    if(estado == 5 && frame != 120) //muere
    {
        if(frame_actual == 119)
        {
            _jugEscena->setFrameLoop(120, 128); //lo dejamos definitivamente muerto
		    _jugEscena->setAnimationSpeed(10);
        }
        else
        {
            if(_jugEscena && frame != 112)
            {
                _jugEscena->setFrameLoop(112, 120);
                _jugEscena->setAnimationSpeed(10);
            }
        }
    }
}

bool MotorGrafico::getPathfindingActivado()
{
    return pathfinding;
}

// Funciones para puzzles
void MotorGrafico::PosicionCamaraEnPuzzles()
{
    _camera->setPosition(vector3df(14, 2, 0)); // No cambiar la Y, si nos la seleccion tendra errores
}

void MotorGrafico::updateMotorPuzzles(short tipo)
{
    _driver->beginScene(true, true, SColor(255,255,255,255));//fondo blanco
    _smgr->drawAll();
    _guienv->drawAll();

    /* Probando a dibujar objetos 2D
    //Rectangulo
    _driver->draw2DRectangle(SColor(255, 255, 128, 64), rect<s32>(40, 40, 200, 200));

    //Poligono
    _driver->draw2DPolygon(position2d<s32>(100, 300), 50.f, SColor(128, 40, 80, 16), 6);*/

    switch(tipo)
    {
        case P_OPCIONES:
            break;
        case P_HANOI:
            // Lineas para dividir la pantalla
            _driver->draw2DLine(position2d<s32>(x_linea1 , 200),
                position2d<s32>(x_linea1, 400 ) , SColor(255, 0, 0, 0));
            _driver->draw2DLine(position2d<s32>(x_linea2 , 200),
                position2d<s32>(x_linea2, 400 ) , SColor(255, 0, 0, 0));
            break;
    }

    _driver->endScene();
}

void MotorGrafico::PuzzlesGui(short tipo, std::string enun, short opciones)
{
    short height_aux = (HEIGHT/2)+100;
    short yIMG = height_aux-125;
    short xIMG = 20;
    short anchoBtn = 40;
    short altoBtn = 30;

    // Atras
    _guienv->addButton(rect<s32>(700,HEIGHT-60,750,HEIGHT-30), 0,
        GUI_ID_ATRAS_BUTTON,L"Atrás", L"Vuelve al menú");

    // Enunciado
    std::wstring widestr = std::wstring(enun.begin(), enun.end());
    const wchar_t* widecstr = widestr.c_str();
    _guienv->addStaticText(widecstr, rect<s32>(60,20,700,50), false);

    switch(tipo)
    {
        case P_OPCIONES: // Opciones
            _guienv->addStaticText(L"Puzzle Opciones", rect<s32>(0,0,200,20), false);
            _guienv->addStaticText(L"Ejemplo", rect<s32>(WIDTH-200,20,
                WIDTH-160,40), false);

            _img = _guienv->addImage(_driver->getTexture("assets/puzzles/particle.bmp"),
                core::position2d<s32>(WIDTH-200, 40));

            switch(opciones) {
                case 2:
                    WIDTH_AUX = WIDTH/4;
                    // x, y, x2, y2
                    _guienv->addButton(rect<s32>(WIDTH_AUX,height_aux,
                        WIDTH_AUX+anchoBtn,height_aux+altoBtn),
                        0, GUI_ID_OP1,L"A", L"A");
                    _guienv->addButton(rect<s32>(WIDTH_AUX*3,height_aux,
                        WIDTH_AUX*3+anchoBtn,height_aux+altoBtn),
                        0, GUI_ID_OP2,L"B", L"B");

                    CargarIMG(WIDTH_AUX-xIMG, yIMG);
                    CargarIMG(WIDTH_AUX*3-xIMG, yIMG);
                    break;

                case 3:
                    WIDTH_AUX = (WIDTH-2)/6;
                    // x, y, x2, y2
                    _guienv->addButton(rect<s32>(WIDTH_AUX,height_aux,
                        WIDTH_AUX+anchoBtn,height_aux+altoBtn),
                        0, GUI_ID_OP1,L"A", L"A");
                    _guienv->addButton(rect<s32>(WIDTH_AUX*3,height_aux,
                        WIDTH_AUX*3+anchoBtn,height_aux+altoBtn),
                        0, GUI_ID_OP2,L"B", L"B");
                    _guienv->addButton(rect<s32>(WIDTH_AUX*5,height_aux,
                        WIDTH_AUX*5+anchoBtn,height_aux+altoBtn),
                        0, GUI_ID_OP3,L"C", L"C");

                    CargarIMG(WIDTH_AUX-xIMG, yIMG);
                    CargarIMG(WIDTH_AUX*3-xIMG, yIMG);
                    CargarIMG(WIDTH_AUX*5-xIMG, yIMG);
                    break;

                case 4:
                    WIDTH_AUX = WIDTH/8;
                    // x, y, x2, y2
                    _guienv->addButton(rect<s32>(WIDTH_AUX,height_aux,
                        WIDTH_AUX+anchoBtn,height_aux+altoBtn),
                        0, GUI_ID_OP1,L"A", L"A");
                    _guienv->addButton(rect<s32>(WIDTH_AUX*3,height_aux,
                        WIDTH_AUX*3+anchoBtn,height_aux+altoBtn),
                        0, GUI_ID_OP2,L"B", L"B");
                    _guienv->addButton(rect<s32>(WIDTH_AUX*5,height_aux,
                        WIDTH_AUX*5+anchoBtn,height_aux+altoBtn),
                        0, GUI_ID_OP3,L"C", L"C");
                    _guienv->addButton(rect<s32>(WIDTH_AUX*7,height_aux,
                        WIDTH_AUX*7+anchoBtn,height_aux+altoBtn),
                        0, GUI_ID_OP4,L"D", L"D");

                    CargarIMG(WIDTH_AUX-xIMG, yIMG);
                    CargarIMG(WIDTH_AUX*3-xIMG, yIMG);
                    CargarIMG(WIDTH_AUX*5-xIMG, yIMG);
                    CargarIMG(WIDTH_AUX*7-xIMG, yIMG);
                    break;
            }
            break;

        case P_HANOI: // Torres de Hanoi
            _guienv->addStaticText(L"Torres de Hanoi", rect<s32>(0,0,200,20), false);

            // Reiniciar
            _guienv->addButton(rect<s32>(700,HEIGHT-90,750,HEIGHT-60), 0,
                GUI_ID_REINICIAR_HANOI,L"Reiniciar", L"Reinicia el juego");

            _myTextBox = _guienv->addStaticText(L"Pasos: ", rect<s32>(60,(WIDTH/2)-10,100,(WIDTH/2)+30), false);

            WIDTH_AUX = (WIDTH-2)/6;
            _guienv->addStaticText(L"IZQ", rect<s32>(WIDTH_AUX,100,WIDTH_AUX+anchoBtn,130), false);
            _guienv->addStaticText(L"CENTRO", rect<s32>(WIDTH_AUX*3,100,WIDTH_AUX*3+anchoBtn,130), false);
            _guienv->addStaticText(L"DER", rect<s32>(WIDTH_AUX*5,100,WIDTH_AUX*5+anchoBtn,130), false);

            // Para la ventana de 800, 600
            // Width = 798, dejamos 1 punto a cada lado
            WIDTH_AUX = (WIDTH-2)/3;    // Dividimos la pantalla en 3 zonas
            x_linea1 = WIDTH_AUX;
            x_linea2 = WIDTH_AUX*2;
            break;
    }
}

void MotorGrafico::TextoPasos(short pasos)
{
    stringw str = L"Pasos: ";
    str += pasos;
    _myTextBox->setText(str.c_str());
    _myTextBox = nullptr;
}

// TO DO: Anyadir string img
void MotorGrafico::CargarIMG(short x, short y)
{
    _puzParticleTexture = _driver->getTexture("assets/puzzles/particle.bmp");
	_img = _guienv->addImage(_puzParticleTexture,core::position2d<s32>(x, y));
}

void MotorGrafico::CrearMeshFicha(float tamanyo, int r, int g, int b)
{
    //_fichaMesh = _geometryCreator->createCubeMesh(vector3df(tamanyo));
    _fichaMesh = _geometryCreator->createCylinderMesh(
        tamanyo,    //radius
        1,          //length
        50,         //tesselation
        SColor(0, r, g, b));

    // insensible a la iluminacion
    _fichaMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}

void MotorGrafico::CrearFichas(short posY, float tamanyo,
    int r, int g, int b)
{
    CrearMeshFicha(tamanyo, r, g, b);
    _ficha = _smgr->addMeshSceneNode(_fichaMesh);
    _ficha->setPosition(vector3df(0, posY, IZQ));
    _ficha->setID(tamanyo);

    // La anyadimos a la lista
    fichasMesh.push_back(move(_ficha));
    _ficha = nullptr;
}

short MotorGrafico::GetZonaVentana()
{
    short posX = GetPosicionRaton().X;
    if ((posX > 0) && (posX <= WIDTH)) {
        if ((posX > 0) && (posX <= WIDTH_AUX)) {
            return IZQ;
        } else if ((posX > WIDTH_AUX) && (posX <= WIDTH_AUX*2)) {
            return CENTRO;
        } else {
            return DER;
        }
    }
    return NO_SELECT;// Fuera de ventana
}

bool MotorGrafico::SeleccionarNodo()
{
    // check for a node being selected
    // Posicion, idBitMask (0=deshabilitada), bNoDebugObjects (true=No tiene en cuenta los objetos de depuracion)
    _nodoSeleccionado = _collmgr->getSceneNodeFromScreenCoordinatesBB(
        _device->getCursorControl()->getPosition(),0,true);

    // Si hay un nodo seleccionado
    if(_nodoSeleccionado)
    {
        // Remember where the node and cursor were when it was clicked on
        initialCursorPosition = _device->getCursorControl()->getPosition();
        // Calcula la posición de la pantalla 2d desde una posición 3d.
        initialObjectPosition = _collmgr->getScreenCoordinatesFrom3DPosition(
            _nodoSeleccionado->getAbsolutePosition(), _camera);

        if (_nodoSeleccionado->getID() != -1) { // Comprobamos que no sea el fondo
            return true;
        }
    } else {
        _nodoSeleccionado = nullptr;
    }
    return false;
}

void MotorGrafico::DeseleccionarNodo()
{
    _nodoSeleccionado = 0;
}

short MotorGrafico::GetFichaY()
{
    return _nodoSeleccionado->getAbsolutePosition().Y;
}

void MotorGrafico::MoverFichas(short pila)
{
    if ((_nodoSeleccionado) && (pila != NO_SELECT))
    {
        plane3df const planeXZ(_nodoSeleccionado->getAbsolutePosition(), vector3df(1.f, 0.f, 0.f));

        position2di currentCursorPosition(_device->getCursorControl()->getPosition());
        position2di effectiveObjectPosition = initialObjectPosition + currentCursorPosition - initialCursorPosition;
        line3df ray(_collmgr->getRayFromScreenCoordinates(effectiveObjectPosition, _camera));
        vector3df intersectWithPlane;

        if(planeXZ.getIntersectionWithLine(ray.start, ray.getVector(), intersectWithPlane))
        {
            _nodoSeleccionado->setPosition(intersectWithPlane);
        }
    }
}

void MotorGrafico::RecolocarFicha(short y, short z)
{
    short x = _nodoSeleccionado->getAbsolutePosition().X;
    _nodoSeleccionado->setPosition(vector3df(x, y, z));
}

void MotorGrafico::ReiniciarHanoi()
{
	short tam = fichasMesh.size();
    short posY=0;
    for (int pos = 0; pos<tam; pos++)
    {
        fichasMesh.at(pos)->setPosition(vector3df(0, posY, IZQ));
        posY++;
    }
}

void MotorGrafico::updateMotorCinematica()
{
    _driver->beginScene(true, true, SColor(0,0,0,0));

    float mile = 1000.0f;
    float ratio = 30.0f;
    float tiempo_frame = mile/ratio;
    int salto = ceil(tiempoUltimoFrame/tiempo_frame);
    if(frame_actual == 0)
    {
        frame_actual = 1;
    }
    else
    {
        if(tiempoUltimoFrame > tiempo_frame)
        {
            //es mayor (va lento)
            frame_actual = frame_actual+(1+salto);
        }
        else
        {
            //es menor (va mas rapido)
            frame_actual = frame_actual+1;
        }
    }

    if(frame_actual < 498)
    {
        //definimos los strings
        std::string fram = "";
        std::string extension = ".jpg";
        float marcaTiempo = Times::GetInstance()->GetTiempo(1);
        std::string ruta = "assets/cinematicas/frames/";
        fram = std::to_string(frame_actual);
        //creamos la ruta completa
        std::string ruta_completa = ruta+fram+extension;
        char buffer[100];
        strcpy(buffer,ruta_completa.c_str());

        if(actual != nullptr && actualTexture != nullptr)
        {
            actual->remove();//remuevo imagen actual
            _driver->removeTexture(actualTexture);//borras textura
            actualTexture = _driver->getTexture(buffer);//creas la textura
            actual = _guienv->addImage(actualTexture,position2d<int>(0,0));//creo imagen actual
        }
        else
        {
            actualTexture = _driver->getTexture(buffer);//creo textura
            actual = _guienv->addImage(_driver->getTexture(buffer),position2d<int>(0,0));//creo imagen con textura
        }

        tiempoUltimoFrame = Times::GetInstance()->CalcularTiempoPasado(marcaTiempo);
        //cout << tiempoUltimoFrame << " " << salto << endl;
    }
    _smgr->drawAll();
	_guienv->drawAll();
	_driver->endScene();
}

bool MotorGrafico::finalCinematica()
{
    if(frame_actual >= 498)
    {
        //borramos los datos
        actual->remove();//remuevo imagen actual
        _driver->removeTexture(actualTexture);//borras textura
        //borramos los punteros
        actual = nullptr;
        actualTexture = nullptr;
        return true;
    }

    return false;
}