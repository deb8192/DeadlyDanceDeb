#ifndef TEntidad_HPP
#define TEntidad_HPP

#include "iostream"
#include <stack>
#include <glm.hpp>
#include <queue>
#include "Shader.hpp"
#include "RMalla.hpp"

class TEntidad
{
    public:

        virtual void beginDraw()=0;

        virtual void endDraw()=0;

        //para TTransform
        virtual void escalar(float,float,float);
        virtual void rotar(float,float,float,float);
        virtual void trasladar(float,float,float);
        //fin TTransform

        //para sincornizar recursos
        virtual void setRecursoObjeto(RMalla *);

        void NoEjecutar();

        void Ejecutar();

        bool GetEjecutar();

        void SetShader(Shader *);

        Shader * GetShader();

        void RemoveShader();

        void TimeEngine();

        float getTime();
        static glm::mat4 * matriz_compartida;//matriz que tiene la ultima operacion

    protected:

        static std::stack<glm::mat4 *> * pila_compartida;//pila para recorrido normal
        static std::queue<glm::mat4 *> * cola_compartida;//cola para recorrida hacia arriba(padre)
        char didentidad;//nos servira para saber que tipo de funcion hace(solo es informativo)
        bool ejecucion = true;//sirve para saber si se debe ejecutar por defecto es true a no ser que se cambie
        Shader * shader = nullptr;//puntero a shader
        float deltaTime = 0.0f;	// Tiempo entre el actual frame y el ultimo
        float lastFrame = 0.0f; // Tiempo del ultimo frame
};

#endif
