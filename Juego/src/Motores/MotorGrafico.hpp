/* Esta clase se encarga de fachada entre la logica del juego y sus aspectos graficos, de momento solo esta irrlicht
cuando este opengl se agregaran mas dependencias. Es una clase singleton (solo habra un objeto de MotorGrafico).*/
#ifndef MotorGrafico_HPP
#define MotorGrafico_HPP

#ifdef WEMOTOR
    //motor catopengl
    #include <Interfaz.hpp>
    #include "../Eventos.hpp"
    #include "../Times.hpp"
#else
    //motorirrlicht
    #include <irrlicht.h> //la utilizaremos para las funcionalidades del motor
    #include "../Inputs.hpp"
#endif

//#include "../Eventos.hpp" //este archivo contiene los ids de los eventos
#include "../ConstantesComunes.hpp"
#include <iostream> //la utilizamos para mostrar el log en la consola.
#include <math.h>
#include <vector>//para los objetos en escena
#include "Animaciones.hpp"

#ifdef WEMOTOR
    //namespaces de catopengl
    /* The unknown key */
    #define GLFW_KEY_UNKNOWN            -1

    /* Printable keys */
    #define GLFW_KEY_SPACE              32
    #define GLFW_KEY_APOSTROPHE         39  /* ' */
    #define GLFW_KEY_COMMA              44  /* , */
    #define GLFW_KEY_MINUS              45  /* - */
    #define GLFW_KEY_PERIOD             46  /* . */
    #define GLFW_KEY_SLASH              47  /* / */
    #define GLFW_KEY_0                  48
    #define GLFW_KEY_1                  49
    #define GLFW_KEY_2                  50
    #define GLFW_KEY_3                  51
    #define GLFW_KEY_4                  52
    #define GLFW_KEY_5                  53
    #define GLFW_KEY_6                  54
    #define GLFW_KEY_7                  55
    #define GLFW_KEY_8                  56
    #define GLFW_KEY_9                  57
    #define GLFW_KEY_SEMICOLON          59  /* ; */
    #define GLFW_KEY_EQUAL              61  /* = */
    #define GLFW_KEY_A                  65
    #define GLFW_KEY_B                  66
    #define GLFW_KEY_C                  67
    #define GLFW_KEY_D                  68
    #define GLFW_KEY_E                  69
    #define GLFW_KEY_F                  70
    #define GLFW_KEY_G                  71
    #define GLFW_KEY_H                  72
    #define GLFW_KEY_I                  73
    #define GLFW_KEY_J                  74
    #define GLFW_KEY_K                  75
    #define GLFW_KEY_L                  76
    #define GLFW_KEY_M                  77
    #define GLFW_KEY_N                  78
    #define GLFW_KEY_O                  79
    #define GLFW_KEY_P                  80
    #define GLFW_KEY_Q                  81
    #define GLFW_KEY_R                  82
    #define GLFW_KEY_S                  83
    #define GLFW_KEY_T                  84
    #define GLFW_KEY_U                  85
    #define GLFW_KEY_V                  86
    #define GLFW_KEY_W                  87
    #define GLFW_KEY_X                  88
    #define GLFW_KEY_Y                  89
    #define GLFW_KEY_Z                  90
    #define GLFW_KEY_LEFT_BRACKET       91  /* [ */
    #define GLFW_KEY_BACKSLASH          92  /* \ */
    #define GLFW_KEY_RIGHT_BRACKET      93  /* ] */
    #define GLFW_KEY_GRAVE_ACCENT       96  /* ` */
    #define GLFW_KEY_WORLD_1            161 /* non-US #1 */
    #define GLFW_KEY_WORLD_2            162 /* non-US #2 */

    /* Function keys */
    #define GLFW_KEY_ESCAPE             256
    #define GLFW_KEY_ENTER              257
    #define GLFW_KEY_TAB                258
    #define GLFW_KEY_BACKSPACE          259
    #define GLFW_KEY_INSERT             260
    #define GLFW_KEY_DELETE             261
    #define GLFW_KEY_RIGHT              262
    #define GLFW_KEY_LEFT               263
    #define GLFW_KEY_DOWN               264
    #define GLFW_KEY_UP                 265
    #define GLFW_KEY_PAGE_UP            266
    #define GLFW_KEY_PAGE_DOWN          267
    #define GLFW_KEY_HOME               268
    #define GLFW_KEY_END                269
    #define GLFW_KEY_CAPS_LOCK          280
    #define GLFW_KEY_SCROLL_LOCK        281
    #define GLFW_KEY_NUM_LOCK           282
    #define GLFW_KEY_PRINT_SCREEN       283
    #define GLFW_KEY_PAUSE              284
    #define GLFW_KEY_F1                 290
    #define GLFW_KEY_F2                 291
    #define GLFW_KEY_F3                 292
    #define GLFW_KEY_F4                 293
    #define GLFW_KEY_F5                 294
    #define GLFW_KEY_F6                 295
    #define GLFW_KEY_F7                 296
    #define GLFW_KEY_F8                 297
    #define GLFW_KEY_F9                 298
    #define GLFW_KEY_F10                299
    #define GLFW_KEY_F11                300
    #define GLFW_KEY_F12                301
    #define GLFW_KEY_F13                302
    #define GLFW_KEY_F14                303
    #define GLFW_KEY_F15                304
    #define GLFW_KEY_F16                305
    #define GLFW_KEY_F17                306
    #define GLFW_KEY_F18                307
    #define GLFW_KEY_F19                308
    #define GLFW_KEY_F20                309
    #define GLFW_KEY_F21                310
    #define GLFW_KEY_F22                311
    #define GLFW_KEY_F23                312
    #define GLFW_KEY_F24                313
    #define GLFW_KEY_F25                314
    #define GLFW_KEY_KP_0               320
    #define GLFW_KEY_KP_1               321
    #define GLFW_KEY_KP_2               322
    #define GLFW_KEY_KP_3               323
    #define GLFW_KEY_KP_4               324
    #define GLFW_KEY_KP_5               325
    #define GLFW_KEY_KP_6               326
    #define GLFW_KEY_KP_7               327
    #define GLFW_KEY_KP_8               328
    #define GLFW_KEY_KP_9               329
    #define GLFW_KEY_KP_DECIMAL         330
    #define GLFW_KEY_KP_DIVIDE          331
    #define GLFW_KEY_KP_MULTIPLY        332
    #define GLFW_KEY_KP_SUBTRACT        333
    #define GLFW_KEY_KP_ADD             334
    #define GLFW_KEY_KP_ENTER           335
    #define GLFW_KEY_KP_EQUAL           336
    #define GLFW_KEY_LEFT_SHIFT         340
    #define GLFW_KEY_LEFT_CONTROL       341
    #define GLFW_KEY_LEFT_ALT           342
    #define GLFW_KEY_LEFT_SUPER         343
    #define GLFW_KEY_RIGHT_SHIFT        344
    #define GLFW_KEY_RIGHT_CONTROL      345
    #define GLFW_KEY_RIGHT_ALT          346
    #define GLFW_KEY_RIGHT_SUPER        347
    #define GLFW_KEY_MENU               348
    #define GLFW_MOUSE_MOVE             349 //para saber si se ha movido el raton
#else
    //namespaces de irrlichts
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
#endif

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

            void LimpiarElementosJuego();
            void LimpiarMotorGrafico();//revisar

            bool CrearVentana(short tipo);//nos crea la ventana del juego. Tipo define lo grande que es por defecto 1024 x 768
            bool VentanaAbierta(); //sirve para saber si la ventana esta activa
            void CerrarJuego();
            void LimpiarDevice();//elimina el dispositivo
            void ActivarFuenteDefault(); //define fuente por defecto
            unsigned short CrearImagen(const char * texto,unsigned int,unsigned int,float);//creas una imagen con el escalado que le proporciones, y en la posicion x e y

            void FondoEscena(int a, int r, int g, int b);
            void FondoEscena(float a, float r, float g, float b);
            void RenderEscena();
            void BorrarScena(); // borra todo lo que haya en la ventana
            void BorrarGui(); // borra todo lo que haya en la ventana relacionado con el gui

            unsigned int CrearTexto(std::string texto, short x1, short y1, short x2, short y2);
            void CrearBoton(short x, short y, short x2, short y2, signed int id,
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

            #ifdef WEMOTOR
                double * GetPosicionRaton();
            #else
                position2di GetPosicionRaton();
            #endif

            void CrearCamara(); // crea una camara para ver el escenario

            bool GetDebugActivado(); // para saber si esta activado

            //cargando
            unsigned short idCargando;
            void AsignarCargando(unsigned short);
            void BorrarCargando();

            //----------------- Revisar

            /*IMPORTANTE para bullet motor de fisicas y Joints*/
            //btHingeConstraint(btRigidBody& rbA,const btTransform& rbAFrame, const btTransform& rbBFrame);

            //cargadores de objetos
            int CargarPlataformas(int rp, int x,int y,int z, int ancho, int largo, int alto, const char* ruta_objeto, const char* ruta_textura);//carga el objeto en scena lo mete en el array
            void CargarLuces(int x,int y,int z,int r,int g,int b,int tipo = 0,float dist = 50.0f,int anim = 0);
            void CargarParticulas(int x, int y, int z, int velocidadx, int velocidady, int velocidadz, float escala, unsigned int nparticulas, float localz, float tvida, const char* ruta_textura);
            void CargarParticulasAccion(int x, int y, int z, int velocidadx, int velocidady, int velocidadz, float escala, unsigned int nparticulas, float localz, float tvida, const char* ruta_textura);
            void IniciarParticulasAccion(unsigned short i, float x, float y, float z, float time);
            void CargarSalaLuz(int sala,int minz,int maxz,int minx,int maxx);
            void CargarLuzEnSala(int sala,int x,int y,int z);
            void CargarEnemigos(int x,int y,int z, const char* ruta_objeto, const char* ruta_textura, bool boss);
            void CargarJugador(int x,int y,int z, int ancho, int largo, int alto, const char* ruta_objeto);
            int CargarObjetos(int accion, int rp, int x,int y,int z, int ancho, int largo, int alto, const char* ruta_objeto, const char* ruta_textura, const char * anima = nullptr , int frame = 1, bool afectaluz = true);
            void CargarCofre(int pos, int rp, int x,int y,int z, const char *ruta_objeto, const char *ruta_textura, const char * anima = nullptr , int frame = 1, bool afectaluz = true);
            void CargarArmaJugador(int x,int y,int z, const char* ruta_objeto, const char* ruta_textura);
            void CargarProyectil(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura);
            void CargarArmaEspecial(int x,int y,int z, const char* ruta_objeto, const char* ruta_textura);
            void CargarRecolectable(int id, int x,int y,int z, const char* ruta_objeto, const char* ruta_textura);
            void llevarObjeto(float x, float y, float z, float rx, float ry, float rz);
            void dispararProyectil(float x, float y, float z, float rx, float ry, float rz, float es);

            void mostrarJugador(float x, float y, float z, float rx, float ry, float rz, float newy, float newz);
            void mostrarEnemigos(float x, float y, float z, float rx, float ry, float rz, unsigned int i);
            void mostrarObjetos(float x, float y, float z, float rx, float ry, float rz, unsigned int i);
            void mostrarCofres(float x, float y, float z, float rx, float ry, float rz, unsigned int i);
            void mostrarArmaEspecial(float x, float y, float z, float rx, float ry, float rz);
            void mostrarBoardArma(int danyoequipada, int danyosuelo, int tipoequipada, int tiposuelo, unsigned int i);
            void borrarArmaEspecial();

            //TRansparencias
            void mallaTransparente(unsigned int id, float t);

            //debug grafico
            void activarDebugGrafico();//se activa o desactiva el modo debug grafico
            void activarPathfinding(); //Temporal, se activa o desactiva el pathfinding
            void clearDebug();//borra toda la informacion de debug en cada update para ver los cambios
            void clearDebug2();
            void dibujarCirculoEventoSonido(int x, int y, int z, float intensidad);//se dibuja el circulo con la intensidad que se solicita en las coordenadas proporcionadas
            void dibujarZona(int x, int y, int z, float ancho, float alto, float profund);
            void dibujarObjetoTemporal(int x, int y, int z, int rx, int ry, int rz ,int ancho, int alto, int profund, int tipo);

            //colision rayo
            bool colisionRayo(int x,int y, int z, int rx, int ry, int rz ,int dimension);
            //void dibujarRayo(int x,int y, int z, int rx, int ry, int rz ,int dimension);//dibuja los rayos o lineas con las indicaciones que pongas, (x,y,z) son donde empieza la linea el primer punto, (rx,ry,rz) rotacion de la linea desde su punto, dimension longitud de la linea

            void colorearJugador(int a, int r, int g, int b);
            void colorearEnemigo(int a, int r, int g, int b, int enem);
            //void colorearObjeto(int a, int r, int g, int b, int obj);

            #ifdef WEMOTOR
                bool getArmaEspecial();
            #else
                IAnimatedMeshSceneNode* getArmaEspecial();
            #endif

            void EraseRecoArma(long unsigned int idx);
            void EraseLlave(long unsigned int idx);
            void ErasePared(long unsigned int idx);
            void ErasePowerUP(long unsigned int idx);
            void EraseCofre(unsigned short idx);
            //void DibujarPared(long unsigned int idx, bool dibujar);
            void EraseEnemigo(std::size_t i);
            void EraseTodosEnemigos();
            void EraseJugador();
            void EraseArma();
            void EraseProyectil();
            //int getEnemigos_Scena();
            //int getObjetos_Scena();

            void debugBox(int x,int y, int z,int ancho, int alto, int largo);
            void debugVision(float x, float y, float z, float rotacion, float longitud);


            //interfaz TO DO: revisar
            void CargarInterfaz();
            void DestruirInterfaz();
            void SetVida(int vida);
            void SetBarraEnergia(int barra);
            void SetDinero(int dinero);
            void SetArma(int arma);
            void RenderInterfaz(bool activada);//TO DO: ¿separar graficos?

            //animaciones
            void cambiarAnimacionJugador(int);//nos sirve para cambiar de animacion al jugador
            void cambiarAnimacion(int,int,int);//modo,id y estado
            void ActualizarAnimacionMotor(Animaciones * anima);//se pasa la animacion a actualizar

            //getters & setters
            bool getPathfindingActivado();

            void RenderMotorCinematica(float marcaTiempo, float tiempoUltimoFrame);
            bool finalCinematica();
            void girarCamara();
            int getCamx();
            int getCamz();
            int getCams();

            void BorrarElemento(signed int id);// Borra un elemento del arbol de nodos a traves de su ID personalizado
            void BorrarElementoPorIdReal(unsigned int id);//borra elemento del arbol de nodos con el id que tiene
            unsigned short GetWidth();
            unsigned short GetHeight();

            // Funciones para Puzzles
            void IniIDPuzzles();
            void BorrarGuiPuzzle(unsigned short tipo, unsigned short opciones);
            void CargarFondoPuzzle();
            void CargarIMGPuzzle(unsigned short x, unsigned short y, std::string img);
            void CrearTextoPuzzles(std::string texto, unsigned short x1, unsigned short y1,
                unsigned short x2, unsigned short y2);

            void HabilitarDinero();
            void DeshabilitarDinero();
            void CambiarCamara();

            //cambiar propiedades del texto
            void CambiarAnchuraTexto(unsigned short,unsigned int);

            //boton
            unsigned int CrearBoton2(short xImagen, short yImagen, unsigned int escalado, short xTexto, short yTexto, unsigned int anchotexto, signed int id,const wchar_t* texto, const wchar_t * rutaimagen = L"assets/images/boton3.png",bool esTexto = true,const char * rutapulsado = nullptr,const char * rutaencima = nullptr);

            //para deshabilitar y habilitar captura de texto
            void ActivarCapturaTexto();
            void DesactivarCapturaTexto();
            char * DevolverTextoCapturado();
            void InicializarCaptura(const char *);
            void BorrarUltimaLetra();

            void CambiarTexto(unsigned int, const char *);//cambia el texto de un objeto tipo texto
            void CambiarColorTexto(unsigned int, float r, float g, float b);//cambia el color del texto
            void CambiarPosicionImagen(signed int event, float x, float y);//cambiar posicion de un evento (imagen)

            void UpdateLights(float x,float y,float z);
            void UpdateBoards(std::vector<unsigned short> boardvect, float x, float y, float z, float d);
            void UpdateBoardsVidaEne(int enem, int vida, int vidamax);

        private: //clases solo accesibles por MotorGrafico

            struct SalasLuz
            {
                unsigned short sala;
                int minz, maxz;
                int minx, maxx;
                std::vector<glm::vec3> luz;
            };

            //clase singleton
            MotorGrafico();
            static MotorGrafico* _unica_instancia;
            //fin clase singleton private
            Animaciones * _aniJugEscena;
            void propiedadesDevice();

            #ifdef WEMOTOR
                //variables y parametros motor catopengl

                Interfaz * _interfaz;//puntero que contiene la entrada al motorgrafico de catopengl

                unsigned short camara;//id de la camara

                std::vector<unsigned short> Plataformas_Scena;//contiene las mmallas del suelo del juego
                std::vector<unsigned short> Luces_Scena;//contiene las luces de la escena
                std::vector<SalasLuz> Salas_luz; //contiene las salas con luz
                std::vector<unsigned short> Enemigos_Scena;//contiene los enemigos reservados (ids)
                std::vector<unsigned short> Textos_Scena;//contiene los enemigos reservados (ids)
                std::vector<unsigned short> BoardsArmas_Scena;//contiene los billboards de armas reservados (ids)
                std::vector<unsigned short> BoardsEnem_Scena;//contiene los billboards de enemigos reservados
                std::vector<unsigned short> Particulas_Scena; //contiene los sistemas de particulas de la escena
                std::vector<unsigned short> Particulas_Accion; //consitne los sistemas de particulas de acciones especificas
                std::vector<unsigned short> Objetos_Scena;//contiene los objetos reservados (ids)
                std::vector<unsigned short> RecoArmas_Scena;//contiene los recolectables reservados (ids)
                std::vector<unsigned short> Llaves_Scena;
                std::vector<unsigned short> PowerUP_Scena;//contiene los power ups reservados (ids)
                std::vector<unsigned short> Paredes_Scena;//paredes rompibles
                std::vector<unsigned short> Cofres_Scena;//cofres

                std::vector<Animaciones *> ObjetosAni_Scena;//contiene los objetos reservados (ids)
                std::vector<Animaciones *> RecoArmasAni_Scena;//contiene los objetos reservados (ids)
                std::vector<Animaciones *> LlavesAni_Scena;//contiene los objetos reservados (ids)
                std::vector<Animaciones *> PowerUPAni_Scena;//contiene los objetos reservados (ids)
                std::vector<Animaciones *> ParedesAni_Scena;
                std::vector<Animaciones *> CofresAni_Scena;

                std::vector<unsigned short> Objetos_Debug;//contiene los elementos que se ven en modo debug
                std::vector<unsigned short> Objetos_Debug2;//para objetos con tiempo para desaparecer

                unsigned short _luzDireccional;
                unsigned short _luzFoco;
                unsigned short _salaActual;
                unsigned short _jugEscena;//id jugador
                bool debugGrafico;//nos sirve para ver las zonas de colision
                unsigned short _armaEspJugador;//id del arma del jugador
                unsigned short _armaEnEscena;
                unsigned short _armaProyectil; //id del proyectil
                unsigned short _armaEsp;//id del arma especial cargado en memoria
                bool pathfinding;//sirve para sacar mensaje por pantalla de si esta activado o no
                bool existearmaexp;
                float center_x, center_y, center_z;

                // Ventana
                short WIDTH_AUX, WIDTH, HEIGHT;
                short x_linea1, x_linea2;
                unsigned short width, height;
                int camx, camz, cams;

                //hud
                unsigned short moneyI;
                unsigned short vida_textura;
                unsigned short energia_textura;
                unsigned short dinero_textura;
                unsigned short arma_textura;
                unsigned short barraVida_textura;
                unsigned short barraEnergia_textura;
                unsigned short manos_textura;
                unsigned short llave_textura;
                unsigned short espada_textura;
                unsigned short daga_textura;

                //puzzles

                // Variables para Puzzles
                unsigned short IDP;
                unsigned short _imgP;
                unsigned short _txtP;
                vector<unsigned short> _imagenesP;
                vector<unsigned short> _textosP;

            #else
                //variables y parametros motor irrlicht

                Inputs input;
                IrrlichtDevice* _device; //puntero a dispositivo por defecto
                IVideoDriver* _driver;
                ISceneManager* _smgr;
                IGUIEnvironment* _guienv;
                const IGeometryCreator* _geometryCreator;
                ISceneCollisionManager* _collmgr;
                ICameraSceneNode* _camera;

                // Ventana
                unsigned short width, height;
                IGUIFont* _font;
                IGUISkin* _skin;

                /** Revisar **/
                IGUIFont* font2;
                std::vector<IAnimatedMeshSceneNode*> Plataformas_Scena;//plataformas en scena
                std::vector<ILightSceneNode*> Luces_Scena;//luces en scena
                std::vector<IAnimatedMeshSceneNode*> Enemigos_Scena;//Enemigos en scena

                IAnimatedMeshSceneNode* _armaEnEscena;//Malla del arma del jugador en escena
                IAnimatedMeshSceneNode* _armaProyectil;//Malla del arma del jugador en escena
                IAnimatedMesh* _armaEsp;//Malla del arma especial del jugador
                IAnimatedMeshSceneNode* _armaEspJugador;//Malla del arma especial del jugador en escena
                std::vector<IAnimatedMeshSceneNode*> Objetos_Scena;//Objetos en scena
                std::vector<IAnimatedMeshSceneNode*> RecoArmas_Scena;//Objetos en scena
                std::vector<IAnimatedMeshSceneNode*> Llaves_Scena;//Objetos en scena
                std::vector<IAnimatedMeshSceneNode*> PowerUP_Scena;//Objetos en scena
                std::vector<IAnimatedMeshSceneNode*> Paredes_Scena;
                std::vector<IAnimatedMeshSceneNode*> Cofres_Scena;
                std::vector<IAnimatedMeshSceneNode*> Objetos_Debug;//Objetos en modo debug
                std::vector<IAnimatedMeshSceneNode*> Objetos_Debug2;//Objetos en modo debug
                IAnimatedMeshSceneNode* _jugEscena;//Jugador en scena
                //debug
                IAnimatedMesh* _linea;
                IAnimatedMesh* _conoVision;
                bool debugGrafico, pathfinding;//nos sirven para saber si tenemos activado el debug grafico y el pathfinding
                ISceneNode* _caja;//box

                IAnimatedMeshSceneNode* _tmpObjEscena;

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
                int frame_actual;//numero de frame actual
                IGUIImage* _actual;//frame actual
                float tiempoUltimoFrame;//nos sirve para saber cuantos saltos tenemos que hacer
                ITexture* _actualTexture;//textura actual
                int camx, camz, cams;

                // Variables para Puzzles
                unsigned short IDP;
                IGUIImage* _imgP;
                IGUIStaticText* _txtP;
                vector<IGUIImage*> _imagenesP;
                vector<IGUIStaticText*> _textosP;

            #endif

            // Variables comunes de para OpenGL/irrlicht
            Constantes constantes;

            // Camara
            unsigned short altura;
            bool camara1;

            //mejoras en inputs
            const int numeroteclas = 349;//contiene el numero de teclas a comprobar
            bool estadoteclas[350];//contiene estado de las teclas
            bool estadoteclas2[350];//contiene si esta pulsado
            void updateTeclas(); //actualiza los estados de las teclas
            float tiempo;//segun que valor se ponga los botones se actualizan mas rapido esta puesto para que se actualicen 10 veces por segundo
    };

#endif /* MotorGrafico_HPP */
