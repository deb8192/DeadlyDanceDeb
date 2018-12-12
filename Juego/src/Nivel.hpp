#include "Sala.hpp"
#include "Jugador.hpp"
#include "Enemigo.hpp"
#include "CargadorNiveles.hpp"
#include "pollo.hpp"
#include <vector>//para tener los diferentes objetos,enemigos, jugadores.
#include <ctime>

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
        void CrearEnemigo(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura, int * propiedades, Sala * sala);//lo utilizamos para crear su modelo en motorgrafico y su objeto
        void CrearJugador(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura, int * propiedades);//lo utilizamos para crear su modelo en motorgrafico y su objeto
        void CrearObjeto(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura, int * propiedades);//lo utilizamos para crear su modelo en motorgrafico y su objeto
        Sala * CrearPlataforma(int x,int y,int z, int ancho, int largo, int centro, const char *ruta_objeto, const char *ruta_textura);//lo utilizamos para crear su modelo en motorgrafico y su objeto
        void CrearLuz(int x,int y,int z);
        void update();//se actualiza todo lo de nivel (interpola(cy-y)^2) cion, posiciones, iluminacion)
        void updateIA();//se actualiza la IA esto se llamara 4 veces por segundo o 60 frames

        Sala * getPrimeraSala();

        //Pruebas Pathfinding
        Enemigo * getPrimerEnemigo();
        void setThen();


    private:

        //clase singleton
        Nivel();
        static Nivel* unica_instancia;
        //fin clase singleton private
        //std::vector<IAnimatedMeshSceneNode*> Objetos_Scena;//Objetos en scena //crear clase objetos

        std::vector<Enemigo*> enemigos;//Enemigos en scena
        Jugador jugador;//objeto del jugador en el nivel
        CargadorNiveles cargador;//nos ayuda a cargar los niveles
        Sala * primeraSala;// la primera sala del arbol
        int id;//id para las figuras
        float dt;
        float frameTime;
        float acumulator;
        float atacktime = 0.0f;
        clock_t newTime;
        clock_t currentTime;
        bool a,s,d,w;
};

#endif
