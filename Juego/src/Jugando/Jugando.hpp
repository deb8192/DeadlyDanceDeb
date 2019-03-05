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
#include "Zona.hpp"
#include "../Armas/Arma.hpp"
#include "../Jugando/InterfazJugador.hpp"

//cargaremos el arbol(ia) desde nivel y se lo pasaremos a su entidad correspondiente, el enemigo la activa llamando a enemigo->runIA()
#include "../CargadorBehaviorTrees.hpp"
#include "../Pathfinder.hpp"

//#include <list>

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
        void PosicionesIniEnemigos();
        void DesactivarDebug();
        void InteractuarNivel();

        bool CargarNivel(int nivel, int tipoJug); //Niveles en assets/maps/xml/
        void CrearJugador();//lo utilizamos para crear su objeto
        void CrearObjeto(int codigo, int accion, const char* nombre, int ataque, int rp, int x,int y,int z, int despX, int despZ, int ancho, int largo, int alto, const char* ruta_objeto, const char* ruta_textura, int* propiedades);//lo utilizamos para crear su modelo en motorgrafico y su objeto
        void cargarCofres(int num);

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
        void setEnemigoPideAyuda(Enemigo* );
        Enemigo* getEnemigoPideAyuda();
        std::vector<Enemigo*> getEnemigos();
        Jugador* GetJugador(); // Por ahora solo se llama desde Pollo.cpp y Murcielago.cpp

    private:

        MotorAudioSystem* _motora;
        SenseEventos* _sense;
        MotorFisicas* _fisicas;
        Times* _controladorTiempo;
        InterfazJugador* _interfaz;

        CargadorNiveles cargador;//nos ayuda a cargar los niveles
        CargadorBehaviorTrees cargadorIA; //Variable para crear la IA de los enemigos
        
        Sala* _primeraSala;// la primera sala del arbol
        
        //TO DO: hacerle un reserve y q el vector sea un puntero
        std::vector<Enemigo*> _enemigos;//Enemigos en scena
        std::vector<Enemigo*> _auxiliadores;  //Enemigos que responden a la ayuda
        Enemigo* _enemPideAyuda;  //Enemigos que pide ayuda
        std::vector<Pathfinder::NodeRecord> recorrido;//Nodos a recorrer en el pathfinding
        Sala* _destinoPathFinding; //sala que se rellena al llamar a pathfinding y se vacía al terminar el recorrido del enemigo
        
        std::vector<Recolectable*> _recolectables;
        std::vector<Interactuable*> _interactuables; //Objetos interactuables del mapa
         std::vector<Recolectable*> _powerup;
        std::vector<Zona*> _zonas; //Array de zonas

        bool reiniciando; // Se utiliza solo en Reanudar por el cambio entre Estados
        Jugador* _jugador;
        bool jugadorInmovil; // Para las colisiones
        float drawTime, lastDrawTime;
        float atacktime; //tiempo de ejecucion del ataque

        int id;//id para las figuras

        int cambia;
        int danyo, danyo2;
        int contadorEnem;

        //Comprobacion de powerup
        //int powerupYES = -1; //no se utiliza
        int int_cpw_aux; //no repetir el mismo objeto si esta uno encima de otro

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