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

    public:

        //constructor y destructor
        TLuz(int);
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

        //sobrecarga Tentidad
        void beginDraw();
        void endDraw();
};

#endif
