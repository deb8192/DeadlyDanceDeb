#ifndef CargadorNiveles_HPP
#define CargadorNiveles_HPP

#include "pugixml.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include "Jugando/Sala.hpp"
#include "Jugando/Zona.hpp"
#include "Objetos/Interactuable.hpp"
#include "Objetos/Recolectable.hpp"
#include "Personajes/Jugador.hpp"
#include "Enemigos/Enemigo.hpp"
#include "Jugando/Waypoint.hpp"

#include "Motores/MotorAudio.hpp"
#include "Motores/MotorGrafico.hpp"
#include "Motores/MotorFisicas.hpp"

//cargaremos el arbol(ia) desde nivel y se lo pasaremos a su entidad correspondiente, el enemigo la activa llamando a enemigo->runIA()
#include "CargadorBehaviorTrees.hpp"

class CargadorNiveles
{
    public:
        CargadorNiveles();
        ~CargadorNiveles();
        void CargarNivelXml(int level, int tipoJug, int* id); //esta funcion carga el nivel desde xml
        void GuardarNivelXml(int); //esta funcion guarda el nivel en xml
        void GuardarNivelBin(int); //esta funcion guarda el nivel en formato bin con el numero que le pases
        void CargarNivelBin(int); //esta funcion carga el nivel desde un archivo binario  
        
        Jugador* GetJugador();
        std::vector<Enemigo*> GetEnemigos();
        std::vector<Zona*> GetZonas();
        std::vector<Recolectable*> GetRecolectables();
        std::vector<Interactuable*> GetInteractuables();
        std::vector<Recolectable*> GetPowerup();
        Enemigo* GetBoss();
        std::vector<Waypoint*> GetWaypoints();

        Sala* CrearPlataforma(int accion, int rp, int x,int y,int z, int ancho, int largo, int alto, int centro, const char* ruta_objeto, const char* ruta_textura);//lo utilizamos para crear su modelo en motorgrafico y su objeto
        void CrearLuz(int x,int y,int z);
        void CrearEnemigo(int accion, int enemigo, int x,int y,int z, int ancho, int largo, int alto, Sala* sala, int* id);//lo utilizamos para crear su modelo en motorgrafico y su objeto
        void CrearBoss(int accion,int enemigo,int x,int y,int z,int ancho, int largo, int alto, Sala* sala, int* id);
        void CrearZona(int accion,int x,int y,int z,int ancho,int largo,int alto, const char* tipo, unsigned short totalElem); //lo usamos para crear zonas
        void CrearObjeto(int codigo, int accion, const char* nombre, int ataque, int rp, int x,int y,int z, int despX, int despZ, int ancho, int largo, int alto, const char* ruta_objeto, const char* ruta_textura, int* propiedades, int* id);//lo utilizamos para crear su modelo en motorgrafico y su objeto
        void CrearWaypoint(Sala* sala, int accion, int compartido, int ID,  int x, int y, int z, int ancho, int largo, int alto, int* arrayConexiones, int sizeConexiones); //Lo usamos para crear waypoints
        
    private:
        Sala* crearSala(pugi::xml_node hijo, Sala* padre, int* id);//se llama recursivamente si hay salas
        //int* lista; //comentado por Marines porq no se usa

        int tipoJug;
        Jugador* _jugador;
        Sala* _primeraSala;// la primera sala del arbol

        CargadorBehaviorTrees cargadorIA; //Variable para crear la IA de los enemigos
        Enemigo* _boss;
        std::vector<Enemigo*> _enemigos;//Enemigos en scena
        std::vector<Recolectable*> _recolectables;
        std::vector<Interactuable*> _interactuables; //Objetos interactuables del mapa
        std::vector<Recolectable*> _powerup;
        std::vector<Zona*> _zonas; //Array de zonas
        std::vector<Waypoint*> _waypoints; //Vector de waypoints del nivel

        MotorGrafico* _motor;
        MotorFisicas* _fisicas;
        MotorAudioSystem* _motora;
};

#endif /* CargadorNiveles_HPP */