#ifndef TPlano_HPP
#define TPlano_HPP

#include "TEntidad.hpp"

class TPlano : public TEntidad
{
    private:

        bool CargarTextura(const char * _ruta);
        void CargarMalla(unsigned int, unsigned int, float, float);
        void UdateMesh();

        GLuint winwidth, winheight;
        // const char * _rutafile;
        // unsigned int px, py;
        // float scaleimage;
        bool cambios = false;
        float pixx, pixy;
        float escaladox, escaladoy;
        int width, height, nrComponents;
        unsigned int textureID;
        unsigned int VAO, VBO, EBO; //Datos de render
        int id;//id del boton

    public:
        // Constructor y destructor
        TPlano(const char *, unsigned int, unsigned int, float, Shader *, GLuint, GLuint);
        ~TPlano();

        void setSize(float,float); //ancho largo
        void setPosition(float,float); //x,y
        void setScale(float,float); //escalado
        bool botonPulsado(double *); //pulsar boton

        // sobrecarga metodos TEntidad
        void beginDraw();
        void endDraw();

        //seccion para botones
        bool Comprobar();
        void CambiarId(int);
        int getID();
};

#endif
