/* Esta clase se encarga de fachada entre la logica del juego y sus aspectos graficos, de momento solo esta irrlicht
cuando este opengl se agregaran mas dependencias. Es una clase singleton (solo habra un objeto de MotorGrafico).*/

#include <irrlicht/irrlicht.h> //la utilizaremos para las funcionalidades del motor
#include "eventos.hpp" //este archivo contiene los ids de los eventos
#include "Inputs.hpp"
#include <iostream> //la utilizamos para mostrar el log en la consola.
#include <vector>//para los objetos en escena

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
            


            /*IMPORTANTE para bullet motor de fisicas y Joints*/
            //btHingeConstraint(btRigidBody& rbA,const btTransform& rbAFrame, const btTransform& rbBFrame);
            

            //eventos facade
            //detecta si esta pulsado un boton, 1=a, 2 =s, 3=d, 4=w, 5=space, 6=intro 
            bool estaPulsado(int);
            //fin eventos del teclado
            //detecta si un evento con un id pasado a sido llamado
            bool ocurreEvento(int);
            //fin evento botones se puede utilizar para cualquier tipo de evento de irrlicht
            void resetEvento(int);//resetea el evento
            
            //cargadores de objetos
            int CargarPlataformas(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura);//carga el objeto en scena lo mete en el array
            void CargarLuces(int x,int y,int z);
            void CargarEnemigos(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura);
            void CargarJugador(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura);
            void CargarObjetos(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura);
            
            void closeGame();
            
            //colision rayo
            bool colisionRayo(int x,int y, int z, int rx, int ry, int rz ,int dimension);

            //debug grafico
            void activarDebugGrafico();//se activa o desactiva el modo debug grafico
            void dibujarCirculoEventoSonido(int x, int y, int z, float intensidad);//se dibuja el circulo con la intensidad que se solicita en las coordenadas proporcionadas
            void clearDebug();//borra toda la informacion de debug en cada update para ver los cambios
            void dibujarRayo(int x,int y, int z, int rx, int ry, int rz ,int dimension);//dibuja los rayos o lineas con las indicaciones que pongas, (x,y,z) son donde empieza la linea el primer punto, (rx,ry,rz) rotacion de la linea desde su punto, dimension longitud de la linea 
            void mostrarJugador(float x, float y, float z, float rx, float ry, float rz);
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
            scene::ICameraSceneNode* camera;
            IGUIFont *font;
            IGUISkin *skin;
            Inputs input;
            std::vector<IAnimatedMeshSceneNode*> Plataformas_Scena;//plataformas en scena
            std::vector<ILightSceneNode*> Luces_Scena;//luces en scena
            std::vector<IAnimatedMeshSceneNode*> Enemigos_Scena;//Enemigos en scena
            IAnimatedMeshSceneNode *Jugador_Scena;//Jugador en scena
            std::vector<IAnimatedMeshSceneNode*> Objetos_Scena;//Objetos en scena
            std::vector<IAnimatedMeshSceneNode*> Objetos_Debug;//Objetos en modo debug
            bool debugGrafico;//nos sirve para saber si tenemos activado el debug grafico
    };

#endif /* MotorGrafico_HPP */