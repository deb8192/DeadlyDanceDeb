#ifndef TLuz_HPP
#define TLuz_HPP

#include "TEntidad.hpp"

class TLuz : public TEntidad
{
    private:

        int numberoflight;
        float * intensidad;
        unsigned int tipo_luz;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        glm::vec3 direction;
        float linear, quadratic;
        float brillos_shader;
        int tipo_anim = 0;
        int animaescala = 0;
        bool cambiaranima = false;
        glm::vec3 posicion;

    public:

        //constructor y destructor
        TLuz(int,int);
        ~TLuz();

        //gestion atributos
        void setIntensidad(float *);
        float getIntensidad();
        void setAmbient(float,float,float);
        void setDiffuse(float,float,float);
        void setSpecular(float,float,float);
        void setNumberoflight(int);
        void setDirection(float,float,float);
        void setLightRange(float);
        void setBrillos(float b);
        float transformToRGB(float c);
        glm::vec3 getPosicion();

        //sobrecarga Tentidad
        void beginDraw();
        void endDraw();
};

#endif
