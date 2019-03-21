#ifndef JUGANDO_HPP
#define JUGANDO_HPP

#include "../Estado.hpp"
#include "../Motores/SenseEventos.hpp"
#include "../CargadorNiveles.hpp"
#include "../Times.hpp"
#include "../Personajes/Jugador.hpp"
#include "../Enemigos/Enemigo.hpp"
#include "../Objetos/Interactuable.hpp"
#include "../Objetos/Recolectable.hpp"
#include "../Armas/Arma.hpp"
#include "../Jugando/InterfazJugador.hpp"
#include "Zona.hpp"
#include "Waypoint.hpp"

#include "../Pathfinder.hpp"


class Jugando: public Estado {
    public:
        Jugando();
        ~Jugando();

        // Funciones de Estado
        void Iniciar();
        void ManejarEventos();
        void Update(); // Se actualiza todo lo de nivel (interpolacion(cy-y)^2), posiciones, iluminacion)
        void UpdateIA(); // Se llama 4 veces por segundo
        void Render();//dibuja y actualiza las posiciones del interpolado

        void Pausar();
        void Reanudar();
        void Reiniciar();

        //Funciones propias
        void ValoresPorDefecto();
        void ValoresPorDefectoJugador();
        void ValoresPorDefectoBoss();
        void PosicionesIniEnemigos();
        void DesactivarDebug();
        void InteractuarNivel();

        bool CargarNivel(int nivel, int tipoJug); //Niveles en assets/maps/xml/
        void CrearJugador();//lo utilizamos para crear su objeto
        void CrearObjeto(int codigo, int accion, const char* nombre, int ataque, int rp, int x,int y,int z, int despX, int despZ, int ancho, int largo, int alto, const char* ruta_objeto, const char* ruta_textura, int* propiedades);//lo utilizamos para crear su modelo en motorgrafico y su objeto
        void cargarCofres(int num);  //Lo usamos para cargar los cofres en las distintas zonas de cofres
        void ConectarWaypoints();

        //Funciones de interacciones
        void CogerObjeto();
        void DejarObjeto();
        void AccionarMecanismo(int);    //Activa mecanismos y o puertas
        void crearObjetoCofre(Interactuable* );
        void activarPowerUp();

        void updateAtEsp();//se actualiza la ejecucion de los ataques
        void updateAt(int* );
        void updateRecorridoPathfinding(Enemigo* );

        void EraseEnemigo(std::size_t i);
        void enemDejarDePedirAyuda();
        Enemigo* getEnemigoPideAyuda();
        std::vector<Enemigo*> getEnemigos();
        Jugador* GetJugador(); // Por ahora solo se llama desde Pollo.cpp y Murcielago.cpp

    private:

        short auxiliarPathfinding = 0;
        MotorAudioSystem* _motora;
        SenseEventos* _sense;
        MotorFisicas* _fisicas;
        Times* _controladorTiempo;
        InterfazJugador* _interfaz;

        CargadorNiveles cargador;//nos ayuda a cargar los niveles

        bool enSalaBoss;
        Enemigo* _boss;
        std::vector<Enemigo*> _enemigos;//Enemigos en scena
        std::vector<Enemigo*> _auxiliadores;  //Enemigos que responden a la ayuda
        Enemigo* _enemPideAyuda;  //Enemigos que pide ayuda
        std::vector<Waypoint*> recorrido;//Nodos a recorrer en el pathfinding
        Sala* _destinoPathFinding; //sala que se rellena al llamar a pathfinding y se vacía al terminar el recorrido del enemigo

        std::vector<Recolectable*> _recolectables;
        std::vector<Interactuable*> _interactuables; //Objetos interactuables del mapa
        std::vector<Recolectable*> _powerup;
        std::vector<Zona*> _zonas; //Array de zonas
        std::vector<Waypoint*> _waypoints; //Vector de waypoints del nivel

        bool reiniciando; // Se utiliza solo en Reanudar por el cambio entre Estados
        Jugador* _jugador;
        bool jugadorInmovil; // Para las colisiones
        float drawTime, lastDrawTime;
        float atacktime; //tiempo de ejecucion del ataque
        float mov_weapon_posX,mov_weapon_posY,mov_weapon_posZ;
        float mov_weapon_rotX,mov_weapon_rotY,mov_weapon_rotZ;
        float proyectilFuera;

        int cambia;
        int danyo, danyo2;
        int contadorEnem;

        //Comprobacion de powerup
        //int powerupYES = -1; //no se utiliza
        int int_cpw_aux; //no repetir el mismo objeto si esta uno encima de otro


        // Variables temporales de Debug
        float* posCofre = new float[3];


        /* No se utilizan:
        float dt, lastUpdateTime, updateTime;
        float frameTime; // frameTime: tiempo por fotograma
        float acumulator;
        float lastAtackEsptime = 0.0f; //registro antiguo del tiempo de ataque especial para su animacion
        bool cogerObjeto = false;
        int objetoCogido = -1;
        */
};
#endif /* JUGANDO_HPP */
