#ifndef Nivel_HPP
#define Nivel_HPP

#include "../Personajes/Jugador.hpp"
#include "../Enemigos/Enemigo.hpp"
#include "../CargadorNiveles.hpp"
#include "../Enemigos/Pollo.hpp"
#include "../Objetos/Interactuable.hpp"
#include "../Objetos/Recolectable.hpp"
#include "Zona.hpp"
#include "../Motores/MotorAudio.hpp"
#include "../Motores/MotorGrafico.hpp"
#include "../Pathfinder.hpp"
#include "../Times.hpp"
#include "../Armas/Arma.hpp"
#include <cstring>
#include <stdlib.h>
#include <time.h>

//cargaremos el arbol(ia) desde nivel y se lo pasaremos a su entidad correspondiente, el enemigo la activa llamando a enemigo->runIA()
#include "../CargadorBehaviorTrees.hpp"
#include "../Arbol2.hpp"
//librerias necesarias


class Nivel
{
    public:

        //singleton public
        ~Nivel(void);
        static Nivel* getInstance() //esto se utiliza para crear el objeto una sola vez
        {
            if(_unica_instancia == 0)
                _unica_instancia = new Nivel();
            return _unica_instancia;
        }
        //fin singleton public
        void LimpiarNivel();

        //void LimpiarNivel();
        bool CargarNivel(int);//carga eñ nivel siempre que exista dicho nivel en assets/maps/xml/

        //cargar objetos
        void recargarJugador();
        void CrearEnemigo(int accion, int enemigo, int x,int y,int z, int ancho, int largo, int alto, const char* ruta_objeto, const char* ruta_textura, int* propiedades, Sala* sala);//lo utilizamos para crear su modelo en motorgrafico y su objeto
        void CrearJugador(int accion, int x,int y,int z, int ancho, int largo, int alto, const char* ruta_objeto, const char *ruta_textura, int* propiedades);//lo utilizamos para crear su modelo en motorgrafico y su objeto

        void CrearObjeto(int codigo, int accion, const char* nombre, int ataque, int x,int y,int z, int despX, int despZ, int ancho, int largo, int alto, const char* ruta_objeto, const char* ruta_textura, int* propiedades);//lo utilizamos para crear su modelo en motorgrafico y su objeto
        void CrearZona(int accion,int x,int y,int z,int ancho,int largo,int alto, const char* tipo, int* propiedades); //lo usamos para crear zonas
        Sala* CrearPlataforma(int accion, int x,int y,int z, int ancho, int largo, int alto, int centro, const char* ruta_objeto, const char* ruta_textura);//lo utilizamos para crear su modelo en motorgrafico y su objeto
        void CrearLuz(int x,int y,int z);
        void cargarCofres(int num);

        void EraseEnemigo(std::size_t i);
        void EraseJugador();

        //Bucle de actualizacion y dibujado de objetos
        void update();//se actualiza todo lo de nivel (interpola(cy-y)^2) cion, posiciones, iluminacion)
        void updateAtEsp(MotorGrafico* );//se actualiza la ejecucion de los ataques
        void updateAt(int* , MotorGrafico* );
        void updateIA();//se actualiza la IA esto se llamara 4 veces por segundo o 15 veces
        void updateRecorridoPathfinding(Enemigo* );
        void Draw();//dibuja y actualiza las posiciones del interpolado

        void setEnemigoPideAyuda(Enemigo* );

        Enemigo* getEnemigoPideAyuda();
        Sala* getPrimeraSala();
        std::vector<Enemigo*>  getEnemigos();
        void setThen();

        //Funciones de interacciones
        void CogerObjeto();
        void DejarObjeto();
        void InteractuarNivel();
        void AccionarMecanismo(int);    //Activa mecanismos y o puertas
        void crearObjetoCofre(Interactuable* newobjeto);
        void activarPowerUp();

        Jugador* GetJugador();

        int getjix();
        int getjiy();
        int getjiz();
        void setjix(int);
        void setjiy(int);
        void setjiz(int);
        void Ejecutar();//activa ejecutar update y updateia
        void NoEjecutar();//desactiva ejecutar update y updateia
        void ActivarLimpieza();//se pone para limpiar el nivel
        bool EstaLimpio();//devuelve si esta limpio el nivel
        void borrarEnemigos();//borra todos los enemigos

    private:

        //clase singleton
        Nivel();
        static Nivel* _unica_instancia;
        //fin clase singleton private
        //std::vector<IAnimatedMeshSceneNode*> Objetos_Scena;//Objetos en scena //crear clase objetos

        std::vector<Enemigo*> enemigos;//Enemigos en scena
        CargadorBehaviorTrees cargadorIA; //Variable para crear la IA de los enemigos
        std::vector<Enemigo*> auxiliadores;  //Enemigos que responden a la ayuda
        Enemigo* _enemPideAyuda = nullptr;  //Enemigos que pide ayuda
        std::vector<Pathfinder::NodeRecord> recorrido;//Nodos a recorrer en el pathfinding
        std::vector<Recolectable*> recolectables;
        std::vector<Recolectable*> powerup;
        std::vector<Zona*> zonas; //Array de zonas
        std::vector<Interactuable*> interactuables; //Objetos interactuables del mapa
        Jugador jugador;//objeto del jugador en el nivel
        CargadorNiveles cargador;//nos ayuda a cargar los niveles
        Sala* _primeraSala;// la primera sala del arbol
        Sala* _destinoPathFinding; //sala que se rellena al llamar a pathfinding y se vacía al terminar el recorrido del enemigo
        MotorFisicas* _fisicas;//motor de fisicas
        int id;//id para las figuras

        float dt, lastUpdateTime, updateTime, lastDrawTime, drawTime;
        float frameTime; // frameTime: tiempo por fotograma
        float acumulator;
        float atacktime = 0.0f; //tiempo de ejecucion del ataque
        float lastAtackEsptime = 0.0f; //registro antiguo del tiempo de ataque especial para su animacion
        clock_t newTime;
        clock_t currentTime;
        Times* _controladorTiempo; //objeto time para usar sus funciones

        //bool a,s,d,w;
        bool cogerObjeto = false, jugadorInmovil = false;
        int objetoCogido = -1;
        int danyo = 0, danyo2 = 0;
        int contadorEnem = 0;
        int cambia;
        //para el metodo recargarjugador()
        int jix = 0;
        int jiy = 0;
        int jiz = 0;
        bool ejecutar;//nos servira para saber si tenemmos que ejecutar el update y el updateia
        bool limpiar;//para saber si hay que limpar el nivel
        bool limpio;//para saber si esta limpio el nivel

        //Comprobacion de powerup
        int powerupYES = -1;

};
#endif
