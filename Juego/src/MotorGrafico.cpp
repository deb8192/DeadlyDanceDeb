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
    smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));
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
  scene::IAnimatedMesh* mesh = smgr->getMesh("assets/models/Puerta.3ds");
  scene::IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);

  scene::IAnimatedMesh* mesh2 = smgr->getMesh("assets/models/MarcoPuerta.3ds");
  scene::IAnimatedMeshSceneNode* node2 = smgr->addAnimatedMeshSceneNode(mesh2);
  //la forma correcta para cargar modelos empleaba xml y me ha dado problemas de violacion de segmento
  //carpeta tutorial: irrlicht-1.8.4/examples/09.Meshviewer/tutorial.html

  /*btBoxShape
  //funciones joints utiles para motor de fisica bullet, 
  //falta elegir motor en clase 
  
  btCollisionShape* pDoorShape = new btBoxShape(btVector3(2.0f, 5.0f, 0.2f));
  m_collisionShapes.push_back(pDoorShape);
  btTransform doorTrans;
  doorTrans.setIdentity();
  doorTrans.setOrigin(btVector3(-5.0f, -2.0f, 0.0f));
  btRigidBody* pDoorBody = createRigidBody(1.0, doorTrans, pDoorShape);
  pDoorBody->setActivationState(DISABLE_DEACTIVATION);
  const btVector3 btPivotA(10.f + 2.1f, -2.0f, 0.0f);  // right next to the door slightly outside
  btVector3 btAxisA(0.0f, 1.0f, 0.0f);                 // pointing upwards, aka Y-axis

  spDoorHinge = new btHingeConstraint(*pDoorBody, btPivotA, btAxisA);

  spDoorHinge->setLimit(-SIMD_PI * 0.25f, SIMD_PI * 0.25f);
  m_dynamicsWorld->addConstraint(spDoorHinge);
  spDoorHinge->setDbgDrawSize(btScalar(5.f));*/
  
}
/*
btHingeConstraint::btHingeConstraint(btRigidBody& rbA, const btTransform& rbAFrame, const btTransform& rbBFrame)
:btTypedConstraint(HINGE_CONSTRAINT_TYPE, rbA),m_rbAFrame(rbAFrame),m_rbBFrame(rbBFrame),
m_angularOnly(false),
m_enableAngularMotor(false)
{
  // flip axis
  m_rbBFrame.getBasis()[0][2] *= btScalar(-1.);
  m_rbBFrame.getBasis()[1][2] *= btScalar(-1.);
  m_rbBFrame.getBasis()[2][2] *= btScalar(-1.);
  
  //start with free
  m_lowerLimit = btScalar(1e30);
  m_upperLimit = btScalar(-1e30); 
  m_biasFactor = 0.3f;
  m_relaxationFactor = 1.0f;
  m_limitSoftness = 0.9f;
  m_solveLimit = false;
}*/


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
