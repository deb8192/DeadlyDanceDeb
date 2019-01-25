#ifndef Recolectable_HPP
#define Recolectable_HPP
#include <iostream>
#include "INobjetos.hpp"
#include "INdrawable.hpp"
//#include "MotorGrafico.hpp"

using namespace std;

//aqui definimos la clase del jugador con herencia de la interfaz INnpc
class Recolectable : public INobjetos , public INdrawable //multiple herencia a esto se le llama derivacion multiple
{
    public:
        Recolectable();         //esto le deja a la entidad el constructor por defecto
        Recolectable(int codigo, int ataque, const char *nombre, int anc, int lar, int alt, const char *objeto, const char *textura);
        ~Recolectable();
        
        //drawable metodos
        void moverseEntidad(float);//Realiza el desplazamiento mediante la interpolacion
        void RotarEntidad(float);//Realiza la rotacion mediante la interpolacion
        void UpdateTimeMove(float time);//actualiza el tiempo del movimiento de la interpolacion
        
        //setters & getters
        void setPosiciones(float nx,float ny,float nz);
        void setNewPosiciones(float nx,float ny,float nz);//modifica las posiciones finales de la interpolacion de la figura
        void setLastPosiciones(float nx,float ny,float nz);
        void setRotacion(float nrx, float nry, float nrz);
        void setNewRotacion(float nrx, float nry, float nrz);
        void setLastRotacion(float nrx, float nry, float nrz);
        void setPosicionesFisicas(float nx,float ny,float nz);
        void initPosicionesFisicas(float nx,float ny,float nz);
        void SetPosicionArrayObjetos(int posicionObjeto);

        void setID(int);
        int getID();

        float getX();
        float getY();
        float getZ();
        float getNewX();
        float getNewY();
        float getNewZ();
        float getLastX();
        float getLastY();
        float getLastZ();
        float getFisX();
        float getFisY();
        float getFisZ();
        float getRX();
        float getRY();
        float getRZ();

        int GetPosicionArrayObjetos();
        int getCodigo();
        int getAtaque();
        const char* getNombre();
        const char* getObjeto();
        const char* getTextura();
        float getAncho();
        float getLargo();
        float getAlto();


    private: 

        //creo que lo mejor esque el objeto que recojas tenga ya su valor de daño
        int potenciaAtaque;
        //En caso de ser una llave, deberá tener un codigo mayor de 0
        int codigoObjeto;   //En caso de igualarse a 0 es un arma, si es -1 es diner y si es -2 es un power-up
        int posicionArrayObjetos;   //Posicion del recolectable en el array de objetos del nivel
};

#endif /* Recolectable_HPP */