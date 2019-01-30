#ifndef Interactuable_HPP
#define Interactuable_HPP
#include "INobjetos.hpp"
#include "INdrawable.hpp"

using namespace std;

//aqui definimos la clase del elemento interactuable con herencia de la interfaz INobjeto y INdrawable
class Interactuable : public INobjetos , public INdrawable //multiple herencia a esto se le llama derivacion multiple
{
    public:
        Interactuable();         //esto le deja a la entidad el constructor por defecto
        Interactuable(int codigo, const char * nombre, int anc, int lar, int alt, const char *objeto, const char *textura, int posicion);
        ~Interactuable();

        //metodos de interaccion
        bool accionar();
        
        //drawable metodos
        void moverseEntidad(float);//Realiza el desplazamiento mediante la interpolacion
        void RotarEntidad(float);//Realiza la rotacion mediante la interpolacion
        void UpdateTimeMove(float time);//actualiza el tiempo del movimiento de la interpolacion
        void UpdateTimeRotate(float time);//actualiza el tiempo de la rotacion de la interpolacion

        void setPosiciones(float nx,float ny,float nz);
        void setNewPosiciones(float nx,float ny,float nz);//modifica las posiciones finales de la interpolacion de la figura
        void setLastPosiciones(float nx,float ny,float nz);
        void setDesplazamientos(float despX, float despZ);
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
        float * GetDesplazamientos();
        float getRX();
        float getRY();
        float getRZ();

        //getters del propio objeto
        int GetPosicionArrayObjetos();
        int getCodigo();
        const char* getNombre();
        const char* getObjeto();
        const char* getTextura();
        float getAncho();
        float getLargo();
        float getAlto();
        int GetPosicionObjetos();


    private: 

        //Si codigoObjeto es > 0 es un numero comun entre dos objetos: una palanca con el mismo numero que una puerta abre dicha puerta
        int codigoObjeto;   //En caso de igualarse a 0 es una puerta sin llave, y si es -1 es un cofre
        bool accionado;     //Dado que son objetos accionables tendra dos estado segun este accionado o no
        int posicionArrayObjetos; //Posicion del elemento en el vector de objetos del motor grafico.
        float * desplazamientos = new float [2];   //Desplazamientos en X y en Z para le giro de la puerta
        
};

#endif /* Interactuable_HPP */