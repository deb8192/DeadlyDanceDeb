#ifndef Pared_HPP
#define Pared_HPP
#include "../Motores/INobjetos.hpp"
#include "../Motores/INdrawable.hpp"
#include "../Motores/MotorGrafico.hpp"

using namespace std;

//aqui definimos la clase del elemento Pared con herencia de la interfaz INobjeto y INdrawable
class Pared : public INobjetos , public INdrawable //multiple herencia a esto se le llama derivacion multiple
{
    public:
        Pared(const char* nombre, int anc, int lar, int alt,
            float x, float y, float z, unsigned short tipoObj);
        
        ~Pared();
        
        //drawable metodos
        void moverseEntidad(float);//Realiza el desplazamiento mediante la interpolacion
        void RotarEntidad(float);//Realiza la rotacion mediante la interpolacion
        void UpdateTimeMove(float time);//actualiza el tiempo del movimiento de la interpolacion
        void UpdateTimeRotate(float time);//actualiza el tiempo de la rotacion de la interpolacion

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
        float getIniX();
        float getIniY();
        float getIniZ();
        float getFisX();
        float getFisY();
        float getFisZ();
        float getRX();
        float getRY();
        float getRZ();

        //getters del propio objeto
        int GetPosicionArrayObjetos();
        float getAncho();
        float getLargo();
        float getAlto();
        //void Render(float updTime, float drawTime);
        const char* GetModelo(); // Malla 3D con la textura
        unsigned short GetTipoObjeto();

    protected:
        
        //TO DO creo que tam se deberia de borrar
        unsigned short tam;
        int posicionArrayObjetos; //Posicion del elemento en el vector de objetos del motor grafico.
        
};

#endif /* Pared_HPP */
