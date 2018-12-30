#ifndef INdrawable_HPP
#define INdrawable_HPP
#include <iostream>

using namespace std;

//aqui definimos la clase interfaz de los objetos o entidades que se pinten (clases no abstractas)
class INdrawable
{

public:
    virtual void setPosiciones(int nx,int ny,int nz)=0;//modifica las posiciones de la figura
    virtual void setID(int)=0;//nos sirve para definir el id que tiene esta figura
    virtual int getID()=0;//nos sirve para saber que id tiene esta figura
/*el protected es para que tenga acceso sus descendientes o parientes*/
protected:
    //posiciones del objeto drawable
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float rx = 0.0f;
    float ry = 0.0f;
    float rz = 0.0f; 
    float rotation = 90.0f;//en grados por defecto
    int id = -1;
    //fin posiciones
};

#endif /* INdrawable_HPP */