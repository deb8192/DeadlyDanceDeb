#ifndef CargadorNiveles_HPP
#define CargadorNiveles_HPP

#include "pugixml.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include "Jugando/Sala.hpp"
#include "Jugando/Zona.hpp"
#include "Objetos/Recolectable.hpp"
#include "Objetos/Pared.hpp"
#include "Personajes/Jugador.hpp"
#include "Enemigos/Enemigo.hpp"
#include "Jugando/Waypoint.hpp"

#include "Motores/MotorAudio.hpp"
#include "Motores/MotorGrafico.hpp"
//#include "Motores/MotorFisicas.hpp"

//cargaremos el arbol(ia) desde nivel y se lo pasaremos a su entidad correspondiente, el enemigo la activa llamando a enemigo->runIA()
#include "CargadorBehaviorTrees.hpp"

#include "Objetos/Puerta.hpp"
#include "Objetos/Palanca.hpp"
#include "Objetos/Cofre.hpp"

class CargadorNiveles
{
    public:
        CargadorNiveles();
        ~CargadorNiveles();
        void CargarNivelXml(int level, int tipoJug); //esta funcion carga el nivel desde xml
        void GuardarNivelXml(int); //esta funcion guarda el nivel en xml
        void GuardarNivelBin(int); //esta funcion guarda el nivel en formato bin con el numero que le pases
        void CargarNivelBin(int); //esta funcion carga el nivel desde un archivo binario  
        
        
        Jugador* GetJugador();
        std::vector<Enemigo*> GetEnemigos();
        std::vector<Enemigo*> GetEneCofres();
        std::vector<Zona*> GetZonas();
        std::vector<Recolectable*> GetRecolectables();
        std::vector<Recolectable*> GetLlaves();
        std::vector<Pared*> GetParedes();
        std::vector<Recolectable*> GetPowerup();
        Enemigo* GetBoss();
        std::vector<Waypoint*> GetWaypoints();

        std::vector<Puerta*> GetPuertas();
        std::vector<Palanca*> GetPalancas();
        std::vector<Cofre*> GetCofres();

        void ReservarMemoriaVectores(int eneMax, int doorsMax, int leversMax, int chestsMax, int waypointsMax, int zonesMax);
        Sala* CrearPlataforma(int accion, int rp, int x,int y,int z, int ancho, int largo, int alto, int centro, const char* ruta_objeto, const char* ruta_textura);//lo utilizamos para crear su modelo en motorgrafico y su objeto
        void CrearLuz(int x,int y,int z);
        void CrearEnemigo(int accion, int enemigo, int x,int y,int z, int ancho, int largo, int alto, Sala* sala);//lo utilizamos para crear su modelo en motorgrafico y su objeto
        void CrearBoss(int accion,int enemigo,int x,int y,int z,int ancho, int largo, int alto, Sala* sala);
        void CrearZona(int accion,int x,int y,int z,int ancho,int largo,int alto, const char* tipo, unsigned short totalElem, Sala* sala); //lo usamos para crear zonas
        void CrearObjeto(int codigo, int accion, const char* nombre, int ataque, int rp, int x,int y,int z, int despX, int despZ, int ancho, int largo, int alto, const char* ruta_objeto, const char* ruta_textura, int* propiedades, unsigned short tipoObj, const char * anima = nullptr , int frame = 1);//lo utilizamos para crear su modelo en motorgrafico y su objeto
        void CrearWaypoint(Sala* sala, int accion, int compartido, int ID,  int x, int y, int z, int ancho, int largo, int alto, int* arrayConexiones, int sizeConexiones); //Lo usamos para crear waypoints
        unsigned short CrearCofreArana(float x, float y, float z,
            float ancho, float alto, float largo, Sala* sala);
        void CargarCofres();  //Lo usamos para cargar los cofres en las distintas zonas de cofres

        int* GetID();

        // Funciones de Debug
        void TrasladarJugadorACofres();

    private:
        Sala* crearSala(pugi::xml_node hijo, Sala* padre);//se llama recursivamente si hay salas
        //int* lista; //comentado por Marines porq no se usa

        int id;//id para las figuras
        int tipoJug;
        Jugador* _jugador;
        Sala* _primeraSala;// la primera sala del arbol

        CargadorBehaviorTrees cargadorIA; //Variable para crear la IA de los enemigos
        Enemigo* _boss;
        std::vector<Enemigo*> _enemigos;//Enemigos en scena
        int chestsMax;
        std::vector<Enemigo*> _eneCofres;
        std::vector<Recolectable*> _reco_armas;
        std::vector<Pared*> _paredes;
        std::vector<Recolectable*> _powerup;
        std::vector<Recolectable*> _llaves;
        std::vector<Zona*> _zonas; //Array de zonas
        std::vector<Waypoint*> _waypoints; //Vector de waypoints del nivel

        MotorGrafico* _motor;
        MotorFisicas* _fisicas;
        MotorAudioSystem* _motora;
        Constantes constantes;

        // Variables temporales de Debug
        float* posCofre = new float[3];

        std::vector<Palanca*> _palancas;
        std::vector<Puerta*> _puertas;
        std::vector<Cofre*> _cofres;
};

#endif /* CargadorNiveles_HPP */