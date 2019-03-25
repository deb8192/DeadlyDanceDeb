#ifndef TTransform_HPP
#define TTansform_HPP


#include <gtc/matrix_transform.hpp>
#include "TEntidad.hpp"

class TTransform : public TEntidad
{
    private:
        glm::mat4 * matriz;

    public:
        //constructor y destructor
        TTransform();
        ~TTransform();

        //gestion matriz
        void identidad();
        void cargar(glm::mat4 * newmat);
        void trasponer();
        void invertir();

        //operaciones de transformacion
        void trasladar(float x,float y,float z);//Trasladar en el espacio 3D (x,y,z)
        void rotar(float g,float x,float y,float z);//Rotar tantos grados, en (X-axis,y-axis,z-axis entre 0 y 1.0)
        void escalar(float x,float y,float z);//Escalar en (x,y,z entre 0 y 1.0)
        float * GetPosicion();//devuelve un array de 3 posiciones 
        
        //sobrecarga de metodos virtuales TEntidad
        void beginDraw();
        void endDraw();

};

#endif
