#ifndef TLuz_HPP
#define TLuz_HPP

#include "TEntidad.hpp"

class TLuz : public TEntidad
{
    private:
    
        float * intensidad;

    public:

        //constructor y destructor
        TLuz();
        ~TLuz();

        //gestion atributos
        void setIntensidad(float *);
        float getIntensidad();
        
        //sobrecarga Tentidad
        void beginDraw();
        void endDraw();
};

#endif