/* Esta clase se encarga de fachada entre la logica del juego y sus aspectos graficos, de momento solo esta irrlicht
cuando este opengl se agregaran mas dependencias. Es una clase singleton (solo habra un objeto de MotorGrafico).*/
#ifndef MotorGrafico_HPP
#define MotorGrafico_HPP

#include <irrlicht/irrlicht.h> //la utilizaremos para las funcionalidades del motor
//#include "../Eventos.hpp" //este archivo contiene los ids de los eventos
#include "../Inputs.hpp" //
#include <iostream> //la utilizamos para mostrar el log en la consola.
#include <math.h>
#include <vector>//para los objetos en escena
#include "../Jugando/InterfazJugador.hpp"//para la interfaz

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

    class MotorGrafico
    {
        public: //clases accesibles desde fuera

            //clase singleton en public
            ~MotorGrafico();
            static MotorGrafico* GetInstance() //esto se utiliza para crear el objeto una sola vez
            {
                if(_unica_instancia == 0)
                _unica_instancia = new MotorGrafico();
                return _unica_instancia;
            }
            //fin singleton public

            void LimpiarMotorGrafico();//revisar

            bool CrearVentana(short tipo);//nos crea la ventana del juego. Tipo define lo grande que es por defecto 1024 x 768
            bool VentanaAbierta(); //sirve para saber si la ventana esta activa
            void CerrarJuego();
            void LimpiarDevice();//elimina el dispositivo
            void ActivarFuenteDefault(); //define fuente por defecto
            
            void FondoEscena(short a, short r, short g, short b);
            void RenderEscena();
            void BorrarScena(); // borra todo lo que haya en la ventana
            void BorrarGui(); // borra todo lo que haya en la ventana relacionado con el gui

            void CrearTexto(std::string texto, short x1, short y1, short x2, short y2);
            void CrearBoton(short x, short y, short x2, short y2, s32 id, 
                const wchar_t* texto, const wchar_t* texto2);

            // detecta si un evento de boton con un id pasado ha sido llamado
            bool OcurreEvento(short);
            void ResetEvento(short); // resetea el evento
            
            // Eventos de teclas
            bool EstaPulsado(short); 
            void ResetKey(short); // resetea la tecla

            // Eventos del raton
            bool PulsadoClicDer();
            bool PulsadoClicIzq();
            bool SueltoClicDer();
            bool SueltoClicIzq();
            void ResetEventoMoveRaton();
            position2di GetPosicionRaton();

            void CrearCamara(); // crea una camara para ver el escenario

            bool GetDebugActivado(); // para saber si esta activado

            //----------------- Revisar
            
            /*IMPORTANTE para bullet motor de fisicas y Joints*/
            //btHingeConstraint(btRigidBody& rbA,const btTransform& rbAFrame, const btTransform& rbBFrame);

            //cargadores de objetos
            int CargarPlataformas(int x,int y,int z, int ancho, int largo, int alto, const char* ruta_objeto, const char* ruta_textura);//carga el objeto en scena lo mete en el array
            void CargarLuces(int x,int y,int z);

            void CargarEnemigos(int accion, int x,int y,int z, int ancho, int largo, int alto, const char* ruta_objeto, const char* ruta_textura);
            void CargarJugador(int x,int y,int z, int ancho, int largo, int alto, const char* ruta_objeto, const char* ruta_textura);
            int CargarObjetos(int accion, int x,int y,int z, int ancho, int largo, int alto, const char* ruta_objeto, const char* ruta_textura);
            void CargarArmaEspecial(int x,int y,int z, const char* ruta_objeto, const char* ruta_textura);

            //colision rayo
            bool colisionRayo(int x,int y, int z, int rx, int ry, int rz ,int dimension);

            //debug grafico
            void activarDebugGrafico();//se activa o desactiva el modo debug grafico
            void activarPathfinding(); //Temporal, se activa o desactiva el pathfinding
            void dibujarCirculoEventoSonido(int x, int y, int z, float intensidad);//se dibuja el circulo con la intensidad que se solicita en las coordenadas proporcionadas
            void dibujarObjetoTemporal(int x, int y, int z, int rx, int ry, int rz ,int ancho, int alto, int profund, int tipo);
            void dibujarZona(int x, int y, int z, float ancho, float alto, float profund);
            void clearDebug();//borra toda la informacion de debug en cada update para ver los cambios
            void clearDebug2();
            void dibujarRayo(int x,int y, int z, int rx, int ry, int rz ,int dimension);//dibuja los rayos o lineas con las indicaciones que pongas, (x,y,z) son donde empieza la linea el primer punto, (rx,ry,rz) rotacion de la linea desde su punto, dimension longitud de la linea
            void mostrarJugador(float x, float y, float z, float rx, float ry, float rz);
            void mostrarEnemigos(float x, float y, float z, float rx, float ry, float rz, unsigned int i);
            void mostrarObjetos(float x, float y, float z, float rx, float ry, float rz, unsigned int i);
            void mostrarArmaEspecial(float x, float y, float z, float rx, float ry, float rz);
            void borrarArmaEspecial();
            void colorearJugador(int a, int r, int g, int b);
            void colorearEnemigo(int a, int r, int g, int b, int enem);

            void colorearObjeto(int a, int r, int g, int b, int obj);
            void debugBox(int x,int y, int z,int ancho, int alto, int largo);
            void debugVision(float x, float y, float z, float rotacion, float longitud);
            void llevarObjeto(float x, float y, float z, float rx, float ry, float rz);
            void CargarArmaJugador(int x,int y,int z, const char* ruta_objeto, const char* ruta_textura);
            void CargarRecolectable(int id, int x,int y,int z, const char* ruta_objeto, const char* ruta_textura);

            IAnimatedMeshSceneNode* getArmaEspecial();

            // Funciones para puzzles
            void PosicionCamaraEnPuzzles();
            void updateMotorPuzzles(short tipo);
            void PuzzlesGui(short tipo, std::string enun, short opciones);
            void TextoPasos(short pasos);
            void CrearFichas(short posY, float tamanyo,
                  int r, int g, int b);
            short GetZonaVentana();
            bool SeleccionarNodo();
            void DeseleccionarNodo();
            short GetFichaY();
            void MoverFichas(short pila);
            void RecolocarFicha(short y, short z);
            void ReiniciarHanoi();

            int getEnemigos_Scena();
            void EraseColectable(long unsigned int idx);
            int getObjetos_Scena();
            void EraseEnemigo(std::size_t i);
            void EraseJugador();
            void EraseArma();
            void ErasePowerUP(long unsigned int idx);

            //interfaz
            void cargarInterfaz();
            void destruirInterfaz();
            void updateInterfaz();

            //animaciones
            void cambiarAnimacionJugador(int);//nos sirve para cambiar de animacion al jugador

            //getters & setters
            bool getPathfindingActivado();


            void updateMotorCinematica();
            bool finalCinematica();

        private: //clases solo accesibles por MotorGrafico

            //clase singleton
            MotorGrafico();
            static MotorGrafico* _unica_instancia;
            //fin clase singleton private

            void propiedadesDevice();

            //variables privadas
            Inputs input;
            IrrlichtDevice* _device; //puntero a dispositivo por defecto
            IVideoDriver* _driver;
            ISceneManager* _smgr;
            IGUIEnvironment* _guienv;
            const IGeometryCreator* _geometryCreator;
            ISceneCollisionManager* _collmgr;
            ICameraSceneNode* _camera;

            // Ventana
            short width, height;
            IGUIFont* _font;
            IGUISkin* _skin;

            /** Revisar **/
            IGUIFont* font2;
            IAnimatedMeshSceneNode* ninja;
            std::vector<IAnimatedMeshSceneNode*> Plataformas_Scena;//plataformas en scena
            std::vector<ILightSceneNode*> Luces_Scena;//luces en scena
            std::vector<IAnimatedMeshSceneNode*> Enemigos_Scena;//Enemigos en scena
            IAnimatedMesh* arma;//Malla del arma del jugador
            IAnimatedMeshSceneNode* Arma_Jugador;//Malla del arma del jugador en escena
            IAnimatedMesh* armaEsp;//Malla del arma especial del jugador
            IAnimatedMeshSceneNode* ArmaEspecial_Jugador;//Malla del arma especial del jugador en escena
            std::vector<IAnimatedMeshSceneNode*> Objetos_Scena;//Objetos en scena
            std::vector<IAnimatedMeshSceneNode*> Recolectables_Scena;//Objetos en scena
            std::vector<IAnimatedMeshSceneNode*> PowerUP_Scena;//Objetos en scena
            std::vector<IAnimatedMeshSceneNode*> Objetos_Debug;//Objetos en modo debug
            std::vector<IAnimatedMeshSceneNode*> Objetos_Debug2;//Objetos en modo debug
            IAnimatedMeshSceneNode* Jugador_Scena;//Jugador en scena
            //debug
            IAnimatedMesh*  linea;
            IAnimatedMesh*  conovision;
            bool debugGrafico, pathfinding;//nos sirven para saber si tenemos activado el debug grafico y el pathfinding
            scene::ISceneNode* n;//box

            core::aabbox3d<f32> bounding_jugador;

            IAnimatedMeshSceneNode* tmpobjt_en_scena;
            IAnimatedMesh* sphere;
            IAnimatedMesh* cube;
            IAnimatedMesh* capsule;

            // Objetos y funciones para puzzles
            IGUIStaticText* myTextBox;

            IMesh* fichaMesh;                         // Malla
            IMeshSceneNode* ficha;                    // Nodo
            std::vector<IMeshSceneNode*> fichasMesh;  // Lista de nodos (fichas)

            // Para seleccionar nodos
            position2di initialCursorPosition;        // Posicion del clic raton
            position2di initialObjectPosition;        // Posicion del objeto que intersecta con el ray
            ISceneNode* nodoSeleccionado = 0;

            // Ventana
            short WIDTH_AUX, WIDTH, HEIGHT;
            short x_linea1, x_linea2;

            IGUIImage* img;
            ITexture*  puzzles_particle_texture;
            vector<IGUIImage*> imagenes;

            enum opcPuzzles { P_OPCIONES = 1, P_HANOI = 2 };
            enum posZ { IZQ=-9, CENTRO=0, DER=9, NO_SELECT=-1 };

            void CrearMeshFicha(float tamanyo, int r, int g, int b);
            void CargarIMG(short x, short y);

            //interfaz
            IGUIImage* vidaI;
            IGUIImage* energiaI;
            IGUIImage* dineroI;
            IGUIImage* armaI;
            IGUIImage* BarraVidaI;
            IGUIImage* BarraEnergiaI;
            IGUIImage* manosI;
            IGUIImage* llaveI;
            IGUIImage* espadaI;
            IGUIImage* dagaI;
            IGUIStaticText* moneyI;
            ITexture* vida_textura;
            ITexture* energia_textura;
            ITexture* dinero_textura;
            ITexture* arma_textura;
            ITexture* barraVida_textura;
            ITexture* barraEnergia_textura;
            ITexture* manos_textura;
            ITexture* llave_textura;
            ITexture* espada_textura;
            ITexture* daga_textura;
            //cinematicas
            int frame_actual = 0;//numero de frame actual
            IGUIImage* actual;//frame actual
            float tiempoUltimoFrame;//nos sirve para saber cuantos saltos tenemos que hacer
            ITexture* actualTexture;//textura actual
    };

#endif /* MotorGrafico_HPP */
