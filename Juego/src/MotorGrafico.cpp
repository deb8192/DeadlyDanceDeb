#include "MotorGrafico.hpp" //se llama a su cabezera para cargar las dependencias

//para clases singleton deben tener un indicador de que se ha creado el unico objeto
MotorGrafico* MotorGrafico::unica_instancia = 0;
//fin indicador singleton

/*Tipo 1(640x480), Tipo 2(800x600), Tipo 3(1024x768), Tipo 4(1280x1024)
Esta clase define que tipo de pantalla quieres
*/
MotorGrafico::MotorGrafico()
{

}

MotorGrafico::~MotorGrafico()
{
    
}

bool MotorGrafico::crearVentana(int tipo)
{
    if(tipo == 1)
    {
        device = createDevice( video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16,false, false, false, 0);
        device->setWindowCaption(L"DeadlyDance LowResolution");
        PropiedadesDevice();
        return true;
    }

    if(tipo == 2)
    {
       device = createDevice( video::EDT_SOFTWARE, dimension2d<u32>(800, 600), 16,false, false, false, 0);
       device->setWindowCaption(L"DeadlyDance MediumResolution");
       PropiedadesDevice();
       return true; 
    }

    if(tipo == 3)
    {
       device = createDevice( video::EDT_SOFTWARE, dimension2d<u32>(1024, 768), 16,false, false, false, 0);
       device->setWindowCaption(L"DeadlyDance NormalResolution");
       PropiedadesDevice();
       return true; 
    }

    if(tipo == 4)
    {
       device = createDevice( video::EDT_SOFTWARE, dimension2d<u32>(1280, 1024), 16,false, false, false, 0);
       device->setWindowCaption(L"DeadlyDance HightResolution");
       PropiedadesDevice();
       return true; 
    }

    return false;
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
    guienv->addStaticText(L"Si ves este texto es que estas viendo el comienzo de un gran juego",rect<s32>(150,10,500,100), true);
}

void MotorGrafico::updateMotor()
{
    driver->beginScene(true, true, SColor(255,100,101,140));
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