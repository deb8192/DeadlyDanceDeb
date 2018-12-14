#include "MotorGrafico.hpp" //se llama a su cabezera para cargar las dependencias
//para clases singleton deben tener un indicador de que se ha creado el unico objeto
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
    if(tipo == 1)
    {
        device = createDevice( video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16,false, false, false, &input);
        device->setWindowCaption(L"DeadlyDance LowResolution");
        device->setResizable(false);
        PropiedadesDevice();
        return true;
    }

    if(tipo == 2)
    {
       device = createDevice( video::EDT_SOFTWARE, dimension2d<u32>(800, 600), 16,false, false, false, &input);
       device->setWindowCaption(L"DeadlyDance MediumResolution");
       device->setResizable(false);
       PropiedadesDevice();
       return true; 
    }

    if(tipo == 3)
    {
       device = createDevice( video::EDT_SOFTWARE, dimension2d<u32>(1024, 768), 16,false, false, false, &input);
       device->setWindowCaption(L"DeadlyDance NormalResolution");
       device->setResizable(false);
       PropiedadesDevice();
       return true; 
    }

    if(tipo == 4)
    {
       device = createDevice( video::EDT_SOFTWARE, dimension2d<u32>(1280, 1024), 16,false, false, false, &input);
       device->setWindowCaption(L"DeadlyDance HightResolution");
       device->setResizable(false);
       PropiedadesDevice();
       return true; 
    }

    return false;
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
    driver->beginScene(true, true, SColor(255,100,255,140));
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

void MotorGrafico::PropiedadesDevice()
{
    cout << "\e[32m Aplicando propiedades a device \e[0m" << endl;
    driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
    
    cout << "\e[32m Propiedades aplicadas \e[0m" << endl;
}

void MotorGrafico::PintarBotonesMenu()
{

    guienv->addButton(rect<s32>(300,200,500,230), 0, GUI_ID_EMPEZAR_BUTTON,L"Iniciar Juego", L"Empieza a jugar");
    guienv->addButton(rect<s32>(300,240,500,270), 0, GUI_ID_CONFIGURACION_BUTTON,L"Configuracion", L"Configuracion del juego");
    guienv->addButton(rect<s32>(300,280,500,310), 0, GUI_ID_CREDITOS_BUTTON,L"Creditos", L"Creditos del juego");
    guienv->addButton(rect<s32>(300,320,500,350), 0, GUI_ID_SALIR_BUTTON,L"Salir del juego", L"Sale del juego");    
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
        case 1:     
            return input.IsKeyDown(irr::KEY_KEY_A);

        case 2:
            return input.IsKeyDown(irr::KEY_KEY_S);
        
        case 3:
            return input.IsKeyDown(irr::KEY_KEY_D);
        
        case 4:
            return input.IsKeyDown(irr::KEY_KEY_W);
        
        case 5:
            return input.IsKeyDown(irr::KEY_SPACE);

        case 6:
            return input.IsKeyDown(irr::KEY_ACCEPT);

        case 7:
            return input.IsKeyDown(irr::KEY_KEY_G);//para modo debug

        case 8:
            return input.IsKeyDown(irr::KEY_KEY_P);
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
        case 1:     
            input.ResetKey(irr::KEY_KEY_A);
        break;
        case 2:
            input.ResetKey(irr::KEY_KEY_S);
        break;
        case 3:
            input.ResetKey(irr::KEY_KEY_D);
        break;
        case 4:
            input.ResetKey(irr::KEY_KEY_W);
        break;
        case 5:
            input.ResetKey(irr::KEY_SPACE);
        break;
        case 6:
            input.ResetKey(irr::KEY_ACCEPT);
        break;
        case 7:
            input.ResetKey(irr::KEY_KEY_G);//para modo debug
        break;
        case 8:
            input.ResetKey(irr::KEY_KEY_P);
        break;
    }
}

int MotorGrafico::CargarPlataformas(int x,int y,int z, const char *ruta_objeto,const char *ruta_textura)
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

void MotorGrafico::CargarEnemigos(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura)
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

void MotorGrafico::CargarJugador(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura)
{
    IAnimatedMesh* jugador = smgr->getMesh(ruta_objeto); //creamos el objeto en memoria
	if (!jugador)
	{
		//error
	}
    else
    {
        IAnimatedMeshSceneNode* jugador_en_scena = smgr->addAnimatedMeshSceneNode(jugador); //metemos el objeto en el escenario para eso lo pasamos al escenario   
        jugador_en_scena->setPosition(core::vector3df(x,y,z));
        Jugador_Scena = jugador_en_scena;
    }
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
    Jugador_Scena->setRotation(core::vector3df(rx,ry,rz));
}

void MotorGrafico::CargarObjetos(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura)
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
        Objetos_Scena.push_back(objeto_en_scena);
    }
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
            objeto_en_scena->setPosition(core::vector3df(x,y,z));
            objeto_en_scena->setScale(core::vector3df(intensidad,intensidad,1));
            Objetos_Debug.push_back(objeto_en_scena);
        }
    }
}

bool MotorGrafico::colisionRayo(int x,int y, int z, int rx, int ry, int rz ,int dimension)
{
    return true;
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