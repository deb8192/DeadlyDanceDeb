#ifndef MotorFisicas_HPP
#define MotorFisicas_CPP


#include "reactphysics3d.h"
#include <vector>

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

            void crearCuerpo(float px, float py, float pz, int type, float ancho, float largo, float alto);// creamos un cuerpo con posiciones x,y,z , a continuacion a ese cuerpo se le agrega una forma de colision que es el type y las medidas
            //int crearCuerpo(float px, float py, float pz, int type, float ancho, float largo, float alto);// creamos un cuerpo con posiciones x,y,z , a continuacion a ese cuerpo se le agrega una forma de colision que es el type y las medidas
            void actualizarPosicionCuerpo(float px, float py, float pz,int posicion);//se le pasa las nuevas posiciones del cuerpo del array de cuerpos de la posicion
            Ray * crearRayo(float x, float y, float z, float longitud);//crea un rayo en esas posiciones con la longitud
            void comprobarColision();
        private:
            //clase singleton 
            MotorFisicas();
            static MotorFisicas* unica_instancia;
            //fin clase singleton private
            WorldSettings config;
            CollisionWorld * space; //espacio o mundo de fisicas
            std::vector<CollisionBody *> cuerpos;//esto contiene por decirlo de alguna forma la instancia(alma) del cuerpo se les tiene que agregar las formas de colisiones(cuadrados,circulos o mallas personalizadas)
    };

#endif