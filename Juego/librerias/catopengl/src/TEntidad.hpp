#ifndef TEntidad_HPP
#define TEntidad_HPP

#include "iostream"
#include <stack>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <queue>
#include "Shader.hpp"
#include "RMalla.hpp"

class TEntidad
{
    public:

        virtual ~TEntidad();

        virtual void beginDraw()=0;

        virtual void endDraw()=0;

        //para TTransform
        virtual void escalar(float,float,float);
        virtual void rotar(float,float,float);
        virtual void trasladar(float,float,float);
        //fin TTransform

        //para sincornizar recursos
        virtual void setRecursoObjeto(RMalla *);

        void NoEjecutar();

        void Ejecutar();

        bool GetEjecutar();

        void SetShader(Shader *);
        void SetShader2(Shader *);
        void SetShader3(Shader *);
        Shader * GetShader();
        Shader * GetShader2();
        Shader * GetShader3();
        void RemoveShader();
        void RemoveShader2();
        void RemoveShader3();
        void TimeEngine();

        float getTime();

        static glm::mat4 * matriz_compartida;//matriz que tiene la ultima operacion

        void EsGui();//lo convierte en un elemento identificado como gui

        void NoEsGui();//si es gui deja de serlo

        bool GetGui();//devuelve true si es gui o false si no lo es

        void EsCamara();//lo convierte en camara

        bool GetCamara();//devuelva si es una camara(true) si no false

    protected:

        static std::stack<glm::mat4 *> * pila_compartida;//pila para recorrido normal
        static std::queue<glm::mat4 *> * cola_compartida;//cola para recorrida hacia arriba(padre)
        char didentidad;//nos servira para saber que tipo de funcion hace(solo es informativo)
        bool ejecucion = true;//sirve para saber si se debe ejecutar por defecto es true a no ser que se cambie
        bool gui = false;//sirve para saber si es un gui
        bool camara = false;//sirve para saber si es una camara
        Shader * shader = nullptr;//puntero a shader
        Shader * shader2 = nullptr;//puntero a shader
        Shader * shader3 = nullptr;//puntero a shader
        float deltaTime = 0.0f;	// Tiempo entre el actual frame y el ultimo
        float lastFrame = 0.0f; // Tiempo del ultimo frame
};

#endif
