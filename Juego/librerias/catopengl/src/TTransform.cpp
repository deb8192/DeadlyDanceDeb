#include "TTransform.hpp"


TTransform::TTransform()
{
    matriz = new glm::mat4(1.0f);
    didentidad = 'T'; //para sabe que funcion hace
}

TTransform::~TTransform()
{
    if(matriz)
    {
        delete matriz;
    }
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
    *matriz = glm::translate(*matriz, glm::vec3(x,y,-z));
}

void TTransform::rotar(float gx,float gy,float gz)
{
    if(gx != 0.0f)gx+=180.0f;
    identidad();
    *matriz = glm::rotate(*matriz, glm::radians(gx), glm::vec3(1,0,0));
    *matriz = glm::rotate(*matriz, glm::radians(gy), glm::vec3(0,1,0));
    *matriz = glm::rotate(*matriz, glm::radians(gz), glm::vec3(0,0,1));
    trasponer();
}

void TTransform::escalar(float x,float y,float z)
{
    identidad();
    *matriz = glm::scale(*matriz, glm::vec3(x,y,z));
}

void TTransform::beginDraw()
{
    matriz_compartida = nullptr;

    //std::cout << " p " <<  pila_compartida->size() << std::endl;
    TEntidad::pila_compartida->push(matriz);
    //std::cout << " c " <<  cola_compartida->size() << std::endl;
    TEntidad::cola_compartida->push(matriz);
}

//Uso: desapila
void TTransform::endDraw()
{
    matriz_compartida = nullptr;

    if(pila_compartida->size() > 0)
    {
        //std::cout << " p " <<  pila_compartida->size() << std::endl;
        TEntidad::pila_compartida->pop();
    }

    if(cola_compartida->size() > 0)
    {
        //std::cout << " c " << cola_compartida->size() << std::endl;
        TEntidad::cola_compartida->pop();
    }
}

float * TTransform::GetPosicion()
{
    float * array = new float[3];
    array[0] = (*matriz)[3][0];
    array[1] = (*matriz)[3][1];
    array[2] = (*matriz)[3][2];
    return array;
}
