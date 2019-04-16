#ifndef MotorFisicas_HPP
#define MotorFisicas_CPP

#include "reactphysics3d.h"
#include <vector>
#include "math.h"
#include "../ConstantesComunes.hpp"

using namespace reactphysics3d;

    class MotorFisicas
    {
        public: //clases accesibles desde fuera
            //clase singleton en public
            ~MotorFisicas();
            static MotorFisicas* getInstance() //esto se utiliza para crear el objeto una sola vez
            {
                if(_unica_instancia == 0)
                    _unica_instancia = new MotorFisicas();
                return _unica_instancia;
            }
            //fin singleton public

            void crearCuerpo(int accion, float px, float py, float pz, int type, float ancho, float alto, float largo, int typeCreator, float despX, float despZ);// creamos un cuerpo con posiciones x,y,z , a continuacion a ese cuerpo se le agrega una forma de colision que es el type y las medidas
            unsigned short CrearCuerpoInter(unsigned short tipoObj, float px, float py, float pz, 
                float ancho, float alto, float largo, float despX, float despZ);
            unsigned short CrearCuerpoRec(int accion, float px, float py, float pz,
                float ancho, float alto, float largo, float despX, float despZ);
            unsigned short CrearCuerpoWaypoint(float px, float py, float pz, float alto);
            //int crearCuerpo(float px, float py, float pz, int type, float ancho, float largo, float alto);// creamos un cuerpo con posiciones x,y,z , a continuacion a ese cuerpo se le agrega una forma de colision que es el type y las medidas
            void actualizarPosicionCuerpo(float px, float py, float pz,int posicion);//se le pasa las nuevas posiciones del cuerpo del array de cuerpos de la posicion
            Ray* crearRayo(float x, float y, float z, float rotation, float longitud);//crea un rayo en esas posiciones con la longitud
            int* colisionRayoUnCuerpo(float x,float y,float z,float rotation, float longitud,int modo = 1);//colisiona con multiples objetos (modo 1 detecta colision con jugador solo, 2 detecta con objetos solo, 3 detecta con enemigos solo)

            void updateJugador(float x, float y, float z);//actualizamos al jugador en el espacio de las fisicas
            void updateEnemigos(float x, float y, float z, unsigned int i);//actualizamos al enemigo en el espacio de las fisicas
            void updatePuerta(float x, float y, float z, float rx, float ry, float rz, float despX, float despZ, unsigned int pos);
            void EraseObstaculo(int idx);
            void EraseColectable(int idx);
            void EraseWaypoint(unsigned short pos);
            void ErasePared(int idx);
            void EraseColectablePowerup(int idx);
            void EraseEnemigo(std::size_t i);
            void EraseTodosEnemigos(std::size_t i);
            void DesactivarCofre(unsigned short pos);
            void EraseJugador();
            void EraseArma();
            CollisionBody* getColectables(int n);
            CollisionBody* getObstacles(int n);
            bool CollidePlayerWaypoint(unsigned short n);
            bool CollideEnemiWaypoint(unsigned short n, unsigned short e);
            bool collideObstaculos();
            bool collideAtackObstacle();
            std::vector<short> collideAttackWall();
            bool collideObstacle();
            bool enemyCollideObstacle(unsigned int enemigo);
            bool collidePlatform();
            bool enemyCollidePlatform(unsigned int enemigo);
            int collideColectable();
            int collideColectablePowerup();
            
            short collidePuerta();
            short collidePalanca();
            short collideCofre();

            void colisionChecker(bool a, bool s, bool d, bool w, float x, float y, float z);
            void llevarBox(float x, float y, float z, float anc, float lar, float alt);
            void girarCamara();
            void updateJugador(float x, float y, float z, float rx, float ry, float rz);//actualizamos al jugador en el espacio de las fisicas
            std::vector <unsigned int> updateArmaEspecial(float x, float y, float z);
            std::vector<unsigned int> updateArma(float x, float y, float z);

            void updateAtaque(float x, float y, float z, float rx, float ry, float rz);
            void updateAtaqueEnemigos(float x, float y, float z, unsigned int i);
            void updateAtaquEspecEnemigos(float x, float y, float z, unsigned int i);

            void setFormaArma(float px, float py, float pz, int anc, int lar, int alt);
            void updateAtaqueEspecial(float x, float y, float z, float rx, float ry, float rz);
            void vaciarupdateArma();

            bool IfCollision(CollisionBody * body1, CollisionBody * body2);
            CollisionWorld* getWorld();
            CollisionBody* getJugador();
            CollisionBody* getEnemies(int n);
            CollisionBody* getEnemiesAtack(int n);
            CollisionBody* getEnemiesAtEsp(int n);
            CollisionBody* getAtack();
            CollisionBody* getColectablesPowerup(int n);
            unsigned int GetRelacionInteractuablesObstaculos(int n);
            unsigned int GetRelacionParedesObstaculos(int n);
            bool CamaraRotara();

            //para limpiar todas las fisicas
            void limpiarFisicas();

        private:
            //clase singleton
            MotorFisicas();
            static MotorFisicas* _unica_instancia;
            //fin clase singleton private

            WorldSettings config;
            CollisionWorld * space; //espacio o mundo de fisicas
            DynamicsWorld * world;

            std::vector<CollisionBody *> enemigos;//esto contiene por decirlo de alguna forma la instancia(alma) del cuerpo se les tiene que agregar las formas de colisiones(cuadrados,circulos o mallas personalizadas)
            std::vector<CollisionBody *> enemigosAtack; //ataque de enemigos
            std::vector<CollisionBody *> armaAtEspEne;//esto contiene por decirlo de alguna forma la instancia(alma) del cuerpo se les tiene que agregar las formas de colisiones(cuadrados,circulos o mallas personalizadas)
            CollisionBody * jugador;//esto contiene por decirlo de alguna forma la instancia(alma) del cuerpo se les tiene que agregar las formas de colisiones(cuadrados,circulos o mallas personalizadas)
            RigidBody * jugadorBody; //esto es para que el jugador colisiones con las puertas y funcione los joints

            std::vector<CollisionBody *> recolectables;//Vector de elementos que se pueden coger
            std::vector<CollisionBody *> recolectables_powerup;//Vector recolectables_powerup
            
            //std::vector<float> interAncho;//Vector de elementos con los que interactuar
           // std::vector<float> interLargo;//Vector de elementos con los que interactuar
            //Vectores con los tres tipos de objetos con los que el jugador puede interactuar
            std::vector<CollisionBody *> _puertas;
            std::vector<CollisionBody *> _palancas;
            std::vector<CollisionBody *> _cofres;

            std::vector<unsigned int> relacionInteractuablesObstaculos;//vector que contiene en la posicion correspondiente a un interactuable en su vector el valor de su posicion en el vector de obstaculos
            std::vector<unsigned int> relacionParedesObstaculos;//vector que contiene en la posicion correspondiente a una pared en su vector el valor de su posicion en el vector de obstaculos
            std::vector<CollisionBody *> obstaculos;//Vector de obstaculos que bloquean el movimiento
            std::vector<CollisionBody *> paredes;//Vector de obstaculos que no son palancas o puertas
            std::vector<CollisionBody *> plataformas;//Vector de plataformas para caminar
            std::vector<CollisionBody *> paredeInvisiblesCamara; //Vector con las paredes invisibles que cambian la camara
            std::vector<CollisionBody *> _waypoints; //Vector con los waypoints para detectar cuando el jugador o los enemigos merodeando cambian de sala
            std::vector<rp3d::Transform> prevTransform;

            CollisionBody * armaAtEsp;//esto contiene por decirlo de alguna forma la instancia(alma) del cuerpo se les tiene que agregar las formas de colisiones(cuadrados,circulos o mallas personalizadas)
            CollisionBody * jugadorAtack; //contiene el ataque normal del jugador
            CollisionBody * arma;//arma normal del jugador
            long double accumulator = 0;
            long double previousFrameTime;

            //las siguientes variables son para movimiento, colisiones y giro de camara
            float ax = 1.0f, az = 20.0f, deg;
            int gcam = 0;
            
            Constantes constantes;

            // Ya no utilizar - MI
            //std::vector<CollisionBody *> objetos;
    };

#endif
