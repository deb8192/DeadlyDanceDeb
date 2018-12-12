#ifndef INdrawable_HPP
#define INdrawable_HPP
#include <iostream>

using namespace std;

//aqui definimos la clase interfaz de los objetos o entidades que se pinten (clases no abstractas)
class INdrawable
{

public:
     virtual ~INdrawable(){};
     
     virtual void setPosiciones(int nx,int ny,int nz){x=nx;y=ny;z=nz;};
     virtual void setID(int id){ ID = id; }

     virtual int getID() { return ID; } 

/*el protected es para que tenga acceso sus descendientes o parientes*/
protected:

    //Provisional
    int ID; //ID de la entidad
    //!Provisional
    //posiciones del objeto drawable
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float rx = 0.0f;
    float ry = 0.0f;
    float rz = 0.0f; 
    //fin posiciones
};

#endif /* INdrawable_HPP */