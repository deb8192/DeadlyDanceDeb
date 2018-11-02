/* Esta clase se encarga de fachada entre la logica del juego y sus aspectos graficos, de momento solo esta irrlicht
cuando este opengl se agregaran mas dependencias. Es una clase singleton (solo habra un objeto de MotorGrafico).*/

#include <irrlicht/irrlicht.h> //la utilizaremos para las funcionalidades del motor
#include "eventos.hpp" //este archivo contiene los ids de los eventos
#include "Inputs.hpp"
#include <iostream> //la utilizamos para mostrar el log en la consola.

//para acortar lineas de programacion se cogen espacios definidos directamente
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;
using namespace idsEventos;
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
            void updateMotorMenu();
            //esto es provisional cuando tengamos diferentes pintados se llamara pero para llamar a todos los pintados
            void updateMotorJuego();
            //esto es provisional cuando tengamos diferentes pintados se llamara pero para llamar a todos los pintados
            void updateMotorCinematica();
            //crea una camara para ver el escenario
            void CrearCamara();
            //crea los botones del menu
            void PintarBotonesMenu();
            //define fuente por defecto
            void activarFuenteDefault();
            //borrar scena
            void borrarScena();//borra todo lo que haya en la ventana
            //borrar gui
            void borrarGui();//borra todo lo que haya en la ventana relacionado con el gui
            
            //eventos facade
            //detecta si esta pulsado un boton, 1=a, 2 =s, 3=d, 4=w, 5=space, 6=intro 
            bool estaPulsado(int);
            //fin eventos del teclado
            //detecta si un evento con un id pasado a sido llamado
            bool ocurreEvento(int);
            //fin evento botones se puede utilizar para cualquier tipo de evento de irrlicht
            
            void closeGame();
            
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
            IGUIFont *font;
            IGUISkin *skin;
            Inputs input;
    };

#endif /* MotorGrafico_HPP */