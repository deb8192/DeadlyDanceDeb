#include "MotorGrafico.hpp" //se llama a su cabezera para cargar las dependencias
//para clases singleton deben tener un indicador de que se ha creado el unico objeto
MotorGrafico* MotorGrafico::unica_instancia = 0;
//fin indicador singleton
//#include <Box2D/Box2D.h>

MotorGrafico::MotorGrafico()
{
    input.setDevice(device);//lo  utilizamos para que los eventos puedan llamar a funciones de 
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
    driver->beginScene(true, true, SColor(255,255,101,140));
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
    smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,10,0));
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

void MotorGrafico::JointsTest()
{ 
    //que gire 
    //HACERLO CON INTERPOLADO NO CON FRAMES
        cout << "\e[36m Se encuentra fuente \e[0m" << endl;
  
    //scene::IAnimatedMesh* mesh = smgr->getMesh("assets/models/sydney.md2");
    
    n = smgr->addCubeSceneNode();
    //node = smgr->addAnimatedMeshSceneNode( mesh );
           
  if (n)
  {      
      n->setMaterialFlag(video::EMF_LIGHTING, false);
      n->setScale(core::vector3df(1,1,1));
      n->setMaterialTexture(0, driver->getTexture("assets/textures/sydney.bmp"));
      n->setPosition(core::vector3df(30,0,0));
  }
 /*      
  if (mesh)
  {      
      node->setMaterialFlag(video::EMF_LIGHTING, false);
      node->setMD2Animation(scene::EMAT_STAND);
      node->setScale(core::vector3df(1,1,1));
      node->setMaterialTexture(0, driver->getTexture("assets/textures/sydney.bmp"));
      node->setPosition(core::vector3df(30,0,0));

  }*/
    //movimiento; http://irrlicht.sourceforge.net/docu/example004.html
}
void MotorGrafico::setThen(){
    dt =1.0f/60.0f;
}
/*const f32 getdt(){
    return dt;
}*/
void MotorGrafico::movimiento()
{
    const f32 MOVEMENT_SPEED = 10.f;
    float newTime, frameTime, interpolation;
    u32 currentTime = device->getTimer()->getTime();//buscar que devuelve cada interacion
	float acumulator = 0.0f;
    
    newTime = device->getTimer()->getTime();
    frameTime = newTime - currentTime;
    if(frameTime>0.25f){
        frameTime=0.25f;
    }

    currentTime = newTime;
    acumulator+=frameTime;

    acumulator -= dt; 
		
	interpolation = acumulator/dt;
    /*
    //ROTAR PERSONAJE 
    core::vector3df rotaPersona = node->getRotation();
    core::vector3df muevePersona = node->getPosition();

    if(rotarPersona == rotarPersona.Z){
        core::vector3df rot(0,0,90);// Esto gira el personaje 90 grados en el eje Z
        node->setRotation(rot);
    }else{
        if(rotarPersona == rotarPersona.Y){

        }
    }
    //MAS INFO SOBRE ROTAR EL PERSONAJE
    ballPosition.Z += movement;
    core::quaternion test;
    test.fromAngleAxis(xAxisAngle, core::vector3df(1,0,0));
    xAxisAngle += 0.1f;
    test.normalize();
    core::vector3df rot;
    test.toEuler(rot);
    ballSceneNode->setRotation(rot * core::RADTODEG);
*/
    core::vector3df rotaPersona = n->getRotation();
    core::vector3df nodePosition = n->getPosition();
/*
    // Variables de la camara
    core::vector3df nodeCamPosition = camera->getPosition();
    core::vector3df nodeCamTarget = camera->getTarget();
  
 
    // Centrar la camara
    nodeCamPosition.X = nodePosition.X;
    nodeCamTarget.X = nodePosition.X;
    nodeCamTarget.Y = nodePosition.Y;
*/
    // Comprobar teclas para mover el personaje y la camara
    if(input.IsKeyDown(irr::KEY_KEY_W))
    {

      nodePosition.Y += MOVEMENT_SPEED;
      //nodeCamPosition.Y += MOVEMENT_SPEED;
      //nodeCamTarget.Y += MOVEMENT_SPEED;
    }
    else if(input.IsKeyDown(irr::KEY_KEY_S))
    {

      nodePosition.Y -= MOVEMENT_SPEED;

      //nodeCamPosition.Y -= MOVEMENT_SPEED;
      //nodeCamTarget.Y -= MOVEMENT_SPEED;
    }

    if(input.IsKeyDown(irr::KEY_KEY_A))
    {

        nodePosition.X -= MOVEMENT_SPEED;
        core::vector3df rot(90,0,0);// Esto gira el personaje 90 grados en el eje Z
        n->setRotation(rot);

      //nodeCamPosition.X -= MOVEMENT_SPEED;
      //nodeCamTarget.X -= MOVEMENT_SPEED;
    }
    else if(input.IsKeyDown(irr::KEY_KEY_D))
    {

      nodePosition.X += MOVEMENT_SPEED;
      //nodeCamPosition.X += MOVEMENT_SPEED;
      //nodeCamTarget.X += MOVEMENT_SPEED;
    }
    n->setPosition(nodePosition);
    n->setRotation(rotaPersona);
    /*
    camera->setPosition(nodeCamPosition);
    camera->setTarget(nodeCamTarget);*/
    
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
    }
    return false;
}

bool MotorGrafico::ocurreEvento(int event)
{
    return input.IsEventOn(event);
}
