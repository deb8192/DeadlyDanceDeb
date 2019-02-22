#include "TCamara.hpp"

//constructor y destructor
TCamara::TCamara()
{
    didentidad = 'C'; //para sabe que funcion hace
}

TCamara::~TCamara()
{

}

//gestion de propiedades
void TCamara::setPerspectiva()
{

}

void TCamara::setParalela()
{

}

void TCamara::beginDraw()
{
    //comprobamos que la cola o pila no haya tenido cambios, si los tiene se vuelve a calcular 
    if(matriz_compartida == nullptr)
    {
        glm::mat4 * _matriz_resultado = nullptr;
        std::queue<glm::mat4 *> * cola_compartidaAuxiliar = new std::queue<glm::mat4 *>; //creamos una cola nueva para ir encolando  los elementos que desencolamos de la cola compartida(se aplicaria parecido con una pila)
        while(cola_compartida->size() > 0)
        {
            
            glm::mat4 * nodo = cola_compartida->front();
            cola_compartidaAuxiliar->push(nodo);
            //cogemos el primer valor de la pila
            if(_matriz_resultado == nullptr)
            {
                _matriz_resultado = new glm::mat4;
                *_matriz_resultado = *nodo;
            }
            else
            {
                *_matriz_resultado = (*_matriz_resultado) * (*nodo);
            }

            cola_compartida->pop();
        }

        delete cola_compartida;//borramos la cola anterior porque esta vacia
        cola_compartida = cola_compartidaAuxiliar;//ponemos la nueva cola que tiene los elementos situados como la anterior

        if(_matriz_resultado != nullptr)//si la matriz de resultado es nula es que no hay nada en la cola por lo que no hay nada que enviar al shader
        {
            //enviar a uniform
            std::cout << (*_matriz_resultado)[0][0] << " " << (*_matriz_resultado)[1][1] << " " << (*_matriz_resultado)[2][2] << " " << (*_matriz_resultado)[3][3] << std::endl;
        }    
    }
    else
    {
        //se le da al uniform
    }
    
}

void TCamara::endDraw()
{

}
