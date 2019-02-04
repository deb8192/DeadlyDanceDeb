#ifndef TEntidad_HPP
#define TEntidad_HPP

class TEntidad
{
    public:

        TEntidad(){}

        virtual void beginDraw()=0;

        virtual void endDraw()=0;


};

#endif