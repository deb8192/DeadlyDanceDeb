#ifndef TEntidad_HPP
#define TEntidad_HPP

#include "iostream"

class TEntidad
{
    public:

        virtual void beginDraw()=0;

        virtual void endDraw()=0;

        virtual void remove()=0;
   
    protected:

        char didentidad;//nos servira para saber que tipo de funcion hace(solo es informativo)

};

#endif