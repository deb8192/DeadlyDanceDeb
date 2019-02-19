#ifndef TEntidad_HPP
#define TEntidad_HPP

#include "iostream"
#include <stack>
#include <glm.hpp>
#include <queue>
#include "Shader.hpp"

class TEntidad
{
    public:

        virtual void beginDraw()=0;

        virtual void endDraw()=0;

        virtual void remove()=0;

        void NoEjecutar();

        void Ejecutar();

        bool GetEjecutar();

        void SetShader(Shader *);

        Shader * GetShader();

        void RemoveShader();

    protected:

        static glm::mat4 * matriz_compartida;//matriz que tiene la ultima operacion
        static std::stack<glm::mat4 *> * pila_compartida;//pila para recorrido normal
        static std::queue<glm::mat4 *> * cola_compartida;//cola para recorrida hacia arriba(padre)
        char didentidad;//nos servira para saber que tipo de funcion hace(solo es informativo)
        bool ejecucion = true;//sirve para saber si se debe ejecutar por defecto es true a no ser que se cambie
        Shader * shader = nullptr;//puntero a shader

};

#endif