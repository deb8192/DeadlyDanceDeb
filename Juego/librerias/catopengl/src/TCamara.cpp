#include "TCamara.hpp"

//constructor y destructor
TCamara::TCamara()
{
    didentidad = 'C'; //para sabe que funcion hace
    //valores por defecto
    esPerspectiva = true;
    cercano=0.1f;
    lejano=100.0f;
    height=600.0f;
    width=800.0f;
    setTarget(0.0f,0.0f,0.0f);
    setUp(0.0f,1.0f,0.0f);
    setPerspectiva();
}

TCamara::~TCamara()
{

}

//gestion de propiedades
void TCamara::setPerspectiva()
{
    projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f),width/height,cercano,lejano);
}

void TCamara::setParalela()
{
    projection = glm::mat4(1.0f);
    projection = glm::ortho(0.0f, width, height, 0.0f, cercano,lejano);
}

void TCamara::beginDraw()
{
    //comprobamos que la cola o pila no haya tenido cambios, si los tiene se vuelve a calcular
    if(matriz_compartida == nullptr)
    {
        glm::vec3 posicion;
        glm::mat4 rotacion;
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
                if(cola_compartida->size() == 1)//traslacion
                {
                    posicion = glm::vec3((*nodo)[3][0],(*nodo)[3][1],(*nodo)[3][2]);
                }

                if(cola_compartida->size() == 2)
                {
                    rotacion = (*nodo);
                }

                *_matriz_resultado = (*_matriz_resultado) * (*nodo);
            }

            cola_compartida->pop();
        }

        delete cola_compartida;//borramos la cola anterior porque esta vacia
        cola_compartida = cola_compartidaAuxiliar;//ponemos la nueva cola que tiene los elementos situados como la anterior

        //Funcion lookAt, calculo de la matriz final
        glm::mat4 view;

        view = glm::lookAt(posicion,cameraTarget,cameraUp);    //lookAt(Posicion, Objetivo, Up Axis)

        view = view * rotacion; //aplicamos la rotacion a la matriz de la vista

        shader->Use();//preparamos el shader

        //posicion de la camara al shader
        shader->setVec3("viewPos", posicion);
        //enviamos projection
        shader->setMat4("projection",projection);
        //enviamos view
        shader->setMat4("view", view);

        if(_matriz_resultado != nullptr)//si la matriz de resultado es nula es que no hay nada en la cola por lo que no hay nada que enviar al shader
        {
            //enviar a uniform
            //std::cout << (*_matriz_resultado)[3][0] << " " << (*_matriz_resultado)[3][1] << " " << (*_matriz_resultado)[3][2] << " " << (*_matriz_resultado)[3][3] << std::endl;
        }
    }
    else
    {
        //Funcion lookAt, calculo de la matriz final
        glm::mat4 view;

        view = glm::lookAt(glm::vec3(10.0f,0.0f,0.0f),cameraTarget,cameraUp);    //lookAt(Posicion, Objetivo, Up Axis)

        shader->Use();//preparamos el shader

        //enviamos projection
        shader->setMat4("projection",projection);
        //enviamos view
        shader->setMat4("view", view);
        //se le da al uniform
    }

}

void TCamara::endDraw()
{

}

void TCamara::setCercano(float newCercano)
{
    cercano = newCercano;
}

void TCamara::setLejano(float newLejano)
{
    lejano = newLejano;
}

void TCamara::setPantalla(float newWidth,float newHeight)
{
    width = newWidth;
    height = newHeight;
}

void TCamara::setTarget(float x, float y, float z)
{
    cameraTarget = glm::vec3(x, y, z);//Objetivo donde apunta la camara, en este caso al origen
}

void TCamara::setUp(float x,float y, float z)
{
    cameraUp = glm::vec3(x, y, z);//Up Axis
}

void TCamara::DesactivarPerspectiva()
{
    esPerspectiva = false;
}

void TCamara::ActivarPerspectiva()
{
    esPerspectiva = true;
}
