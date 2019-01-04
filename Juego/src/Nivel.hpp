//#include "Sala.hpp"
#include "Jugador.hpp"
#include "Enemigo.hpp"
#include "CargadorNiveles.hpp"
#include "pollo.hpp"
#include "Recolectable.hpp"
#include "MotorAudio.hpp"
#include "Pathfinder.hpp"
//#include "MotorGrafico.hpp"
//#include <vector>//para tener los diferentes objetos,enemigos, jugadores.
#include <ctime>
#include "Arma.hpp"
#include <cstring>
//#include "MotorFisicas.hpp"

#ifndef Nivel_HPP
#define Nivel_HPP

class Nivel
{

    public:

        //singleton public
        ~Nivel(void);
        static Nivel *getInstance() //esto se utiliza para crear el objeto una sola vez
        {
            if(unica_instancia == 0)
            unica_instancia = new Nivel();
            return unica_instancia;
        }
        //fin singleton public

        bool CargarNivel(int);//carga eñ nivel siempre que exista dicho nivel en assets/maps/xml/

        //cargar objetos
        void CrearEnemigo(int accion, int x,int y,int z, int ancho, int largo, int alto, const char *ruta_objeto, const char *ruta_textura, int * propiedades, Sala * sala);//lo utilizamos para crear su modelo en motorgrafico y su objeto
        void CrearJugador(int accion, int x,int y,int z, int ancho, int largo, int alto, const char *ruta_objeto, const char *ruta_textura, int * propiedades);//lo utilizamos para crear su modelo en motorgrafico y su objeto
        void CrearObjeto(int accion, const char* nombre, int ataque, int x,int y,int z, int ancho, int largo, int alto, const char *ruta_objeto, const char *ruta_textura, int * propiedades);//lo utilizamos para crear su modelo en motorgrafico y su objeto
        Sala * CrearPlataforma(int accion, int x,int y,int z, int ancho, int largo, int alto, int centro, const char *ruta_objeto, const char *ruta_textura);//lo utilizamos para crear su modelo en motorgrafico y su objeto
        void CrearLuz(int x,int y,int z);
        void EraseEnemigo(int i);
        void EraseJugador(int i);
        void update();//se actualiza todo lo de nivel (interpola(cy-y)^2) cion, posiciones, iluminacion)
        void updateAtEsp(MotorGrafico *);//se actualiza la ejecucion de los ataques
        void updateAt(int *, MotorGrafico *);
        void updateIA();//se actualiza la IA esto se llamara 4 veces por segundo o 60 frames
        std::vector<Enemigo*> getEnemies();

        Sala * getPrimeraSala();


        //Pruebas Pathfinding y ataque especial
        std::vector<Enemigo*>  getEnemigos();
        Jugador getJugador();
        void setThen();

    private:

        //clase singleton
        Nivel();
        static Nivel* unica_instancia;
        //fin clase singleton private
        //std::vector<IAnimatedMeshSceneNode*> Objetos_Scena;//Objetos en scena //crear clase objetos

        std::vector<Enemigo*> enemigos;//Enemigos en scena
        std::vector<Pathfinder::NodeRecord> recorrido;//Nodos a recorrer en el pathfinding
        std::vector<Recolectable*> recolectables;
        Jugador jugador;//objeto del jugador en el nivel
        CargadorNiveles cargador;//nos ayuda a cargar los niveles
        Sala * primeraSala;// la primera sala del arbol
        MotorFisicas *fisicas;//motor de fisicas (hace falta mas descripcion ?)
        int id;//id para las figuras
        float dt;
        float frameTime;
        float acumulator;
        float atacktime = 0.0f;
        float atackEsptime = 0.0f;
        clock_t newTime;
        clock_t currentTime;

        bool a,s,d,w,atEsp;
        bool cogerObjeto = false;
        int objetoCogido = -1;
        int danyo = 0, danyo2 = 0;
        unsigned int enemigoSeleccionado = 0;
};

#endif
