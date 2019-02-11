#include "TTransform.hpp"


TTransform::TTransform()
{
    didentidad = 'T'; //para sabe que funcion hace
}

TTransform::~TTransform()
{

}

void TTransform::remove()
{
    this->~TTransform();
}

void TTransform::identidad()
{
    matriz = glm::mat4(1.0f);
}

void TTransform::cargar(glm::mat4 newmat)
{
    matriz = newmat;
}

void TTransform::trasponer()
{
    matriz = glm::transpose(matriz);
}

void TTransform::invertir()
{
    matriz = glm::inverse(matriz);
}

void TTransform::multiplicarVector(glm::vec4 newvec)
{

}

void TTransform::multiplicarMatriz(glm::mat4 newmat)
{

}

void TTransform::trasladar(float x,float y,float z)
{
    matriz = glm::translate(matriz, glm::vec3(x,y,z));
}

void TTransform::rotar(float g,float x,float y,float z)
{
    matriz = glm::rotate(matriz, glm::radians(g), glm::vec3(x,y,z));
}

void TTransform::escalar(float x,float y,float z)
{
    matriz = glm::scale(matriz, glm::vec3(x,y,z));
}

void TTransform::beginDraw()
{
    std::cout << didentidad << std::endl;
}

void TTransform::endDraw()
{

}
