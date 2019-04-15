#ifndef Arma_HPP
#define Arma_HPP
#include <iostream>
#include "../Motores/INobjetos.hpp"
#include "../Motores/INdrawable.hpp"
#include "../ConstantesComunes.hpp"

using namespace std;

//aqui definimos la clase del jugador con herencia de la interfaz INnpc
class Arma : public INobjetos , public INdrawable //multiple herencia a esto se le llama derivacion multiple
{
    public:
        Arma();         //esto le deja a la entidad el constructor por defecto
        Arma(int ataque, int anc, int lar, int alt, unsigned short tipoObj);
        ~Arma();

        //drawable metodos
        void moverseEntidad(float);//Realiza el desplazamiento mediante la interpolacion
        void RotarEntidad(float);//Realiza la rotacion mediante la interpolacion
        void UpdateTimeMove(float time);//actualiza el tiempo del movimiento de la interpolacion

        void setPosiciones(float nx,float ny,float nz);
        void setPosicionesArmaEsp(float nx,float ny,float nz, float ry);
        void setNewPosiciones(float nx,float ny,float nz);
        void setLastPosiciones(float nx,float ny,float nz);
        void setRotacion(float nrx, float nry, float nrz);
        void setNewRotacion(float nrx, float nry, float nrz);
        void setLastRotacion(float nrx, float nry, float nrz);
        void setPosicionesFisicas(float nx,float ny,float nz);
        void initPosicionesFisicas(float nx,float ny,float nz);

        //setters
        void setAtaque(int);
        //void getPosiciones();

        //getters
        int getAtaque();
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
        float getIniX();
        float getIniY();
        float getIniZ();
        float getFisX();
        float getFisY();
        float getFisZ();
        float getRX();
        float getRY();
        float getRZ();
        float getAncho();
        float getLargo();
        float getAlto();
        const char* GetModelo(); // Malla 3D con la textura
        const char* GetTextura();
        unsigned short GetTipoObjeto();

    private:
        int potenciaAtaque;
        Constantes constantes;
};

#endif /* Arma_HPP */
