#ifndef TEntidad_HPP
#define TEntidad_HPP

#include "iostream"
#include <stack>
#include <glm.hpp>

class TEntidad
{
    public:

        virtual void beginDraw()=0;

        virtual void endDraw()=0;

        virtual void remove()=0;

        void NoEjecutar();

        void Ejecutar();

        bool GetEjecutar();

   
    protected:
        static glm::mat4 * matriz_compartida;
        static std::stack<glm::mat4 *> * pila_compartida;
        char didentidad;//nos servira para saber que tipo de funcion hace(solo es informativo)
        bool ejecucion = true;//sirve para saber si se debe ejecutar por defecto es true a no ser que se cambie

};

#endif