#ifndef JUGANDO_HPP
#define JUGANDO_HPP

#include "../Estado.hpp"
#include "../Motores/SenseEventos.hpp"
#include "../CargadorNiveles.hpp"
#include "../CargadorPuzzles.hpp"
#include "../Times.hpp"
//#include "../Personajes/Jugador.hpp"
#include "../Enemigos/Enemigo.hpp"
//#include "../Objetos/Interactuable.hpp"
#include "../Objetos/Puerta.hpp"
#include "../Objetos/Palanca.hpp"
#include "../Objetos/Cofre.hpp"
#include "../Objetos/Recolectable.hpp"
#include "../Objetos/Pared.hpp"
#include "../Armas/Arma.hpp"
#include "../Jugando/InterfazJugador.hpp"
#include "ZonaRespawn.hpp"
#include "ZonaCofre.hpp"
#include "ZonaEscondite.hpp"
#include "ZonaOscura.hpp"
#include "Waypoint.hpp"

#include "../Pathfinder.hpp"
#include "../ConstantesComunes.hpp"

class Jugando: public Estado {
    public:
        Jugando(unsigned int nivel,unsigned int tipoJugador,unsigned int dinero, unsigned int slot);
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
        void EstPuzzle(bool ganar);

        //Funciones propias
        void ValoresPorDefecto();
        void ValoresPorDefectoJugador();
        void ValoresPorDefectoBoss();
        void PosicionesIniEnemigos();
        void DesactivarDebug();
        void InteractuarNivel();

        bool CargarNivel(int nivel, int tipoJug); //Niveles en assets/maps/xml/
        void CrearJugador();//lo utilizamos para crear su objeto
        unsigned short NumeroAleatorio(unsigned short limite_inf, unsigned short limite_sup);
        void CrearPowerUp(int x,int y,int z, unsigned short tipoObjeto,
            unsigned short cantidad);
        void CrearObjeto(int x,int y,int z,int ancho,int largo,int alto,
            unsigned short tipoObjeto, unsigned short ataque);//lo utilizamos para crear su modelo en motorgrafico y su objeto
        void RespawnEnemigos();
        void ConectarWaypoints();
        void CambiarSalaJugador(unsigned short i);
        void CambiarSalaEnemigo(unsigned short n, unsigned short m);

        //Funciones de interacciones
        void RecogerLlave(int rec_llave);
        void RecogerArma(int rec_col);
        void DejarObjeto();
        void ComprobarBorrarProyectil();
        void AccionarMecanismo(int,const unsigned short);    //Activa mecanismos y o puertas
        void activarPowerUp();

        void updateAtEsp();//se actualiza la ejecucion de los ataques
        void updateAt(int* );
        void updateRecorridoPathfinding(Enemigo* );

        void EraseEnemigo(std::size_t i);
        void enemDejarDePedirAyuda();
        Enemigo* getEnemigoPideAyuda();
        std::vector<Enemigo*> getEnemigos();
        Jugador* GetJugador(); // Por ahora solo se llama desde Pollo.cpp y Murcielago.cpp
        
        void AbrirPantallaPuzzle();
        void AbrirCofre(float x, float y, float z, bool esArana);
        void CrearEnemigoArana();
        void CargarBossEnMemoria();
        void CambiarAranyaPorCofre(int idC, float x,float y, float z, 
            unsigned int posArrayArana, unsigned int posAct, unsigned int posObs, Sala* sala);

    private:

        short auxiliarPathfinding = 0;
        MotorAudioSystem* _motora;
        SenseEventos* _sense;
        MotorFisicas* _fisicas;
        Times* _controladorTiempo;
        InterfazJugador* _interfaz;
        Constantes constantes;
        
        CargadorNiveles cargador;//nos ayuda a cargar los niveles
        CargadorPuzzles cargPuzzles; // contiene todos los puzzles
        Puzzle* _puzzle;

        bool enSalaBoss;
        bool lvDificil;         //Nivel de dificultad del juego. Se modifica cada minuto
        Enemigo* _boss;
        std::vector<Enemigo*> _enemigos;//Enemigos en scena
        std::vector<Enemigo*> _eneCofres;//Cofres arana desactivados
        unsigned short probArana; // Probabilidad de que salga cofre arana
        std::vector<Enemigo*> _auxiliadores;  //Enemigos que responden a la ayuda
        Enemigo* _enemPideAyuda;  //Enemigos que pide ayuda
        std::vector<Waypoint*> recorrido;//Nodos a recorrer en el pathfinding
        Sala* _destinoPathFinding; //sala que se rellena al llamar a pathfinding y se vacía al terminar el recorrido del enemigo

        std::vector<Recolectable*> _reco_armas;
        std::vector<Recolectable*> _llaves;
        std::vector<Pared*> _paredes;
        std::vector<Recolectable*> _powerup;
        std::vector<ZonaCofre*> _zonasCofre; //Array de zonas de cofres
        std::vector<ZonaRespawn*> _zonasRespawn; //Array de zonas de respawn
        std::vector<ZonaOscura*> _zonasOscuras; //Array de zonas de oscuras
        std::vector<ZonaEscondite*> _zonasEscondite; //Array de zonas de escondite
        std::vector<Waypoint*> _waypoints; //Vector de waypoints del nivel

        std::vector<Palanca*> _palancas;
        std::vector<Puerta*> _puertas;
        std::vector<Cofre*> _cofres;

        INnpc::VectorEspacial posicionMediaEnemigos;  //Posicion media que comparten los pollos que atacan en bandada
        
        bool reiniciando, puzzleResuelto; // Se utiliza solo en Reanudar por el cambio entre Estados
        bool ganarPuzzle;
        bool desactivarColisionesJugador;
        Cofre* _cofreP;

        Jugador* _jugador;
        bool jugadorInmovil; // Para las colisiones
        float drawTime, lastDrawTime, respawnTime, lastRespawnTime;
        float atacktime; //tiempo de ejecucion del ataque
        float mov_weapon_posX,mov_weapon_posY,mov_weapon_posZ;
        float mov_weapon_rotX,mov_weapon_rotY,mov_weapon_rotZ;
        float proyectilFuera;

        // TO DO: Cambia comentado porque ya se ha arreglado la entrada de inputs, quitar al asegurarnos
        //int cambia;
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

       //valores pasados por los estados del menu iniciar o continuar
       unsigned int nivelJ;
       unsigned int tipoJugadorJ;
       unsigned int dineroJ;
       unsigned int slotJ;
       
};
#endif /* JUGANDO_HPP */
