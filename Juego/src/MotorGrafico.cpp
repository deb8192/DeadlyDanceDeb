#include "MotorGrafico.hpp" //se llama a su cabezera para cargar las dependencias
//para clases singleton deben tener un indicador de que se ha creado el unico objeto

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

MotorGrafico* MotorGrafico::unica_instancia = 0;
//fin indicador singleton

/*Tipo 1(640x480), Tipo 2(800x600), Tipo 3(1024x768), Tipo 4(1280x1024)
Esta clase define que tipo de pantalla quieres
*/
MotorGrafico::MotorGrafico()
{
    input.setDevice(device);//lo  utilizamos para que los eventos puedan llamar a funciones de
    debugGrafico = false;
}

MotorGrafico::~MotorGrafico()
{

}

bool MotorGrafico::crearVentana(int tipo)
{
    std::string titulo = "";
    switch(tipo)
    {
        case 1:
            WIDTH=640; HEIGHT=480;
            titulo = "DeadlyDance LowResolution";
            break;

        case 2:
            WIDTH=800; HEIGHT=600;
            titulo = "DeadlyDance MediumResolution";
            break;

        case 3:
            WIDTH=1024; HEIGHT=768;
            titulo = "DeadlyDance NormalResolution";
            break;

        case 4:
            WIDTH=1280; HEIGHT=1024;
            titulo = "DeadlyDance HightResolution";
            break;

        default:
            return false;
    }
    device = createDevice( video::EDT_SOFTWARE, dimension2d<u32>(WIDTH, HEIGHT), 16,false, false, false, &input);

    std::wstring widestr = std::wstring(titulo.begin(), titulo.end());
    const wchar_t* widecstr = widestr.c_str();
    device->setWindowCaption(widecstr);

    device->setResizable(false);
    PropiedadesDevice();
    return true;
}

void MotorGrafico::closeGame()
{
    device->closeDevice();
}

bool MotorGrafico::sigueFuncionando()
{
    return device->run();
}

void MotorGrafico::limpiarDevice()
{
    device->drop();
}

void MotorGrafico::crearTextoDePrueba()
{
    guienv->addStaticText(L"Deadly Dance",rect<s32>(0,0,80,20), true);
}

void MotorGrafico::updateMotorMenu()
{
    driver->beginScene(true, true, SColor(255,100,101,140));
	smgr->drawAll();
	guienv->drawAll();
	driver->endScene();
}

void MotorGrafico::updateMotorJuego()
{
    driver->beginScene(true, true, SColor(255,0,0,0));
	smgr->drawAll();
	guienv->drawAll();
	driver->endScene();
}

void MotorGrafico::updateMotorCinematica()
{
    driver->beginScene(true, true, SColor(0,0,0,0));
	
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
        float marcaTiempo = times::getInstance()->getTiempo(1); 
        std::string ruta = "assets/cinematicas/frames/";
        fram = std::to_string(frame_actual);
        //creamos la ruta completa
        std::string ruta_completa = ruta+fram+extension;
        char buffer[100];
        strcpy(buffer,ruta_completa.c_str());
        actual = guienv->addImage(driver->getTexture(buffer),position2d<int>(0,0));
        tiempoUltimoFrame = times::getInstance()->calcularTiempoPasado(marcaTiempo);
        cout << tiempoUltimoFrame << " " << salto << endl;
    }
    smgr->drawAll();
	guienv->drawAll();
	driver->endScene();
}

void MotorGrafico::CrearCamara()
{
  //primer vector traslacion, segundo rotacion
  //  smgr->addCameraSceneNode(0, vector3df(0,0,90), vector3df(0,0,0));
  camera = smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,0,0));
}
/******----------------Crear Jugador------------------******
 * Metodo que sirve para generar la malla 3D de un jugador
 * al iniciar estado Juego.
 * Entradas:
 *      malla: string con la direccion del modelo 3D
 */

void MotorGrafico::crearJugador(std::string malla)
{
    ninja = smgr->addAnimatedMeshSceneNode(smgr->getMesh(malla.c_str()));
    ninja->setScale(core::vector3df(0.1,0.1,0.1));
}

void MotorGrafico::PropiedadesDevice()
{
    cout << "\e[32m Aplicando propiedades a device \e[0m" << endl;
    driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
    geometryCreator = smgr->getGeometryCreator();
    collmgr = smgr->getSceneCollisionManager();

    cout << "\e[32m Propiedades aplicadas \e[0m" << endl;
}

void MotorGrafico::PintarBotonesMenu()
{
	guienv->addButton(rect<s32>(300,200,500,230), 0, GUI_ID_EMPEZAR_BUTTON,L"Iniciar Juego", L"Empieza a jugar");
    guienv->addButton(rect<s32>(300,240,500,270), 0, GUI_ID_PUZZLES_BUTTON,L"Puzzles", L"Minijuego");
    guienv->addButton(rect<s32>(300,280,500,310), 0, GUI_ID_ARBOLES_BUTTON,L"Cargar Árbol", L"Carga un XML");
    guienv->addButton(rect<s32>(300,320,500,350), 0, GUI_ID_CONFIGURACION_BUTTON,L"Configuracion", L"Configuracion del juego");
    guienv->addButton(rect<s32>(300,360,500,390), 0, GUI_ID_CREDITOS_BUTTON,L"Creditos", L"Creditos del juego");
    guienv->addButton(rect<s32>(300,400,500,430), 0, GUI_ID_SALIR_BUTTON,L"Salir del juego", L"Sale del juego");
}

void MotorGrafico::activarFuenteDefault()
{
    skin = guienv->getSkin();
    font = guienv->getFont("assets/fonts/default.bmp");
    if (font)
    {
        skin->setFont(font);
        cout << "\e[36m Se encuentra fuente \e[0m" << endl;
    }

    skin->setFont(guienv->getBuiltInFont(), EGDF_TOOLTIP);
}

void MotorGrafico::borrarScena()
{
    smgr->clear();
}

void MotorGrafico::borrarGui()
{
    guienv->clear();
}

bool MotorGrafico::estaPulsado(int boton)
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

        case KEY_ESPACIO:
            return input.IsKeyDown(irr::KEY_SPACE);

        case KEY_ACEPTAR:
            return input.IsKeyDown(irr::KEY_ACCEPT);

        case KEY_G_DEBUG:
            return input.IsKeyDown(irr::KEY_KEY_G);//para modo debug

        case KEY_P:
            return input.IsKeyDown(irr::KEY_KEY_P);

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

bool MotorGrafico::ocurreEvento(int event)
{
    return input.IsEventOn(event);
}

void MotorGrafico::resetEvento(int event)
{
    input.ResetEvento(event);
}

void MotorGrafico::resetKey(int event)
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

void MotorGrafico::botonesMuerteJugador(){
    guienv->addButton(rect<s32>(300,200,500,230), 0, GUI_ID_REINICIAR_BUTTON,L"Reiniciar Juego", L"Empieza a jugar");
    guienv->addButton(rect<s32>(300,240,500,270), 0, GUI_ID_MENU_BUTTON,L"Menu", L"Menu del juego");
}

void MotorGrafico::resetEventoMoveRaton()
{
    input.ResetEventoRaton(irr::EMIE_MOUSE_MOVED);
}

position2di MotorGrafico::GetPosicionRaton()
{
    return input.GetMouseState().Position;
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

int MotorGrafico::CargarPlataformas(int x,int y,int z, int ancho, int largo, int alto, const char *ruta_objeto,const char *ruta_textura)
{
    IAnimatedMesh* objeto = smgr->getMesh(ruta_objeto); //creamos el objeto en memoria
	if (!objeto)
	{
		//error
        return -1;//no se ha podido crear esta sala
	}
    else
    {
        IAnimatedMeshSceneNode* objeto_en_scena = smgr->addAnimatedMeshSceneNode(objeto); //metemos el objeto en el escenario para eso lo pasamos al escenario
        objeto_en_scena->setPosition(core::vector3df(x,y,z));
        objeto_en_scena->setMaterialTexture(0, driver->getTexture(ruta_textura));
        Plataformas_Scena.push_back(objeto_en_scena);
        return (Plataformas_Scena.size()-1);
    }
}

void MotorGrafico::CargarLuces(int x,int y,int z)
{
    // add light 1 (more green)
    scene::ILightSceneNode* light1 =
    smgr->addLightSceneNode(0, core::vector3df(x,y,z),video::SColorf(0.5f, 1.0f, 0.5f, 0.0f), 100.0f);

    light1->setDebugDataVisible ( scene::EDS_BBOX );


    // add fly circle animator to light 1
    scene::ISceneNodeAnimator* anim = smgr->createFlyCircleAnimator (core::vector3df(x,y,z),0.0f, -0.003f);
    light1->addAnimator(anim);
    anim->drop();

    Luces_Scena.push_back(light1);
    // attach billboard to the light
    scene::IBillboardSceneNode* bill =
        smgr->addBillboardSceneNode(light1, core::dimension2d<f32>(10, 10));

    bill->setMaterialFlag(video::EMF_LIGHTING, false);
    bill->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
    bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    bill->setMaterialTexture(0, driver->getTexture("assets/models/particlegreen.jpg"));
}

void MotorGrafico::CargarEnemigos(int accion, int x,int y,int z, int ancho, int largo, int alto, const char *ruta_objeto, const char *ruta_textura)
{
    IAnimatedMesh* enemigo = smgr->getMesh(ruta_objeto); //creamos el objeto en memoria

	if (!enemigo)
	{
		//error
	}
    else
    {
        IAnimatedMeshSceneNode* enemigo_en_scena = smgr->addAnimatedMeshSceneNode(enemigo); //metemos el objeto en el escenario para eso lo pasamos al escenario
        enemigo_en_scena->setPosition(core::vector3df(x,y,z));
        Enemigos_Scena.push_back(enemigo_en_scena);

    }
}

void MotorGrafico::CargarJugador(int x,int y,int z, int ancho, int largo, int alto, const char *ruta_objeto, const char *ruta_textura)
{
    IAnimatedMesh* jugador = smgr->getMesh(ruta_objeto); //creamos el objeto en memoria
	if (!jugador)
	{
		//error
	}
    else
    {
        IAnimatedMeshSceneNode* jugador_en_scena = smgr->addAnimatedMeshSceneNode(jugador); //metemos el objeto en el escenario para eso lo pasamos al escenario
        cout << x << " " << y << " " << z << " " << endl;
        jugador_en_scena->setPosition(core::vector3df(x,y,z));
        Jugador_Scena = jugador_en_scena;
        Jugador_Scena->setScale(core::vector3df(3,3,3));
        Jugador_Scena->setFrameLoop(30, 44);
		Jugador_Scena->setAnimationSpeed(10);
        //const SColor COLOR  = SColor(255,0,0,255);
        //smgr->getMeshManipulator()->setVertexColors(Jugador_Scena->getMesh(),COLOR);
    }
}


void MotorGrafico::CargarArmaJugador(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura)
{
    IAnimatedMesh* arma = smgr->getMesh(ruta_objeto); //creamos el objeto en memoria
    if (!arma)
    {
        //error
    }
    else
    {
        IAnimatedMeshSceneNode* arma_en_scena = smgr->addAnimatedMeshSceneNode(arma); //metemos el objeto en el escenario para eso lo pasamos al escenario
        arma_en_scena->setPosition(core::vector3df(x,y,z));
        Arma_Jugador = arma_en_scena;
    }
}

void MotorGrafico::CargarRecolectable(int id, int x,int y,int z, const char *ruta_objeto, const char *ruta_textura)
{
    IAnimatedMesh* recol = smgr->getMesh(ruta_objeto); //creamos el objeto en memoria
    if (!recol)
    {
        //error
    }
    else
    {
        IAnimatedMeshSceneNode* recol_en_scena = smgr->addAnimatedMeshSceneNode(recol); //metemos el objeto en el escenario para eso lo pasamos al escenario
        recol_en_scena->setPosition(core::vector3df(x,y,z));
        Recolectables_Scena.push_back(recol_en_scena);
    }
}

void MotorGrafico::llevarObjeto(float x, float y, float z, float rx, float ry, float rz)
{
    if(Arma_Jugador)
    {
     Arma_Jugador->setPosition(core::vector3df(x,y,z));
     Arma_Jugador->setRotation(core::vector3df(rx,ry,rz));

    }
}

void MotorGrafico::CargarArmaEspecial(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura)
{
    armaEsp = smgr->getMesh(ruta_objeto); //creamos el objeto en memoria

}

void MotorGrafico::mostrarJugador(float x, float y, float z, float rx, float ry, float rz)
{

    // Variables de la camara
    core::vector3df nodeCamPosition = camera->getPosition();
    core::vector3df nodeCamTarget = camera->getTarget();

    // Centrar la camara
    nodeCamPosition.X = x;
    nodeCamPosition.Y = y+30;
    nodeCamPosition.Z = z-40;
    nodeCamTarget.X = x;
    nodeCamTarget.Y = y;
    nodeCamTarget.Z = z;

    camera->setPosition(nodeCamPosition);
    camera->setTarget(nodeCamTarget);


    Jugador_Scena->setPosition(core::vector3df(x,y,z));
    Jugador_Scena->setRotation(core::vector3df(rx,ry-180,rz));

}

void MotorGrafico::mostrarEnemigos(float x, float y, float z, float rx, float ry, float rz, unsigned int i)
{
    Enemigos_Scena.at(i)->setPosition(core::vector3df(x,y,z));
    Enemigos_Scena.at(i)->setRotation(core::vector3df(rx,ry,rz));

}

void MotorGrafico::CargarObjetos(int accion, int x,int y,int z, int ancho, int largo, int alto, const char *ruta_objeto, const char *ruta_textura)
{
    IAnimatedMesh* objeto = smgr->getMesh(ruta_objeto); //creamos el objeto en memoria
	if (!objeto)
	{
		//error
	}
    else
    {
        IAnimatedMeshSceneNode* objeto_en_scena = smgr->addAnimatedMeshSceneNode(objeto); //metemos el objeto en el escenario para eso lo pasamos al escenario
        objeto_en_scena->setPosition(core::vector3df(x,y,z));

        //de momento en el escenario solo se diferencia entre recolectables (2) y el resto de objetos al cargarlos
        accion == 2 ?
            Recolectables_Scena.push_back(objeto_en_scena) :
            Objetos_Scena.push_back(objeto_en_scena);
    }
}

void MotorGrafico::mostrarArmaEspecial(float x, float y, float z, float rx, float ry, float rz)
{
    if (!armaEsp)
	{
		//error
	}
    else
    {
        if(ArmaEspecial_Jugador)
        {
            this->borrarArmaEspecial();
        }
        ArmaEspecial_Jugador = smgr->addAnimatedMeshSceneNode(armaEsp); //metemos el objeto en el escenario para eso lo pasamos al escenario
        ArmaEspecial_Jugador->setPosition(core::vector3df(x + 6.5*(sin(DEGTORAD*ry)),y,z + 6.5*(cos(DEGTORAD*ry))));
        ArmaEspecial_Jugador->setRotation(core::vector3df(rx,ry -180,rz));
        ArmaEspecial_Jugador->setScale(core::vector3df(0.25,0.25,0.25));
        smgr->getMeshManipulator()->setVertexColors(ArmaEspecial_Jugador->getMesh(),SColor(255, 125, 150, 160));
    }
}

void MotorGrafico::borrarArmaEspecial()
{
    ArmaEspecial_Jugador->remove();
    ArmaEspecial_Jugador = nullptr;
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
        IAnimatedMesh* circulo = smgr->getMesh("assets/models/circuloDebugSonido.obj");
        if(!circulo)
        {
            //no se ha podido cargar
        }
        else
        {
            //vamos a cargar el circulo en su posicion con su intensidad
            //cout << "\e[36m Generamos Circulo \e[0m" << endl;
            IAnimatedMeshSceneNode* objeto_en_scena = smgr->addAnimatedMeshSceneNode(circulo); //metemos el objeto en el escenario para eso lo pasamos al escenario
            SColor COLOR  = SColor(127, 255, 0, 0);
            smgr->getMeshManipulator()->setVertexColors(objeto_en_scena->getMesh(),COLOR);
            objeto_en_scena->setPosition(core::vector3df(x,y,z));
            objeto_en_scena->setScale(core::vector3df(intensidad,1,intensidad));
            Objetos_Debug.push_back(objeto_en_scena);
        }
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
      tmpobjt = smgr->getMesh("assets/models/sphere.obj");
    }else if(tipo == 2)
    {
      tmpobjt = smgr->getMesh("assets/models/cube.obj");
    }else if(tipo == 3)
    {
      tmpobjt = smgr->getMesh("assets/models/capsule.obj");
    }
    IAnimatedMeshSceneNode* tmpobjt_en_scena = smgr->addAnimatedMeshSceneNode(tmpobjt);
    tmpobjt_en_scena->setPosition(core::vector3df(x,y,z));
    tmpobjt_en_scena->setRotation(core::vector3df(rx,ry,rz));
    tmpobjt_en_scena->setScale(core::vector3df(ancho,alto,profund));
    SColor COLOR  = SColor(255,255,0,255);
    smgr->getMeshManipulator()->setVertexColors(tmpobjt_en_scena->getMesh(),COLOR);
    Objetos_Debug2.push_back(tmpobjt_en_scena);
  }
}

bool MotorGrafico::colisionRayo(int x,int y, int z, int rx, int ry, int rz ,int dimension)
{
    return true;
}

//esta funcion es para ver la caja del bounding box creada en motor fisicas
//abra que pasarle el numero de caja
void MotorGrafico::debugBox(int x,int y, int z,int ancho, int alto, int largo)
{
    scene::ISceneNode *n = smgr->addCubeSceneNode();
    cout << x << y << z << ancho << largo << alto << endl;
    if(n)
    {
        n->setMaterialFlag(video::EMF_LIGHTING, false);
        //n->setPosition(core::vector3df(x,y,z));
        //n->setScale(core::vector3df(ancho/5,alto/5,largo/5));
        n->setPosition(core::vector3df(0,0,20));
        n->setScale(core::vector3df(4,1,0.2));
    }
}

void MotorGrafico::dibujarRayo(int x,int y, int z, int rx, int ry, int rz ,int dimension)
{
    if(debugGrafico)
    {
        IAnimatedMesh* linea = smgr->getMesh("assets/models/linea.obj");
        if(!linea)
        {
            //no se ha podido cargar
        }
        else
        {
            //vamos a cargar el circulo en su posicion con su intensidad
            //cout << "\e[36m Generamos Circulo \e[0m" << endl;
            IAnimatedMeshSceneNode* objeto_en_scena = smgr->addAnimatedMeshSceneNode(linea); //metemos el objeto en el escenario para eso lo pasamos al escenario
            objeto_en_scena->setPosition(core::vector3df(x,y,z));
            objeto_en_scena->setRotation(core::vector3df(rx,ry,rz));
            objeto_en_scena->setScale(core::vector3df(dimension,0.2,0.5));
            Objetos_Debug.push_back(objeto_en_scena);
        }
    }
}

void MotorGrafico::colorearJugador(int a, int r, int g, int b)
{
  SColor COLOR  = SColor(a, r, g, b);
  smgr->getMeshManipulator()->setVertexColors(Jugador_Scena->getMesh(),COLOR);
}

void MotorGrafico::colorearEnemigo(int a, int r, int g, int b, int enem)
{
  SColor COLOR  = SColor(a, r, g, b);
  long unsigned int valor = enem;
  if(Enemigos_Scena.size() > 0 && valor < Enemigos_Scena.size())//para no salirnos si no existe en motorgrafico
  smgr->getMeshManipulator()->setVertexColors(Enemigos_Scena[enem]->getMesh(),COLOR);
}

void MotorGrafico::colorearObjeto(int a, int r, int g, int b, int obj)
{
  SColor COLOR  = SColor(a, r, g, b);
  long unsigned int valor = obj;
  if(Objetos_Scena.size() > 0 && valor < Objetos_Scena.size())//para no salirnos si no existe en motorgrafico
  smgr->getMeshManipulator()->setVertexColors(Objetos_Scena[obj]->getMesh(),COLOR);
}

IAnimatedMeshSceneNode* MotorGrafico::getArmaEspecial()
{
    return ArmaEspecial_Jugador;
}


// Funciones para puzzles
void MotorGrafico::PosicionCamaraEnPuzzles()
{
    camera->setPosition(vector3df(14, 2, 0)); // No cambiar la Y, si nos la seleccion tendra errores
}

void MotorGrafico::updateMotorPuzzles(short tipo)
{
    driver->beginScene(true, true, SColor(255,255,255,255));//fondo blanco
    smgr->drawAll();
    guienv->drawAll();

    /* Probando a dibujar objetos 2D
    //Rectangulo
    driver->draw2DRectangle(SColor(255, 255, 128, 64), rect<s32>(40, 40, 200, 200));

    //Poligono
    driver->draw2DPolygon(position2d<s32>(100, 300), 50.f, SColor(128, 40, 80, 16), 6);*/

    switch(tipo)
    {
        case P_OPCIONES:
            break;
        case P_HANOI:
            // Lineas para dividir la pantalla
            driver->draw2DLine(position2d<s32>(x_linea1 , 200),
                position2d<s32>(x_linea1, 400 ) , SColor(255, 0, 0, 0));
            driver->draw2DLine(position2d<s32>(x_linea2 , 200),
                position2d<s32>(x_linea2, 400 ) , SColor(255, 0, 0, 0));
            break;
    }

    driver->endScene();
}

void MotorGrafico::PuzzlesGui(short tipo, std::string enun, short opciones)
{
    short height_aux = (HEIGHT/2)+100;
    short yIMG = height_aux-125;
    short xIMG = 20;
    short anchoBtn = 40;
    short altoBtn = 30;

    // Atras
    guienv->addButton(rect<s32>(700,HEIGHT-60,750,HEIGHT-30), 0,
        GUI_ID_BACK_MENU_BUTTON,L"Atrás", L"Vuelve al menú");

    // Enunciado
    std::wstring widestr = std::wstring(enun.begin(), enun.end());
    const wchar_t* widecstr = widestr.c_str();
    guienv->addStaticText(widecstr, rect<s32>(60,20,700,50), false);

    switch(tipo)
    {
        case P_OPCIONES: // Opciones
            guienv->addStaticText(L"Puzzle Opciones", rect<s32>(0,0,200,20), false);
            guienv->addStaticText(L"Ejemplo", rect<s32>(WIDTH-200,20,
                WIDTH-160,40), false);

            img = guienv->addImage(driver->getTexture("assets/puzzles/particle.bmp"),
                core::position2d<s32>(WIDTH-200, 40));

            switch(opciones) {
                case 2:
                    WIDTH_AUX = WIDTH/4;
                    // x, y, x2, y2
                    guienv->addButton(rect<s32>(WIDTH_AUX,height_aux,
                        WIDTH_AUX+anchoBtn,height_aux+altoBtn),
                        0, GUI_ID_OP1,L"A", L"A");
                    guienv->addButton(rect<s32>(WIDTH_AUX*3,height_aux,
                        WIDTH_AUX*3+anchoBtn,height_aux+altoBtn),
                        0, GUI_ID_OP2,L"B", L"B");

                    CargarIMG(WIDTH_AUX-xIMG, yIMG);
                    CargarIMG(WIDTH_AUX*3-xIMG, yIMG);
                    break;

                case 3:
                    WIDTH_AUX = (WIDTH-2)/6;
                    // x, y, x2, y2
                    guienv->addButton(rect<s32>(WIDTH_AUX,height_aux,
                        WIDTH_AUX+anchoBtn,height_aux+altoBtn),
                        0, GUI_ID_OP1,L"A", L"A");
                    guienv->addButton(rect<s32>(WIDTH_AUX*3,height_aux,
                        WIDTH_AUX*3+anchoBtn,height_aux+altoBtn),
                        0, GUI_ID_OP2,L"B", L"B");
                    guienv->addButton(rect<s32>(WIDTH_AUX*5,height_aux,
                        WIDTH_AUX*5+anchoBtn,height_aux+altoBtn),
                        0, GUI_ID_OP3,L"C", L"C");

                    CargarIMG(WIDTH_AUX-xIMG, yIMG);
                    CargarIMG(WIDTH_AUX*3-xIMG, yIMG);
                    CargarIMG(WIDTH_AUX*5-xIMG, yIMG);
                    break;

                case 4:
                    WIDTH_AUX = WIDTH/8;
                    // x, y, x2, y2
                    guienv->addButton(rect<s32>(WIDTH_AUX,height_aux,
                        WIDTH_AUX+anchoBtn,height_aux+altoBtn),
                        0, GUI_ID_OP1,L"A", L"A");
                    guienv->addButton(rect<s32>(WIDTH_AUX*3,height_aux,
                        WIDTH_AUX*3+anchoBtn,height_aux+altoBtn),
                        0, GUI_ID_OP2,L"B", L"B");
                    guienv->addButton(rect<s32>(WIDTH_AUX*5,height_aux,
                        WIDTH_AUX*5+anchoBtn,height_aux+altoBtn),
                        0, GUI_ID_OP3,L"C", L"C");
                    guienv->addButton(rect<s32>(WIDTH_AUX*7,height_aux,
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
            guienv->addStaticText(L"Torres de Hanoi", rect<s32>(0,0,200,20), false);

            // Reiniciar
            guienv->addButton(rect<s32>(700,HEIGHT-90,750,HEIGHT-60), 0,
                GUI_ID_REINICIAR_HANOI,L"Reiniciar", L"Reinicia el juego");

            myTextBox = guienv->addStaticText(L"Pasos: ", rect<s32>(60,(WIDTH/2)-10,100,(WIDTH/2)+30), false);

            WIDTH_AUX = (WIDTH-2)/6;
            guienv->addStaticText(L"IZQ", rect<s32>(WIDTH_AUX,100,WIDTH_AUX+anchoBtn,130), false);
            guienv->addStaticText(L"CENTRO", rect<s32>(WIDTH_AUX*3,100,WIDTH_AUX*3+anchoBtn,130), false);
            guienv->addStaticText(L"DER", rect<s32>(WIDTH_AUX*5,100,WIDTH_AUX*5+anchoBtn,130), false);

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
    myTextBox->setText(str.c_str());
}

void MotorGrafico::CrearMeshFicha(float tamanyo, int r, int g, int b)
{
    //fichaMesh = geometryCreator->createCubeMesh(vector3df(tamanyo));
    fichaMesh = geometryCreator->createCylinderMesh(
        tamanyo,    //radius
        1,          //length
        50,         //tesselation
        SColor(0, r, g, b));

    // insensible a la iluminacion
    fichaMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}

void MotorGrafico::CrearFichas(short posY, float tamanyo,
    int r, int g, int b)
{
    CrearMeshFicha(tamanyo, r, g, b);
    ficha = smgr->addMeshSceneNode(fichaMesh);
    ficha->setPosition(vector3df(0, posY, IZQ));
    ficha->setID(tamanyo);

    // La anyadimos a la lista
    fichasMesh.push_back(ficha);
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
    nodoSeleccionado = collmgr->getSceneNodeFromScreenCoordinatesBB(
        device->getCursorControl()->getPosition(),0,true);

    // Si hay un nodo seleccionado
    if(nodoSeleccionado)
    {
        // Remember where the node and cursor were when it was clicked on
        initialCursorPosition = device->getCursorControl()->getPosition();
        // Calcula la posición de la pantalla 2d desde una posición 3d.
        initialObjectPosition = collmgr->getScreenCoordinatesFrom3DPosition(
            nodoSeleccionado->getAbsolutePosition(), camera);

        if (nodoSeleccionado->getID() != -1) { // Comprobamos que no sea el fondo
            return true;
        }
    }
    return false;
}

void MotorGrafico::DeseleccionarNodo()
{
    nodoSeleccionado = 0;
}

short MotorGrafico::GetFichaY()
{
    return nodoSeleccionado->getAbsolutePosition().Y;
}

void MotorGrafico::MoverFichas(short pila)
{
    if ((nodoSeleccionado) && (pila != NO_SELECT))
    {
        plane3df const planeXZ(nodoSeleccionado->getAbsolutePosition(), vector3df(1.f, 0.f, 0.f));

        position2di currentCursorPosition(device->getCursorControl()->getPosition());
        position2di effectiveObjectPosition = initialObjectPosition + currentCursorPosition - initialCursorPosition;
        line3df ray(collmgr->getRayFromScreenCoordinates(effectiveObjectPosition, camera));
        vector3df intersectWithPlane;

        if(planeXZ.getIntersectionWithLine(ray.start, ray.getVector(), intersectWithPlane))
        {
            nodoSeleccionado->setPosition(intersectWithPlane);
        }
    }
}

void MotorGrafico::RecolocarFicha(short y, short z)
{
    short x = nodoSeleccionado->getAbsolutePosition().X;
    nodoSeleccionado->setPosition(vector3df(x, y, z));
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

void MotorGrafico::EraseColectable(int idx)
{
    Recolectables_Scena[idx]->setVisible(false);
    Recolectables_Scena[idx]->remove();
    Recolectables_Scena.erase(Recolectables_Scena.begin() + idx);
}
//Cuando enemigo muere lo borramos
void MotorGrafico::EraseEnemigo(int i)
{
    long unsigned int valor = i;

    if(valor >= 0 && valor < Enemigos_Scena.size())
    {
        Enemigos_Scena[i]->setVisible(false);
        Enemigos_Scena[i]->remove();
        Enemigos_Scena.erase(Enemigos_Scena.begin() + i);
    }
}
//Cuando enemigo muere lo borramos
void MotorGrafico::EraseJugador(int i){
    /*Jugador_Scena[i]->setVisible(false);
    Jugador_Scena[i]->remove();
    Jugador_Scena.erase(Jugador_Scena.begin() + i); */
}

//Devolver cantidad de enemigos en escena para recorrerlos en metodo muerteEnemigo
int MotorGrafico::getEnemigos_Scena(){
    return Enemigos_Scena.size();
}

void MotorGrafico::EraseArma()
{
    Arma_Jugador->setVisible(false);
    Arma_Jugador->remove();
}

// TO DO: Anyadir string img
void MotorGrafico::CargarIMG(short x, short y)
{
	img = guienv->addImage(driver->getTexture("assets/puzzles/particle.bmp"),
    	core::position2d<s32>(x, y));
}

void MotorGrafico::debugVision(float x, float y, float z, float rotacion, float longitud)
{
    if(debugGrafico)
    {
        if(!conovision)
        {

            conovision = smgr->getMesh("assets/models/conovision.obj");
        }

        if(!conovision)
        {
            //no se ha podido cargar
        }
        else
        {
            IAnimatedMeshSceneNode* objeto_en_scena = smgr->addAnimatedMeshSceneNode(conovision); //metemos el objeto en el escenario para eso lo pasamos al escenario
            objeto_en_scena->setPosition(core::vector3df(x,y+1,z));
            SColor COLOR  = SColor(0, 255, 0, 0);
            smgr->getMeshManipulator()->setVertexColors(objeto_en_scena->getMesh(),COLOR);

            core::vector3df rotation = objeto_en_scena->getRotation();
            objeto_en_scena->setRotation(core::vector3df(rotation.X,(-1*(rotacion-180)),rotation.Z));

            rotation = objeto_en_scena->getRotation();

            objeto_en_scena->setScale(core::vector3df(longitud/2,1.0f,0.01f));
            Objetos_Debug.push_back(objeto_en_scena);
        }
    }
}


void MotorGrafico::cargarInterfaz()
{
    //activamos la interfaz
    InterfazJugador * interfaz = InterfazJugador::getInstance();
    interfaz->activar();//activamos la interfaz por defecto

    vidaI = guienv->addImage(driver->getTexture("assets/images/51.png"),position2d<int>(10,10));
    energiaI = guienv->addImage(driver->getTexture("assets/images/21.png"),position2d<int>(10,58));
    dineroI = guienv->addImage(driver->getTexture("assets/images/61.png"),position2d<int>(680,10));
    armaI = guienv->addImage(driver->getTexture("assets/images/11.png"),position2d<int>(730,530));
    BarraVidaI = guienv->addImage(driver->getTexture("assets/images/4.png"),position2d<int>(50,15));
    BarraEnergiaI = guienv->addImage(driver->getTexture("assets/images/3.png"),position2d<int>(48,65));
    
    //imagenes tipo objeto que se lleva por defecto manos
    manosI = guienv->addImage(driver->getTexture("assets/images/manos.png"),position2d<int>(738,534));
    llaveI = guienv->addImage(driver->getTexture("assets/images/llave.png"),position2d<int>(738,534));
    espadaI = guienv->addImage(driver->getTexture("assets/images/espada.png"),position2d<int>(738,534));
    dagaI = guienv->addImage(driver->getTexture("assets/images/daga.png"),position2d<int>(738,534));

    BarraVidaI->setMaxSize(dimension2du(121,29));//maximo 121/100 y esto multiplicado por la cantidad de vida
    BarraEnergiaI->setMaxSize(dimension2du(63,27));//maximo 63/100 y esto multiplicado por la cantidad de energia 
    font2 = guienv->getFont("assets/fonts/myfont.xml");

    moneyI = guienv->addStaticText(L"1000 M",rect<s32>(710,21,750,40),false); //falta ver los cambios de fuente y ponerlo correctamente

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
    int frame = Jugador_Scena->getStartFrame();
    int frame_actual = Jugador_Scena->getFrameNr();
    //animaciones para heavy
    if(estado == 0 && frame != 30 && frame != 120) //esta quieto
    {
        if(Jugador_Scena)
        {
            Jugador_Scena->setFrameLoop(30, 44);
		    Jugador_Scena->setAnimationSpeed(10);
        }
    }

    if(estado == 1 && frame != 0 && frame != 120) //se mueve
    {
        if(Jugador_Scena)
        {
            Jugador_Scena->setFrameLoop(0, 30);
		    Jugador_Scena->setAnimationSpeed(20);
        }
    }

    if(estado == 2 && frame != 48  && frame != 120) //ataca
    {
        if(Jugador_Scena)
        {
            Jugador_Scena->setFrameLoop(48, 70);
		    Jugador_Scena->setAnimationSpeed(15);
        }
    }

    if(estado == 3 && frame != 72  && frame != 120) //ataque especial
    {
        if(Jugador_Scena)
        {
            Jugador_Scena->setFrameLoop(72, 98);
		    Jugador_Scena->setAnimationSpeed(10);
        }
    }

    if(estado == 4  && frame != 99  && frame != 120) //coger objeto
    {
        if(Jugador_Scena)
        {
            Jugador_Scena->setFrameLoop(99, 112);
		    Jugador_Scena->setAnimationSpeed(10);
        }
    }    

    if(estado == 5 && frame != 120) //muere
    {
        if(frame_actual == 119)
        {
            Jugador_Scena->setFrameLoop(120, 128); //lo dejamos definitivamente muerto
		    Jugador_Scena->setAnimationSpeed(10);
        }
        else
        {
            if(Jugador_Scena && frame != 112)
            {
                Jugador_Scena->setFrameLoop(112, 120);
                Jugador_Scena->setAnimationSpeed(10);
            }
        }
    }
}