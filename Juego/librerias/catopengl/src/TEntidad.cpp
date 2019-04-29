#include "TEntidad.hpp"

glm::mat4* TEntidad::matriz_compartida = new glm::mat4;
std::stack<glm::mat4 *> * TEntidad::pila_compartida = new std::stack<glm::mat4 *>;
std::queue<glm::mat4 *> * TEntidad::cola_compartida = new std::queue<glm::mat4 *>;

TEntidad::~TEntidad()
{
    shader = nullptr;
}

//Uso: bloquea la entidad para que no pueda ser ejecutado por el draw
//Entradas: ninguna
//Salidas: ninguna
void TEntidad::NoEjecutar()
{
    ejecucion  = false;
}

//Uso: desbloquea le entidad para que pueda ser ejecutada
//Entradas: ninguna
//Salidas: ninguna
void TEntidad::Ejecutar()
{
    ejecucion  = true;
}

bool TEntidad::GetEjecutar()
{
    return ejecucion;
}

//Uso: devuelve el puntero del shader que ejecuta esta entidad
//Entradas: ninguna
//Salidas: puntero Shader
Shader * TEntidad::GetShader()
{
    return shader;
}

Shader * TEntidad::GetShader2()
{
    return shader2;
}

Shader * TEntidad::GetShader3()
{
    return shader3;
}

Shader * TEntidad::GetShader4()
{
    return shader4;
}


//Uso: asigna el shader a esta entidad, para que se llame en el draw
//Entradas: Shader (programa que contiene el vextex y fragment)
//Salidas: ninguna
void TEntidad::SetShader(Shader * sha)
{
    shader = sha;
}

void TEntidad::SetShader2(Shader * sha)
{
    shader2 = sha;
}

void TEntidad::SetShader3(Shader * sha)
{
    shader3 = sha;
}

void TEntidad::SetShader4(Shader * sha)
{
    shader4 = sha;
}

//Uso: Pone el shader local nullptr
//Entradas: ninguna
//Salidas: ninguna
void TEntidad::RemoveShader()
{
    shader = nullptr;
}

void TEntidad::RemoveShader2()
{
    shader2 = nullptr;
}

void TEntidad::RemoveShader3()
{
    shader3 = nullptr;
}

void TEntidad::RemoveShader4()
{
    shader4 = nullptr;
}

void TEntidad::escalar(float,float,float)
{

}

void TEntidad::rotar(float,float,float)
{

}

void TEntidad::trasladar(float,float,float)
{

}

void TEntidad::setRecursoObjeto(RMalla * valor)
{

}

void TEntidad::TimeEngine()
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

float TEntidad::getTime()
{
    return deltaTime;
}

void TEntidad::EsGui()
{
    gui = true;
}

void TEntidad::NoEsGui()
{
    gui = false;
}

bool TEntidad::GetGui()
{
    return gui;
}

void TEntidad::EsCamara()
{
    camara = true;
}

bool TEntidad::GetCamara()
{
    return camara;
}
