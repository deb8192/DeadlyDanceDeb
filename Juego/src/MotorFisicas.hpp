#ifndef MotorFisicas_HPP
#define MotorFisicas_CPP


#include "reactphysics3d.h"
#include <vector>
#include "math.h"

using namespace reactphysics3d;

    class MotorFisicas
    {
        public: //clases accesibles desde fuera
            //clase singleton en public
            ~MotorFisicas(void);
            static MotorFisicas *getInstance() //esto se utiliza para crear el objeto una sola vez
            {
                if(unica_instancia == 0)
                unica_instancia = new MotorFisicas();
                return unica_instancia;
            }
            //fin singleton public

            void crearCuerpo(int accion, float px, float py, float pz, int type, float ancho, float alto, float largo, int typeCreator);// creamos un cuerpo con posiciones x,y,z , a continuacion a ese cuerpo se le agrega una forma de colision que es el type y las medidas
            //int crearCuerpo(float px, float py, float pz, int type, float ancho, float largo, float alto);// creamos un cuerpo con posiciones x,y,z , a continuacion a ese cuerpo se le agrega una forma de colision que es el type y las medidas
            void actualizarPosicionCuerpo(float px, float py, float pz,int posicion);//se le pasa las nuevas posiciones del cuerpo del array de cuerpos de la posicion
            Ray * crearRayo(float x, float y, float z, float rotation, float longitud);//crea un rayo en esas posiciones con la longitud
            int * colisionRayoUnCuerpo(float x,float y,float z,float rotation, float longitud,int modo = 1);//colisiona con multiples objetos (modo 1 detecta colision con jugador solo, 2 detecta con objetos solo, 3 detecta con enemigos solo)

            void updateJugador(float x, float y, float z);//actualizamos al jugador en el espacio de las fisicas
            void updateEnemigos(float x, float y, float z, unsigned int i);//actualizamos al enemigo en el espacio de las fisicas
            void EraseColectable(int idx);
            void EraseEnemigo(std::size_t i);
            void EraseJugador();
            void EraseArma();
            CollisionBody* getColectables(int n);
            CollisionBody* getObstacles(int n);
            bool collideObstacle();
            bool collidePlatform();
            int collideColectable();
            int collideInteractuable();
            void colisionChecker(bool a, bool s, bool d, bool w, float x, float y, float z);
            void llevarBox(float x, float y, float z, float anc, float lar, float alt);

            void updateJugador(float x, float y, float z, float rx, float ry, float rz);//actualizamos al jugador en el espacio de las fisicas
            std::vector <unsigned int> updateArmaEspecial(float x, float y, float z);
            std::vector<unsigned int> updateArma(float x, float y, float z);
            void updateAtaque(float x, float y, float z, float rx, float ry, float rz);
            void updateAtaqueEnemigos(float x, float y, float z, unsigned int i);
            void updateAtaquEspecEnemigos(float x, float y, float z, unsigned int i);

            void setFormaArma(float px, float py, float pz, int anc, int lar, int alt);
            void setFormaRecolectable(int id, float px, float py, float pz, int anc, int lar, int alt);
            void updateAtaqueEspecial(float x, float y, float z, float rx, float ry, float rz);
            void vaciarupdateArma();

            bool IfCollision(CollisionBody * body1, CollisionBody * body2);
            CollisionWorld* getWorld();
            CollisionBody* getJugador();
            CollisionBody* getEnemies(int n);
            CollisionBody* getEnemiesAtack(int n);
            CollisionBody* getEnemiesAtEsp(int n);
            CollisionBody* getAtack();

        private:
            //clase singleton
            MotorFisicas();
            static MotorFisicas* unica_instancia;
            //fin clase singleton private
            WorldSettings config;
            CollisionWorld * space; //espacio o mundo de fisicas
            std::vector<CollisionBody *> enemigos;//esto contiene por decirlo de alguna forma la instancia(alma) del cuerpo se les tiene que agregar las formas de colisiones(cuadrados,circulos o mallas personalizadas)
            std::vector<CollisionBody *> enemigosAtack; //ataque de enemigos
            std::vector<CollisionBody *> armaAtEspEne;//esto contiene por decirlo de alguna forma la instancia(alma) del cuerpo se les tiene que agregar las formas de colisiones(cuadrados,circulos o mallas personalizadas)
            CollisionBody * jugador;//esto contiene por decirlo de alguna forma la instancia(alma) del cuerpo se les tiene que agregar las formas de colisiones(cuadrados,circulos o mallas personalizadas)

            std::vector<CollisionBody *> recolectables;//Vector de elementos que se pueden coger
            std::vector<CollisionBody *> interactuables;//Vector de elementos con los que interactuar
            std::vector<CollisionBody *> obstaculos;//Vector de obstaculos que bloquean el movimiento
            std::vector<CollisionBody *> plataformas;//Vector de plataformas para caminar

            CollisionBody * armaAtEsp;//esto contiene por decirlo de alguna forma la instancia(alma) del cuerpo se les tiene que agregar las formas de colisiones(cuadrados,circulos o mallas personalizadas)
            CollisionBody* jugadorAtack; //contiene el ataque normal del jugador
            CollisionBody * arma;//arma normal del jugador

            std::vector<CollisionBody *> objetos;

    };

#endif
