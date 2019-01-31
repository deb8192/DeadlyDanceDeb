#ifndef TTransform_HPP
#define TTansform_HPP

#include "TEntidad.hpp"

class TTransform : public TEntidad
{
    private:
        float * matriz [4][4];
    
    public:
        //constructor y destructor
        TTransform();
        ~TTransform();

        //gestion matriz
        void identidad();
        void cargar(float *);
        void trasponer();
        void invertir();
        void multiplicarVector(float *);//se le pasa un array de una dimension de longitud 4
        void multiplicarMatriz(float *);//se le pasa una matriz de 4x4

        //operaciones de transformacion
        void trasladar(float,float,float);
        void rotar(float,float,float,float);
        void escalar(float,float,float);

        //sobrecarga de metodos virtuales TEntidad
        void beginDraw();
        void endDraw();
        
};

#endif