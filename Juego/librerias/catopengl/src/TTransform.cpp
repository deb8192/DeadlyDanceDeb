#include "TTransform.hpp"


TTransform::TTransform()
{
    matriz = new glm::mat4(1.0f);
    didentidad = 'T'; //para sabe que funcion hace
}

TTransform::~TTransform()
{

}

void TTransform::identidad()
{
   *matriz = glm::mat4(1.0f);
}

void TTransform::cargar(glm::mat4 * newmat)
{
    matriz = newmat;
}

void TTransform::trasponer()
{
    *matriz = glm::transpose(*matriz);
}

void TTransform::invertir()
{
    *matriz = glm::inverse(*matriz);
}

void TTransform::trasladar(float x,float y,float z)
{                  
    identidad();                                                                  
    *matriz = glm::translate(*matriz, glm::vec3(x,y,z));
}

//
void TTransform::rotar(float g,float x,float y,float z)
{
    identidad();
    *matriz = glm::rotate(*matriz, glm::radians(g), glm::vec3(x,y,z));
}

void TTransform::escalar(float x,float y,float z)
{
    identidad();
    *matriz = glm::scale(*matriz, glm::vec3(x,y,z));
}

void TTransform::beginDraw()
{
    std::cout << didentidad << " se debe pintar-> " << pila_compartida->size() << std::endl;
    TEntidad::pila_compartida->push(matriz);
}

//Uso: desapila 
void TTransform::endDraw()
{  
    if(pila_compartida->size() > 0)
    {
        TEntidad::pila_compartida->pop();
    }
}