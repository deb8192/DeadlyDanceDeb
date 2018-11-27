#include "Sala.hpp"
#include "Jugador.hpp"
#include "Enemigo.hpp"
#include "CargadorNiveles.hpp"
#include <vector>//para tener los diferentes objetos,enemigos, jugadores.

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
        void CrearEnemigo(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura, int * propiedades);//lo utilizamos para crear su modelo en motorgrafico y su objeto
        void CrearJugador(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura, int * propiedades);//lo utilizamos para crear su modelo en motorgrafico y su objeto
        void CrearObjeto(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura, int * propiedades);//lo utilizamos para crear su modelo en motorgrafico y su objeto
        void CrearPlataforma(int x,int y,int z, const char *ruta_objeto, const char *ruta_textura);//lo utilizamos para crear su modelo en motorgrafico y su objeto
        void CrearLuz(int x,int y,int z);
        

    private:
        
        //clase singleton 
        Nivel();
        static Nivel* unica_instancia;
        //fin clase singleton private 
        //std::vector<IAnimatedMeshSceneNode*> Objetos_Scena;//Objetos en scena //crear clase objetos
        
        std::vector<Enemigo> enemigos;//Enemigos en scena
        Jugador jugador;//objeto del jugador en el nivel
        CargadorNiveles cargador;//nos ayuda a cargar los niveles
        Sala * primeraSala;// la primera sala del arbol
};

#endif 
