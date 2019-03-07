#include "TMalla.hpp"

//Uso: Constructor
TMalla::TMalla(int ft)
{
    didentidad = 'M'; //para sabe que funcion hace es informativo
    frames_totales = 0;
    mallas_totales = 0;
    frame_inicial = 0;
    frame_final = ft;
    frame_actual = 0;
    velocidad_animacion = 30;
}

//Uso: destructor
TMalla::~TMalla()
{

}

//Uso: Pone el shader local nullptr
//Entradas: ninguna
//Salidas: ninguna
void TMalla::cargarMalla(unsigned short,unsigned short)
{
    //aqui llamamos a objetos->ObtenerFrame(1); y se carga en memoria para pintarlo
}

// sobrecarga metodos TEntidad
void TMalla::beginDraw()
{
    TimeEngine(); //Tiempo del motor
    //calcular el frame
    frame_actual = frame_actual + getTime() * velocidad_animacion;
    //bucle de la animacion
    if(frame_actual >= frame_final)frame_actual = frame_inicial;

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
                /*if(cola_compartida->size() == 1)
                {
                    std::cout << (*nodo)[3][0] << " " << (*nodo)[3][1] << " " << (*nodo)[3][2] << std::endl;
                }*/

                *_matriz_resultado = (*_matriz_resultado) * (*nodo);
            }

            cola_compartida->pop();
        }

        if(_matriz_resultado != nullptr)
        {
            if(frame_actual < frame_final)//pasa por los frames de la animacion
            {
                shader->setMat4("model", (*_matriz_resultado));
                objetos->Draw(shader,frame_actual);
            }
        }
    }
    else
    {
        if(matriz_compartida != nullptr)
        {
            if(frame_actual < frame_final)//pasa por los frames de la animacion
            {
                shader->setMat4("model", (*matriz_compartida));
                objetos->Draw(shader,frame_actual);
            }
        }
    }

}

void TMalla::endDraw()
{

}

void TMalla::BucleAnimacion(unsigned short,unsigned short)
{

}

void TMalla::SiguienteAnimacion()
{

}

void TMalla::DefinirAnimaciones()
{

}

unsigned short TMalla::getFrameInicio()
{
    return 0;
}

unsigned short TMalla::getFrameFinal()
{
    return 0;
}

unsigned short TMalla::getFrameActual()
{
    return 0;
}

bool TMalla::setTiempoAnimacion(unsigned short)
{
    return false;
}

void TMalla::setRecursoObjeto(RMalla * objeto)
{
    objetos = objeto;
}
