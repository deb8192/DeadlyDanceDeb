/* Esta clase se encarga de fachada entre la logica del juego y sus aspectos graficos, de momento solo esta irrlicht
cuando este opengl se agregaran mas dependencias. Es una clase singleton (solo habra un objeto de MotorGrafico).*/

#include <irrlicht/irrlicht.h> //la utilizaremos para las funcionalidades del motor
#include <iostream> //la utilizamos para mostrar el log en la consola.

//para acortar lineas de programacion se cogen espacios definidos directamente
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;
//fin de acortes

#ifndef MotorGrafico_HPP
#define MotorGrafico_CPP

    class MotorGrafico
    {
        public: //clases accesibles desde fuera
            
            //clase singleton en public
            ~MotorGrafico(void);
            static MotorGrafico *getInstance() //esto se utiliza para crear el objeto una sola vez
            {
                if(unica_instancia == 0)
                unica_instancia = new MotorGrafico();
                return unica_instancia;  
            }
            //fin singleton public

            bool crearVentana(int tipo);//nos crea la ventana del juego. Tipo define lo grande que es por defecto 1024 x 768
            bool sigueFuncionando(); //sirve para saber si la ventana esta activa
            void limpiarDevice();//elimina el dispositivo
            void crearTextoDePrueba();//texto de prueba de que va el motor
            //esto es provisional cuando tengamos diferentes pintados se llamara pero para llamar a todos los pintados
            void updateMotor();
            //crea una camara para ver el escenario
            void CrearCamara();

        private: //clases solo accesibles por MotorGrafico

            //clase singleton 
            MotorGrafico();
            static MotorGrafico* unica_instancia;
            //fin clase singleton private
            void PropiedadesDevice();
            //variables privaddas
            IrrlichtDevice *device; //puntero a dispositivo por defecto
            IVideoDriver *driver;
	        ISceneManager *smgr;
	        IGUIEnvironment *guienv;
    };

#endif /* MotorGrafico_HPP */