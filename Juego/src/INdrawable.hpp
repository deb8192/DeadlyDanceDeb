#ifndef INdrawable_HPP
#define INdrawable_HPP
#include <iostream>

using namespace std;

//aqui definimos la clase interfaz de los objetos o entidades que se pinten (clases no abstractas)
class INdrawable
{

public:
    // Estructura con el alias "Posiciones"
    typedef struct {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
    } Posiciones;

    virtual void moverseEntidad(float)=0;//Realiza el desplazamiento mediante la interpolacion
    virtual void RotarEntidad(float)=0;//Realiza la rotacion mediante la interpolacion
    virtual void UpdateTimeMove(float time)=0;//actualiza el tiempo del movimiento de la interpolacion

    virtual void setPosiciones(float nx,float ny,float nz)=0;//modifica las posiciones de la figura
    virtual void setNewPosiciones(float nx,float ny,float nz)=0;//modifica las posiciones finales de la interpolacion de la figura
    virtual void setLastPosiciones(float nx,float ny,float nz)=0;//modifica las posiciones antiguas de la interpolacion de la figura
    virtual void setPosicionesFisicas(float nx,float ny,float nz)=0;//modifica las posiciones de las fisicas
    virtual void setRotacion(float nrx, float nry, float nrz)=0;//Modifica la rotacion de la figura
    virtual void setNewRotacion(float nrx, float nry, float nrz)=0;//modifica la rotaciones finales de la interpolacion de la figura
    virtual void setLastRotacion(float nrx, float nry, float nrz)=0;//modifica las rotaciones amtiguas de la interpolacion de la figura
    virtual void initPosicionesFisicas(float nx,float ny,float nz)=0;//inicializa las fisicas
    virtual void setID(int)=0;//nos sirve para definir el id que tiene esta figura
    virtual int getID()=0;//nos sirve para saber que id tiene esta figura

    virtual float getX()=0;
    virtual float getY()=0;
    virtual float getZ()=0;
    virtual float getNewX()=0;
    virtual float getNewY()=0;
    virtual float getNewZ()=0;
    virtual float getLastX()=0;
    virtual float getLastY()=0;
    virtual float getLastZ()=0;
    virtual float getFisX()=0;
    virtual float getFisY()=0;
    virtual float getFisZ()=0;
    virtual float getRX()=0;
    virtual float getRY()=0;
    virtual float getRZ()=0;
    //virtual int getAnimacion(); //no lo pongo porque lo tendria que definir en todo

/*el protected es para que tenga acceso sus descendientes o parientes*/
protected:
    //posiciones del objeto drawable
    Posiciones posActual;
    Posiciones posPasada; //Posiciones antiguas de la interpolacion
    Posiciones posFutura; //Posiciones finales de la interpolacion
    Posiciones posFisicas; //Posicion para colocar las fisicas de los objetos

    Posiciones rotActual;  //Rotacion
    Posiciones rotPasada;
    Posiciones rotFutura;
    
    float moveTime, rotateTime; //variables para controlar la interpolacion del movimiento y la rotacion;
    float rotation = 0.0f; //en grados por defecto
    int id = -1;
    int animacion = 0;  //nos sirve para cambiar de animacion //por defecto en reposo
    int animacionAnterior = 0; //nos sirve para saber si debemos cambiar de animacion por la nueva
    //fin posiciones
};

#endif /* INdrawable_HPP */