#ifndef TCamara_HPP
#define TCamara_HPP

#include "TEntidad.hpp"

class TCamara : public TEntidad
{
    private:
        bool esPerspectiva;
        float cercano,lejano;

    public:
        //constructor y destructor
        TCamara();
        ~TCamara();
        void remove();
        
        //gestion de propiedades
        void setPerspectiva();
        void setParalela();

        //sobrecarga Tentidad
        void beginDraw();
        void endDraw();

};

#endif