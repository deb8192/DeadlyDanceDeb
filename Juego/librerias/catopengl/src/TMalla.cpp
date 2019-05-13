#include "TMalla.hpp"

//Uso: Constructor
TMalla::TMalla(int ft)
{
    didentidad = 'M'; //para sabe que funcion hace es informativo
    transparente = 1.0f;
    frames_totales = ft;
    mallas_totales = 0;
    frame_inicial = 0;
    frame_final = ft;
    frame_actual = 0;
    actual_time = 0;
    bucle = true;//se ejecuta en bucle la animacion
    setVelocidadAnimacion(300);
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
    if(render == true)
    {
        shader->Use();
        shader->setFloat("trasparencia", transparente);
    }
    else
    {
        shader2->Use();
    }
    TimeEngine(); //Tiempo del motor
    //calcular el frame
    actual_time = actual_time + getTime();
    float end_time = ((1000.0f/velocidad_animacion) / 1000.0f);
    //cout << actual_time << "  " << end_time << endl;
    if(actual_time >= end_time)
    {
        if(frame_actual < frame_final)
        {
            frame_actual++;
        }
        actual_time = 0;
    }

    //bucle de la animacion
    if(frame_actual >= frame_final && bucle)
    {
        frame_actual = frame_inicial;
    }

    if(matriz_compartida == nullptr)
    {
        glm::mat4 * _matriz_resultado = nullptr;
        std::queue<glm::mat4 *> * cola_compartidaAuxiliar = new std::queue<glm::mat4 *>; //creamos una cola nueva para ir encolando  los elementos que desencolamos de la cola compartida(se aplicaria parecido con una pila)
        glm::mat4 * _matriz_escalado = new glm::mat4(1.0f);
        glm::mat4 * _matriz_traslade = new glm::mat4(1.0f);
        glm::mat4 * _matriz_rotacion = new glm::mat4(1.0f);

        while(cola_compartida->size() > 0)
        {
            glm::mat4 * nodo = cola_compartida->front();
            cola_compartidaAuxiliar->push(nodo);
            //cogemos el primer valor de la pila
            if(_matriz_resultado == nullptr)
            {
                _matriz_resultado = new glm::mat4(1.0f);
                *_matriz_resultado = (*_matriz_resultado)*(*nodo);

                if(cola_compartida->size() == 3)
                {
                    //std::cout << "escalado: "<< "\n" << (*nodo)[0][0] << " " << (*nodo)[1][0] << " " << (*nodo)[2][0]  << " " << (*nodo)[3][0] << "\n" << (*nodo)[0][1] << " " << (*nodo)[1][1] << " " << (*nodo)[2][1]  << " " << (*nodo)[3][1] << "\n" << (*nodo)[0][2] << " " << (*nodo)[1][2] << " " << (*nodo)[2][2]  << " " << (*nodo)[3][2] << "\n" << (*nodo)[0][3] << " " << (*nodo)[1][3] << " " << (*nodo)[2][3]  << " " << (*nodo)[3][3] << std::endl;
                    *_matriz_escalado = *nodo;
                }
            }
            else
            {
                if(cola_compartida->size() == 1)
                {
                    //std::cout << "traslacion: "<< "\n" << (*nodo)[0][0] << " " << (*nodo)[1][0] << " " << (*nodo)[2][0]  << " " << (*nodo)[3][0] << "\n" << (*nodo)[0][1] << " " << (*nodo)[1][1] << " " << (*nodo)[2][1]  << " " << (*nodo)[3][1] << "\n" << (*nodo)[0][2] << " " << (*nodo)[1][2] << " " << (*nodo)[2][2]  << " " << (*nodo)[3][2] << "\n" << (*nodo)[0][3] << " " << (*nodo)[1][3] << " " << (*nodo)[2][3]  << " " << (*nodo)[3][3] << std::endl;
                    *_matriz_traslade = *nodo;
                }

                if(cola_compartida->size() == 2)
                {
                    //std::cout << "rotacion: "<< "\n" << (*nodo)[0][0] << " " << (*nodo)[1][0] << " " << (*nodo)[2][0]  << " " << (*nodo)[3][0] << "\n" << (*nodo)[0][1] << " " << (*nodo)[1][1] << " " << (*nodo)[2][1]  << " " << (*nodo)[3][1] << "\n" << (*nodo)[0][2] << " " << (*nodo)[1][2] << " " << (*nodo)[2][2]  << " " << (*nodo)[3][2] << "\n" << (*nodo)[0][3] << " " << (*nodo)[1][3] << " " << (*nodo)[2][3]  << " " << (*nodo)[3][3] << std::endl;
                    *_matriz_rotacion = *nodo;
                }


                //*_matriz_resultado = (*_matriz_resultado) * (*nodo);
            }

            cola_compartida->pop();
        }

        *_matriz_resultado = (*_matriz_traslade) * (*_matriz_rotacion) * (*_matriz_escalado);

        if(_matriz_resultado != nullptr)
        {
            if(frame_actual <= frame_final)//pasa por los frames de la animacion
            {
                if(render == true)
                {
                    shader->setMat4("model", (*_matriz_resultado));
                    objetos->Draw(shader,frame_actual);
                }
                else
                {
                    shader2->setMat4("model", (*_matriz_resultado));
                    objetos->Draw(shader2,frame_actual);
                }
            }
        }

        delete cola_compartida;//borramos la cola anterior porque esta vacia
        delete _matriz_escalado;
        delete _matriz_traslade;
        delete _matriz_rotacion;
        delete _matriz_resultado;
        cola_compartida = cola_compartidaAuxiliar;//ponemos la nueva cola que tiene los elementos situados como la anterior

    }
    else
    {
        if(matriz_compartida != nullptr)
        {
            if(frame_actual < frame_final)//pasa por los frames de la animacion
            {
                if(render == true)
                {
                    shader->setMat4("model", (*matriz_compartida));
                    objetos->Draw(shader,frame_actual);
                }
                else
                {
                    shader2->setMat4("model", (*matriz_compartida));
                    objetos->Draw(shader2,frame_actual);
                }
            }
        }
    }
    if(render == false)render = true; //para que en el siguiente draw sea render
}

void TMalla::endDraw()
{

}

void TMalla::BucleAnimacion(unsigned short ini,unsigned short fin)
{
        if(ini >= 0 && ini <= frames_totales && fin >= 0 && fin <= frames_totales && ini <= fin)
        {
            frame_inicial = ini;
            frame_final = fin;
            frame_actual = ini;
        }
        else
        {
            cout << "ERROR: Los frames del bucle tienen que estar entre 0 y " << frames_totales << endl;
        }
}

void TMalla::setVelocidadAnimacion(float v)
{
    velocidad_animacion = v;
}

unsigned short TMalla::getFrameInicio()
{
    return frame_inicial;
}

unsigned short TMalla::getFrameFinal()
{
    return frame_final;
}

unsigned short TMalla::getFrameActual()
{
    return frame_actual;
}

void TMalla::setRecursoObjeto(RMalla * objeto)
{
    objetos = objeto;
}

void TMalla::setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    objetos->SetColor(r,g,b,a);
}

void TMalla::setTexture(const char * _ruta)
{
    objetos->SetTexture(_ruta);
}

void TMalla::EstaEnBucleAnimacion(bool bu)
{
    bucle = bu;
}

void TMalla::setTransparencia(float t)
{
    if(t != transparente)
    {
        if(t > 1.0f)t = 1.0f;
        if(t < 0.0f)t = 0.0f;
        transparente = t;
    }
}

void TMalla::setRender(bool r)
{
    render = r;
}
