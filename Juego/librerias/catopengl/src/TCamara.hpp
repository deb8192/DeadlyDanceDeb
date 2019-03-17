#ifndef TCamara_HPP
#define TCamara_HPP

#include "TEntidad.hpp"

class TCamara : public TEntidad
{
    private:
        bool esPerspectiva;//si no lo es se aplica octo
        float cercano,lejano;//zFar y zNear (esto ayuda a limitar los planos de clipping) todo lo que este entre posicion+zFar y posicion zNear se dibujara
        float height,width;//altura y ancho
        glm::vec3 cameraUp; //indica hacia donde miran las normales (regla de la mano derecha)
        glm::vec3 cameraTarget; //donde esta mirando
        glm::mat4 projection; //matriz de como se ve la camara

    public:
        //constructor y destructor
        TCamara(GLuint, GLuint);
        ~TCamara();

        //gestion de propiedades
        void setPerspectiva();
        void setParalela();

        //sobrecarga Tentidad
        void beginDraw();
        void endDraw();

        //Funciones propias
        void setCercano(float);//define el plano de recorte cercano
        void setLejano(float);//define el plano de recorte lejano
        void setTarget(float,float,float);//indica donde esta mirando la camara
        void setUp(float,float,float);//0(hacia dentro)-1(hacia fuera) donde miran las normales por defecto 0,1,0 = x,y,z
        void ActivarPerspectiva();//por defecto activo (activa la perspectica)
        void DesactivarPerspectiva();//desactiva la perpestiva, habilita ortho
        void setPantalla(float,float);//cambio resolucion pantalla
};

#endif
