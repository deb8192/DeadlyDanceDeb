#ifndef TTransform_HPP
#define TTansform_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "TEntidad.hpp"

class TTransform : public TEntidad
{
    private:
        glm::mat4 matriz;

    public:
        //constructor y destructor
        TTransform();
        ~TTransform();
        void remove();

        //gestion matriz
        void identidad();
        void cargar(glm::mat4 newmat);
        void trasponer();
        void invertir();
        void multiplicarVector(glm::vec4 newvec);//se le pasa un array de una dimension de longitud 4
        void multiplicarMatriz(glm::mat4 newmat);//se le pasa una matriz de 4x4

        //operaciones de transformacion
        void trasladar(float x,float y,float z);     //Trasladar en el espacio 3D (x,y,z)
        void rotar(float g,float x,float y,float z); //Rotar tantos grados, en (X-axis,y-axis,z-axis entre 0 y 1.0)
        void escalar(float x,float y,float z);       //Escalar en (x,y,z entre 0 y 1.0)

        //sobrecarga de metodos virtuales TEntidad
        void beginDraw();
        void endDraw();

};

#endif
